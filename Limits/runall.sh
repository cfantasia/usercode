#!/bin/bash

root -b -q Expected_Evts.C

root -b -q CalcLimit.C
root -b -q PlotLimit.C++

root -b -q "CalcSig.C(0)" #For W'
root -b -q "CalcSig.C(1)" #For TC  

root -b -q "PlotSig.C++(0)" #For W'
root -b -q "PlotSig.C++(1)" #For TC

