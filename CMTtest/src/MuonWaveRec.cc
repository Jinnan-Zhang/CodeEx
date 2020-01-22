#ifndef MuonWaveRec_cc
#define MuonWaveRec_cc
#include "MuonWaveRec.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "EvtNavigator/NavBuffer.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "SniperKernel/SniperPtr.h"
#include "RootWriter/RootWriter.h"
#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "Event/ElecHeader.h"
#include "Event/CalibHeader.h"
#include "Identifier/CdID.h"
#include <TFile.h>
#include "TROOT.h"
#include <iostream>
#include <TTree.h>
#include <sstream>
#include "TVirtualFFT.h"
#include "math.h"
#include "TH1D.h"
using namespace std;

DECLARE_ALGORITHM(MuonWaveRec);

MuonWaveRec::MuonWaveRec(const string& name): AlgBase(name)
					    , m_threshold(0.1)
					    , m_length(1250)
					    , m_totalPMT(17739)
{
  declProp("Threshold", m_threshold);
  declProp("Length", m_length);
  declProp("TotalPMT", m_totalPMT);
}

MuonWaveRec::~MuonWaveRec(){}

bool MuonWaveRec::initialize(){

  m_memMgr = SniperPtr<IDataMemMgr>(getParent(), "BufferMemMgr").data();

  SniperPtr<RootWriter> svc(getParent(), "RootWriter");
  if(svc.invalid()){
    LogError << "Failed to locate RootWriter!" << endl;
    return false;
  }

  gROOT->ProcessLine("#include <vector>");

  m_calib = svc->bookTree("CALIBEVT", "simple output of calibration data");
  m_calib->Branch("Charge", &m_charge);
  m_calib->Branch("Time", &m_time);
  m_calib->Branch("PMTID", &m_pmtId);
  m_calib->Branch("TotalPE", &m_totalpe, "TotalPE/F");

  return true;

}

bool MuonWaveRec::execute(){

  LogDebug << "start muon waveform reconstruction" << endl;

  //
  m_charge.clear();
  m_time.clear();
  m_pmtId.clear();
  m_totalpe = 0.;

  // read the event from elec sim file
  SniperDataPtr<JM::NavBuffer> navBuf(getParent(), "/Event");
  JM::EvtNavigator *nav = navBuf->curEvt();
  JM::ElecHeader *eh = dynamic_cast<JM::ElecHeader*>(nav->getHeader("/Event/Elec"));
  JM::ElecEvent *ee = dynamic_cast<JM::ElecEvent*>(eh->event());
  const JM::ElecFeeCrate &efc = ee->elecFeeCrate();
  m_crate = const_cast<JM::ElecFeeCrate*>(&efc);

  map<int, JM::ElecFeeChannel> feeChannels = m_crate->channelData();

  list<JM::CalibPMTChannel*> cpcl;//Calib PMT Channel List

  map<int, JM::ElecFeeChannel>::iterator it;

  // loop over PMTs
  for(it=feeChannels.begin(); it!=feeChannels.end(); ++it){

    // check if PMT IDs are valid
    int pmtID = it->first;
    if(pmtID > m_totalPMT) continue;

    // retrieve channel data & check if ok
    JM::ElecFeeChannel &channel = it->second;
    if(channel.adc().size()==0){
      continue;
    }
    if(channel.adc().size()!=m_length){
      LogError << "Length of the electronics simulation data is " << channel.adc().size() << " ns." << endl;
      LogError << "Length of the pre-defined length of muon waveform reco is " << m_length << " ns." << endl;
      LogError << "ERROR: inconsistent waveform length in the unfolding!" << endl;
      return false;
    }

    //int pmtID = it->first;
    double nPE = 0.;
    double firstHitTime = 0.;
    double riseTime = 0.;
    vector<double> charge;
    vector<double> time;

    // do muon waveform reco
    bool status = waveReco(channel, charge, time, riseTime);
    if(status == false){
      LogError << "Error when doing the muon waveform reconstruction!" << endl;
      return false;
    }

    // check if threshold is passed
    if(charge.size() == 0 || charge.size() != time.size()) continue; // threshold is not passed

    // convert pmtID
    unsigned int detID = CdID::id(static_cast<unsigned int>(pmtID), 0);
    for(int i=0; i<charge.size(); i++){
      nPE += charge.at(i);
      m_charge.push_back(charge.at(i));
      m_time.push_back(time.at(i));
      m_pmtId.push_back(detID);
    }
    m_totalpe += nPE;
    firstHitTime = time.at(0);

    // set relevant quantities
    JM::CalibPMTChannel *cpc = new JM::CalibPMTChannel;
    cpc->setNPE(nPE);
    cpc->setPmtId(detID);
    cpc->setFirstHitTime(firstHitTime);
    cpc->setRiseTime(riseTime);
    cpc->setTime(time);
    cpc->setCharge(charge);
    cpcl.push_back(cpc);

  }

  // fill user output data
  m_calib->Fill();
  
  // set cpcl and event
  JM::CalibEvent *ce = new JM::CalibEvent;
  ce->setCalibPMTCol(cpcl);
  JM::CalibHeader *ch = new JM::CalibHeader;
  ch->setEvent(ce);
  nav->addHeader("/Event/Calib", ch);

  LogDebug << "end muon waveform reconstruction" << endl; 

  return true;
  
}

