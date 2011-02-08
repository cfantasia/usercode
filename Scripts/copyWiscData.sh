#!/bin/bash

PNFSBase=/pnfs/cms/WAX/
SRMWiscBase=srm://cmssrm.hep.wisc.edu:8443
SRMFNALBase=srm://cmssrm.fnal.gov:8443

OutputStr=11/store/user/fantasia/38X

for Directory in \
    TrileptonPatTupleV05-03-10-EG2010A \
    TrileptonPatTupleV05-03-10-Electron2010B \
    TrileptonPatTupleV05-03-10-Mu2010A \
    TrileptonPatTupleV05-03-10-Mu2010B \
    DileptonPatTupleV05-03-10-EG2010A \
    DileptonPatTupleV05-03-10-Electron2010B \
    DileptonPatTupleV05-03-10-Mu2010A \
    DileptonPatTupleV05-03-10-Mu2010B
  do
  
  PNFSDir=$PNFSBase/$OutputStr/$Directory
  if [ -d $PNFSDirectory ]; then
      echo $Directory exists
  else 
      echo "Directory does not exists"
      mkdir $PNFSDir
      chmod 775 $PNFSDir
  fi 
  
  for File in `less filelists/${Directory}.txt`
    do
    #echo $File
#    echo ${File%%klukas*}
    Filename=${File##*klukas/}
    echo $Filename

    echo  ${SRMWiscBase}/$File ${SRMFNALBase}/${OutputStr}/$Filename
    if [ -f $PNFSBase/$OutputStr/$Filename ]; then
        echo file exists, skipping
    else
        echo Copying 
        srmcp ${SRMWiscBase}/$File ${SRMFNALBase}/${OutputStr}/$Filename
    fi
  done
done
