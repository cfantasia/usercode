#!/bin/bash



for file in `grep .root list | awk '{print $2;}'`
  do                                                                                                                      
  
  rm $file
done