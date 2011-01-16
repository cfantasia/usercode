#!/bin/bash
Era="2010B"
Ver="V05-03-10"
for Skim in \
    TrileptonPatTuple \
    DileptonPatTuple
  do
  Filename=${Skim}-${Era}_WZ
  
  cp wzTreeMaker.py $Filename.py
  echo "process.GlobalTag.globaltag = 'GR_R_38X_V15::All'"  >> $Filename.py
  echo "process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/$Filename.root'" >> $Filename.py
  echo 'process.source = cms.Source("PoolSource",' >> $Filename.py
  echo 'fileNames = cms.untracked.vstring(*(' >> $Filename.py
  
  for PD in \
      Mu \
      Electron
  do
    
    for Directory in \
        ${Skim}${Ver}-${PD}${Era}
      do
      
      for File in `ls /pnfs/cms/WAX/11/store/user/fantasia/38X/${Directory}`
        do
  
        echo $Directory/$File
        echo "'/store/user/fantasia/38X/${Directory}/${File}'," >> $Filename.py
        
      done     
    done
  done
  echo ')))' >> $Filename.py
  echo Done making $Filename.py
done
  