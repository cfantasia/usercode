#!/bin/bash

Cur=`pwd`
echo $Cur

Energy="8TeV"
  #Default mass file, used as starting point
DMASS=1000
Tune=TuneZ2star

for Dir in RSGravitonToWWToLNuJJ  RSGravitonToZZToLLJJ   RSGravitonToZZToLLNuNu RSGravitonToZZToNuNuJJ
  do

  if [[ $Dir == RSGraviton*L* ]]
      then
      Gen="pythia6_tauola"
  else
      Gen="pythia6"
  fi


  cd ${Cur}/${Dir}

  echo Dir is `pwd`


  if [ -e "${Dir}_kMpl005_M_${DMASS}_7TeV_${Gen}_cff.py" ]; then
      #Rename
      mv -f ${Dir}_kMpl005_M_${DMASS}_{7,8}TeV_${Gen}_cff.py

      #Change COM energy
      /usr/bin/perl -p -i -e "s/7000/8000/g" ${Dir}_kMpl005_M_${DMASS}_${Energy}_${Gen}_cff.py
  fi

  #Add Tune name
  if [ ! -e "${Dir}_kMpl005_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py" ]; then
      mv ${Dir}_kMpl005_M_${DMASS}{,_${Tune}}_${Energy}_${Gen}_cff.py
  fi

  for Mass in 750 1000 1250 1500 1750 2000
    do 
     # make a copy for each mass point
    cp ${Dir}_kMpl005_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py ${Dir}_kMpl005_M_${Mass}_${Tune}_${Energy}_${Gen}_cff.py

    #replace mass in config file
    /usr/bin/perl -p -i -e "s/${DMASS}/${Mass}/g" ${Dir}_kMpl005_M_${Mass}_${Tune}_${Energy}_${Gen}_cff.py
  done


done