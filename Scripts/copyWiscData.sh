#!/bin/bash
# Get with srmls srm://cmssrm.hep.wisc.edu:8443//pnfs/hep.wisc.edu/store/user/jklukas/ | grep DileptonPatTupleMC
# srm://cmssrm.hep.wisc.edu:8443/srm/v2/server?SFN=/hdfs/store/

if [ $# -ne 2 ]
then
  echo "Usage: `basename $0` IN_SITE OUT_SITE"
  exit 65
fi

Ver="42X"
#WISC
WISC_USER=fantasia #jklukas
WISC_BASE=/hdfs
WISC_SRM=srm://cmssrm.hep.wisc.edu:8443/${WISC_BASE}
WISC_PNFS=store/user/${WISC_USER}

#FNAL
FNAL_USER=fantasia
FNAL_BASE=/pnfs/cms/WAX
FNAL_SRM=srm://cmssrm.fnal.gov:8443
FNAL_PNFS=11/store/user/${FNAL_USER}/${Ver}

#CERN
CERN_USER=f/fantasia
CERN_BASE=""
CERN_SRM=srm://srm-cms.cern.ch:8443
CERN_PNFS=/castor/cern.ch/user/${CERN_USER}


IN=$1
OUT=$2

if [ "$IN" = "WISC" ]; then
    IN_USER=$WISC_USER
    IN_BASE=$WISC_BASE
    IN_SRM=$WISC_SRM
    IN_PNFS=$WISC_PNFS
fi
if [ "$IN" = "FNAL" ]; then
    IN_USER=$FNAL_USER
    IN_BASE=$FNAL_BASE
    IN_SRM=$FNAL_SRM
    IN_PNFS=$FNAL_PNFS
fi
if [ "$IN" = "CERN" ]; then
    IN_USER=$CERN_USER
    IN_BASE=$CERN_BASE
    IN_SRM=$CERN_SRM
    IN_PNFS=$CERN_PNFS
fi
if [ "$OUT" = "WISC" ]; then
    OUT_USER=$WISC_USER
    OUT_BASE=$WISC_BASE
    OUT_SRM=$WISC_SRM
    OUT_PNFS=$WISC_PNFS
fi
if [ "$OUT" = "FNAL" ]; then
    OUT_USER=$FNAL_USER
    OUT_BASE=$FNAL_BASE
    OUT_SRM=$FNAL_SRM
    OUT_PNFS=$FNAL_PNFS
fi
if [ "$OUT" = "CERN" ]; then
    OUT_USER=$CERN_USER
    OUT_BASE=$CERN_BASE
    OUT_SRM=$CERN_SRM
    OUT_PNFS=$CERN_PNFS
fi

for FileList in `ls filelists/ | grep .txt`
  do
  Directory=${FileList%%.txt}
  echo Directory is  $Directory
  
  for File in `less filelists/${Directory}.txt`
    do
    #strip off $IN_BASE/$IN_PNFS
    Filename=${File##*$IN_BASE/$IN_PNFS/}
#    Filename=${Directory}/${File##*${Directory}/}
#    Filename=${Directory}/`basename $File`
#    echo $File
#    echo $Filename

    INPUT=$IN_SRM/${IN_PNFS}/$Filename
    OUTPUT=$OUT_SRM/${OUT_PNFS}/$Filename
    
    if [ -f ${OUT_BASE}/${OUT_PNFS}/$Filename ]; then
        echo $Filename exists, skipping
    else
        echo Copying \"$INPUT\" \"$OUTPUT\"
####        srmcp $INPUT $OUTPUT #doesn't work on lpc
####        lcg-cp -v "srm://cmssrm.hep.wisc.edu:8443//hdfs/store/user/jklukas/MC-W06-06-05A/WprimeToWZTo3LNu_emt_M-1000_7TeV-pythia6/MCPatOmnilepton-WprimeToWZTo3LNu_emt_M-1000_7TeV-pythia6/patTuple_cfg-step3-step2-WprimeToWZTo3LNu_emt_M-1000_7TeV-pythia6-0372.root" test.root
        lcg-cp -n 4 $INPUT $OUTPUT
    fi
  done
done
