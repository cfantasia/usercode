#!/bin/bash
while read LINE
do
  RUN=${LINE%%:*}
  LUMI=${LINE%:*}
  LUMI=${LUMI##*:}

  dbs search --query="find file where run=${RUN} and lumi=${LUMI} and dataset=/SingleMu/Run2011A-PromptReco-v1/AOD" | grep .root
  dbs search --query="find file where run=${RUN} and lumi=${LUMI} and dataset=/SingleElectron/Run2011A-PromptReco-v1/AOD" | grep .root

done < ../candEvts.txt