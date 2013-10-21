#!/bin/bash

Cur=`pwd`
echo $Cur

DefEn=8
for En in 7 8 9 10 11 12 13 14 
do
Energy="${En}TeV"

echo Energy is $Energy

  #Default mass file, used as starting point
DMASS=XXX
Tune=TuneZ2star

for Dir in WprimeToWZToLLLNu # WprimeToWZToJJLL WprimeToWZToLNuJJ WprimeToWZToLLLNu WprimeToWZToJJNuNu  
  do

  if [[ $Dir == WprimeToWZTo*L* ]]
      then
      Gen="pythia6_tauola"
  else
      Gen="pythia6"
  fi


  cd ${Cur}/${Dir}

  echo Dir is `pwd`


  if [ -e "${Dir}_M_${DMASS}_${Tune}_${DefEn}TeV_${Gen}_cff.py" ]; then
      #Rename
      cp ${Dir}_M_${DMASS}_${Tune}_{${DefEn},${En}}TeV_${Gen}_cff.py

      #Change COM energy
      /usr/bin/perl -p -i -e "s/${DefEn}000/${En}000/g" ${Dir}_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py
  fi

#  #Add Tune name
#  if [ ! -e "${Dir}_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py" ]; then
#      mv ${Dir}_M_${DMASS}{,_${Tune}}_${Energy}_${Gen}_cff.py
#  fi

  for Mass in `seq 300 100 4000` #200 250 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 #{4..20}
    do 

    if [[ ${Dir}_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py != ${Dir}_M_${Mass}_${Tune}_${Energy}_${Gen}_cff.py ]]; then
         # make a copy for each mass point
        cp ${Dir}_M_${DMASS}_${Tune}_${Energy}_${Gen}_cff.py ${Dir}_M_${Mass}_${Tune}_${Energy}_${Gen}_cff.py
        
         #replace mass in config file
        /usr/bin/perl -p -i -e "s/${DMASS}/${Mass}/g" ${Dir}_M_${Mass}_${Tune}_${Energy}_${Gen}_cff.py
    fi
  done

  
done
done