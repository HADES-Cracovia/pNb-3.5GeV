#ifndef FWPAD_H
#define FWPAD_H

#include <vector>

class FWPad {

   int id;
   int classId;
   std::vector<FWPad*> pads; 
   std::vector<FWPad*>::iterator padsIt; 

public:

   FWPad(int i) : id(i)
   {
      classId = (id < 144) ? 0 : (id < 208) ? 1 : 2;
   }
   ~FWPad() {}

   void addPad( FWPad *p ) { pads.push_back( p ); }
   bool isNext(int i);
   int getId() const { return id; }
   int getClassId() const { return classId; }
   void setId(int i) { id = i; }
   void setClassId(int c) { classId = c; }
   FWPad* getFWPad() { return this; }

};


#endif // FWPAD_H
