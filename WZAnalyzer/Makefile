# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

include ~/Makefile.arch


#------------------------------------------------------------------------------
INPUTFILEO	= InputFile.$(ObjSuf)
WZTREEO	= WZTree.$(ObjSuf)
WZANALYSISO	= WZAnalysis.$(ObjSuf)

EXECUTEWPRIMEO	= ExecuteWprime.$(ObjSuf)
EXECUTEWPRIME		= ExecuteWprime$(ExeSuf)

EXECUTESMWZO	= ExecuteSMWZ.$(ObjSuf)
EXECUTESMWZ		= ExecuteSMWZ$(ExeSuf)

EXECUTEZJETSO	= ExecuteZJets.$(ObjSuf)
EXECUTEZJETS		= ExecuteZJets$(ExeSuf)

MAKEPLOTSO	= MakePlots.$(ObjSuf)
MAKEPLOTS		= MakePlots$(ExeSuf)

COMO  = $(WZANALYSISO) $(WZTREEO) $(INPUTFILEO)

OBJS	      = $(EXECUTEWPRIMEO) $(EXECUTESMWZO) $(EXECUTEZJETSO) $(MAKEPLOTSO) $(COMO)
PROGRAMS    = $(EXECUTEWPRIME) $(EXECUTESMWZ) $(EXECUTEZJETS) $(MAKEPLOTS)

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .C .h

all:	$(PROGRAMS)
		@echo "$@ done"

$(EXECUTEWPRIME):  $(EXECUTEWPRIMEO) $(WZANALYSISO) $(WZTREEO) $(INPUTFILEO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@  
		@echo "$@ done"

$(EXECUTESMWZ):  $(EXECUTESMWZO) $(WZANALYSISO) $(WZTREEO) $(INPUTFILEO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@  
		@echo "$@ done"

$(EXECUTEZJETS):  $(EXECUTEZJETSO) $(WZANALYSISO) $(WZTREEO) $(INPUTFILEO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@  
		@echo "$@ done"

$(MAKEPLOTS):  $(MAKEPLOTSO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@  
		@echo "$@ done"


clean:
		@rm -f $(OBJS) core

distclean:      clean
		@rm -f $(PROGRAMS) $(EVENTSO) $(EVENTLIB) *Dict.* *.def *.exp \
		   *.root *.ps *.so *.lib *.dll *.d .def so_locations
		@rm -rf cxx_repository
		-@cd RootShower && $(MAKE) distclean

%$(ObjSuf): %.C %.h
		$(CXX) $(CXXFLAGS) -c $< 
		@echo "did this for $< and $^ and $@"
