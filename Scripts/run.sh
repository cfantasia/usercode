#!/bin/tcsh -f

#echo You gave me $# parameters
set Mode=${1}
set Process=${2}
set Offset=0

if ( $# < 2 ) then
    echo Usage: $0 MODE Number PWD
endif

if ( $# > 2 ) then
    echo Moving to ${3}
    set SRC_Dir=${3}
    
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

# if ( $Process < 10 ) then
#     set ProcessPadded = 00${Process}
# else if ( $Process < 100 ) then
#     set ProcessPadded = 0${Process}
# else
#     set ProcessPadded = ${Process}
# endif 
# echo $ProcessPadded

set OutFile=Sample${Process}_${Mode}.txt
#set OutFile=${Mode}_Sample${Process}.txt

switch ($Mode)
    case "WprimeWZ": #Wprime WZ
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWprimeWZ_cfg.py ${Process} >& $OutFile
        breaksw
    case "HadVZ": #Had VZ
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWprimeHadVZ_cfg.py ${Process} >& $OutFile
        breaksw
    case "HadVW": #Had WZ
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWprimeHadVW_cfg.py ${Process} >& $OutFile
        breaksw
    case "TB": #TB
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWprimeTB_cfg.py ${Process} >& $OutFile
        breaksw
    case "EWKWZ": #EWK WZ
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeEWKWZ_cfg.py ${Process} >& $OutFile
        breaksw
    case "WZMatrix": #Matrix Method
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWprimeWZMatrix_cfg.py ${Process} >& $OutFile
        breaksw
    case "WZEffRate": #Eff Rate
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWZEffRate_cfg.py ${Process} >& $OutFile
        breaksw
    case "WZElecFakeRate": #Elec Fake Rate
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWZFakeRate_cfg.py ${Process} >& $OutFile
        breaksw
    case "WZMuonFakeRate": #Muon Fake Rate
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeWZFakeRate_cfg.py ${Process} >& $OutFile
        breaksw
    case "TTbar": #HadVZ TTbar check
        time WPrimeAnalyzer UserCode/CMGWPrimeGroup/bin/analyzeTTbar_cfg.py ${Process} >& $OutFile
        breaksw
    default:
        echo "You didn't choose a valid mode: " $Mode
        exit 1
endsw

date

exit 0
