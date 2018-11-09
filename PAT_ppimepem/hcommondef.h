#ifndef HCOMMONDEF_H
#define HCOMMONDEF_H

#include <map>
#include <vector>
#include <string>

class HParticleCandidate;
class HParticle;
class HHypCandidate;
class HNtuple;

namespace CommonDefinitions {

enum EParticle { eUnknown=0, ePositron=2, eElectron=3, ePiPlus=8, ePiMinus=9, eProton=14, eDeuteron=45, eLeptonPos=102, eLeptonNeg=103, eHadronPos=104, eHadronNeg=105 };

typedef std::multimap< EParticle, HParticleCandidate* > MultiParticle;
typedef std::vector< HParticle* > ParticleCandSeq;
typedef std::pair< EParticle, HParticleCandidate* > MultiPair;
typedef std::map< EParticle, int > ParticleNum;

typedef std::multimap< std::string, HHypCandidate* > MultiHyp;
typedef std::pair< std::string, HHypCandidate* > MultiHypPair;
typedef std::map< std::string, int > HypNum;
typedef std::map< std::string, int > ReactionNum;

typedef std::multimap< std::string, std::string > MultiHypPid;

typedef MultiParticle::iterator MultiParticleIter;
typedef std::vector< HParticle* >::iterator ParticleCandSeqIter;
typedef std::map< EParticle, int >::iterator ParticleNumIter;
typedef std::pair< MultiParticleIter, MultiParticleIter > MultiParticleIterPair;

typedef MultiHyp::iterator MultiHypIter;
typedef std::map< std::string, int >::iterator HypNumIter;
typedef std::pair< MultiHypIter, MultiHypIter > MultiHypIterPair;

typedef std::map< std::string, float > NtuplePair;
typedef std::map< std::string, float >::iterator NtuplePairIter;
//typedef std::map< const char*, HNtuple* > Ntuple;
//typedef std::map< const char*, HNtuple* >::iterator NtupleIter;

typedef std::vector< EParticle > ParticleSeq;


EParticle convertId(const char* name);
EParticle convertId(int n);
std::string convertId(EParticle eid);

}  // eof namespace



#endif // HCOMMONDEF_H
