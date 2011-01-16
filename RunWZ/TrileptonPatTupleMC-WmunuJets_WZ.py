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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-WmunuJets_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-06A6BF65-3E7D-DF11-80F8-0024E8768C64.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-0815748E-3B7D-DF11-BCBA-0024E8768C23.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-083A6CD7-347D-DF11-8FFA-00151796C100.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-0EF1AE64-3E7D-DF11-A9E8-0024E8769B46.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-16E947F0-327D-DF11-9703-0024E8768217.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-1A24CFB7-3B7D-DF11-8098-001D0967D91D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-1C81ABD2-357D-DF11-AE25-0015178C4A78.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-1E9EFB8D-3D7D-DF11-8E34-0024E876994B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-20A2F745-337D-DF11-96BE-0024E876824B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-2248FD69-3E7D-DF11-841B-0026B94E288C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-241E6F08-2E7D-DF11-9C7C-0015178C6B78.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-265FBD61-3E7D-DF11-B944-00151796D698.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-26D9BA9F-297D-DF11-8B98-001D0967DC1F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-283627D7-447D-DF11-9262-001D0967DF53.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-283FB069-3E7D-DF11-A2B2-0024E876827F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-2AED06D6-347D-DF11-BE17-00151796D918.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-2CAB4682-337D-DF11-9F87-0024E876A862.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-3056AE22-3B7D-DF11-8066-001D0967DF26.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-30CF9782-327D-DF11-ADF0-00151796D7C0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-34C3B908-2E7D-DF11-80B1-0024E86E8DA7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-3A512C01-2A7D-DF11-8ED8-001D0967DB11.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-3C4728FE-297D-DF11-BB3A-0015178C4AE8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-3E67A201-3F7D-DF11-9EA4-0024E87687D8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-40CC0268-3E7D-DF11-9BB8-0024E86E8CF1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-422BC49B-297D-DF11-BB7A-001D0967D639.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-4652B7D6-347D-DF11-B66F-0015178C4C5C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-4A212332-687D-DF11-8C65-0024E8769965.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-4A5C7512-327D-DF11-8750-00151796D8B0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-4AA92968-3A7D-DF11-AEDD-0024E8767D52.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-4EA2C9F9-297D-DF11-87C0-00151785FF78.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-507FA5D4-347D-DF11-997F-001D0967D5D5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-52151FD1-447D-DF11-A535-00151796D6F0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-54B870D9-3B7D-DF11-935A-00151796D5AC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-54DCC4EC-327D-DF11-B4D4-0015178C4A78.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-58AF74FA-3E7D-DF11-956A-0024E87680F4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-5A09C800-2A7D-DF11-A005-0024E8768BD5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-5A5CA496-2D7D-DF11-8157-0015178C6728.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-5ABE77D1-357D-DF11-9FE4-001D0967D0DF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-5CC8895D-687D-DF11-BB14-0024E8768840.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-620E13A9-337D-DF11-902B-0024E8767DA0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6413AE94-2D7D-DF11-8B35-001D0967D7DD.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-666D7F02-337D-DF11-B4F0-0024E8768819.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6840B681-347D-DF11-AB1C-001D0967DD96.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6AA3A976-E67D-DF11-B723-00151796D698.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6E0CEA04-2E7D-DF11-9DCA-00151796C058.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6E10706A-3E7D-DF11-ABE3-0024E8769B2C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-6EAD6564-3E7D-DF11-AA9D-0024E8769B87.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-746D1800-2A7D-DF11-8061-001D0967C085.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-764D2A40-3C7D-DF11-898C-0024E86E8D66.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-76B96C5C-3A7D-DF11-9B93-0024E8766393.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-7A571708-2E7D-DF11-91C5-0015178C1804.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-7C739367-3E7D-DF11-A5E8-0024E8768C09.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-7CC587F8-3E7D-DF11-9B25-0024E8768D34.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-7E1E8FD7-347D-DF11-98BC-0015178C67C8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-82BAFC16-2E7D-DF11-BCF6-0024E876885A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-881F2D08-387D-DF11-8036-00151796D674.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-885FA7E0-3B7D-DF11-A0BA-0024E86E8D66.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-8C9B03F6-3E7D-DF11-B9DD-0026B94D1AD5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-8E34328F-3B7D-DF11-AA9F-0024E8768C4A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-8E5E24F4-327D-DF11-98D5-001D0967C649.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-94177C0F-2E7D-DF11-A203-0024E8769B87.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-96DEEB4D-2A7D-DF11-8223-0024E8768BEF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-98037D09-2A7D-DF11-827E-0024E876827F.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-98A04264-3A7D-DF11-848F-0024E87699E7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-9AD134DE-3B7D-DF11-A90F-0024E87680C0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-9C1A0081-327D-DF11-AB1B-0015178C48B0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-9E10F839-347D-DF11-95F4-0024E8768390.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-A0A1CC62-3A7D-DF11-93DF-0024E8766386.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-A2F341D0-357D-DF11-AED0-001D0967DC0B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-A4EEB8F5-327D-DF11-A3A6-0024E86E8D18.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-A64731FD-3E7D-DF11-B82C-0024E8769BA1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-A68EEF6D-417D-DF11-AA7F-0024E8766422.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-AA2694B2-397D-DF11-9319-001D09675427.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-AADC41A1-327D-DF11-A2A9-001D0967CE69.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-ACCBB863-3A7D-DF11-A30F-0024E8768299.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-AEDFBDF9-297D-DF11-8D00-0015178C646C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-B23F988E-3D7D-DF11-B89C-0026B94D1B3D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-B2782D07-2E7D-DF11-AF4F-00151796C0EC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-B63109BC-3A7D-DF11-8D9B-0024E8769B94.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-B8E56CD4-357D-DF11-9786-0015178C48E4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-BE162AFB-297D-DF11-B995-0026B94E280A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-C223D427-387D-DF11-B695-00151796C158.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-C258F7E4-3B7D-DF11-B797-001D0967DA3A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-C2E76C5D-417D-DF11-9F37-0024E87680C0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-C67E89DB-337D-DF11-957B-00151796C10C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-CC4358AB-337D-DF11-B364-0024E8769972.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-CE94C900-387D-DF11-8FC0-0015178C6B04.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-D0815A7F-347D-DF11-A228-001D0967D26A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-D234BFFB-397D-DF11-A80D-001D0967DFB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-D475AD5B-3A7D-DF11-A21D-0024E8769958.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-D830FC1C-3E7D-DF11-BB8C-0024E87663E1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-D86509A0-287D-DF11-94FD-00151796D67C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-DC2906A8-337D-DF11-BF98-0015178C4BE8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-DCBEB231-687D-DF11-B35E-0024E8768217.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-DE6D90A5-337D-DF11-B55A-0024E87680CD.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E0B9C1DC-3B7D-DF11-B7E0-0024E8767D38.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E4666530-347D-DF11-91E9-0024E8768453.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E6BA66D2-447D-DF11-BAF3-001D0967D2E7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E6C4FA71-3E7D-DF11-94D3-0024E8769B7A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E6CFE17E-677D-DF11-B339-001D0968F256.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E88C8BA6-2C7D-DF11-A0F4-0024E87687F2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-E8E1AFEF-327D-DF11-957E-0015178C4D3C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-EACB8870-387D-DF11-AC4E-0024E8768439.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-EC2C4CD5-347D-DF11-9807-00151796D910.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-EE11800C-387D-DF11-B568-00151796D9A8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-EE12DC96-2D7D-DF11-90C4-0015179ECBB8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-F0C3BADD-3B7D-DF11-87A9-0024E876820A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-F45D8964-3E7D-DF11-9AC9-0024E86E8D32.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-F8199B0C-387D-DF11-A839-0026B94D1B16.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-F8A6DCF1-297D-DF11-8847-0024E87699C0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WmunuJets/TrileptonPatTupleMC-V05-03-03-FC73393E-3C7D-DF11-B42D-0026B94D1AD5.root',
)))
