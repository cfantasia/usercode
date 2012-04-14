#!/bin/bash
if [ "$#" -lt 1 ]; then
   echo "Usage: `basename $0` Mode [Offset]"
   exit
fi

Mode=${1}
WD=$(pwd)

if [ "$#" -gt 1 ]; then
    Offset=${2}
    NJobs=1
else
    ./run.sh $Mode 999 >& /dev/null
    Offset=0
    NJobs=$(grep "You asked for sample " ${Mode}_Sample999.txt | awk '{print $8;}')
fi

date

if [ ! -d Logs ]; then
    mkdir Logs 
fi

#echo ${WD}, $NJobs, $Mode

/bin/rm -f ${Mode}.cfg
cat > ${Mode}.cfg << EOF

requirements = ARCH == "X86_64"

universe = vanilla
executable = run.sh

# Copy environment variables that are set at submit time, such as
# LD_LIBRARY_PATH.
getenv = true

should_transfer_files = yes
when_to_transfer_output = ON_EXIT

output = Logs/stdout_\$(Process).\$(cluster)
error = Logs/stderr.\$(cluster)
log = Logs/log.\$(cluster)
notify_user = fantasia@bu.edu
Arguments = ${Mode} \$(Process) ${WD} ${Offset}

#notify = Error
#notification = never
notification = error

queue ${NJobs}

EOF

condor_submit ${Mode}.cfg
