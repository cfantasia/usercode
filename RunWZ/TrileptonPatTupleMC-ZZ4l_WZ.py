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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZZ4l_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-0A4084EE-6B46-DF11-8880-003048D4DFA4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-0ACBB943-6F46-DF11-B0B0-003048D439C6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-284205A4-6F46-DF11-8ED8-0030487F0EDD.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-40C10503-6F46-DF11-AC93-0030487F1A31.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-54CDDF92-6746-DF11-BBA0-003048C693EE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-6E12A46C-6F46-DF11-907E-003048D436D4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-86356326-DE46-DF11-81C8-003048C69296.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-887BB302-6F46-DF11-9F77-003048C69314.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-8EA6A953-6F46-DF11-B01C-0030488A0CA4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-926C6F69-6F46-DF11-A229-0030487D5D91.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-94EA1EC0-7046-DF11-9D75-003048D439B6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-961EE312-6546-DF11-A3E0-003048D439B6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-9CD45757-7C46-DF11-8B53-0030488A0C1E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-DC1F31F4-6B46-DF11-B751-0030487F91D9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-DE2CC188-6546-DF11-8C41-0030487F929B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ4l/TrileptonPatTupleMC-V05-03-03-E4F64D81-6546-DF11-8E73-0030487D710F.root',
)))
