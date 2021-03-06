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
    reportAfter = cms.int32(10000),                  

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
          samplename = cms.string("WZ"),
          description = cms.untracked.string("WZ"),
          x_section = cms.untracked.double(0.879),
          Nprod_evt = cms.untracked.int32(1221134),
          subdir = cms.untracked.string("dcache:"),
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola.txt"),
        ),

 
        cms.PSet(
          samplename = cms.string("TTJets"),
          description = cms.untracked.string("TTJets"),
          x_section = cms.untracked.double(157.5),
          Nprod_evt = cms.untracked.int32(50098875),
          subdir = cms.untracked.string("dcache:"),
          pathname = cms.string("filelists/MCPatTrilepton-W06-06-05A-TTJets_TuneZ2_7TeV-madgraph-tauola.txt"),
        ),

        cms.PSet(
          samplename = cms.string("ZZ2e2m"),
          description = cms.untracked.string("ZZ2e2mu"),
          x_section = cms.untracked.double(0.03078),
          Nprod_evt = cms.untracked.int32(499917),
          subdir = cms.untracked.string("dcache:"),
          pathname = cms.string("filelists/MCPatTrilepton-W06-06-05A-ZZTo2e2mu_7TeV-powheg-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("ZZ4e"),
          description = cms.untracked.string("ZZ4e"),
          x_section = cms.untracked.double(0.0154),
          Nprod_evt = cms.untracked.int32(499929),
          subdir = cms.untracked.string("dcache:"),
          pathname = cms.string("filelists/MCPatTrilepton-W06-06-05A-ZZTo4e_7TeV-powheg-pythia6.txt"),
        ),


        cms.PSet(
          samplename = cms.string("ZZ4m"),
          description = cms.untracked.string("ZZ4m"),
          x_section = cms.untracked.double(0.0154),
          Nprod_evt = cms.untracked.int32(499918),
          subdir = cms.untracked.string("dcache:"),
          pathname = cms.string("filelists/MCPatTrilepton-W06-06-05A-ZZTo4mu_7TeV-powheg-pythia6.txt"),
        ),

        
      ),#end of files

    ),#end of inputfiles
    
    )


