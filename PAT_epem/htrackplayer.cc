#include "htrackplayer.h"
#include "walldef.h"
#include "hstartdef.h"
#include "hgeantkine.h"
#include "heditor.h"

ClassImp(HTrackPlayer)

extern int wallflag;
extern int startflag;

//-----------------------------------------------------------------
  HTrackPlayer::HTrackPlayer(HParticlePool& ref) : 
      HReconstructor( const_cast<Text_t*>("trackplayer"), const_cast<Text_t*>("trackplayer") ), 
	  partPool(ref)
  {
  }

//-----------------------------------------------------------------
  HTrackPlayer::~HTrackPlayer() 
  {
  }



//-----------------------------------------------------------------
Bool_t HTrackPlayer::init()
{
	m_pContItPart = 0;         // Iterator
	m_pContCatPart = 0;        // Category
	m_pFWallCat = 0;
	m_pFWallCatIter = 0;
	m_pGeantStartCat = 0;
	m_pGeantStartCatIter = 0;
    m_pStartCat = 0;
    m_pStartCatIter = 0;
    m_pPTrackerCat = 0;
    m_pPTrackerCatIter = 0;
	m_pGeantKineCat = 0;
	m_pGeantKineCatIter = 0;
    //m_pBTCat = 0;
    //m_pBTCatIter = 0;

      


	if ((m_pContCatPart =
		gHades->getCurrentEvent()->getCategory(catParticleCand)) == 0) {
		ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catParticleCand cat");
		return kFALSE;
	}
	m_pContItPart = (HIterator *) m_pContCatPart->MakeIterator();

        if ( wallflag == 1 )
        {
	   if ((m_pFWallCat =
		   gHades->getCurrentEvent()->getCategory(catWallHit)) == 0) {
		   ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catWallHit cat");
		   return kFALSE;
	   }
	   m_pFWallCatIter = (HIterator *) m_pFWallCat->MakeIterator();
        }


       if (startflag == 1 && simflag > 0)
       {
          if ((m_pGeantStartCat =
               gHades->getCurrentEvent()->getCategory(catStartGeantRaw)) == 0) {
               ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catGeantStart cat");
           return kFALSE;
          }
          m_pGeantStartCatIter = (HIterator *) m_pGeantStartCat->MakeIterator();
       }

       if (startflag == 1)
       {
          if ((m_pStartCat =
               gHades->getCurrentEvent()->getCategory(catStartHit)) == 0) {
               ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catStartHit cat");
           return kFALSE;
          }
          m_pStartCatIter = (HIterator *) m_pStartCat->MakeIterator();
       }

        if ( simflag > 0 )
        {
	   if ((m_pGeantKineCat =
		   gHades->getCurrentEvent()->getCategory(catGeantKine)) == 0) {
		   ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catGeantKine cat");
		   return kFALSE;
	   }
	   m_pGeantKineCatIter = (HIterator *) m_pGeantKineCat->MakeIterator();
        }

        // BT
        //if ((m_pBTCat =
        //        gHades->getCurrentEvent()->getCategory(catParticleBtRing)) == 0) {
        //        ErrorMsg(ERROR, "HTrackPlayer::init", 1, "Cannot get catParticleBtRing cat");
        //        return kFALSE;
        //}
        //m_pBTCatIter = (HIterator *) m_pBTCat->MakeIterator();


	return kTRUE;
}

//-----------------------------------------------------------------
Int_t HTrackPlayer::execute()
{
   partPool.reset();
   partPool.loop( m_pContItPart );
#ifdef DEBUG
   partPool.dump();
#endif
   itCut = vCut.begin();
   while( itCut != vCut.end() )
   {
      (*itCut)->select(*this);
      ++itCut;
   }   
   
   if (startflag > 0 && simflag > 0) partPool.fill( m_pFWallCatIter, m_pGeantKineCatIter, m_pGeantStartCatIter );
   else partPool.fill( m_pFWallCatIter, m_pGeantKineCatIter, m_pStartCatIter, 0 );

   return 0;
}



