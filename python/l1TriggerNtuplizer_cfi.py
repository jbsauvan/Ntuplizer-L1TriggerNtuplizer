import FWCore.ParameterSet.Config as cms

l1TriggerNtuplizer = cms.EDAnalyzer('L1TriggerNtuplizer',
    fillStage1 = cms.bool(False),
    fillStage2 = cms.bool(False),
    stage1EgToken = cms.InputTag("caloStage1FinalDigis"),
    stage1TauToken = cms.InputTag("caloStage1FinalDigis"),
    stage2TowerToken = cms.InputTag("caloStage2Digis"), #After Compression
    stage2EgToken = cms.InputTag("caloStage2Digis"),
    stage2TauToken = cms.InputTag("caloStage2Digis")
)
