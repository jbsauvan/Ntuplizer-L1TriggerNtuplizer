/**
 *  @file  L1TStage2Filler.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    06/25/2014
 *
 *  @internal
 *     Created :  06/25/2014
 * Last update :  06/25/2014 05:17:24 PM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */




#ifndef L1TSTAGE2FILLER_H
#define L1TSTAGE2FILLER_H

#include <vector>


namespace l1t
{
    class CaloTower;
    class EGamma;
    class Tau;
}

class TTree;

class L1TStage2Filler
{
    public:
        L1TStage2Filler(TTree* tree);
        ~L1TStage2Filler();
        void fill(const edm::Handle< BXVector<l1t::CaloTower> >& towers, 
                const edm::Handle< BXVector<l1t::EGamma> >& egs,
                const edm::Handle< BXVector<l1t::Tau> >& taus);
        void clear();

    private:
        TTree* m_tree;

        // towers
        int              m_tower_n;
        std::vector<int> m_tower_hwEta;
        std::vector<int> m_tower_hwPhi;
        std::vector<int> m_tower_hwEtEm;
        std::vector<int> m_tower_hwEtHad;
        std::vector<int> m_tower_hwEtRatio;
        std::vector<int> m_tower_hwQual;

        // egammas
        int                 m_eg_n;
        std::vector<double> m_eg_pt;
        std::vector<double> m_eg_eta;
        std::vector<double> m_eg_phi;
        std::vector<int>    m_eg_hwPt;
        std::vector<int>    m_eg_hwEta;
        std::vector<int>    m_eg_hwPhi;
        std::vector<int>    m_eg_hwQual;
        std::vector<int>    m_eg_hwIso;

        // taus
        int                 m_tau_n;
        std::vector<double> m_tau_pt;
        std::vector<double> m_tau_eta;
        std::vector<double> m_tau_phi;
        std::vector<int>    m_tau_hwPt;
        std::vector<int>    m_tau_hwEta;
        std::vector<int>    m_tau_hwPhi;
        std::vector<int>    m_tau_hwQual;
        std::vector<int>    m_tau_hwIso;
};

#endif
