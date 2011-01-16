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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-WlnuJetsMadgraph_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-02E01C3F-0B85-DF11-A897-001D0967DA3A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-042D79F2-E884-DF11-8A59-00151796D730.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-049EEEAF-5D85-DF11-86C3-00151796D894.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-06D71AFD-DB84-DF11-A18D-001D0967D689.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0A3A20E0-5E85-DF11-88F5-0015178C68A4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0ACB93D1-6385-DF11-8FEA-0026B94D1AC8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0C28008C-7485-DF11-BDBB-0024E8766379.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-0E1E39A1-E384-DF11-A9A7-0026B94D1AA1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-105A6F3B-0285-DF11-AF81-0024E87680C0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-1286BD0B-4785-DF11-A3FE-0024E876998C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-189E41E8-D284-DF11-B4C2-0024E876A83B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-1A9B45A8-5F85-DF11-AF49-0024E8769B53.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-1AE471EA-7585-DF11-9797-0024E8766379.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-20E8FBAD-0085-DF11-896B-0015178C6BE0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-24187649-E484-DF11-A608-0024E8768299.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-262BEC3D-3C85-DF11-A08B-0026B94D1A94.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-2823CB6E-6485-DF11-B335-0026B94E27F0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-2CFB39C5-DC84-DF11-8F47-00151796D80C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-2E9C7279-6A85-DF11-A74B-0026B94D1AEF.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-341A1A65-7185-DF11-A57F-00151796C1D0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-365275AB-F584-DF11-AA92-0026B94D1AA1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-3ECF174B-7485-DF11-BEB9-00151796C1A4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-4066FD48-DF84-DF11-9E59-0015178C486C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-406A1A17-5E85-DF11-B600-001D0967DAC1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-442FF66E-1185-DF11-8C60-0026B94D1B30.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-469DC187-EA84-DF11-8BE5-0024E86E8D8D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-4CC64468-2486-DF11-AA90-001D0967DA76.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-4EE5EA16-5585-DF11-91E4-0015178C4DBC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-50D5FEE3-5E85-DF11-B5E6-0026B94E280A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-54085FFB-F684-DF11-AF10-0015178C4890.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-5696B321-5585-DF11-B667-00151796C1C4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-56FDA55E-D384-DF11-8A8A-00151796D6D4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-58CB91D6-7185-DF11-81C5-00151796C0E0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-58D21A89-E484-DF11-A0EC-00151796C47C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-5A23BDAE-0085-DF11-BD40-0024E87683C4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-5A894FA7-5F85-DF11-B593-00151796C184.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-5E5A7C79-1385-DF11-8539-00151796D67C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-646BF49C-DE84-DF11-BDE4-00151796C458.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-64DC4C3E-3C85-DF11-8B46-0026B94D1B30.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-68F02844-0B85-DF11-A668-0015178C6BD4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-6C5F4109-6A85-DF11-A126-0015178C65F4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-6CECED87-E484-DF11-9287-0015178C6744.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-740CBA6C-6A85-DF11-B19E-001D0967DA76.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-78703093-DE84-DF11-96F2-001D0967DF0D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-7A2E5069-0085-DF11-ADC5-0024E876824B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-7C8360EE-5E85-DF11-AE73-0024E8766379.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-7EBFCC6F-6A85-DF11-A106-0024E8768258.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-8042100D-D384-DF11-A895-0015178C48FC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-84B96DBE-8485-DF11-BC5F-0026B94D1AA1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-8A04E488-E484-DF11-A01F-0015178C6ADC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-8C55BBEB-0685-DF11-A532-00151796D6EC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-8C7A590C-5585-DF11-9838-001D0967404B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-8CDDB4A7-3C85-DF11-9838-0024E876A7FA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-90C25ACC-5B85-DF11-A63A-001D0967D9F4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-927FB2DB-F484-DF11-845D-00151796C1BC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-928BF0D6-D284-DF11-A5EC-0024E8769AF8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-94E51F04-4785-DF11-BD73-00151796C0EC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-989E149F-F584-DF11-B4D3-0024E8768101.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-9CF3BA8D-8485-DF11-A3E5-0015178C6ADC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-9E72A6A3-7585-DF11-8422-0024E86E8D4C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-9EB3A0F9-E984-DF11-A0D9-0024E87687CB.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-A6862BA9-4C85-DF11-B283-00151796C1B0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-A6A22D28-E784-DF11-B150-0015178C48B8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-AEDE4880-7A85-DF11-A80F-00151796C058.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B2BD4D0D-4785-DF11-B905-001D0967D9E5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B2EB60EC-0385-DF11-B462-001D0967DF53.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B87726D5-6385-DF11-A7B8-001D0967DFB2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-B8B9EC79-E984-DF11-8EDA-0015178C0224.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-BC279833-7B85-DF11-B1D2-0024E8768819.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-BCF37FD3-D284-DF11-A330-0015178C4890.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-BE071FEE-4885-DF11-9720-0015178C48B8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-BECAFE11-EC84-DF11-8A8B-0015178C4CE8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-C465DAA3-5F85-DF11-BEFD-001D0967D03A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-C4CB67F3-0385-DF11-981A-0026B94D1B3D.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-C6FA6DB0-5F85-DF11-AB51-0015178C4CB0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CAE1BC7D-F984-DF11-AE7F-00151796D59C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CC9BAC06-E384-DF11-AE82-0024E876A7ED.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CE28F4A3-0585-DF11-AA7C-0024E8768258.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CE342CE8-D284-DF11-A23E-0024E876A83B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-CE45FFDC-4485-DF11-B449-0024E8768867.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-D22CFCDF-5E85-DF11-AC29-0015178C64AC.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-D499EB4C-E484-DF11-8028-0024E8766386.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-DABB7E34-3C85-DF11-9AF1-0015178C4B54.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-DC3A72C6-E084-DF11-918B-001D0967D25B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-DC44634A-0285-DF11-8CB0-001D0967CF8B.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-E279A71E-5485-DF11-A247-001D0967D9F4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-E2F21710-4785-DF11-88C9-001D0967D337.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-E81B5EDF-7585-DF11-8C6C-0024E876A814.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-E8C7580D-4785-DF11-B831-001D0967DEF9.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-EA65587E-E184-DF11-8AC3-001D0967DA53.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-EC4AA3BD-0685-DF11-9FAF-001D0967D314.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-EC93F959-7F85-DF11-8530-0015178C66B8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-EEB04AE2-6385-DF11-AC7B-0015178C6A5C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-F0EB0D12-DF84-DF11-9FCD-0024E87683F8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-F47621C4-E984-DF11-B79A-001D0967CE69.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-F60364CA-7585-DF11-BE61-0015178C4878.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-F6A12B3A-4B85-DF11-9937-00151796D4E8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-F6F10C78-1385-DF11-B6BE-0015178C4874.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-WlnuJetsMadgraph/TrileptonPatTupleMC-V05-03-03-FE91FCBD-7185-DF11-AFC2-001D0967D6E8.root',
)))
