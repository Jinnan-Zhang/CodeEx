// $Id:$

/********************************************************************
 * Copyright (C) 2005, Germano Percossi                             *
 *                                                                  *
 * All rights reserved.                                             *
 *                                                                  *
 * For the licensing terms see COPYING file                         *
 ********************************************************************/

/*!
    @class TSmear
    @author Germano Percossi
    @date 24/06/2005
    
    A Class to be described
*/

#ifndef __CINT__

#include <iostream>
#include "TH2D.h"
#include "TMath.h"

#endif // __CINT__



using std::cout;
using std::endl;
using TMath::Power;

const char TSmear::fgProtFormula[] = {
  "([0]+[1]*exp(-x/[2])) * exp(-y/ ([3]+[4]*x) ) "
  "+ [5]*exp(-exp(-(y-([6]+[7]*x+[8]*pow(x,2)))/[9]) "
  "- (y-([6]+[7]*x+[8]*pow(x,2)))/[9] + 1)"
};

const char TSmear::fgElecFormula[] = {
  "[0] + ([1]/(([2]+[3]*x)*sqrt(2 * 3.14159))) "
  " * exp(-pow((y-([4]+[5]*x))/([2]+[3]*x),2)/2)"
  " * ( 1"
  " + (([6]+[7]*exp(-x/[8]))/6) * ("
  " pow((y-([4]+[5]*x))/([2]+[3]*x) ,3)"
  " - 3*((y-([4]+[5]*x))/([2]+[3]*x))"
  " )"
  " + ([9]/24) * ("
  " pow((y-([4]+[5]*x))/([2]+[3]*x) ,4)"
  " - 6*pow((y-([4]+[5]*x))/([2]+[3]*x) ,3) +3"
  " )"
  " )"
};


//____________________________________________________________________
/*!

*/
TSmear::TSmear( )
{
  fPID = -1;
  fCause = new AxisData( );
  fEffect = new AxisData( );
  fFunction = 0;
  fHisto = 0;
}

//____________________________________________________________________
/*!
   A constructor with arguments.

   @param[in] n_cause Number of bins dedicated to Causes:
          they are on the X scale of matrix.
   @param[in] n_effect Number of bins dedicated to Effects:
          they are on the Y scale of matrix.
   @param[in] particleID Defines particle according to enum type EPID
   @param[in] formula If a customizable particle is selected, this
          parameter matters and a valid formula must be supplied. \n
          In this case the only way to set up a function is to ask
          for its pointer via GetFunc( void ) and do the necessary
          step by yourself. \n Be careful!!!
*/
TSmear::TSmear( Int_t n_cause , Int_t n_effect , Int_t particleID )
{
  if ( (n_cause <= 0) || (n_effect <=0) )
    return;

  fFunction = 0;
  fHisto = 0;
  fCause = new AxisData( n_cause, 5, 350 );
  fEffect = new AxisData( n_effect, 1e-3, 10 );

  // Check for existing type of particle: if it fails, custom
  // is the default.
  switch ( particleID ) {
  case kElec :
    break;
  case kProt :
    break;
  default :
    particleID = kCustom;
  }
  fPID = particleID;

  InitFunc( );
  ComputeBinning( *fCause );
  ComputeBinning( *fEffect );
}


//____________________________________________________________________
/*!
   
 */
TSmear::AxisData::AxisData( ) :
  fBins( )
{
  fNbins = 0;
  fAxisLow = 0;
  fAxisMax = 0;
  fOpt = "LIN";
}


//____________________________________________________________________
/*!

*/
TSmear::AxisData::AxisData( Int_t nbins, Double_t xlow, Double_t xmax,
			    Option_t *scale
			  ) :
  fOpt( scale ) ,
  fBins( nbins +1 )
{
  fNbins = nbins;
  fAxisLow = xlow;
  fAxisMax = xmax;
}


//____________________________________________________________________
/*!

*/
TSmear::~TSmear()
{
  delete fHisto;
  fHisto = 0;
  delete fCause;
  delete fEffect;
  fCause = fEffect = 0;
}


//____________________________________________________________________
/*!
   This function effectively takes care of binning according
   to options and data stored in the axis.
   @param[in,out] axis The axis where binning will take place.
*/
void TSmear::ComputeBinning( AxisData & axis )
{
  Double_t *array, range, step;
  Int_t idx;

  array = axis.fBins.GetArray( );
  array[0] = axis.fAxisLow;
  array[axis.fNbins] = axis.fAxisMax;

  if ( axis.fOpt == "LIN" ) {
    range = axis.fAxisMax - axis.fAxisLow;
    step = range / axis.fNbins;
    for ( idx = 1 ; idx < axis.fNbins ; idx++ )
      array[idx] = array[idx -1] + step;
  }
  else { // LOG case
    range = axis.fAxisMax / axis.fAxisLow;
    step = Power( range , 1.0 / axis.fNbins );
    for ( idx = 1 ; idx < axis.fNbins ; idx++ )
      array[idx] = array[idx -1] * step;
  }
}


