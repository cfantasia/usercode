#!/bin/bash
PNFSDir="38X"
Ver="V05-03-03"
for Skim in \
    DileptonPatTupleMC \
    TrileptonPatTupleMC
  do
  
  for Sample in \
      TC225 \
      TC300 \
      TC400 \
      TC500 \
      Wprime300 \
      Wprime400 \
      Wprime500 \
      Wprime600 \
      Wprime700 \
      Wprime800 \
      Wprime900 \
      TTbar \
      WmunuJets \
      Zgamma2l \
      TTbar2l \
      ZZ \
      ZllJetsMadgraph \
      WZ3l \
      ZZ4l \
      ZmumuJets \
      WenuJets \
      ZeeJets \
      ZmumuJetsPowheg \
      WlnuJetsMadgraph \
      ZeeJetsPowheg \
      ZJetToEE_Pt_0to15 \
      ZJetToEE_Pt_15to20 \
      ZJetToEE_Pt_20to30 \
      ZJetToEE_Pt_30to50 \
      ZJetToEE_Pt_50to80 \
      ZJetToEE_Pt_80to120 \
      ZJetToEE_Pt_120to170 \
      ZJetToEE_Pt_170to230 \
      ZJetToEE_Pt_230to300 \
      ZJetToEE_Pt_300 \
      ZJetToMuMu_Pt_0to15 \
      ZJetToMuMu_Pt_15to20 \
      ZJetToMuMu_Pt_20to30 \
      ZJetToMuMu_Pt_30to50 \
      ZJetToMuMu_Pt_50to80 \
      ZJetToMuMu_Pt_80to120 \
      ZJetToMuMu_Pt_120to170 \
      ZJetToMuMu_Pt_170to230 \
      ZJetToMuMu_Pt_230to300 \
      ZJetToMuMu_Pt_300

    do
    
    Filename=${Skim}-${Sample}_WZ

    if [ -f ${Filename}.py ]; then
        echo $Filename exists
    else 
        
        cp wzTreeMaker.py $Filename.py
        echo "process.GlobalTag.globaltag = 'START38_V13::All'"  >> $Filename.py
        echo "process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/$Filename.root'" >> $Filename.py
        echo 'process.source = cms.Source("PoolSource",' >> $Filename.py
        echo 'fileNames = cms.untracked.vstring(*(' >> $Filename.py
        
        for Directory in \
            ${Skim}-${Ver}-${Sample}
          do
          
          for File in `ls /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory}`
            do
            
            echo $Directory/$File
            echo "'/store/user/fantasia/${PNFSDir}/${Directory}/${File}'," >> $Filename.py
            
          done     
        done
        echo ')))' >> $Filename.py
        echo Done making $Filename.py
    fi 
  done
done
