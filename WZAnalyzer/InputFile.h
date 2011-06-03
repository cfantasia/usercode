#ifndef _InputFile_h_
#define _InputFile_h_

#include <iostream>
#include <string>
#include "TTree.h"

class InputFile {
public:
  InputFile();
  InputFile(float cross_sect);

  float x_sect; // cross-section in pb
  float Nprod_evt; // # of events produced
  float weight; // cross-section * integrated luminosity / (# of events produced)
  std::string pathname;
  std::string description; // sample description
  TTree * tree; // pointer to ROOT file

private:

};

#endif//#define _InputFile_h_
