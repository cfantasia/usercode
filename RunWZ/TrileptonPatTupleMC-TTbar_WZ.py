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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-TTbar_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-00A071D6-924E-DF11-9502-001E0B5FC422.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-0A40D7C2-AF4E-DF11-8468-0017A4770028.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-163C0A0A-924E-DF11-909E-0022649E7902.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-1A6EE179-924E-DF11-A56F-0017A4771018.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-227DB7C3-B04E-DF11-BF66-0017A4770004.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-24029964-9D4E-DF11-8286-0017A4770024.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-38E04FA8-AB4E-DF11-B47C-0017A4770C18.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-3E45BDB3-904E-DF11-966C-0017A4770038.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-4EF89E83-A84E-DF11-A8D5-0017A4770C24.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-568041B5-AD4E-DF11-BA64-0017A477081C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-62F9739D-A94E-DF11-9C2C-0017A4770800.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-669AC17B-A64E-DF11-845E-0017A4770C10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-705D478F-904E-DF11-801C-00237DA1494E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-70D60957-9C4E-DF11-B9B7-0017A477001C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-8664EF71-9D4E-DF11-94FD-0017A4770C28.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-88B139D5-8C4E-DF11-8D18-0017A477081C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-8E206F31-904E-DF11-B439-001E0B5FB53E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-961357B1-964E-DF11-BBCB-001E0B5FA51A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-9883C38F-9D4E-DF11-B4DE-0017A477001C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-9C57F56F-A94E-DF11-AD41-0017A477043C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-A86927D8-8C4E-DF11-8146-00237DA15C00.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-AC4E7FC0-AE4E-DF11-92A0-0017A4770C08.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-BA64FB8E-904E-DF11-87B0-001CC4C10E02.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-BE47C9C2-AC4E-DF11-A523-0017A4770C34.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-D2933364-A04E-DF11-9DF9-0017A4770018.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-D80E4BC2-AE4E-DF11-9155-0017A4770000.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-D8127E04-A94E-DF11-95B2-0017A4770818.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-DA28E8AA-AD4E-DF11-9436-0017A4771024.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-DEB9F020-A94E-DF11-8B5B-0017A4770C04.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-EAFBF0A2-AB4E-DF11-84CE-0017A4770424.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-F086724D-944E-DF11-A2C2-0017A4770800.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar/TrileptonPatTupleMC-V05-03-03-FACCF1C2-AE4E-DF11-AB96-0017A4770430.root',
)))
