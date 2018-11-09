CC=g++
TARGET=analpp
OBJS=main.o data.o EpEm.o EpEp.o EmEm.o
HEADERS=data.h EpEm.h EpEp.h EmEm.h
ROOTLIBS=`root-config  --libs` -lTuple -lHFilter

CPPFLAGS+=-g -L/u/przygoda/HNTUPLE64 -L/u/przygoda/HFILTER64 -L/u/przygoda/PLUTO64/ -Wl,--no-as-needed 
FFLAGS+=-g -I/u/przygoda/HNTUPLE64 -I/u/przygoda/HFILTER64 -I/u/przygoda/PLUTO64/src
#FFLAGS+=-g -pg -fprofile-arcs
#CPPFLAGS+=-g 

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

