import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'GR10_P_V11::All'
process.GlobalTag.globaltag = 'GR_R_38X_V15::All'
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("UserAnalysis.WZAnalysis.wzTreeMaker_cfi")

process.wzTreeMaker.numEventsNames = ['nEventsTotal',
                                      'nEventsHLT',
                                      'nEventsPat',
                                      'nEventsFiltered']

# Manage text output
process.MessageLogger.cerr.FwkReport.reportEvery = 50
process.MessageLogger.cerr.threshold = 'ERROR'
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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTuple-2010B-Nov4ReReco_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_100_1_7Tc.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_101_1_n90.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_102_1_etn.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_103_1_ula.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_104_1_5KS.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_105_1_R5Z.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_106_1_R3Y.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_107_1_cPg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_108_1_kLy.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_109_1_hHN.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_10_1_O1t.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_11_1_JAP.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_12_1_BXB.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_13_1_4T3.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_14_1_dV3.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_15_1_MoG.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_16_1_8pe.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_17_1_gYu.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_18_1_VSc.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_19_1_nal.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_1_1_XkC.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_20_1_8Vh.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_21_1_bj3.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_22_1_sOU.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_23_1_VeD.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_24_1_JDo.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_25_1_CEH.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_26_1_x8y.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_27_1_ZXg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_28_1_5oU.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_29_1_xdv.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_2_1_HKE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_30_1_qkx.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_31_1_bat.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_32_1_lKk.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_33_1_2Wx.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_34_1_i4Q.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_35_1_iB5.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_36_1_864.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_37_1_CQr.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_38_1_quv.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_39_1_5sI.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_3_1_Dkl.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_40_1_fKg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_42_1_gvP.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_43_1_meb.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_44_1_x0x.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_45_1_WwZ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_46_1_8lq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_47_1_c0e.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_48_1_env.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_49_1_e9z.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_4_1_Lz6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_50_1_Yc7.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_51_1_fEc.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_52_1_DeI.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_53_1_RLW.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_54_1_ohv.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_55_1_hgf.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_56_1_vkD.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_57_1_qvg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_58_1_szH.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_59_1_r0B.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_5_1_wFk.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_60_1_RiI.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_61_1_KKO.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_62_1_yzs.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_63_1_Uah.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_64_1_EXJ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_65_1_n8k.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_66_1_dgq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_67_1_evE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_68_1_ku6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_69_1_Tsp.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_6_1_0mh.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_70_1_fkD.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_71_1_QCu.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_73_1_nRp.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_74_1_035.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_75_1_ZxR.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_76_1_t9u.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_77_1_YdZ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_78_1_T6r.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_79_1_NKh.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_7_1_MF9.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_80_1_tu0.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_81_1_rdq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_82_1_3bw.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_83_1_ncu.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_84_1_iUs.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_85_1_3Gg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_87_1_EtN.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_88_1_nO2.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_8_1_9Lt.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_90_1_7TY.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_91_1_NhY.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_92_1_VnN.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_93_1_NIW.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_94_1_APe.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_95_1_Kns.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_96_1_AS6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_97_1_9op.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_98_1_CP6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_99_1_02x.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Mu2010B-Nov4ReReco-v01/patTuple_9_1_6YU.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_100_1_l76.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_101_1_peQ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_102_1_YjB.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_103_1_RVn.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_104_1_9mA.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_105_1_Nxk.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_106_1_e0S.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_107_1_yLB.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_108_1_BXV.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_109_1_6f4.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_10_1_npY.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_110_1_bly.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_11_1_Olg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_12_1_h7F.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_13_1_VoJ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_14_1_oLH.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_15_1_PJC.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_16_1_po6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_17_1_nzk.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_18_1_LXN.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_19_1_D7s.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_1_1_GGO.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_20_1_9Nn.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_21_1_I68.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_22_1_YBE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_23_1_p5D.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_24_1_ihs.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_25_1_t1Z.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_26_1_qup.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_27_1_fbM.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_28_1_o0h.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_29_1_04B.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_2_1_sEg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_30_1_3gs.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_31_1_8lH.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_32_1_W8U.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_33_1_2Qg.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_34_1_H4U.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_35_1_kK0.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_36_1_QAd.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_37_1_SD8.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_38_1_3HT.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_39_1_muw.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_3_1_7fz.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_40_1_JjI.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_41_1_kay.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_42_1_4ht.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_43_1_6s9.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_44_1_TBM.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_45_1_BXc.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_46_1_75s.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_47_1_ma4.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_48_1_XGx.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_49_1_pfE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_4_1_v1K.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_50_1_ivK.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_51_1_2CD.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_52_1_2dl.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_53_1_0mC.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_54_1_c3Z.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_55_1_8Fi.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_56_1_i00.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_57_1_vFc.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_58_1_BIM.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_59_1_jIF.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_5_1_P83.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_60_1_Mld.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_61_1_aXZ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_62_1_QD8.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_63_1_C03.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_64_1_SiK.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_65_1_oar.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_66_1_B2r.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_67_1_v3R.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_68_1_FH7.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_69_1_VZB.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_6_1_sT8.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_70_1_EYU.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_71_1_Uys.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_72_1_Kv0.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_73_1_yCE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_74_1_7ry.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_75_1_Diq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_76_1_8Am.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_77_1_qtI.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_78_1_1W5.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_79_1_P9I.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_7_1_JDE.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_80_1_qH3.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_81_1_uVY.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_82_1_yeA.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_83_1_MnZ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_84_1_N4U.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_85_1_ML3.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_86_1_Rpf.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_87_1_jqG.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_88_1_Sew.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_89_1_1eq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_8_1_2IW.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_90_1_GRp.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_91_1_OHq.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_92_1_HKa.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_93_1_Hie.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_94_1_BPG.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_95_1_FBl.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_96_1_pb7.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_97_1_emQ.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_98_1_Xsa.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_99_1_sg6.root',
'/store/user/fantasia/38X/TrileptonPatTuple-Electron2010B-Nov4ReReco-v01/patTuple_9_1_2TY.root',
)))