bool MuonWaveRec::finalize(){

  return true;

}



bool MuonWaveRec::waveReco(JM::ElecFeeChannel &channel, std::vector<double> &charge, std::vector<double> &time, double &riseTime){

  // temp: riseTime
  riseTime = 5.;

  // get FADC output
  vector<unsigned int>& adc_int = channel.adc();
  if(adc_int.size()==0){
    return false;
  }

  // recover physical waveform
  vector<double> adc;
  for(int i=0; i<adc_int.size(); i++){
    if(adc_int.at(i)>>8 == 0) adc.push_back(double(adc_int.at(i)));
    else if(adc_int.at(i)>>8 == 1) adc.push_back((double(adc_int.at(i)) - (1<<8)) * .4/.06);
    else if(adc_int.at(i)>>8 == 2) adc.push_back((double(adc_int.at(i)) - (2<<8)) * 8./.06);
    else adc.push_back(255.*8./.06);
  }

  // baseline correction
  double baseline = 0.; // determine baseline
  for(int i=0; i<100; i++){ // use first 100 bins
    baseline+=adc.at(i);
  }
  baseline/=100.;
  vector<double>& adc_baselineCorr = adc; // correct for baseline
  if(adc.size() != adc_baselineCorr.size()){
    std::cout << "WARNING: vectors adc and adc_baselineCorr don't have same size." << std::endl;
  }
  for(int i=0; i<adc.size(); i++){
    adc_baselineCorr.at(i) -= baseline;
  }

  // determine charge
  double temp_charge = 0.;
  for(int i=0; i<m_length; i++){
    temp_charge += adc_baselineCorr.at(i);
  }
  temp_charge /= 251.; // 251. has been found as optimal number in study

  // determine first hit time
  int maxX_glob = 0; // determine global maximum
  double maxY_glob = 0.;
  for(int i=0; i<m_length; i++){
    if(adc.at(i) > maxY_glob){
      maxX_glob = i;
      maxY_glob = adc_baselineCorr.at(i);
    }
  }
  double temp_time = 0; // search threshold of waveform by going to earlier times
  for(int i=maxX_glob; i>0; i--){
    if(adc_baselineCorr.at(i) < m_threshold * maxY_glob){
      temp_time = i - .5 + (m_threshold * maxY_glob - adc_baselineCorr.at(i)) / (adc_baselineCorr.at(i+1) - adc_baselineCorr.at(i));
      break;
    }
  }

  // determine rise time
  double temp_riseTime_lo = 0.;
  double temp_riseTime_up = 0.;
  for(int i=0; i<maxX_glob+1; i++){ // determine begin of rise time
    if(adc_baselineCorr.at(i) > .1 * maxY_glob){ // rise time begins when waveform reaches 10% of its maximum height
      //temp_riseTime_lo = i + (adc_baselineCorr.at(i) - .1*maxY_glob) / (adc_baselineCorr.at(i) - adc_baselineCorr.at(i-1)); // interpolate within bin
      temp_riseTime_lo = i - 1.5 + (.1 * maxY_glob - adc_baselineCorr.at(i-1)) /  (adc_baselineCorr.at(i) - adc_baselineCorr.at(i-1)); // interpolate within bin
      break;
    }
  }
  for(int i=0; i<maxX_glob+1; i++){ // determine end of rise time
    if(adc_baselineCorr.at(i) > .9 * maxY_glob){ // rise time ends when waveform reaches 90% of its maximum height
      //temp_riseTime_up = i + (adc_baselineCorr.at(i) - .1*maxY_glob) / (adc_baselineCorr.at(i) - adc_baselineCorr.at(i-1)); // interpolate within bin
      temp_riseTime_up = i - 1.5 + (.9 *maxY_glob - adc_baselineCorr.at(i-1)) / (adc_baselineCorr.at(i) - adc_baselineCorr.at(i-1)); // interpolate within bin
      break;
    }
  }
  riseTime = double(temp_riseTime_up - temp_riseTime_lo);

  // push charge and time values to vector
  charge.push_back(temp_charge);
  time.push_back(temp_time);

  return true;

}

#endif
