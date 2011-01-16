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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/DileptonPatTupleMC-ZeeJets_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-02EA248D-7646-DF11-A1F0-00E08178C129.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-0495E4E3-BB47-DF11-9471-0025B3E06466.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-061E80F6-7545-DF11-A736-003048D47A24.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-08F33214-9646-DF11-8E00-001A64789D80.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-0E67D33A-C247-DF11-A76A-002481E150FC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-0E996701-7846-DF11-9CC6-00E08178C0FF.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-106CC448-4145-DF11-88B0-002481E14FCA.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-12667AB8-9646-DF11-8C0B-003048D4603E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-145430DC-9546-DF11-9175-00E081791737.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-14D47047-9746-DF11-8610-00E08178C12B.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-14D4E2DC-5E45-DF11-A74A-0025B3E05CF6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-16364838-2645-DF11-A9C6-003048D45FF6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-181661BD-9B45-DF11-9AA7-003048D45F2C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-18AAD440-5146-DF11-959F-003048673F7E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-20B71488-ED44-DF11-BAD4-0025B3E05D5C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-20F03FB5-9646-DF11-AC13-00E081791847.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-226A4150-7E46-DF11-A47F-0025B3E064F8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-26AE9EFC-7746-DF11-98BF-00E08179178F.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-2ED1A48B-7646-DF11-ADF4-003048D45FB6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-3212F730-D14A-DF11-8783-0025B3E064F0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-324A15BA-9646-DF11-B9B4-003048D47716.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-342255BD-E246-DF11-8B86-003048673EA8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-3871B9AB-4746-DF11-8D99-00E08178C111.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-3C8E402F-5945-DF11-9621-003048D45F76.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-3E3A6297-5C46-DF11-BB6C-003048D476F0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-4C5089BE-5E45-DF11-965F-0025B3E06698.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-4E2D067B-B747-DF11-86B6-002481E14D46.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-4EAB84F8-6448-DF11-B4BD-001A64789D60.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-50162EC6-ED44-DF11-9A30-00E0817917A3.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-52887BBB-2245-DF11-B7E2-002481E15000.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-5618A7E6-7746-DF11-AD0C-002481E154EC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-5C5C01F9-6448-DF11-97DF-001A6478A7C4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-5EDEBE07-9A45-DF11-9A54-0025B3E05DAC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-607D4577-5246-DF11-83FA-001A6478705C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-64A2D065-9646-DF11-8C79-001A64789E4C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-64E049E2-BB47-DF11-9EC8-003048D479F2.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-68CF3AE0-9A45-DF11-B96C-0025B3E06658.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-6E95EA2C-9B45-DF11-B513-003048D477B6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-724D4FE5-5C46-DF11-A62E-003048D476FC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-72946728-7946-DF11-B17D-001A64789D74.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-784770A4-EC44-DF11-97E8-003048D46084.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-78E0BFBB-EC44-DF11-A6BD-001A6478ABB4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-7CBAC122-B747-DF11-8042-002481E14E30.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-8467176B-8445-DF11-9EA4-003048D45F24.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-84D4C40F-4C46-DF11-8F7B-001A64789D18.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-866DBD53-B447-DF11-831F-003048D4770C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-86DAC6F8-7646-DF11-B425-003048D460B2.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-8E1CF637-8D45-DF11-ABDF-003048D46118.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-901E53C7-ED44-DF11-A944-00E0817917F1.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-90EB42F6-8845-DF11-B705-003048D479D4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-92AC68D9-5C46-DF11-9098-003048D46112.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-92B03959-9A45-DF11-84F0-003048D479E0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-94F07D96-9E46-DF11-B354-003048D46038.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-964BD4B9-EC44-DF11-8353-003048D46090.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-968A6537-2645-DF11-948B-0025B3E05D34.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-98472637-8D45-DF11-97F6-003048D476B4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-9E96883C-4846-DF11-A256-00E081791805.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-A255D043-B747-DF11-AE48-002481E14FBA.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-A412AA8B-8845-DF11-9D6A-003048D47A54.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-A4DAF0B4-EC44-DF11-AD4A-002481E14E58.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B00D6C46-8646-DF11-AE95-00E08178C0EF.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B0852554-B447-DF11-A3B7-00E081791793.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B26181FB-2545-DF11-9E3C-0025B31E3C06.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B4AB36C9-4B46-DF11-9A70-001A6478945C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B6116499-1945-DF11-980F-002481E150EE.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B62B6D50-4D46-DF11-B4C5-003048D460C0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B68D873A-C247-DF11-B4F1-002481E14F8C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-B8ED4F01-7846-DF11-801D-001A64789488.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-BC9208FC-5C46-DF11-BD7F-002481E14D84.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-C029C157-5346-DF11-BD82-00E0817918A5.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-C0D3D4DE-B747-DF11-931B-003048D47A08.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-C44F97FE-7946-DF11-A80A-003048D45F3E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-CA1EA330-5346-DF11-A02E-003048D46024.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-CC49A924-B747-DF11-B5B2-0025B3E05BC6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-CCEA7372-0A4A-DF11-904D-00E08178C16B.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D074A8AC-2B45-DF11-A13E-003048D460C4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D20CB36E-8246-DF11-A276-00E081791767.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D49A54C1-7646-DF11-8CE7-003048D460AC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D8DB85DC-5E45-DF11-8025-003048D476C6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D8F08F1F-7946-DF11-BC1F-003048D46272.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-D8FEAA69-7946-DF11-9A41-003048D479D6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-DC97E9D2-8E46-DF11-9AF1-003048D45F60.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-DCEF83B4-7946-DF11-9A1A-003048D47A62.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-E0075C0F-9A45-DF11-AA6D-003048D45F2C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-E4496EE3-BB47-DF11-BCE9-003048D45F52.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-E64EB91C-9646-DF11-B598-003048D477BA.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-E6ED5303-6246-DF11-88C6-001A64789E00.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-EA78F8F9-8845-DF11-8624-00E081791801.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-EE49D299-5C46-DF11-AFE7-001A6478AB7C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-EE674A21-9E46-DF11-A86A-002481E154EC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-EE98DE8B-8845-DF11-8DB7-003048D47720.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-F6339A99-5C46-DF11-9E07-003048D45F52.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-F85F3604-9C45-DF11-A524-0025B31E3D32.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-FA25F6D7-9B49-DF11-ABC8-003048D47A08.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-FE4C79A9-4746-DF11-BE56-00E081791803.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-ZeeJets/DileptonPatTupleMC-V05-03-03-FE62C4D6-7746-DF11-970F-00E0817917A1.root',
)))
