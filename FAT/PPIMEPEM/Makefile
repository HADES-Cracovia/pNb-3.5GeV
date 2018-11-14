CC=g++
TARGET=analpp
OBJS=main.o data.o PPimEpEm.o PPimEpEp.o PPimEmEm.o
HEADERS=data.h PPimEpEm.h PPimEpEp.h PPimEmEm.h
ROOTLIBS=`root-config  --libs` -lTuple -lHFilter -Lparticle -lHydra
ROOTLIBS += -lPid -lPidUtil -lPairs -lParticle
ROOTLIBS += -lMdcTrackG -lMdcTrackD -lMdcTrackS -lKick

ROOTLIBS += -lHodo -lWall -lShowerTofino -lShower -lTofino -lTof
ROOTLIBS += -lMdc -lRichUtil -lRich -lRpc -lHodo
ROOTLIBS += -lTriggerUtil -lTrigger -lStart
ROOTLIBS += -lQA -lTools

CPPFLAGS+=-g -L/u/przygoda/HNTUPLE64 -L/u/przygoda/HFILTER64 -L/u/przygoda/PLUTO64/ -L/lustre/nyx/hades/user/kempter/svn/hydra_BT/lib  -Wl,--no-as-needed
FFLAGS+=-g -I/u/przygoda/HNTUPLE64 -I/u/przygoda/HFILTER64 -I/u/przygoda/PLUTO64/src -I/lustre/nyx/hades/user/kempter/svn/hydra_BT/include

ifdef NOCUT
  FFLAGS += -DNOCUT
endif

ifdef RECTANG
  FFLAGS += -DRECTANG
endif

ifdef TARG
  FFLAGS += -DTARG
endif



.SUFFIXES   : .o .cc
.SUFFIXES   : .o .C

.cc.o :
	$(CC) $(FFLAGS) `root-config  --cflags` -c $<
.C.o :
	$(CC) $(FFLAGS) `root-config  --cflags` -c $<


all: $(OBJS) $(HEADERS)
	$(CC)  $(CPPFLAGS) $(ROOTLIBS) -o $(TARGET) $(OBJS)

clean:
	-rm -rf *.o *.d $(TARGET) 

