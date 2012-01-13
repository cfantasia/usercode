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
          samplename = cms.string("Wprime200"),
          description = cms.untracked.string("Wprime200"),
          x_section = cms.untracked.double(1.324),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-200_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime300"),
          description = cms.untracked.string("Wprime300"),
          x_section = cms.untracked.double(0.8599),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-300_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime400"),
          description = cms.untracked.string("Wprime400"),
          x_section = cms.untracked.double(0.2768),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-400_7TeV-pythia6.txt"),
        ),


        cms.PSet(
          samplename = cms.string("Wprime500"),
          description = cms.untracked.string("Wprime500"),
          x_section = cms.untracked.double(0.1074),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-500_7TeV-pythia6.txt"),
        ),


        cms.PSet(
          samplename = cms.string("Wprime600"),
          description = cms.untracked.string("Wprime600"),
          x_section = cms.untracked.double(0.0489),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-600_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime700"),
          description = cms.untracked.string("Wprime700"),
          x_section = cms.untracked.double(0.0244),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-700_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime800"),
          description = cms.untracked.string("Wprime800"),
          x_section = cms.untracked.double(0.01328),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-800_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime900"),
          description = cms.untracked.string("Wprime900"),
          x_section = cms.untracked.double(0.00744),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-900_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1000"),
          description = cms.untracked.string("Wprime1000"),
          x_section = cms.untracked.double(0.00442),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1000_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1100"),
          description = cms.untracked.string("Wprime1100"),
          x_section = cms.untracked.double(0.002704),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1100_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1200"),
          description = cms.untracked.string("Wprime1200"),
          x_section = cms.untracked.double(0.001690),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1200_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1300"),
          description = cms.untracked.string("Wprime1300"),
          x_section = cms.untracked.double(0.001082),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1300_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1400"),
          description = cms.untracked.string("Wprime1400"),
          x_section = cms.untracked.double(0.000690),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1400_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("Wprime1500"),
          description = cms.untracked.string("Wprime1500"),
          x_section = cms.untracked.double(0.000456),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-WprimeToWZTo3LNu_emt_M-1500_7TeV-pythia6.txt"),
        ),
        

        cms.PSet(
          samplename = cms.string("TC300"),
          description = cms.untracked.string("TC300"),
          x_section = cms.untracked.double(0.05822),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-300_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC400"),
          description = cms.untracked.string("TC400"),
          x_section = cms.untracked.double(0.01751),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-400_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC500"),
          description = cms.untracked.string("TC500"),
          x_section = cms.untracked.double(0.007056),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-500_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC600"),
          description = cms.untracked.string("TC600"),
          x_section = cms.untracked.double(0.003364),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-600_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC700"),
          description = cms.untracked.string("TC700"),
          x_section = cms.untracked.double(0.001774),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-700_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC800"),
          description = cms.untracked.string("TC800"),
          x_section = cms.untracked.double(0.0009728),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-800_7TeV-pythia6.txt"),
        ),

        cms.PSet(
          samplename = cms.string("TC900"),
          description = cms.untracked.string("TC900"),
          x_section = cms.untracked.double(0.0009866),
          Nprod_evt = cms.untracked.int32(20000),
          subdir = cms.untracked.string("dcache:");
          pathname = cms.string("filelists/MCPatOmnilepton-W06-06-05A-TCRhoToWZTo3LNu_emt_M-900_7TeV-pythia6.txt"),
        ),



        
      ),#end of files

    ),#end of inputfiles
    
    )


