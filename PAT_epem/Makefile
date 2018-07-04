APP_NAME := ana
SOURCE_FILES :=  heditor.cc hcommondef.cc hcut.cc htrackcut.cc htimecut.cc hgraphcut.cc hdedxcut.cc hparticlecandidate.cc hparticle.cc hhypcandidate.cc heventpool.cc hpool.cc hparticledatapool.cc hparticlepool.cc hhypdatapool.cc hhyppool.cc hpidpool.cc htrackplayer.cc hparticleplayer.cc hhypplayer.cc hntuple.cc hfile.cc houtputfile.cc houtput.cc main.cc wall/fwpad.cc wall/fwdetector.cc wall/fwsinglehit.cc wall/fwclusterhit.cc wall/fwhit.cc

MAX_PARTICLES = 4

USES_RFIO    := no
USES_CERNLIB := no
USES_ORACLE  := no
#CPP_FLAGS    += -g  -fno-inline -DDEBUG -DMAX_PARTICLES_IN_COMB=$(MAX_PARTICLES)
CPP_FLAGS    += -DMAX_PARTICLES_IN_COMB=$(MAX_PARTICLES)



include $(HADDIR)/hades.def.mk

#LD	     += -g  -fno-inline -DDEBUG
LD	     += 

# override default list of linked Hydra libraries - before they can act on the rules


.PHONY:  default
default: build install

include $(HADDIR)/hades.app.mk
