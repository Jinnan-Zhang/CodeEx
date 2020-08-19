// $Id:$

/********************************************************************
 * Copyright (C) 2005, Germano Percossi                             *
 *                                                                  *
 * All rights reserved.                                             *
 *                                                                  *
 * For the licensing terms see COPYING file                         *
 ********************************************************************/

#ifndef TSmear_hh
#define TSmear_hh

#ifndef __CINT__

#include "Rtypes.h"
#include "TString.h"
#include "TH2.h"
#include "TF2.h"
#include "TArrayD.h"

#endif // __CINT__

//! A brief description of this class

class TSmear {

private:
  //! Axis general structure
  struct AxisData {
    Int_t fNbins;         ///< Number of bins
    Double_t fAxisLow;    ///< Axis Low Edge
    Double_t fAxisMax;    ///< Axis Max Edge
    TString fOpt;         ///< Scale Options
    TArrayD fBins;        ///< Bin Edges Array
    AxisData();
    AxisData( Int_t nbins, Double_t xlow, Double_t xmax,
	      Option_t *scale = "LIN"
	    );
  };
  Int_t fPID;           ///< Particle ID
  AxisData *fCause;     ///< Causes Axis descriptor
  AxisData *fEffect;    ///< Effects Axis descriptor
  TF2 *fFunction;        ///< Function actually used
  TH2 *fHisto;
  static const char fgElecFormula[];    ///< Electrons' formula
  static const char fgProtFormula[];    ///< Protons' formula
  
public:
  //! Particle enumeration type according to Geant
  enum EPID {
    kCustom = 0,      ///< customizable particle
    kElec = 2,
    kProt = 14
  };

private:
  void InitFunc ( void );

protected:
  void ComputeBinning( AxisData & axis );
  void SetScale( AxisData* , Option_t* );

public:
  TSmear( );
  TSmear( Int_t n_cause , Int_t n_effect , Int_t particleID );
  ~TSmear( );
  void CreateHisto( void );
  Int_t DeleteHisto( void ) { delete fHisto; fHisto = 0; }
  TH2* GetHisto( void ) { return fHisto; }
  TF2* const GetFunc( void ) { return fFunction; }
  Int_t GetNXbins( void ) const { return fCause->fNbins; }
  Int_t GetNYbins( void ) const { return fEffect->fNbins; }
  const Double_t* const GetXbins( void ) const
    { fCause->fBins.GetArray( ); }
  const Double_t* const GetYbins( void )
    { fEffect->fBins.GetArray( ); }
  Double_t GetXmin( void ) const { return fCause->fAxisLow; }
  Double_t GetXmax( void ) const { return fCause->fAxisMax; }
  Double_t GetYmin( void ) const { return fEffect->fAxisLow; }
  Double_t GetYmax( void ) const { return fEffect->fAxisMax; }
  void SetCauseScale( Option_t* scale ) { SetScale( fCause, scale ); }
  void SetEffectScale( Option_t* scale )
    { SetScale( fEffect, scale ); }

};

#endif // TSmear_hh
