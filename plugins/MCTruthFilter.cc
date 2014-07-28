#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TTree.h"


class MCTruthFilter : public edm::EDFilter 
{

    private:
        int m_pid;
        edm::InputTag m_genParticlesTag;

        int m_nrPass;
        int m_nrTot;

    public:
        explicit MCTruthFilter(const edm::ParameterSet& para);
        ~MCTruthFilter(){}

        virtual bool filter(edm::Event& event,const edm::EventSetup& setup);
        virtual void endJob();
};

MCTruthFilter::MCTruthFilter(const edm::ParameterSet& para):
    m_nrPass(0),
    m_nrTot(0)
{
    m_genParticlesTag = para.getParameter<edm::InputTag>("genParticlesTag");
    m_pid = para.getParameter<int>("pid");
}

bool MCTruthFilter::filter(edm::Event& event,const edm::EventSetup& setup)
{
    edm::Handle<reco::GenParticleCollection> genParticles;
    event.getByLabel(m_genParticlesTag,genParticles);
    bool pass=false;
    if(!genParticles.isValid()) pass=true;
    else pass=genParticles->at(7).pdgId()==m_pid;

    m_nrTot++;
    if(pass)
    {
        m_nrPass++;
        return true;
    }
    else return false;

}
void MCTruthFilter::endJob()
{
    // edm::Service<TFileService> fs;
    // fs->file().cd();
    //quick and dirty hack as writing ints directly isnt working
    // TTree* tree = new TTree("preFilterEventCountTree","Event count");
    // tree->Branch("nrPass",&nrPass_,"nrPass/I");
    // tree->Branch("nrTot",&nrTot_,"nrTot/I");
    // tree->Fill();

}




DEFINE_FWK_MODULE(MCTruthFilter);
