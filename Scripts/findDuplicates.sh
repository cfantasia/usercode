#!/bin/bash

Ver="V380B"
Dir=/pnfs/cms/WAX/11/store/user/fantasia/42X

for Directory in `ls ${Dir} | grep ${Ver}`
  do
#  find ${Dir}/${Directory}/ | grep .root >& ${Directory}.txt
#  echo ""
#  echo ${Directory}
  i=0
  Count=999
  TtlCount=`find ${Dir}/$Directory/ | grep .root | wc -l`
  while [ $Count -gt 0 ]
    do
    i=$[$i+1]    
    Count=`find ${Dir}/$Directory/*_${i}_?_???.root  2>/dev/null | wc -l` 


    if [ $Count -gt 1 ]; then
        nExtraFiles=$[$Count-1]
        echo "File $i in $Directory has $nExtraFiles duplicates"
        ls -sh `find ${Dir}/$Directory/*_${i}_?_???.root | head -$nExtraFiles`
        ###Note: This line below will delete extra files but please be careful
        #rm `find ${Dir}/$Directory/*_${i}_?_???.root | head -$nExtraFiles`
    fi

  done
  LastSeen=$[$i-1]    
  
  if [ $TtlCount -ne $LastSeen ]; then    
      NMiss=$[$TtlCount-$LastSeen]
      echo "------------"
      echo "$Directory Missing at least 1 file, expected $TtlCount but ended on $LastSeen"
      while [ $i -le $TtlCount ]; do
          if [ ! -f ${Dir}/${Directory}/*_${i}_*_*.root ]; then
              echo "e.g. ${Dir}/${Directory}/patTuple_${i}_?_???.root"
              TtlCount=$[$TtlCount+1]
          fi
          i=$[$i+1]
      done
      echo "------------"
  fi
done
