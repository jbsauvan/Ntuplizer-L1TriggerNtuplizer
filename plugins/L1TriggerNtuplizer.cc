// -*- C++ -*-
//
// Package:    Ntuplizer/L1TriggerNtuplizer
// Class:      L1TriggerNtuplizer
// 
/**\class L1TriggerNtuplizer L1TriggerNtuplizer.cc Ntuplizer/L1TriggerNtuplizer/plugins/L1TriggerNtuplizer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jean-Baptiste Sauvan
//         Created:  Wed, 25 Jun 2014 12:07:40 GMT
//
//


#include <TTree.h>

#include "Ntuplizer/L1TriggerNtuplizer/interface/L1TriggerNtuplizer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "CondFormats/L1TObjects/interface/CaloParams.h"
#include "CondFormats/DataRecord/interface/L1TCaloParamsRcd.h"

#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Tau.h"


#include "Ntuplizer/L1TriggerNtuplizer/interface/L1TStage1Filler.h"
#include "Ntuplizer/L1TriggerNtuplizer/interface/L1TStage2Filler.h"


L1TriggerNtuplizer::L1TriggerNtuplizer(const edm::ParameterSet& iConfig)
{
    edm::Service<TFileService> fs ;
    m_tree  = fs->make <TTree>("l1TriggerTree","l1TriggerTree"); 

    m_fillStage1 = iConfig.getParameter<bool>("fillStage1");
    m_fillStage2 = iConfig.getParameter<bool>("fillStage2");

    m_l1tStage1Filler = NULL;
    m_l1tStage2Filler = NULL;
    if(m_fillStage1) m_l1tStage1Filler = new L1TStage1Filler(m_tree);
    if(m_fillStage2) m_l1tStage2Filler = new L1TStage2Filler(m_tree);

    m_tree->Branch("event", &m_event, "event/I");
    m_tree->Branch("run",   &m_run,   "run/I");
    m_tree->Branch("lumi",  &m_lumi,  "lumi/I");

    if(m_fillStage1)
    {
        m_stage1_egToken      = consumes<l1t::EGammaBxCollection>     (iConfig.getParameter<edm::InputTag>("stage1EgToken"));
        m_stage1_tauToken     = consumes<l1t::TauBxCollection>        (iConfig.getParameter<edm::InputTag>("stage1TauToken"));
    }
    if(m_fillStage2)
    {
        m_stage2_towerToken   = consumes<l1t::CaloTowerBxCollection>  (iConfig.getParameter<edm::InputTag>("stage2TowerToken"));
        m_stage2_egToken      = consumes<l1t::EGammaBxCollection>     (iConfig.getParameter<edm::InputTag>("stage2EgToken"));
        m_stage2_tauToken     = consumes<l1t::TauBxCollection>        (iConfig.getParameter<edm::InputTag>("stage2TauToken"));
    }
}


L1TriggerNtuplizer::~L1TriggerNtuplizer()
{
    if(m_l1tStage1Filler) delete m_l1tStage1Filler;
    if(m_l1tStage2Filler) delete m_l1tStage2Filler;
}



void L1TriggerNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;

    Handle< BXVector<l1t::EGamma> >    stage1_egs;
    Handle< BXVector<l1t::Tau> >       stage1_taus;
    Handle< BXVector<l1t::CaloTower> > stage2_towers;
    Handle< BXVector<l1t::EGamma> >    stage2_egs;
    Handle< BXVector<l1t::Tau> >       stage2_taus;

    if(m_fillStage1)
    {
        iEvent.getByToken(m_stage1_egToken,stage1_egs);
        iEvent.getByToken(m_stage1_tauToken,stage1_taus);
    }
    if(m_fillStage2)
    {
        iEvent.getByToken(m_stage2_towerToken,stage2_towers);
        iEvent.getByToken(m_stage2_egToken,stage2_egs);
        iEvent.getByToken(m_stage2_tauToken,stage2_taus);
    }

    m_event = iEvent.id().event();
    m_run   = iEvent.id().run();
    m_lumi  = iEvent.luminosityBlock();

    if(m_fillStage1) m_l1tStage1Filler->fill(stage1_egs, stage1_taus);
    if(m_fillStage2) m_l1tStage2Filler->fill(stage2_towers, stage2_egs, stage2_taus);

    m_tree->Fill();
}


void L1TriggerNtuplizer::beginJob()
{
}

void L1TriggerNtuplizer::endJob() 
{
}

void L1TriggerNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  //edm::ParameterSetDescription desc;
  //desc.setUnknown();
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TriggerNtuplizer);
