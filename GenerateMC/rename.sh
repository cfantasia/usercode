#!/bin/bash

Cur=`pwd`
echo $Cur

Energy="8TeV"
  #Default mass file, used as starting point
DMASS=300
Tune=TuneZ2star

for Dir in WprimeToWZToLLLNu #WprimeToWZToJJLL WprimeToWZToLNuJJ WprimeToWZToLLLNu WprimeToWZToJJNuNu  
  do

  cd ${Cur}/${Dir}

  echo Dir is `pwd`

  for name in `ls ../${Dir}/*` `ls ../Test_${Dir}/*`
    do
    
    oldname=$name #`basename $name`

    newname=$oldname

    newname=$(echo $newname | sed 's/2J/JJ/')
    newname=$(echo $newname | sed 's/2L/LL/')
    newname=$(echo $newname | sed 's/2Nu/NuNu/')
    newname=$(echo $newname | sed 's/3L/LLL/')

    echo $oldname becomes $newname
   
    mv $oldname $newname 
    /usr/bin/perl -p -i -e "s/2J/JJ/g" $newname
    /usr/bin/perl -p -i -e "s/2L/LL/g" $newname
    /usr/bin/perl -p -i -e "s/2Nu/NuNu/g" $newname
    /usr/bin/perl -p -i -e "s/3L/LLL/g" $newname
    
  done
done