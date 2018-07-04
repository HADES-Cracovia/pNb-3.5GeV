//-----------------------------------------------------------------------------
#include "htimecut.h"
#include "hhypplayer.h"
#include "hcommondef.h"
#include <TError.h>
#include <TMath.h>
#include <string>


// ****************************************************************************
ClassImp(HTimeCut)

using namespace std;
using namespace CommonDefinitions;


//-----------------------------------------------------------------------------
Bool_t HTimeCut::select(HReconstructor& rec)
{
   HHypPlayer& dataRec = dynamic_cast<HHypPlayer&>(rec);
   HPidPool *pPool = dataRec.getPool();
   //cout << "PID POOL : " << pPool->size() << endl;
   HHypCandidate *pCand = 0;
   if ( getName() == string("all") )
   {
      int i = 0;
	  while (  ( pCand = pPool->getHyp( i ) ) != 0 )
	  {
	     calcTofMom( pCand );
             calcTof( pCand );
	     ++i;
	  }
   }
   else
   {
      int i = 0;
	  while ( ( pCand = pPool->getHyp( getName(), i ) ) != 0 )
	  {
	     calcTofMom( pCand );
	     calcTof( pCand );
	     ++i;
	  }
   }

return kTRUE;
}


//-----------------------------------------------------------------------------
void HTimeCut::calcTofMom(HHypCandidate *pHyp)
{
   for (int i=0; i<pHyp->getSize(); ++i)
   {
      calcTofMom( pHyp->getPart(i) );
   }
}


//-----------------------------------------------------------------------------
void HTimeCut::calcTofMom(HParticle *pPart)
{
  /* 
   id = pPart->get("id");
   mom = pPart->get("p");
   theta = pPart->get("theta");
   phi = pPart->get("phi");
   beta = pPart->get("beta");
   q = pPart->get("q");
   vect.SetXYZ(mom*sin(theta*D2R)*cos(phi*D2R),
               mom*sin(theta*D2R)*sin(phi*D2R),
               mom*cos(theta*D2R));
   //tof = pPart->get("tof_exp");
   //track_length = beta * C * tof; // time in ns !!! see below
   //////////track_length = pPart->get("tracklength");
   //////////pPart->set("track_length", track_length );
   if (q>0)
   {
       if (id == 2.) part.SetVectM(vect, 0.51099906);
       else if (id == 8.) part.SetVectM(vect, 139.56995);
       else if (id == 14.) part.SetVectM(vect, 938.27231);
       else if (id == 45.) part.SetVectM(vect, 1875.613);
   }
   else
   {
       if (id == 3.) part.SetVectM(vect, 0.51099906);
       else if (id == 9.) part.SetVectM(vect, 139.56995);
   }
   pPart->set("tof_mom", track_length / (part.Beta()*C) );
   */
   pPart->set("tof_mom", pPart->get("sim_p"));
}