//____________________________________________________________________
/*!
   If an histo already exists, is harmless.
   Otherwise a fresh one will be created according to fFunction,
   selected particle and AxisData values. \n
   Correct normalization is achieved using a numerical trick.
*/
void TSmear::CreateHisto( void )
{
  Int_t xNbins, yNbins;
  Double_t *xbin, *ybin;

  if ( fHisto )
    return;

  TString name( "smearing" );
  switch ( fPID ) {
  case kElec :
    name += "_elec";
    break;
  case kProt :
    name += "_prot";
    break;
  }

  xNbins = fCause->fNbins;
  yNbins = fEffect->fNbins;
  xbin = fCause->fBins.GetArray( );
  ybin = fEffect->fBins.GetArray( );

  fHisto = new TH2D( name.Data() , name.Data() ,
                     xNbins      , xbin        ,
                     yNbins      , ybin
                   );

  Int_t ix, jy, kx, minibin = 50;
  Double_t value, step, k, tmp, Norm;
  Double_t min[2]; Double_t max[2];
  for( ix = 0; ix < xNbins; ix++ ) {
     step = ( xbin[ix+1] - xbin[ix] ) / minibin;
    for( jy = 0 ; jy < yNbins; jy++ ) {
      k = xbin[ix];
      value = 0;
      for( kx = 0 ; kx < minibin; kx++ ) {

         //tmp = fFunction->Integral( k        , k + step   ,
         //                       ybin[jy] , ybin[jy+1]
         //                     );
         Int_t nevl, ifail;
         Double_t relerr;
         min[0]=k; min[1]=ybin[jy]; max[0]=k+step; max[1]=ybin[jy+1];
         tmp = fFunction->IntegralMultiple(2, min, max, 17, 10000, 0.001, relerr, nevl, ifail);
         if (ifail==1) {
            fFunction->SetRange(k,ybin[jy], k+step, ybin[jy+1]);
            fFunction->Draw("lego"); return;
         }

        Norm = fFunction->Integral( k       , k + step     ,
                                   ybin[0] , ybin[yNbins]
                                 );
        value += (tmp / Norm);
        k+=step;
      }
      value /= (xbin[ix+1] - xbin[ix]) * minibin;
      fHisto->SetBinContent( ix + 1 , jy + 1 , value );
    }
  }
}


//____________________________________________________________________
/*!
   Initialize function : name, formula and parameters are set.\n
   The formula is chosen according to selected particle.
*/
void TSmear::InitFunc( void )
{
  // Set TF1 attributes depending on particle
  switch ( fPID ) {
  case kElec :
    fFunction = new TF2( "electron_func", fgElecFormula );
    fFunction->SetParameters( 0.0     , 9.2    , 0.00139 ,
			      0.00089 , 0.0378 , 0.0246  ,
			      -1      , 1.42   , 35      ,
			      0.1
			    );
    break;
  case kProt :
    fFunction = new TF2( "proton_func", fgProtFormula );
    fFunction->SetParameters( 38.0    , 150.0      , 13.0        ,
                             0.117   , 0.00407    , 21600.0     ,
                             0.00629 , 1.28335e-6 , -1.79408e-9 ,
                             0.0009
                           );
    break;
  default : // kCustom
    return; // cannot handle default cases
  }

  fFunction->SetRange( fCause->fAxisLow , fEffect->fAxisLow ,
                      fCause->fAxisMax , fEffect->fAxisMax
                    );
}


//____________________________________________________________________
/*!
   Set axis scale according to specified options. \n
   Checks are done to ensure correct options. \n
   This function cannot be called directly; use
   SetCauseScale(Option_t*) or SetEffectScale(Option_t*): \n
   this avoid wrong axis to be passed. \n
   At the end rebinning is made calling proper function.
   @param[in,out] axis  Axis to change
   @param[in]     scale Type of scale to use for binning. \n
               Valid options are: \n
                 "LIN" - bin size equal to preceding one \n
                 "LOG" - bin size equal to preceding one multiplied \n
                         for a given factor
*/
void TSmear::SetScale( AxisData* axis, Option_t* scale )
{
  TString tmp( scale );
  tmp.ToUpper( );
  if ( tmp != "LIN" ) {
    if ( tmp != "LOG" )
      return;
  }
  (*axis).fOpt = tmp;

  ComputeBinning( *axis );
}

