#include "hades.h"
#include "hevent.h"
#include "heventheader.h"
#include "hpidpool.h"
//#include "hpidpoolhandle.h"
#include <algorithm>
#include <iostream>


// ****************************************************************************
ClassImp(HPidPool)

//-----------------------------------------------------------------------------
HPidPool::HPidPool(HOutputFile *ptr) : HPool(ptr), HHypDataPool() 
{
   reset();
}

//-----------------------------------------------------------------------------
HPidPool::~HPidPool() 
{ 
   reset();  
}

//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, EParticle p1)
{
   if ( HPool::add( name, p1 ) )
   {
      hypPid.insert( pair<std::string, std::string>( name, oldname ) );
      return true;
   }
   return false;
}

#if MAX_PARTICLES_IN_COMB > 1
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, EParticle p1, EParticle p2)
{
   if ( HPool::add( name, p1, p2 ) )
   {
      hypPid.insert( pair<std::string, std::string>( name, oldname ) );
      return true;
   }
   return false;
}
#endif

#if MAX_PARTICLES_IN_COMB > 2
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, EParticle p1, EParticle p2, EParticle p3)
{
   if ( HPool::add( name, p1, p2, p3 ) )
   {
	  hypPid.insert( pair<std::string, std::string>( name, oldname ) );
	  return true;
   }
   return false;
}
#endif

#if MAX_PARTICLES_IN_COMB > 3
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, EParticle p1, EParticle p2, EParticle p3, EParticle p4)
{
   if ( HPool::add( name, p1, p2, p3, p4 ) )
   {
	  hypPid.insert( pair<std::string, std::string>( name, oldname ) );
	  return true;
   }
   return false;
}
#endif

//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, const char* p1)
{
   return add( oldname, name, convertId(p1) );
}

#if MAX_PARTICLES_IN_COMB > 1
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, const char* p1, const char* p2)
{
   return add( oldname, name, convertId(p1), convertId(p2) );
}
#endif

#if MAX_PARTICLES_IN_COMB > 2
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, const char* p1, const char* p2, const char* p3)
{
   return add( oldname, name, convertId(p1), convertId(p2), convertId(p3) );
}
#endif

#if MAX_PARTICLES_IN_COMB > 3
//-----------------------------------------------------------------------------
bool HPidPool::add(const char* oldname, const char* name, const char* p1, const char* p2, const char* p3, const char* p4)
{
   return add( oldname, name, convertId(p1), convertId(p2), convertId(p3), convertId(p4) );
}
#endif
   
//-----------------------------------------------------------------------------
void HPidPool::reset()
{
   hypNum.clear();

   std::for_each( hypCand.begin(), hypCand.end(), DelPidCand() ); 
   hypCand.clear();
}


//-----------------------------------------------------------------------------
void HPidPool::loop(HHypPool& ref)
{
   objIt = objectList.begin();
   while ( objIt != objectList.end() )
   {
      // this loop is over all patterns
	  for (int i=0; i<ref.getNum( hypPid.find( (*objIt)->getName() )->second ); ++i)
	  {
	     HHypCandidate *tmpPtr = ref.getHyp( hypPid.find( (*objIt)->getName() )->second, i );
		 // here we have hyp candidate and we need to create new hyp with new "particle id candidates"
         HHypCandidate *newCand = new HHypCandidate( *objIt );
		 for (int j=0; j<tmpPtr->getSize(); ++j)
		 {
	   	    tmpPtr->getPart( j )->setId( (*objIt)->get( j ) );
	   	    *newCand += tmpPtr->getPart( j );
		 }
		 // here we have a new copy of hyp candidate with new pid
              addHypCand( (*objIt)->getName(), newCand );

	  }

      ++objIt;
   }
}


//-----------------------------------------------------------------------------
void HPidPool::fill() 
{

   HParticle *ptrP = 0;
   HHypCandidate *ptrH = 0;
   HHypCandidate *ptrHBest = 0;
   std::string key;
   double chi2;
   //EParticle eid;
   
   eventData.update();

   if (ptrFile != 0)
   {
       // internal loop over all hyp patterns
       for (objIt = objectList.begin(); objIt != objectList.end(); ++objIt)
       {
       	  // loop over all hyps stored

          chi2 = 10000000.;
          ptrHBest = 0;
          hypIter = hypCand.begin();
          while(hypIter != hypCand.end())
          {
       	     if ( (*objIt)->getName() == hypIter->first )
       	     {
       	        ptrH = hypIter->second;
                // below we select the lowest chi2 
                if (ptrH->isActive() && ptrH->getChi2() < chi2)
                // this is MODIFICATION selecting only NEGATIVE chi2 set in htimecut.cc
                //if (ptrH->isActive() && ptrH->getChi2() < 0)
                {
                   chi2 = ptrH->getChi2();
                   ptrHBest = ptrH;
                }
             }
       	     ++hypIter;
          }

          // for the lowest chi2 I change the sign to negative in order to recognize it in the next
          // loop and utilize the same variable
          if (ptrHBest != 0)
          {
             ptrHBest->setChi2( -1.* ptrHBest->getChi2() );
          }


          hypIter = hypCand.begin();
          while(hypIter != hypCand.end())
          {
       	     if ( (*objIt)->getName() == hypIter->first )
       	     {
       	        ptrH = hypIter->second;
				numId.clear();
                for (int i=0; i<ptrH->getSize(); ++i)
                {
                   ++numId[ ptrH->getPart(i)->getEId() ];
                }

       	        for (int i=0; i<ptrH->getSize(); ++i)
                {
                   ptrP = ptrH->getPart(i);
                   key  = convertId( convertId( ptrP->getId() ) );
                   if ( ptrH->getNum( ptrP->getEId() ) > 1 )
                   {
                      int k = numId[ ptrH->getPart(i)->getEId() ]--;
                      (*objIt)->setPrefix(key+static_cast<char>(k+48)+string("_"));
                   }
                   else
                   {
                      (*objIt)->setPrefix(key+"_");
                   }
                   (*objIt)->setSuffix();

                   for (NtuplePairIter it = ptrP->begin(); it != ptrP->end(); ++it)
                   {
                      (*objIt)->set( it->first, it->second );
                   }
                   for (NtuplePairIter it = ptrP->getCandidate()->begin(); it != ptrP->getCandidate()->end(); ++it)
                   {
                      if (ptrP->isName(it->first) == false)
                      {
                         (*objIt)->set( it->first, it->second );
                      }
                   }

                } 
               
               (*objIt)->setPrefix();
			   (*objIt)->setSuffix();

               //if (ptrH->isActive() == true) // best chi2
               if (ptrH->getChi2() < 0 && ptrH->isActive() == true) // best chi2
               {
			      eventData.set( "isBest", 1 );
               }
               //else if (ptrH->isActive() == true) // not best chi2 but pid ok
               //{
			      //eventData.set( "isBest", 0 );
               //}
	       else
	       {
	                      // all combinations not fulfilling pid cuts
			      eventData.set( "isBest", -1 );
	       }

			   for (NtuplePairIter it = eventData.begin(); it != eventData.end(); ++it)
			   {
			      (*objIt)->set( it->first, it->second );
			   }
               
               (*objIt)->fill(); 
       	     }
       	     ++hypIter;
          }
       } // end of patterns
   } // if ptrFile   
}