//-----------------------------------------------------------------------------
void HTimeCut::calcTof(HHypCandidate *pHyp)
{
   int pid = 0;
   size = pHyp->getSize();
   delta_chi2.clear();
   sort_idx.clear();
   cand.clear();
   best_cand.clear();
   delta_chi2.resize( size );
   sort_idx.resize( size );
   for (int i=0; i<size; ++i)
   {
      delta_chi2[i] = 0.;
      sort_idx[i] = 0.;
   }
   tof_new_arr.resize( size );
   for (int i=0; i<size; ++i)
   {
       tof_new_arr[i].clear();
       tof_new_arr[i].resize( size );
       for (int j=0; j<size; ++j)
       {
          tof_new_arr[i][j] = 0.;
       }
   }

   for (int i=0; i<size; ++i)
   {
      //  for i particle
      p1 = pHyp->getPart(i);
      sort_index = ( p1->get("system") == 1 ) ? 0 : ( p1->get("system") == 0 ) ? 10 : 100;
      if ( p1->get("tofino_mult") > 1 ) sort_index = 100;

      /************************ special case: do not use pi+ for time calibration **********************/
      //if ( p1->getId() == 8 ) sort_index = 100;
      /************************ special case: do not use d (deuteron) for time calibration *************/
      //if ( p1->getId() == 45 ) sort_index = 100;
      /*************************************************************************************************/

      pid = (int)p1->get("id");
      sort_index += ( pid == 3 ) ? 1 : ( pid == 2 ) ? 2 : ( pid == 9 ) ? 3 : ( pid == 14 ) ? 4 : ( pid==8 ) ? 5 : ( pid == 45 ) ? 6 : 9;
	  /************** FORCE PARTICLE ID ************************/
	   if (pid == 3) sort_index = 0;
	   if (pid == 14) sort_index = 1;
	  /****************************************************/

      sort_idx[i] = sort_index;

      for (int j=0; j<size; ++j)
      {
         // current reference particle is "i"
         if (j != i)
         {
            p2 = pHyp->getPart(j);
            delta_tof = ( p1->get("tof_exp") - p2->get("tof_exp") ) / 2.;
            tof_mean  = ( p1->get("tof_mom") + p2->get("tof_mom") ) / 2.;
            tof_new_arr[i][j] = tof_mean - delta_tof;
            tof_new_arr[i][i] += (tof_mean + delta_tof)/((double)size-1.) ;
         }

      }
   }
   for (int i=0; i<size; ++i)
   {
      // now delta chi2 for i particle
      for (int j=0; j<size; ++j)
      {
         p2 = pHyp->getPart(j);
         delta_chi2[i] += pow( tof_new_arr[i][j] - p2->get("tof_mom"), 2 ) / pow( p2->get("resolution"), 2 );
      }

   }
   // now time to choose best delta / sorting some indices...
   for (int i=0; i<size; ++i)
   {
      if ( best_cand.find( (int)sort_idx[i] ) != best_cand.end() )
      {
         best_cand[ (int)sort_idx[i] ].insert( pair<double, int>( delta_chi2[i], i ) );
      }
      else
      {
         cand.clear();
         cand.insert( pair<double, int>( delta_chi2[i], i ) );
         best_cand.insert( pair<int, multimap<double, int> >( (int)sort_idx[i], cand ) );
      }
   }
   best_chi2 = -1;
   best_index = -1;
   best_cand_iter = best_cand.begin();
   if( best_cand_iter != best_cand.end() )
   {
      cand_iter = best_cand_iter->second.begin();
      if ( cand_iter != best_cand_iter->second.end() )
      {
         best_chi2 = cand_iter->first;
         best_index = cand_iter->second;
      }
   }

   // here you have to check if the track in the combination is white and if yes, set low chi2
   bool kCleanTracks = true;
   double chi2tmp = 0.0;
   //if ( size == 0 ) kCleanTracks = false;
   //cout << " - - -- - - - " <<  endl;
   for (int j=0; j<size; ++j) {
       p1 = pHyp->getPart(j);
       chi2tmp += p1->get("rkchi2")*p1->get("rkchi2");
       //cout << " id p theta phi : " << p1->getId() << ","<<p1->get("p")<<","<<p1->get("theta")<<","<<p1->get("phi")<<" part chi2 " << p1->get("rkchi2") << endl;
       // lepton
       // if ( (p1->get("sim_id")==3) && (p1->get("sim_parentid")==0) && (p1->get("sim_iscommon")>=76))
       // hadron
       //if ( (p1->get("sim_id")==3) && (p1->get("sim_parentid")==0) && (p1->get("sim_iscommon")>=74))
       //if ( ! ((p1->get("sim_parentid")==0) && (p1->get("sim_iscommon")>=74)) ) kCleanTracks = false;
       //cout << "id " << p1->get("sim_id") << " parentid " << p1->get("sim_parentid") << " iscommon " << p1->get("sim_iscommon") << endl;
       //cout << "id " << p1->getId() << endl;
       // - - - - - - if ( ! (p1->get("sim_parentid")==-1)  ) kCleanTracks = false; // CONVENTION HAS CHANGED !!!
   }
   chi2tmp = sqrt( chi2tmp );
   //cout << " full chi2 " << chi2tmp << endl;

   //cout << " wynik: " << kCleanTracks << endl << " = = = = == " << endl;
   if ( kCleanTracks && chi2tmp > 0.0 ) {
      pHyp->setChi2( chi2tmp );
   } else {
      pHyp->setChi2( 1000000 );
   }
   // ----------------------------------------------------------------------------------------



   for (int i=0; i<size; ++i)
   {
      //  for i particle
      p1 = pHyp->getPart(i);
      // p1->set("tof_new", tof_new_arr[best_index][i]);
      //p1->set("tof_new", p1->get("tof_exp"));
      // p1->set("beta_new", p1->get("track_length") / (C * tof_new_arr[best_index][i]) );
      //p1->set("beta_new", p1->get("track_length") / (C * p1->get("tof_exp") ) );
//double tof_exp = (p1->get("tracklength")/1000.)/(p1->get("beta")*C)*1e+9 -4.279; // LH2 time shift
      double tof_exp = (p1->get("tracklength")/1000.)/(p1->get("beta")*C)*1e+9; 
      p1->set("tof_new", tof_exp);
      //p1->set("beta_new", (p1->get("tracklength")/1000.)*1e+9 / (C * tof_exp) );
      //cout << "TOF exp: " << tof_exp << " beta new: " << (p1->get("tracklength")/1000.)*1e+9 / (C * tof_exp) << endl;
      p1->set("beta_new", p1->get("beta"));
      //cout << "BETA: " << p1->get("beta") << endl;
   }

}


