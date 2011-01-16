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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZmumuJets_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-00EF6EDB-4045-DF11-9105-90E6BA0D09EC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-0214904D-F544-DF11-A7DE-90E6BA442F27.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-04387DE7-6545-DF11-9816-E0CB4E1A1180.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-0631A1E0-2045-DF11-BB20-90E6BA442F27.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-083684B7-4645-DF11-9F64-90E6BA442EEC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-0A05385D-F444-DF11-B44B-00261834B561.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-0A39AAD8-4045-DF11-852F-E0CB4E19F973.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-0CE53BA9-4E45-DF11-AE6C-90E6BA442F0E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-14BB722C-DF44-DF11-B84B-90E6BA442F41.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-1A5E9C76-4E45-DF11-90F9-90E6BA442F32.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-1AB74534-3945-DF11-A333-001EC9D81D54.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-20862436-6045-DF11-9BEC-001EC9D7FA10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-20E9A07B-1345-DF11-9C22-E0CB4E1A1150.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-26120BD4-5845-DF11-897B-90E6BA442F44.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-288C324F-4E45-DF11-9B0B-E0CB4E19F982.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-289961E5-E044-DF11-9455-90E6BA19A258.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-2A18F24B-F544-DF11-81D9-00261834B580.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-2CD4966F-3745-DF11-B02B-90E6BA19A22B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-30E6B6A1-F244-DF11-9F49-00261834B559.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-3452AA97-4345-DF11-9C3D-0030487CDAC6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-38262142-DF46-DF11-8238-0030487C6A90.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-3A26449E-0545-DF11-8602-001EC9D8B16D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-4816D5E8-3A45-DF11-B7E8-003048678A04.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-48420B7C-2C45-DF11-B3F1-90E6BA442F02.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-4AB51CB8-4645-DF11-B7AB-E0CB4E1A1169.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-4AD7A5A9-6345-DF11-BDA8-90E6BA442F36.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-4C17A20D-4E45-DF11-9BE8-E0CB4E1A118F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-4C458CA9-E044-DF11-8E42-90E6BA19A241.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-50A59DE7-4045-DF11-9F3D-E0CB4E1A11A7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-50C855C6-1345-DF11-AB1F-00261834B569.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-540F4F7B-1F45-DF11-B973-90E6BAE8CC13.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-5468A3FD-3045-DF11-8245-00261834B575.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-5A03D345-5945-DF11-AC93-90E6BA19A22F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-60E0F3CC-4645-DF11-A894-001EC9D7FA0C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-62EC72B5-1245-DF11-8026-90E6BA442EF7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-64675344-D144-DF11-B2D0-0022198F5D33.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-6C18417A-4E45-DF11-9862-E0CB4E19F96E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-6CC030D7-4045-DF11-ACB3-E0CB4E1A1183.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-6EA9ACD9-4045-DF11-A03D-0030487CDAC8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-78BC7973-4E45-DF11-A373-90E6BA19A260.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-7E1013D3-0545-DF11-B2D2-90E6BA19A238.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-824FE51D-DD44-DF11-B852-90E6BA19A21C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-8272D173-2C45-DF11-B5F2-E0CB4E1A117D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-8C3E6A2C-0A45-DF11-B5C2-90E6BA442F2B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-9032494A-A145-DF11-8A69-0030487CDAC2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-905E4B67-FC44-DF11-9AEE-003048D29312.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-942716B7-4645-DF11-920A-E0CB4E19F972.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-9452FCA7-4E45-DF11-969F-90E6BA19A203.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-94A21BED-3A45-DF11-8DBC-E0CB4E1A115D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-96219679-F444-DF11-B489-90E6BA442F0F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-9C59E0C9-3945-DF11-BD04-90E6BA0D0998.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-9E29A959-4145-DF11-8558-003048D2910A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-A0FAFEB4-1245-DF11-AEE0-90E6BA442F10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-A81C8578-F444-DF11-BE33-001EC9D7F68B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-AE6B0CC5-3945-DF11-9228-90E6BA0D0988.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-B209837D-2C45-DF11-BC29-90E6BA0D09B3.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-B2CF5AA1-F244-DF11-99B0-90E6BA19A25E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-B2DCB3C6-3945-DF11-A653-E0CB4E19F973.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-B49039E5-5245-DF11-A28A-90E6BA19A226.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-B65AFC4F-1345-DF11-93A2-90E6BA442F27.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-BA39BB44-5945-DF11-ADDE-90E6BA442F05.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-C20D60F1-D144-DF11-A0F4-90E6BA442F0F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-C469F378-F444-DF11-8445-90E6BA0D09CA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-C487069D-3A45-DF11-98E3-0030487C6A2C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-CA025883-2C45-DF11-9BC8-90E6BA19A24A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-CA102C23-5545-DF11-9D38-90E6BA19A25A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-CA97B8DD-4045-DF11-9E01-90E6BA0D09AC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-CC2CE65D-0B45-DF11-A81E-E0CB4E1A1189.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-CE5C655A-4E45-DF11-8344-E0CB4E19F958.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-D424B666-3745-DF11-AC2A-90E6BAE8CC13.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-D8CFB086-D744-DF11-9EDF-90E6BA442EF8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-DC5F99AB-4E45-DF11-B1D8-E0CB4E19F96B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-DCA291E3-3A45-DF11-B975-90E6BA442F28.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-DEB3143D-0A45-DF11-A731-0022198F5B49.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-E6E17622-5545-DF11-B202-001EC9D7FA10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-EA7173E9-2045-DF11-AF13-001EC9D81D54.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-EEEB8741-4F45-DF11-BC29-90E6BA19A226.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-F239E90C-4E45-DF11-A301-90E6BA442F33.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-FE686E88-F444-DF11-BE59-001EC9D8D085.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJets/TrileptonPatTupleMC-V05-03-03-FE7B301B-DD44-DF11-9E50-E0CB4E1A1195.root',
)))
