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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/DileptonPatTupleMC-WenuJets_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-045E9064-BB48-DF11-AFBB-00215E2217A0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-0A1DDD21-9748-DF11-9F02-E41F131816C4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-0CAD22B0-B848-DF11-B582-00215E93D738.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-0CE605ED-C348-DF11-A0F1-00215E2220A0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-10584B4D-9E48-DF11-BE51-00215E21D6DE.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-12474856-C548-DF11-833D-E41F13181D30.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-140726CC-B448-DF11-93F1-00215E93ED9C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-146E893B-BC48-DF11-81E4-00215E21DCD8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-16055122-C548-DF11-A61A-E41F13181CA8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-18D68827-9748-DF11-AD76-00215E22218A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-1A167E70-B748-DF11-B428-00215E21DC7E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-1E5CC82D-BB48-DF11-AA42-E41F13181A6C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-2E567EF9-B148-DF11-8D64-E41F1318168C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-3682085D-B348-DF11-B254-00215E21DB76.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-36FB5625-A648-DF11-B0B9-E41F131816B4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-3A431279-AF48-DF11-9EA7-00215E2208EE.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-3AB1BC30-C148-DF11-875F-00215E93E7DC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-3E5629F3-AC48-DF11-A91F-E41F13181A04.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4049F87F-9D48-DF11-BA7F-E41F131811A8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4656E673-B748-DF11-B5EC-00215E221FB0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-48575E80-C148-DF11-911B-E41F13181C30.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4A6B990E-BF48-DF11-989A-00215E2217CA.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4AA7AFFC-A648-DF11-A933-00215E21D540.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4C7070B4-A448-DF11-A3DB-E41F1318152C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-4CC09614-9C48-DF11-83EC-E41F131816A8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-50A9099D-B848-DF11-8602-E41F13181D40.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-544349C3-A548-DF11-8358-00215E2211B8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-545EE11C-B248-DF11-B600-00215E21D588.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-5C1822B5-AD48-DF11-A601-00215E21E1C4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-5EAB3A05-B048-DF11-B280-00215E22278A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-60CFBBB1-A748-DF11-BADB-00215E22185A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-60E7955F-C148-DF11-B58D-00215E21D870.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-62B2D97B-C148-DF11-8A83-E41F13181D00.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-62DC52AD-9C48-DF11-97C1-00215E22185A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-64933AED-B148-DF11-A8A3-E41F13181A88.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-701973E0-AD48-DF11-867C-E41F131819F8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-78FB87DF-B948-DF11-B499-E41F131816A8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-80225E43-C448-DF11-99CE-00215E221098.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-8077BA3C-BA48-DF11-AB61-00215E21D540.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-82EE1492-B948-DF11-8C39-00215E22190E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-84E76817-A948-DF11-9F56-E41F13181460.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-8AB99B79-B448-DF11-BA3D-E41F131816B4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-9001E38A-BD48-DF11-818B-E41F13181D28.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-907ED42B-B348-DF11-A03E-00215E2220A0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-9459FDF2-9D48-DF11-AC51-00215E2222E0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-96ACF819-A948-DF11-BF24-E41F13181460.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-96DCA34D-AE48-DF11-8D1E-E41F1318156C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-98D2D618-A948-DF11-A9BD-E41F13181D30.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-9EC1D862-C248-DF11-BDDA-E41F13181A00.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-A646E8B2-9E48-DF11-A422-00215E222316.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-A897B6FC-AB48-DF11-985D-00215E22278A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-AA16B498-B448-DF11-9C28-00215E21D61E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-AC3DB481-C048-DF11-8953-E41F13181018.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-ACE19D77-B048-DF11-B789-E41F13181398.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-B018815B-C248-DF11-B37E-00215E21EBCC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-B08CD7A2-9C48-DF11-A73E-E41F131815CC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-B6693CC5-B448-DF11-8681-00215E222790.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-BC429D2A-A648-DF11-AC5F-00215E22122A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-BED8279D-B648-DF11-A07B-00215E21D4D4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-C09B254C-B848-DF11-8817-00215E221FB0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-C444F507-CB48-DF11-A8EE-00215E21D732.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-C65DC49B-B648-DF11-820C-00215E21D82E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-C81653EE-AB48-DF11-A5C7-E41F13181D40.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-C8C4A747-AA48-DF11-96D7-00215E222382.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-CC741305-AA48-DF11-B790-E41F13181B0C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-CED4AA92-A048-DF11-A497-00215E22190E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-D014508D-B448-DF11-976B-E41F131815A4.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-D20309B1-C848-DF11-8789-00215E21D7C8.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-D6371E5D-C048-DF11-8007-E41F13181A70.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-D67DE657-9E48-DF11-9816-00215E21D72C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-D69A553E-AE48-DF11-8E94-00215E22200A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-E0CFA64E-AE48-DF11-B6E8-00215E2216AA.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-E26FEBA3-9A48-DF11-9126-00215E21D462.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-E2F2D87C-AB48-DF11-80D1-00215E2219E6.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-E2FB7CEE-C348-DF11-993D-00215E93E7AC.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-E4E20F11-B748-DF11-B67B-00215E222316.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-ECC05FF6-9648-DF11-857A-00215E21D870.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-EE2AD0D3-AA48-DF11-92B0-00215E21F214.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-F27F902B-C148-DF11-82E2-00215E222790.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-F653E4B8-BC48-DF11-A78F-00215E21EB7E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-FA06BDE4-B548-DF11-8AC9-00215E21D9AE.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-FA229D5A-C648-DF11-AD49-00215E222226.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WenuJets/DileptonPatTupleMC-V05-03-03-FC449FC8-AA48-DF11-96CE-E41F1318170C.root',
)))
