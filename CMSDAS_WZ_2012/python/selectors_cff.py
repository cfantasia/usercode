import FWCore.ParameterSet.Config as cms

#####################
######  Muons  ######
#####################

#Note: These cuts are <= and >= 
muSelectors = cms.PSet(
    VBTF = cms.PSet(
       minPt = cms.untracked.double(10.),
       maxEta = cms.untracked.double(2.4),
       minIsGlobal = cms.untracked.int32(1),
       maxDxy = cms.untracked.double(0.2),
    ),
    WZLoose = cms.PSet(),
    WZRelaxed = cms.PSet(),
    WZTight = cms.PSet(),
    )
muSelectors.WZLoose = muSelectors.VBTF.clone(
    minPt = 10.,
    maxIso03 = cms.untracked.double(0.15)
    )
muSelectors.WZTight = muSelectors.VBTF.clone(
    minPt = 20.,
    maxIso03 = cms.untracked.double(0.1)
    )

#####################
####  Electrons  ####
#####################

# indices correspond to working points: 95, 90, 85, 80, 70, 60 (% efficiencies)
cutsMissingHits = [0, 0, 0, 0, 0, 0]
cutsConvDist = [0., 0., 0.02, 0.02, 0.02, 0.02]
cutsConvDcot = [0., 0., 0.02, 0.02, 0.02, 0.02]
cutsEBCombRelIso = [0.150, 0.085, 0.053, 0.070, 0.030, 0.016]
cutsEBSigmaIEtaIEta = [0.012, 0.01, 0.01, 0.01, 0.01, 0.01]
cutsEBDeltaPhi = [0.800, 0.071, 0.039, 0.027, 0.020, 0.020]
cutsEBDeltaEta = [0.007, 0.007, 0.005, 0.005, 0.004, 0.004]
cutsEECombRelIso = [0.100, 0.051, 0.042, 0.060, 0.016, 0.008]
cutsEESigmaIEtaIEta = [0.031, 0.031, 0.031, 0.031, 0.031, 0.031]
cutsEEDeltaPhi = [0.7, 0.047, 0.028, 0.021, 0.021, 0.021]
cutsEEDeltaEta = [0.011, 0.011, 0.007, 0.006, 0.005, 0.004]

elSelectors = cms.PSet(
    WZLoose = cms.PSet(),
    WZRelaxed = cms.PSet(),
    WZTight = cms.PSet(),
    )

for i, s in enumerate(["wp95", "wp90", "wp85", "wp80", "wp70", "wp60"]):
    pset = cms.PSet(
        barrel = cms.PSet(
           maxMissingHits = cms.untracked.int32(cutsMissingHits[i]),
           minConv = cms.untracked.double(cutsConvDist[i]),#Hack bc we need an OR of these two cuts below
           maxCombRelIso = cms.untracked.double(cutsEBCombRelIso[i]),
           maxSigmaIEtaIEta = cms.untracked.double(cutsEBSigmaIEtaIEta[i]),
           maxDeltaPhi = cms.untracked.double(cutsEBDeltaPhi[i]),
           maxDeltaEta = cms.untracked.double(cutsEBDeltaEta[i]),
           ),
        endcap = cms.PSet(
           maxMissingHits = cms.untracked.int32(cutsMissingHits[i]),
           minConv = cms.untracked.double(cutsConvDist[i]),#Hack bc we need an or of these two cuts below
           maxCombRelIso = cms.untracked.double(cutsEECombRelIso[i]),
           maxSigmaIEtaIEta = cms.untracked.double(cutsEESigmaIEtaIEta[i]),
           maxDeltaPhi = cms.untracked.double(cutsEEDeltaPhi[i]),
           maxDeltaEta = cms.untracked.double(cutsEEDeltaEta[i]),
           ),
        )
    setattr(elSelectors, s, pset)
    
elSelectors.WZLoose = elSelectors.wp95.clone()
elSelectors.WZLoose.barrel.minPt = cms.untracked.double(10.)
elSelectors.WZLoose.endcap.minPt = cms.untracked.double(10.)

elSelectors.WZTight = elSelectors.wp80.clone()
elSelectors.WZTight.barrel.minPt = cms.untracked.double(20.)
elSelectors.WZTight.endcap.minPt = cms.untracked.double(20.)
