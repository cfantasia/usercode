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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-TTbar2l_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-04609CBE-5546-DF11-9D24-001E0B5FA528.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-0E74FCC5-E346-DF11-801A-00237DA1CDBE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-1041B027-E146-DF11-BDCB-0017A4770008.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-14A8818B-5546-DF11-B89B-0017A4770400.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-1ADDF725-E146-DF11-8659-0022649F01AA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-1CF386A3-E446-DF11-A55B-0017A477041C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-200FED54-E446-DF11-B83F-001A4BA98052.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-20A28DE6-3F44-DF11-A656-0017A4770018.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-240BAA1A-4644-DF11-8157-00237DA15C66.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-26A283A2-E446-DF11-93C5-0017A477001C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-2EF0F0F1-5446-DF11-AFF9-001E0B5FA542.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-306C1C9E-E046-DF11-A4B7-0017A477003C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-3261C6F0-E246-DF11-A2BB-0017A4770008.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-36773A36-5646-DF11-AA39-00237DA1CD92.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-3A1E4C31-6E44-DF11-A819-001CC443B76C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-3AFA6CCA-4B44-DF11-AB5E-001E0B472C96.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-402921B3-5446-DF11-828E-00237DA1680E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-48FC380D-E446-DF11-B94D-0017A4770C14.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-4C329DE5-E046-DF11-B4C3-0017A4770C2C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-4C3F92FC-5446-DF11-B7CE-0017A4770C28.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-501445E4-E046-DF11-9AB7-0017A4770C28.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-58510E43-5646-DF11-8098-0017A4770814.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-5E7D8F35-5646-DF11-BDF2-00237DA2F1DC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-60CCC42E-5446-DF11-A85F-0017A477040C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-664EB9C9-5546-DF11-99FC-0022649E7902.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-6805FF49-E046-DF11-81D1-0017A4771000.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-68C3F693-E046-DF11-B7DE-00237DA10D06.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-6E9C63A8-E446-DF11-9947-00237DA13C16.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-72F8E44D-E046-DF11-86F6-0017A477040C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-74C56F07-5546-DF11-98D2-00237DA2F1DC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-78E66354-E446-DF11-8F80-0017A4770400.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-7A5D7A7C-3E44-DF11-A724-00237DA12FFE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-7CB59309-5546-DF11-8057-0017A477041C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-88933DF8-5446-DF11-983A-0017A477043C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-8C1B71A3-E446-DF11-943A-0017A4770024.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-923FDFF3-E246-DF11-A0F4-0017A4770808.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-92D3492F-5446-DF11-AF73-0017A477001C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-948944A0-E446-DF11-B05C-0017A477042C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-9A6D482F-5446-DF11-B78D-0017A4771028.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-9CF2040A-3D44-DF11-85A4-0017A477100C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-9ED9794C-E046-DF11-9C4F-0017A4770818.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-A43F2CBE-5546-DF11-A5B6-00237DA096F8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-A80686CB-5546-DF11-AA0E-0017A4770424.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-A859FAC2-E146-DF11-A3E4-0017A4770400.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-B4929558-E446-DF11-8842-0017A4770400.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-B6F7721E-4644-DF11-8235-00237DA2F1DC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-BAC5B02A-E146-DF11-BE20-0017A4770C3C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-BAC618FE-5446-DF11-88C7-0017A4770020.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-BEE91A82-E346-DF11-910A-0017A477102C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-C48A2365-3F44-DF11-B88F-0017A4770C30.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-C82C1A15-5546-DF11-AB42-0017A477000C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-CEB4ECEE-E246-DF11-BC0A-00237DA12FFE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-D25356EC-E246-DF11-83E4-0017A4771030.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-D26200B2-5546-DF11-936E-001CC443B76C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-DA3D9E4F-4344-DF11-98A2-0017A4770838.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-DAAD95EB-E246-DF11-9EA4-0017A4770010.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-DCCFA32A-5446-DF11-93B7-00237DA13FB6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-E8C16BD5-6C44-DF11-B704-0022649E7902.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-EAE4232D-5446-DF11-B04B-0017A4770014.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-F0D3BC13-E446-DF11-975A-00237D9F2120.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-F89D90BC-5446-DF11-84CE-001E0B5FA528.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TTbar2l/TrileptonPatTupleMC-V05-03-03-FAB4C80F-E246-DF11-B259-0017A4770810.root',
)))
