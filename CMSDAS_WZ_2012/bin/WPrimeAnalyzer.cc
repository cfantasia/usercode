#include <memory>
#include <iostream>

#include <TSystem.h>

#include <TH1.h>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "FWCore/ParameterSet/interface/ProcessDesc.h"

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "UserCode/CMSDAS_WZ_2012/interface/WZAnalyzer.h"

using std::cout; using std::cerr; using std::endl;

int main(int argc, char* argv[]) 
{
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  TH1::SetDefaultSumw2();
  
  // only allow one argument for this simple example which should be the
  // the python cfg file
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py] <fileToRun>" << std::endl;
    return -1;
  }

  char * config_file = argv[1];
  int fileToRun = argc > 2 ? atoi(argv[2]) : -1;

  PythonProcessDesc builder(config_file);
  const edm::ParameterSet& cfg = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("WprimeAnalyzer");

  WZAnalyzer* wprimeAnalyzer = new WZAnalyzer(cfg, fileToRun);
  wprimeAnalyzer->run();

  if(wprimeAnalyzer) delete wprimeAnalyzer;

  return 0;
}

