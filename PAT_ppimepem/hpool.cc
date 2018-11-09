#include "hades.h"
#include "hevent.h"
#include "heventheader.h"
#include "hpool.h"
#include <algorithm>
#include <iostream>

using namespace std;


// ****************************************************************************
ClassImp(HPool)

//-----------------------------------------------------------------------------
HPool::HPool(HOutputFile *ptr) : ptrFile(ptr)
{
}


//-----------------------------------------------------------------------------
HPool::~HPool() 
{ 
   std::for_each( objectList.begin(), objectList.end(), DelPCObj() ); 
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, EParticle p1)
{
   if (false == isObject(name))
   {
      objectList.push_back( new HPattern( name, p1, ptrFile ) );
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, EParticle p1, EParticle p2)
{
   if (false == isObject(name))
   {
      objectList.push_back( new HPattern( name, p1, p2, ptrFile ) );
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, EParticle p1, EParticle p2, EParticle p3)
{
   if (false == isObject(name))
   {
      objectList.push_back( new HPattern( name, p1, p2, p3, ptrFile ) );
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, EParticle p1, EParticle p2, EParticle p3, EParticle p4)
{
   if (false == isObject(name))
   {
      objectList.push_back( new HPattern( name, p1, p2, p3, p4, ptrFile ) );
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, const char* p1)
{
   return add( name, convertId(p1) );
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, const char* p1, const char* p2)
{
   return add( name, convertId(p1), convertId(p2) );
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, const char* p1, const char* p2, const char* p3)
{
   return add( name, convertId(p1), convertId(p2), convertId(p3) );
}

//-----------------------------------------------------------------------------
bool HPool::add(const char* name, const char* p1, const char* p2, const char* p3, const char* p4)
{
   return add( name, convertId(p1), convertId(p2), convertId(p3), convertId(p4) );
}

//-----------------------------------------------------------------------------
bool HPool::isObject(const char* name)
{
   if (objectList.end() == std::find_if( objectList.begin(), objectList.end(), std::bind2nd( IsPCName(), name ) ))
   {
      return false;
   }
return true;
}


//-----------------------------------------------------------------------------
HPattern* HPool::getObject(const char* name)
{
   if ( isObject(name) )
   {
      return *std::find_if( objectList.begin(), objectList.end(), std::bind2nd( IsPCName(), name ));
   }
return 0;
}

