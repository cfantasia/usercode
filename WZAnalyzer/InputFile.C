#include "InputFile.h"
using namespace std;

InputFile::InputFile(){
  x_sect = 0; Nprod_evt = 0; weight = 0; tree = 0;
}
InputFile::InputFile(float cross_sect){
  x_sect = cross_sect; Nprod_evt = 0; weight = 0; tree = 0;
}
