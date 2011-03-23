#!/bin/bash

for Directory in `ls /pnfs/cms/WAX/11/store/user/fantasia/41X/`
  do
  find /pnfs/cms/WAX/11/store/user/fantasia/41X/${Directory}/*.root >& filelists/${Directory}.txt

done
