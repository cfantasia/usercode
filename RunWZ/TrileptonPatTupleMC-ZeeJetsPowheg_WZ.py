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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZeeJetsPowheg_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-00BDDD88-7260-DF11-9F87-001E0B626A94.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-086BD033-2460-DF11-9ED6-001F2965D276.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-0A7C04F1-5160-DF11-9345-001F29651428.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-0CC7940D-D15F-DF11-928B-001D0967D5B2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-169125E7-FB5F-DF11-8831-0024E87680DA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-18EDAB24-D05F-DF11-864D-0024E87663E1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-1AED0D12-3860-DF11-8FC4-001C23C0DF83.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2009D813-FF5F-DF11-B0C3-001D0967E061.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-205FF34D-3560-DF11-A5E7-0024E8768CB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2202C38B-4660-DF11-A5E4-00151796D428.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-22CE2B1A-0160-DF11-AFA3-0024E8769A01.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-262C47DF-6860-DF11-93BF-A4BADB3D004C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-28DA4790-4360-DF11-9B55-0019B9CABE2A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2A47C2E3-0660-DF11-8D59-00151796C14C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2A97EC1C-3560-DF11-B383-A4BADB1E6031.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2CBFC540-3B60-DF11-B170-0024E8768BEF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-2E4FA0EB-FB5F-DF11-920F-0024E8769B7A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-32E938F2-3160-DF11-ACB7-001D0967DD0A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-36168EF9-3A60-DF11-BCD7-A4BADB1E6F7A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-362C925B-3260-DF11-B50D-001E0B8D786C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-368C411C-2B60-DF11-A583-A4BADB3CF260.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-3C5F8326-6060-DF11-818B-001EC94BA114.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-40190553-0360-DF11-9F4C-A4BADB1C5D42.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-424FF18A-3860-DF11-AEE6-0024E8767DAD.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-48C74A71-D05F-DF11-9A03-0024E87683B7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-48FA98BE-6060-DF11-8DBA-001E0B8D786C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-4E6ACF1A-4E60-DF11-9748-001C23C0D109.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-4E8DF2EF-0F60-DF11-AF05-A4BADB3CE8FE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-54EA8349-6260-DF11-B029-A4BADB3CF260.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-584C6854-3560-DF11-8381-0024E8767D45.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-5ADE313D-0360-DF11-8277-0026B939004D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-5C1582D9-3260-DF11-ABA6-0026B94E28A6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-602126C6-6E60-DF11-89F4-001E0B62D9AC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-6056535F-0560-DF11-AEB7-0024E86E8CFE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-6276051F-2B60-DF11-B369-00221983E092.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-6408637F-2460-DF11-B1B0-00221952AA1F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-64C76156-2B60-DF11-AA80-001EC94BFDB6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-662CD279-7160-DF11-BE7B-0024E8768D41.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-687046C2-FB5F-DF11-918C-A4BADB1E6796.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-68981E3D-3060-DF11-8887-A4BADB1C5D42.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-6A63D250-5F60-DF11-91BE-001F296534E6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-6A90B50F-0460-DF11-B382-0024E87680DA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-70D6D48A-5460-DF11-80CA-001D0967DB5C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-72143933-FE5F-DF11-8972-00151796D534.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-72D8848D-3960-DF11-BD32-A4BADB1E79A5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-74D6063D-D15F-DF11-B365-0024E86E8D0B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-76EB3310-6460-DF11-A8A5-0015178C6BE0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-780DDFD2-3660-DF11-9EA4-0026B937C6C9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-7C865CCB-3960-DF11-A1F6-0026B93AA8FF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-7ED96343-4C60-DF11-90F1-00151796C080.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-8066C5EF-0460-DF11-85C5-0024E8768C8B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-8886F57F-3560-DF11-80CA-A4BADB3CE43E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-88D2A9BE-0F60-DF11-82A7-A4BADB1E6055.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-9032DEF5-0460-DF11-BB13-A4BADB1E6F7A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-96636F10-CD5F-DF11-8A47-0024E87687D8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-9849B863-5760-DF11-8CAE-0019B9CACEF7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-9CE4072A-D05F-DF11-A470-0024E8767D5F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-A04743CB-0460-DF11-B1DF-0024E87680A6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-A223CC77-3C60-DF11-B7DC-001C23C105F2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-A6CE13E3-5260-DF11-876A-A4BADB1E763D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-A855C0F9-7E60-DF11-94C7-001F29659BB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-AAAD3926-D05F-DF11-9294-0024E8768272.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-AC63B976-4260-DF11-95B3-001D0967C464.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-AEA11AB0-D15F-DF11-9E9F-0024E87680DA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-B4380683-3960-DF11-B0A0-001EC94BA169.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-B48F356C-6D62-DF11-93AC-0024E8769B2C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-B8A58515-7A60-DF11-A8C8-001E0B8D7834.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-BA976B00-3360-DF11-9206-001F2965D442.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-BC1EE183-2460-DF11-BF96-001E0B62EBB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-C0F46656-0160-DF11-94CD-0026B937D37D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-C21981F7-5F60-DF11-9AD7-001F2965F212.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-C642017C-2460-DF11-806C-A4BADB3CF3B5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-C83FCDD2-1660-DF11-9E97-0019B9CB01A7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-CA14EE86-2960-DF11-AD03-0024E87682A6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-CE3DF0EC-0260-DF11-B4CC-001EC94B4EF5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-D00806E3-5160-DF11-A86F-001E0B8D7834.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-D02F2529-7060-DF11-A269-00215AA5B7DC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-D285A27C-2460-DF11-A8E6-A4BADB3D004C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-D696B89F-0360-DF11-BBB0-A4BADB1E72B0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-D6F05E5B-0B60-DF11-AE66-0024E87687E5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-DC0CF693-2360-DF11-A5E6-00237DA1FBE8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-DEAC4929-7060-DF11-9C1D-A4BADB3D004C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-E040F0B3-0360-DF11-9925-0026B939004D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-E2CEA567-3C60-DF11-9130-0024E876636C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-E6BC02DB-7460-DF11-ACBE-001E0B8D7834.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-EC76E6A9-3960-DF11-A28F-00151796C1C8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-F08DF35A-0160-DF11-8261-0026B937D37D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-F2440DB8-3060-DF11-BFD4-A4BADB1E763D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-F2768BA3-1260-DF11-BEFF-0019B9CACF1A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-FA041C22-CD5F-DF11-B7EC-0024E876842C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-FAA8714C-3560-DF11-B24B-001D0967C8D3.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-FC7A9C43-0360-DF11-89C2-001C23C0C7AB.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZeeJetsPowheg/TrileptonPatTupleMC-V05-03-03-FE384DB3-3660-DF11-8C47-001C23BEBF16.root',
)))
