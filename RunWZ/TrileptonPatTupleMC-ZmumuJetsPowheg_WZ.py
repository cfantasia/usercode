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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZmumuJetsPowheg_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-0053E3C4-6162-DF11-B4D2-001C23C105CA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-024155CF-6362-DF11-8319-A4BADB3D004C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-048B87CD-6660-DF11-9C2C-0015178C4D70.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-08043D09-6562-DF11-844E-A4BADB3D00FF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-0A4B36BE-7E60-DF11-9B4D-001C23C105CF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-0C8BBFA6-6E62-DF11-BC1C-0024E8768C16.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-0CCBF5A1-7062-DF11-8276-0024E876841F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-0EE5AF94-5460-DF11-98A2-0024E8767DA0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-10973F8A-6462-DF11-9077-0024E8767D04.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-125E41A6-6E62-DF11-8432-0015179ECB84.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-18930E06-F262-DF11-89BA-001F29652580.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-1EA4F74F-7360-DF11-B89D-00237DA1FBE8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-20E6E6C8-6562-DF11-BD59-001EC94BA3B8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-26D8989A-8260-DF11-9BD0-001C23C0DF83.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-28AC89FB-5A60-DF11-A51B-A4BADB22B465.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-2AF9FCEA-7962-DF11-8183-0015178C691C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-3051D890-6362-DF11-8261-001E0B62EBB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-3427D4F8-6662-DF11-BC12-0026B93B1193.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-34990274-5760-DF11-9548-001C23C0DF83.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-36C59360-6560-DF11-88EC-A4BADB1E6F7A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-3E97C720-6060-DF11-9F18-001EC94BE81B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-3EB88794-9562-DF11-B148-0026B93785F5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-46090399-8260-DF11-83E8-0024E8769B39.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-465C1797-9862-DF11-924F-0024E8768D68.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-46BC4EF2-B462-DF11-8FE0-0015178C4D14.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-4A425C0F-6562-DF11-A0A5-001EC94B4F59.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-52EEC3BB-8862-DF11-A084-001D0967D652.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-5A30C20D-8C60-DF11-9D06-001F29657434.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-5E257809-7162-DF11-AED3-0024E8768D34.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-5E84E581-9562-DF11-BB49-001EC94BF99E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-60D23BFE-7460-DF11-BC27-001D0967CFC7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-626B0861-6262-DF11-B186-003048678A44.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-62B3361D-7162-DF11-A484-A4BADB3CEBCE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-6A6B5468-6162-DF11-A3AD-001EC94BFDD9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-6ED849C5-5E60-DF11-B13B-001D0967D03A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-709001D4-EA62-DF11-AD8F-001D09FD0D10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-74738950-6462-DF11-A19C-A4BADB3CF208.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-74E78E36-7A60-DF11-B43D-001EC94BE9F4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-7AB32D74-7B60-DF11-9648-0024E8768C3D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-7E0B6465-1C64-DF11-821A-A4BADB3CF8F5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-80AA7E6A-9962-DF11-BE6E-0024E8768D5B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-80E6D9AF-5F60-DF11-8C4E-001C23C0E208.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-868A229A-5F60-DF11-BE72-001EC94BA3B8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-8AE33A2B-6860-DF11-AFB7-001EC94B442B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-8C5C0D0E-5B60-DF11-A2DF-0026B937C6C9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-90244D91-8060-DF11-8486-00151796D464.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-90410F2B-6562-DF11-B265-001EC94BF99E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-924D98DA-7060-DF11-97FD-0019B9CAF827.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-94D6EEEA-5B60-DF11-9108-A4BADB22B39F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-9839464F-3663-DF11-A5AA-001E0B62B950.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-9ADCDE06-6562-DF11-9472-0026B93A2144.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-9E650E9F-1963-DF11-B7CE-0024E8768D1A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-A25F6CED-8A60-DF11-849D-A4BADB1C0EF3.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-A4445A95-5460-DF11-9EFD-A4BADB22A680.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-A49CF0BF-6662-DF11-B15B-0024E8768D0D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-AADA370F-6B60-DF11-9E99-0019B9CB030F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-AC151970-6762-DF11-8A0A-001EC94BA3CC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-AC8B7297-9862-DF11-895C-0024E87683D1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-ACC7298D-6660-DF11-9A7C-00E0814296AA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-AEBB23EC-8A60-DF11-8462-A4BADB1C5E28.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-B262BB83-1C63-DF11-A4D9-A4BADB3D004C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-B4E063BD-8060-DF11-82A9-0019B9CABE75.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-B6A24C5D-7060-DF11-ACED-001F296544A8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-B82D6E73-7E60-DF11-9FF1-001F29659484.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-BA2310E1-6062-DF11-9293-A4BADB1CF89C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-BE34D1CD-6162-DF11-890A-0015178C4D04.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-BE496C82-3363-DF11-AFB6-A4BADB3CF272.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-C68DC2FA-7060-DF11-8BEB-0019B9CAB9CD.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-C82139D0-1C64-DF11-97D4-A4BADB3CF8F5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-D06675D0-7860-DF11-B47E-0026B93A0356.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-D21A4219-1D64-DF11-A4EC-001D09FD0D10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-D4D8F6DA-6062-DF11-B9C5-001D096B0E2C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-D6D80C49-6762-DF11-BD8D-001EC94BF09F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-D84931CE-7960-DF11-8458-001D0967D512.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-DC03A1AB-6262-DF11-8956-A4BADB1E79A5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-DC910724-7A60-DF11-B05E-001C23BED6A2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-E07B97DE-8062-DF11-B585-0024E8768412.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-E2C33253-7E60-DF11-AFFE-0024E876885A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-E41932A6-5660-DF11-B2CB-0024E876884D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-E4F229C4-8A60-DF11-BEDC-A4BADB1E6B36.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-EAD6530F-6162-DF11-A3CE-0026B937C6C9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-EC22039F-6562-DF11-A99E-0019B9D96FC5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-F0888524-6262-DF11-A836-001C23C102BB.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-F29F7AE7-7460-DF11-928E-0024E8768BEF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-F4A6969A-9562-DF11-8192-00E08142962E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-F6F629C9-7E60-DF11-B9CB-0019B9CAF827.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-FAC3BC84-8260-DF11-8E1B-0024E87682B3.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZmumuJetsPowheg/TrileptonPatTupleMC-V05-03-03-FCD6E07C-9562-DF11-9C9A-001EC94BA3D1.root',
)))
