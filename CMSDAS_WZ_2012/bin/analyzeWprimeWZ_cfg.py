import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from UserCode.CMGWPrimeGroup.selectors_cff import *

process = cms.Process("WPrimeAnalysis")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring()
)

process.MessageLogger = cms.Service("MessageLogger")

process.WprimeAnalyzer = cms.PSet(
    ## common input for wrapped analyzers
    fileNames   = cms.vstring(),  ## keep empty!

    outputFile  = cms.string("WprimeWZ.root"),
    logFile = cms.string("WprimeWZ.dat"),
    candEvtFile = cms.string("WprimeWZ.evt"),

    maxEvents   = cms.int32(-1),                     
    reportAfter = cms.int32(-10),                  

    muons = cms.InputTag('selectedPatMuons'),
    electrons = cms.InputTag('selectedPatElectrons'),
    met   = cms.InputTag('patMETsPF'),
    hltEventTag = cms.InputTag('patTriggerEvent'),
    pileupTag  = cms.InputTag('addPileupInfo'),
    vertexTag  = cms.InputTag('offlinePrimaryVertices'),

    electronSelectors = elSelectors,
    muonSelectors     = muSelectors,

    debug = cms.bool(True),
#    debug = cms.bool(False),

    #PileUp Inputs
    MCPUDistFile = cms.string('UserCode/CMGWPrimeGroup/root_macros/MCSummer11S4PUDist.root'),
    MCPUDistHist = cms.string('Fall11Dist'),
    DataPUDistFile = cms.string('UserCode/CMGWPrimeGroup/root_macros/Cert_160404-180252_7TeV_Collisions11_JSON.pileupTruth_v2_finebin.root'),
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
          samplename = cms.string("data_testDoubleE"),
          description = cms.untracked.string("Summer11_RSZZmmjj_750"),
          x_section = cms.untracked.double(0.00835),
          Nprod_evt = cms.untracked.int32(56754),
          pathname = cms.string("//uscms_data/d3/fladias/DoubleEtest.root"),
        ),
        cms.PSet(
          samplename = cms.string("testDoubleE"),
          description = cms.untracked.string("Summer11_RSZZmmjj_750"),
          x_section = cms.untracked.double(0.00835),
          Nprod_evt = cms.untracked.int32(10000),
          pathname = cms.string("//uscms_data/d3/fladias/WZtest.root"),
        ),
      ),#end of files

    ),#end of inputfiles
    
    )


