/**
 *  @file  L1TStage1Filler.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    06/27/2014
 *
 *  @internal
 *     Created :  06/27/2014
 * Last update :  06/27/2014 02:57:49 PM
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */






#ifndef L1TSTAGE1FILLER_H
#define L1TSTAGE1FILLER_H

#include <vector>


namespace l1t
{
    class EGamma;
    class Tau;
}

class TTree;

class L1TStage1Filler
{
    public:
        L1TStage1Filler(TTree* tree);
        ~L1TStage1Filler();
        void fill(const edm::Handle< BXVector<l1t::EGamma> >& egs,
                const edm::Handle< BXVector<l1t::Tau> >& taus);
        void clear();

    private:
        TTree* m_tree;

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
