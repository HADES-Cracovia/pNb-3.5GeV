#ifndef HPOOL_H
#define HPOOL_H

#include <list>
#include "hcommondef.h"
#include "hiterator.h"
#include "hntuple.h"
#include "houtputfile.h"
#include "houtput.h"
#include "hparticlecandidate.h"
#include "hpattern.h"
#include "heventpool.h"

using namespace CommonDefinitions;


class HPool {

public:

   HPool(HOutputFile *ptr = 0);
   virtual ~HPool() = 0;

   void setOutput(HOutputFile *ptr) { ptrFile = ptr; }

   bool add(const char* name, EParticle p1);
   bool add(const char* name, EParticle p1, EParticle p2);
   bool add(const char* name, EParticle p1, EParticle p2, EParticle p3);
   bool add(const char* name, EParticle p1, EParticle p2, EParticle p3, EParticle p4);
   bool add(const char* name, const char* p1);
   bool add(const char* name, const char* p1, const char* p2);
   bool add(const char* name, const char* p1, const char* p2, const char* p3);
   bool add(const char* name, const char* p1, const char* p2, const char* p3, const char* p4);

   void set(HEventPool* previous) { eventData.set( previous ); }
   HEventPool* getEventPool() { return &eventData; }

protected:

   HEventPool eventData;

   std::list<HPattern*> objectList;
   std::list<HPattern*>::iterator objIt;

   bool isObject(const char* name);
   HPattern* getObject(const char* name);

   HOutputFile *ptrFile; 


ClassDef(HPool, 0) 
};



#endif // HPOOL_H 
