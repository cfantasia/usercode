#!/bin/bash
PNFSDir="38X"
for Sample in \
    Wprime400 \
    Wprime500 \
    Wprime600 \
    Wprime700 \
    Wprime800 \
    Wprime900 \
    TC225 \
    TC300 \
    TC400 \
    TC500

  do
  Directory1="TrileptonPatTupleMC-V05-03-03-${Sample}"
  Directory2="gen${Sample}"
  
  #mv /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory1} /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory2}
  mkdir /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory1}/
  chmod 775 /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory1}/
  mv /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory2}/*PAT* /pnfs/cms/WAX/11/store/user/fantasia/${PNFSDir}/${Directory1}/
done
