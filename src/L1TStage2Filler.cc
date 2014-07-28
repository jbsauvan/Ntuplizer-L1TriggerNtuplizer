/**
 *  @file  L1TStage2Filler.cc
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    06/25/2014
 *
 *  @internal
 *     Created :  06/25/2014
 * Last update :  06/25/2014 09:20:20 PM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

#include <TTree.h>

#include "Ntuplizer/L1TriggerNtuplizer/interface/L1TStage2Filler.h"



/*****************************************************************/
L1TStage2Filler::L1TStage2Filler(TTree* tree):
    m_tree(tree)
/*****************************************************************/
{
    m_tree->Branch("l1t_stage2_tower_n",         &m_tower_n, "l1t_stage2_tower_n/I");
    m_tree->Branch("l1t_stage2_tower_hwEta",     &m_tower_hwEta);
    m_tree->Branch("l1t_stage2_tower_hwPhi",     &m_tower_hwPhi);
    m_tree->Branch("l1t_stage2_tower_hwPt",      &m_tower_hwPhi);
    m_tree->Branch("l1t_stage2_tower_hwEtEm",    &m_tower_hwEtEm);
    m_tree->Branch("l1t_stage2_tower_hwEtHad",   &m_tower_hwEtHad);
    m_tree->Branch("l1t_stage2_tower_hwEtRatio", &m_tower_hwEtRatio);
    m_tree->Branch("l1t_stage2_tower_hwQual",    &m_tower_hwQual);

    m_tree->Branch("l1t_stage2_eg_n",      &m_eg_n, "l1t_stage2_eg_n/I");
    m_tree->Branch("l1t_stage2_eg_pt",     &m_eg_pt);
    m_tree->Branch("l1t_stage2_eg_eta",    &m_eg_eta);
    m_tree->Branch("l1t_stage2_eg_phi",    &m_eg_phi);
    m_tree->Branch("l1t_stage2_eg_hwPt",   &m_eg_hwPt);
    m_tree->Branch("l1t_stage2_eg_hwEta",  &m_eg_hwEta);
    m_tree->Branch("l1t_stage2_eg_hwPhi",  &m_eg_hwPhi);
    m_tree->Branch("l1t_stage2_eg_hwQual", &m_eg_hwQual);
    m_tree->Branch("l1t_stage2_eg_hwIso",  &m_eg_hwIso);

    m_tree->Branch("l1t_stage2_tau_n",      &m_tau_n, "l1t_stage2_tau_n/I");
    m_tree->Branch("l1t_stage2_tau_pt",     &m_tau_pt);
    m_tree->Branch("l1t_stage2_tau_eta",    &m_tau_eta);
    m_tree->Branch("l1t_stage2_tau_phi",    &m_tau_phi);
    m_tree->Branch("l1t_stage2_tau_hwPt",   &m_tau_hwPt);
    m_tree->Branch("l1t_stage2_tau_hwEta",  &m_tau_hwEta);
    m_tree->Branch("l1t_stage2_tau_hwPhi",  &m_tau_hwPhi);
    m_tree->Branch("l1t_stage2_tau_hwQual", &m_tau_hwQual);
    m_tree->Branch("l1t_stage2_tau_hwIso",  &m_tau_hwIso);

}

/*****************************************************************/
L1TStage2Filler::~L1TStage2Filler()
/*****************************************************************/
{
}


/*****************************************************************/
void L1TStage2Filler::fill(const edm::Handle< BXVector<l1t::CaloTower> >& towers, 
                const edm::Handle< BXVector<l1t::EGamma> >& egs,
                const edm::Handle< BXVector<l1t::Tau> >& taus)
/*****************************************************************/
{
    clear();

    for ( auto itr = towers->begin(0); itr != towers->end(0); ++itr ) 
    {
        const l1t::CaloTower& tower = *itr;
        if(tower.hwEtEm()>0 || tower.hwEtHad()>0)
        {
            m_tower_hwEta    .push_back( tower.hwEta()     ); 
            m_tower_hwPhi    .push_back( tower.hwPhi()     );
            m_tower_hwEtEm   .push_back( tower.hwEtEm()    );
            m_tower_hwEtHad  .push_back( tower.hwEtHad()   );
            m_tower_hwEtRatio.push_back( tower.hwEtRatio() );
            m_tower_hwQual   .push_back( tower.hwQual()    );
        }
    }
    m_tower_n = m_tower_hwEta.size();


    m_eg_n = (egs->end(0)-egs->begin(0));
    for ( auto itr = egs->begin(0); itr != egs->end(0); ++itr ) 
    {
        const l1t::EGamma& eg = *itr;
        m_eg_pt    .push_back( eg.pt()     );
        m_eg_eta   .push_back( eg.eta()    );
        m_eg_phi   .push_back( eg.phi()    );
        m_eg_hwPt  .push_back( eg.hwPt()   );
        m_eg_hwEta .push_back( eg.hwEta()  );
        m_eg_hwPhi .push_back( eg.hwPhi()  );
        m_eg_hwQual.push_back( eg.hwQual() );
        m_eg_hwIso .push_back( eg.hwIso()  );
    }

    m_tau_n = (taus->end(0)-taus->begin(0));
    for ( auto itr = taus->begin(0); itr != taus->end(0); ++itr ) 
    {
        const l1t::Tau& tau = *itr;
        m_tau_pt    .push_back( tau.pt()     );
        m_tau_eta   .push_back( tau.eta()    );
        m_tau_phi   .push_back( tau.phi()    );
        m_tau_hwPt  .push_back( tau.hwPt()   );
        m_tau_hwEta .push_back( tau.hwEta()  );
        m_tau_hwPhi .push_back( tau.hwPhi()  );
        m_tau_hwQual.push_back( tau.hwQual() );
        m_tau_hwIso .push_back( tau.hwIso()  );
    }

}


/*****************************************************************/
void L1TStage2Filler::clear()
/*****************************************************************/
{
    m_tower_n = 0;
    m_eg_n = 0;
    m_tau_n = 0;

    m_tower_hwEta    .clear();
    m_tower_hwPhi    .clear();
    m_tower_hwEtEm   .clear();
    m_tower_hwEtHad  .clear();
    m_tower_hwEtRatio.clear();
    m_tower_hwQual   .clear();

    m_eg_pt          .clear();
    m_eg_eta         .clear();
    m_eg_phi         .clear();
    m_eg_hwPt        .clear();
    m_eg_hwEta       .clear();
    m_eg_hwPhi       .clear();
    m_eg_hwQual      .clear();
    m_eg_hwIso       .clear();

    m_tau_pt         .clear();
    m_tau_eta        .clear();
    m_tau_phi        .clear();
    m_tau_hwPt       .clear();
    m_tau_hwEta      .clear();
    m_tau_hwPhi      .clear();
    m_tau_hwQual     .clear();
    m_tau_hwIso      .clear();


}
