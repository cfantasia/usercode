#!/bin/bash

#This script will copy your config to the right area in gen package
# make a .py file and run it
# it will append the time taken to the end of the log file for later use

Cur=`pwd`
echo $Cur

for Dir in WprimeToWZToJJLL WprimeToWZToLNuJJ WprimeToWZToLLLNu WprimeToWZToJJNuNu RSGravitonToWWToLNuJJ  RSGravitonToZZToLLJJ   RSGravitonToZZToLLNuNu RSGravitonToZZToNuNuJJ
  do

  if [ ! -d "${Cur}/Test_${Dir}" ]; then
      mkdir ${Cur}/Test_${Dir}
  else
      echo Dir already exists
  fi
  cd ${Cur}/Test_${Dir}

  echo Now `pwd`

  for ConfigFull in `ls ../${Dir}/*.py`
    do

    #echo Full is $ConfigFull
    Config=`basename $ConfigFull .py`
    #echo Short is $Config 
 
    #2) Note that in 2012, cards are divided into groups by the c-o-m energy, so put your edited
    #card in Configuration/GenProduction/python/EightTeV/
    cp ../${Dir}/$Config.py ../../Configuration/GenProduction/python/EightTeV/
    
    if [ ! -e "${Config}_py_GEN.log" ]; then
        #echo No file named ${Config}_py_GEN.log found
       
       
        #3) Make a python config file by running, e.g. (use your GEN fragment here):
        ##cmsDriver.py Configuration/GenProduction/python/EightTeV/WToENu_TuneZ2star_8TeV_pythia6_cff.py -s GEN --conditions START50_V13::All --beamspot Realistic7TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 1000 --no_exec
        
        #########old method   cmsDriver.py Configuration/GenProduction/python/EightTeV/$Config.py -s GEN --conditions START50_V13::All --beamspot Realistic7TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 10000 --no_exec
        
        #cmsDriver.py Configuration/GenProduction/python/EightTeV/WToENu_TuneZ2star_8TeV_pythia6_cff.py -s GEN --conditions START50_V13::All --beamspot Realistic8TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 1000 --no_exec
        cmsDriver.py Configuration/GenProduction/python/EightTeV/$Config.py -s GEN --conditions START50_V13::All --beamspot Realistic8TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 10000 --no_exec --no_output

        cmsRun ${Config}_py_GEN.py >& ${Config}_py_GEN.log

    else
        echo Skipping file ${Config}_py_GEN.log because it already exists
    fi #if file doesn't exist

    continue #Cory: This is only added because I just want xsec


    if [ ! -e "${Config}_py_GEN_SIM.log" ]; then
        #cmsDriver.py Configuration/GenProduction/python/EightTeV/WToENu_TuneZ2star_8TeV_pythia6_cff.py -s GEN,SIM --conditions START50_V13::All --beamspot Realistic8TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 10 --no_exec        
        cmsDriver.py Configuration/GenProduction/python/EightTeV/$Config.py -s GEN,SIM --conditions START50_V13::All --beamspot Realistic8TeVCollision --datatier GEN-SIM --eventcontent RAWSIM -n 10 --no_exec

        #4) Run it:
        #time cmsRun WToENu_TuneZ2star_8TeV_pythia6_cff_py_GEN.py
    
        { /usr/bin/time -f "%e" cmsRun ${Config}_py_GEN_SIM.py >& ${Config}_py_GEN_SIM.log; } 2>>${Config}_py_GEN_SIM.log

        #5) Make note of the time it takes to run and the size of the output file, and the cross section
        #(in picobarns) - these are the numbers that you will have to provide to us.

    else
        echo Skipping file ${Config}_py_GEN_SIM.log because it already exists
    fi #if file doesn't exist

  done #Loop over files in dir
done #loop over dir

echo All Done.


