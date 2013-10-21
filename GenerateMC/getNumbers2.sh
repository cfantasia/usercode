#!/bin/bash

#This script will extract all the useful numbers from the pythia log file

Cur=`pwd`
echo $Cur

for Dir in WprimeToWZToLLLNu #WprimeToWZToJJLL WprimeToWZToLNuJJ WprimeToWZToLLLNu WprimeToWZToJJNuNu  \
    #RSGravitonToWWToLNuJJ  RSGravitonToZZToLLJJ  RSGravitonToZZToLLNuNu RSGravitonToZZToNuNuJJ
  do

#  mkdir ${Cur}/Test_${Dir}
  cd ${Cur}/Test_${Dir}

  echo Now `pwd`
  rm -f xSec_*.dat

  for ConfigFull in `ls ../${Dir}/*.py`
    do

    #echo Full is $ConfigFull
    Config=`basename $ConfigFull .py`
    #echo Short is $Config 
    
#5) Make note of the time it takes to run and the size of the output file, and the cross section
#(in picobarns) - these are the numbers that you will have to provide to us.

    xsecline=$(grep "0 All included subprocesses" ${Config}_py_GEN.log)
    #xsecline=$(grep "142 f" ${Config}_py_GEN.log)
    #echo GEN line is $xsecline
    #echo $xsecline | awk '{print $12;}' 

    xsecold=$(echo $xsecline | awk '{print $10;}')
    #echo old is $xsecold

    #convert to correct format for C
    xsecnew=$(echo $xsecold | sed 's/D/e/')
    #echo new is xsecnew

    #convert from mb to pb
    xsecnew_pb=$(awk -v a="1e9" -v b=$xsecnew 'BEGIN{print (a * b)}')

    DSname=$(echo $Config | sed 's/_cff//')
    DSname=$(echo $DSname | sed 's/_M_/_M-/')
    DSname=$(echo $DSname | sed 's/_pythia/-pythia/')
    DSname=$(echo $DSname | sed 's/_tauola/-tauola/')

    xsecline=$(grep "0 All included subprocesses" ${Config}_py_GEN_SIM.log)
    #echo GEN-SIM line is $xsecline
    nGen=$(echo $xsecline | awk '{print $7;}')
    size=$(echo `ls ${Config}_py_GEN_SIM.root -l` | awk '{print $5;}')

    time=$(tail --lines=1 ${Config}_py_GEN_SIM.log)
    #echo time is $time

    mass=$(echo $Config | awk 'BEGIN { FS = "_" } ; { print $3 }')

    En=$(echo $Config | awk 'BEGIN { FS = "_" } ; { print $5 }')
    En=$(echo $En | sed 's/TeV//')

    #Coming from gen file: xsec,  
    #Coming from gen-sim file: ngen, time, size
    echo $DSname $Config 0 50000 1.00 $xsecnew_pb $nGen $time $size
    echo $mass $xsecnew_pb >> xSec_WZ_${En}TeV.dat
  done
  

done