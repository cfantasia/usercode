#!/bin/bash

source /uscmst1/prod/sw/cms/setup/shrc prod
set SCRAM_ARCH slc5_ia32_gcc434

cd /uscms/home/fantasia/CMSSW_3_8_6_patch1/src
eval `scramv1 runtime -sh`

cd RunWZ

for Directory in \
    TrileptonPatTuple-2010A \
    TrileptonPatTuple-2010B \
    TrileptonPatTupleMC-TC225 \
    TrileptonPatTupleMC-TC300 \
    TrileptonPatTupleMC-TC400 \
    TrileptonPatTupleMC-TC500 \
    TrileptonPatTupleMC-Wprime300 \
    TrileptonPatTupleMC-Wprime400 \
    TrileptonPatTupleMC-Wprime500 \
    TrileptonPatTupleMC-Wprime600 \
    TrileptonPatTupleMC-Wprime700 \
    TrileptonPatTupleMC-Wprime800 \
    TrileptonPatTupleMC-Wprime900 \
    TrileptonPatTupleMC-WZ3l \
    TrileptonPatTupleMC-TTbar2l \
    TrileptonPatTupleMC-TTbar \
    TrileptonPatTupleMC-ZZ4l \
    TrileptonPatTupleMC-ZZ \
    TrileptonPatTupleMC-ZeeJets \
    TrileptonPatTupleMC-Zgamma2l \
    TrileptonPatTupleMC-ZmumuJets \
    TrileptonPatTupleMC-WenuJets \
    TrileptonPatTupleMC-WmunuJets \
    TrileptonPatTupleMC-ZeeJetsPowheg \
    TrileptonPatTupleMC-ZmumuJetsPowheg \
    TrileptonPatTupleMC-WlnuJetsMadgraph \
    TrileptonPatTupleMC-ZllJetsMadgraph \
    TrileptonPatTupleMC-ZJetToEE_Pt_0to15 \
    TrileptonPatTupleMC-ZJetToEE_Pt_15to20 \
    TrileptonPatTupleMC-ZJetToEE_Pt_20to30 \
    TrileptonPatTupleMC-ZJetToEE_Pt_30to50 \
    TrileptonPatTupleMC-ZJetToEE_Pt_50to80 \
    TrileptonPatTupleMC-ZJetToEE_Pt_80to120 \
    TrileptonPatTupleMC-ZJetToEE_Pt_120to170 \
    TrileptonPatTupleMC-ZJetToEE_Pt_170to230 \
    TrileptonPatTupleMC-ZJetToEE_Pt_230to300 \
    TrileptonPatTupleMC-ZJetToEE_Pt_300 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_0to15 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_15to20 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_20to30 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_30to50 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_50to80 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_80to120 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_120to170 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_170to230 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_230to300 \
    TrileptonPatTupleMC-ZJetToMuMu_Pt_300
  do

  if [ -f ${Directory}_WZ.log ]; then
      echo Log File $Directory exists
  else 
      echo Running on ${Directory}_WZ.py
      date
      cmsRun ${Directory}_WZ.py >& ${Directory}_WZ.log
  fi
done
