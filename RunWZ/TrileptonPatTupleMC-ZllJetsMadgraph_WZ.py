import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("UserAnalysis.WZAnalysis.wzTreeMaker_cfi")

process.wzTreeMaker.numEventsNames = ['nEventsTotal',
                                      'nEventsHLT',
                                      'nEventsPat',
                                      'nEventsFiltered']

# Manage text output
process.MessageLogger.cerr.FwkReport.reportEvery = 50
process.MessageLogger.cerr.threshold = 'ERROR'
process.MessageLogger.cerr.default.limit = 3
process.wzTreeMaker.debug = False

# To run on data, change useMC to False in wzPat_cff.py.  That variable is
# in both this module and patAndFilter to choose between MC and data.

# Apply electron ID requirements for the bosons
process.wzTreeMaker.eidTypeZ = cms.untracked.string("")
process.wzTreeMaker.eidTypeW = cms.untracked.string("")

# Any branch whose name matches one of these perl-style regular expressions
# will not be generated in the ouput tree (use '.*' for wildcard)
process.wzTreeMaker.contentToDrop = ["jet.*"]
process.wzTreeMaker.contentToKeep = []

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.p = cms.Path(process.wzTreeMaker)
process.GlobalTag.globaltag = 'START38_V13::All'
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZllJetsMadgraph_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0C096217-3A47-DF11-9E65-003048C692A4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0EB44D6B-4347-DF11-BC33-0030487D605B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-12E8365D-3F47-DF11-A374-00304889D562.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-18D2909C-3847-DF11-B601-0030487F0EDF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-1A9FC50E-4047-DF11-8288-003048C69408.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-245A060F-3A47-DF11-8D2C-0030487D857D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-2EE9EA96-3947-DF11-B555-003048D462FE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-361BC40E-4047-DF11-AB92-0030487F1BE5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-3AE7B4A0-3847-DF11-9909-003048C692B6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-46F34523-3F47-DF11-A7AB-0030487D86CB.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-4E3A7272-4247-DF11-8C3C-003048D439B6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-58694126-3B47-DF11-BFF5-0030487D5DA5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-5E3E28A3-3847-DF11-B9C8-0030487F1F23.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-604C4EE5-B047-DF11-964E-0030487F4B8B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-662F704E-4247-DF11-BE4D-003048D3CA06.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-6EFAD58A-4547-DF11-8CBA-0030487F8E69.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-7436B10E-4047-DF11-926F-003048C6930E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-76171D10-4047-DF11-A15A-003048C693EE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-7A0D100F-4047-DF11-A460-0030487F1BD7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-907FABD3-5247-DF11-A943-0030487D5D67.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-90DBE2E7-4147-DF11-96E1-003048C66182.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-92F35F11-4047-DF11-A089-003048C693FA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-9AEE6117-3A47-DF11-9973-003048C692A4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-A21346EA-4647-DF11-9BA3-003048D4363C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-A6FA9317-4047-DF11-BA6E-003048D462BE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B284F652-3947-DF11-83AD-003048C68FEC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B617FE25-3B47-DF11-956C-0030487EBB2B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-BAFE4FC5-3647-DF11-8B08-003048C692FA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-C0F4B505-3A47-DF11-A6CA-0030487D814B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-C8E5F16C-4347-DF11-81AF-0030488A1188.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CE84A018-3F47-DF11-81B6-0030488A0CB6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CEEB8F54-3947-DF11-AA55-003048D4364C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-DC7D87C7-3847-DF11-AC03-003048D4DFAA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-E29EF75C-3947-DF11-A24A-003048D3CDE0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZllJetsMadgraph/TrileptonPatTupleMC-V05-03-03-EE0BA8CA-3847-DF11-AB98-0030487F1BD7.root',
)))
