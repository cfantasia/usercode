#!/bin/bash

Cur=`pwd`
echo $Cur

for Dir in WprimeToWZToJJLL WprimeToWZToLNuJJ WprimeToWZToLLLNu WprimeToWZToJJNuNu  \
    RSGravitonToWWToLNuJJ  RSGravitonToZZToLLJJ  RSGravitonToZZToLLNuNu RSGravitonToZZToNuNuJJ
  do

  cd ${Cur}/${Dir}

  echo Dir is `pwd`

  for ConfigFull in `ls *.py`
    do

    echo $ConfigFull

    #echo Full is $ConfigFull
    Config=`basename $ConfigFull .py`
    #echo Short is $Config 

    xsecline=$(grep "0 All included subprocesses" ../Test_$Dir/${Config}_py_GEN.log)
    #xsecline=$(grep "142 f" ${Config}_py_GEN.log)
    #echo GEN line is $xsecline
    #echo $xsecline | awk '{print $12;}' 

    xsecold=$(echo $xsecline | awk '{print $10;}')
    #echo old is $xsecold

    #convert to correct format for C
    xsecnew=$(echo $xsecold | sed 's/D/e/')
    #echo new is xsecnew

    #convert from mb to pb
    xsec_pb=$(awk -v a="1e9" -v b=$xsecnew 'BEGIN{print (a * b)}')

    /usr/bin/perl -p -i -e "s/comEnergy = cms.double\(8000.0\),/comEnergy = cms.double\(8000.0\),\n    crossSection = cms.untracked.double\($xsec_pb\),/g" $ConfigFull
    
  done
done