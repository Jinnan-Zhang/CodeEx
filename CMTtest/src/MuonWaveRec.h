#ifndef MuonWaveRec_h
#define MuonWaveRec_h

#include "SniperKernel/AlgBase.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "TTree.h"
#include "TH1D.h"
#include <vector>

class ElecFeeCrate;
class DataBuffSvcV2;

namespace JM{
  class ElecFeeCrate;
  class ElecFeeChannel;
  class CalibHeader;
}

class MuonWaveRec: public AlgBase
{

 public:
  MuonWaveRec(const std::string& name);

  ~MuonWaveRec();

  bool initialize();
  bool execute();
  bool finalize();

 private:

  bool waveReco(JM::ElecFeeChannel &channel, std::vector<double> &charge, std::vector<double> &time, double &riseTime);
  
  IDataMemMgr* m_memMgr;

  JM::ElecFeeCrate *m_crate;

  double m_threshold;
  int m_length;
  int m_totalPMT;	

  //user data
  TTree* m_calib;
  std::vector<float> m_charge;
  std::vector<float> m_time;
  std::vector<int> m_pmtId;
  float m_totalpe;

};

#endif
