#!/bin/tcsh -f

if ( $# < 2 ) then
    echo "Usage: `basename $0` MODE Number [CWD] [Offset]"
endif

#echo You gave me $# parameters
set Mode=${1}
set Process=${2}
set Offset=0


if ( $# > 2 ) then
    echo Moving to ${3}
    set SRC_Dir=${3}
    
    #This IS LPC Specific to get cmsenv to work
    source /uscmst1/prod/sw/cms/setup/cshrc prod
    setenv SCRAM_ARCH slc5_amd64_gcc434

    cd $SRC_Dir
    eval `scramv1 runtime -csh`

    pwd
    date

    echo Mode is $Mode
    echo Process Number is $Process
    if ( $# > 3 ) then
        set Offset=${4}
        echo Offset Number is $Offset
        @ Process = ( $Process + $Offset )
        echo Sample Number is $Process
    endif
endif

set OutFile=${Mode}_Sample${Process}.txt

switch ($Mode)
    case "WprimeWZ": #Wprime WZ
        set Config=analyzeWprimeWZ_cfg.py
        breaksw
    case "HadVZ": #Had VZ
        set Config=analyzeWprimeHadVZ_cfg.py
        breaksw
    case "HadVW": #Had WZ
        set Config=analyzeWprimeHadVW_cfg.py
        breaksw
    case "TB": #TB
        set Config=analyzeWprimeTB_cfg.py
        breaksw
    case "EWKWZ": #EWK WZ
        set Config=analyzeEWKWZ_cfg.py
        breaksw
    case "WZMatrix": #Matrix Method
        set Config=analyzeWprimeWZMatrix_cfg.py
        breaksw
    case "WZEffRate": #Eff Rate
        set Config=analyzeWZEffRate_cfg.py
        breaksw
    case "WZFakeRateElec": #Elec Fake Rate
        set Config=analyzeWZFakeRateElec_cfg.py
        breaksw
    case "WZFakeRateMuon": #Muon Fake Rate
        set Config=analyzeWZFakeRateMuon_cfg.py
        breaksw
    case "TTbar": #HadVZ TTbar check
        set Config=analyzeTTbar_cfg.py
        breaksw
    default:
        echo "You didn't choose a valid mode: " $Mode
        exit 1
endsw

time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/${Config} ${Process} >& $OutFile
#I don't want to use $OutFile if using condor, right?

date

exit 0
