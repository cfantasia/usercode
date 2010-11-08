//---------------------------------------------
// Author: Edgar Carrera
// 2010-01-13
// This macro will be used for analyzing
// Wprime -> WZ -> lllnu events
// It works on an root-uple of events with
// variables created by the "official" CMS WZ code
//---------------------------------------------
#ifndef _ExecuteTTbar_h_
#define _ExecuteTTbar_h_

#include <ExecuteFunctions.C>
#include <ExecuteCuts.C>

// +++++++++++++++++++ Histogram Definitions
const int Num_histo_sets = 4; //matches the number of cuts
const string Cut_Name[] = {"NoCuts", 
                           "Tag", 
                           "Probe", 
                           "AllCuts"};

// +++++++++++++++++++ Declare the methods that we use:
void ExecuteTTbar();
bool PassFakeLeptonTagCut();
bool PassFakeLeptonProbeCut();

#endif//#define _ExecuteTTbar_h_
