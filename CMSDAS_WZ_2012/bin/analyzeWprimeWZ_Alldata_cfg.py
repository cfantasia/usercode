import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from UserCode.CMSDAS_WZ_2012.selectors_cff import *

process = cms.Process("WPrimeAnalysis")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring()
)

process.MessageLogger = cms.Service("MessageLogger")

process.WprimeAnalyzer = cms.PSet(
    ## common input for wrapped analyzers
    fileNames   = cms.vstring(),  ## keep empty!

    outputFile  = cms.string("WprimeWZ.root"),

    maxEvents   = cms.int32(-1),                     
    reportAfter = cms.int32(-10),                  

    muons = cms.InputTag('userPatMuons'),
    electrons = cms.InputTag('userPatElectrons'),
    met   = cms.InputTag('patMETsPF'),
    hltEventTag = cms.InputTag('patTriggerEvent'),
    pileupTag  = cms.InputTag('addPileupInfo'),
    vertexTag  = cms.InputTag('offlinePrimaryVertices'),

    electronSelectors = elSelectors,
    muonSelectors     = muSelectors,

    debug = cms.bool(True),
#    debug = cms.bool(False),

    #PileUp Inputs
    MCPUDistFile = cms.string('UserCode/CMSDAS_WZ_2012/root_macros/MCPUDist.root'),
    MCPUDistHist = cms.string('Fall11Dist'),
    DataPUDistFile = cms.string('UserCode/CMSDAS_WZ_2012/root_macros/Cert_160404-180252_7TeV_Collisions11_JSON.pileupTruth_v2_finebin.root'),
    DataPUDistHist = cms.string('pileup'),
    puScale = cms.double(1.0),

    ## input specific for this analyzer
    LooseElectronType = cms.untracked.string("WZLoose"),
    TightElectronType = cms.untracked.string("WZTight"),
    LooseMuonType = cms.untracked.string("WZLoose"),
    TightMuonType = cms.untracked.string("WZTight"),
    
    # +++++++++++++++++++General Cut values
    maxNumZs = cms.uint32(1),
    minNLeptons = cms.untracked.uint32(2),
    minMET = cms.untracked.double(30.),
    
    # +++++++++++++++++++W Cuts
    minWtransMass = cms.untracked.double(0.),
    
    # +++++++++++++++++++Z Cuts
    minZl1Pt =  cms.double(20.),
    minZl2Pt =  cms.double(10.),
    
    minZmass =  cms.untracked.double(60.),
    maxZmass =  cms.untracked.double(120.),

    # +++++++++++++++++++Analysis Cuts
    minHt = cms.untracked.double(270.),
    minZpt =  cms.untracked.double(0.),
    minWpt = cms.untracked.double(0.),
    
    # +++++++++++++++++++Input Files
    inputFiles = cms.PSet(
      top_level_dir = cms.untracked.string(""),
      lumi_ipb = cms.double(5000),
      files = cms.VPSet(
    
        cms.PSet(
          samplename = cms.string("data1"),
          description = cms.untracked.string("DoubleMu_May10"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleMu-Run2011A-May10ReReco-v1.txt"),
          ),


        cms.PSet(
          samplename = cms.string("data2"),
          description = cms.untracked.string("DoubleE_May10"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleElectron-Run2011A-May10ReReco-v1.txt"),
          ),


        cms.PSet(
          samplename = cms.string("data3"),
          description = cms.untracked.string("DoubleMu_PRv4"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleMu-Run2011A-PromptReco-v4.txt"),
        ),


        cms.PSet(
          samplename = cms.string("data4"),
          description = cms.untracked.string("DoubleE_PRv4"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleElectron-Run2011A-PromptReco-v4.txt"),
        ),

        cms.PSet(
          samplename = cms.string("data5"),
          description = cms.untracked.string("DoubleMu_Aug05"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleMu-Run2011A-05Aug2011-v1.txt"),
        ),


        cms.PSet(
          samplename = cms.string("data6"),
          description = cms.untracked.string("DoubleE_Aug05"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleElectron-Run2011A-05Aug2011-v1.txt"),
        ),


        cms.PSet(
          samplename = cms.string("data7"),
          description = cms.untracked.string("DoubleM_PRv6"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleMu-Run2011A-PromptReco-v6.txt"),
        ),



        cms.PSet(
          samplename = cms.string("data8"),
          description = cms.untracked.string("DoubleE_PRv6"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleElectron-Run2011A-PromptReco-v6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("data9"),
          description = cms.untracked.string("DoubleM_PRv1"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleMu-Run2011B-PromptReco-v1.txt"),
        ),


        cms.PSet(
          samplename = cms.string("data10"),
          description = cms.untracked.string("DoubleE_PRv1"),
          x_section = cms.untracked.double(1),
          Nprod_evt = cms.untracked.int32(9999),
          subdir = cms.untracked.string("/"),
          pathname = cms.string("filelists/DataPatTrilepton-W06-06-05A-DoubleElectron-Run2011B-PromptReco-v1.txt"),
        ),
 


       
      ),#end of files

    ),#end of inputfiles
    
    )


