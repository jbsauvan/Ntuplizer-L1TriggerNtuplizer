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


#ifndef L1TRIGGERNTUPLIZER_H
#define L1TRIGGERNTUPLIZER_H

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


class TTree;

class L1TStage1Filler;
class L1TStage2Filler;

class L1TriggerNtuplizer : public edm::EDAnalyzer 
{
    public:
        explicit L1TriggerNtuplizer(const edm::ParameterSet&);
        ~L1TriggerNtuplizer();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


    private:
        virtual void beginJob() override;
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
        virtual void endJob() override;

        bool m_fillStage1;
        bool m_fillStage2;

        TTree* m_tree; 
        int m_event;
        int m_run;
        int m_lumi;
        L1TStage1Filler* m_l1tStage1Filler;
        L1TStage2Filler* m_l1tStage2Filler;

        // Stage-1 inputs
        edm::EDGetToken m_stage1_egToken;
        edm::EDGetToken m_stage1_tauToken;
        // Stage-2 inputs
        edm::EDGetToken m_stage2_towerToken;
        edm::EDGetToken m_stage2_egToken;
        edm::EDGetToken m_stage2_tauToken;

};

#endif
