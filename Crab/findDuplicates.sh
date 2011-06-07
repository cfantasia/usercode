#!/bin/bash

Ver="B05-06-03"
Dir=/pnfs/cms/WAX/11/store/user/fantasia/42X

for Directory in `ls ${Dir} | grep ${Ver}`
  do
#  find ${Dir}/${Directory}/ | grep .root >& ${Directory}.txt
  echo ""
#  echo ${Directory}
  i=0
  Count=999
  TtlCount=`find ${Dir}/$Directory/ | grep .root | wc -l`
  while [ $Count -gt 0 ]
    do
    i=$[$i+1]    
    Count=`find ${Dir}/$Directory/*_${i}_*_*.root  2>/dev/null | wc -l` 


    if [ $Count -gt 1 ]; then
        nExtraFiles=$[$Count-1]
        echo "File %i in $Directory has at least $nExtraFiles duplicates"
        find ${Dir}/$Directory/*_${i}_*_*.root | head -$nExtraFiles
    fi

  done
    i=$[$i-1]    
  
  if [ $TtlCount -ne $i ]; then    
      echo "$Directory Missing at least 1 file, expected $TtlCount but ended on $i"
      echo "e.g. ${Dir}/${Directory}/Filename_${i}.root"
  fi
done
