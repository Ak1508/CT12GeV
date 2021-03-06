// Filename: CTRun.h
// Description: 
// Author: Latif Kabir < latif@jlab.org >
// Created: Tue Oct 17 18:10:57 2017 (-0400)
// URL: jlab.org/~latif

#ifndef CTRUN_H
#define CTRUN_H

#include <iostream>
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"

class CTRun: public TObject
{
    TString fFileName;
    TString fSimcFileName;
    Int_t fRunNumber;
    Int_t fLastRun;
    Int_t fFirstRun;
    void Init();
    void Init(TString file_name);
    void SetBranchAddressCT();
    void SetBranchAddressSimc();
    TFile *fFile;
    TFile *fSimcFile;
    TChain *fChain;
    TChain *fSimcChain;
    Int_t fRunCounter;
    Int_t fSimcFileCounter;
    
    //---Cut values ----
    //beta cut
    Double_t fPBetaMin;
    Double_t fPBetaMax;
    Double_t fHBetaMin;
    Double_t fHBetaMax;

    //Cerenkov Counter cut
    Double_t fPCerMin;
    Double_t fPCerMax;
    Double_t fPnCerMin;
    Double_t fPnCerMax;
    Double_t fHCerMin;
    Double_t fHCerMax;

    // Calorimeter Cut
    Double_t fPCalMin;
    Double_t fPCalMax;
    Double_t fHCalMin;
    Double_t fHCalMax;

    //Pre-shower counter
    Double_t fPPreShMin;
    Double_t fPPreShMax;
    Double_t fHPreShMin;
    Double_t fHPreShMax;
    
public:
    
    CTRun(Int_t runNumber);
    CTRun(TString fileName);
    CTRun();
    CTRun(Int_t firstRun, Int_t lastRun);
    ~CTRun();

    Bool_t fRunExist;
    Bool_t fSimcExist;
    TString fCTcut;
    TEventList * fCTEvents;
    
    void Print();
    TTree* GetTree();
    TChain* GetChain();
    TTree* GetSimcTree();
    TChain* GetSimcChain();

    Int_t GetRunNumber();
    void ActivateCTBranches();
    void AddSimc(TString SimcFileName, Int_t makeFriend = -1); //Set makeFriend to any value other than -1 to add as friend

    //max = -1 means set no upper bound
    //min = -1 means set no lower bound
    void DefinePBetaCut(Double_t min = -1, Double_t max = -1); 
    void DefineHBetaCut(Double_t min = -1, Double_t max = -1);
    void DefinePCerCut(Double_t min = -1, Double_t max =-1);
    void DefinePnCerCut(Double_t min = -1, Double_t max =-1);
    void DefineHCerCut(Double_t min = -1, Double_t max = -1);
    void DefinePCalCut(Double_t min = -1, Double_t max =-1);
    void DefineHCalCut(Double_t min = -1, Double_t max = -1);
    void DefinePPreShCut(Double_t min = -1, Double_t max =-1);
    void DefineHPreShCut(Double_t min = -1, Double_t max = -1);
    void SetDefaultCut();
    void PrintCut();
    void ClearCut();
    
    void ApplyCut();
    //==========================================================================
    //                      All branch/Leaf Variables from Data
    //==========================================================================
    //------------ Kinematics ----------------------------
    //SHMS
    Double_t fP_kin_secondary_pmiss;
    Double_t fP_kin_secondary_pmiss_x;
    Double_t fP_kin_secondary_pmiss_y;
    Double_t fP_kin_secondary_pmiss_z;
    Double_t fP_kin_secondary_emiss;
    Double_t fP_kin_secondary_emiss_nuc;
    Double_t fP_DC_reftime;
    Double_t fP_DC_tdcmultipl;

    //HMS
    Double_t fH_kin_primary_W;
    Double_t fH_kin_primary_Q2;
    Double_t fH_kin_primary_nu;
    
    //------------- Golden Track Quantities -----------------
    //SHMS
    Double_t fP_gtr_p;
    Double_t fP_gtr_dp;
    Double_t fP_gtr_beta;
    //HMS
    Double_t fH_gtr_p;
    Double_t fH_gtr_dp;
    Double_t fH_gtr_beta;

    //--------- Vertex/Target Coord --------------
    //SHMS
    Double_t fH_gtr_x;
    Double_t fH_gtr_th;    
    Double_t fH_gtr_y;
    Double_t fH_gtr_ph;

    //HMS
    Double_t fP_gtr_x;
    Double_t fP_gtr_th;    
    Double_t fP_gtr_y;
    Double_t fP_gtr_ph;
    
    // --------- Drift Chamber ----------------
    //SHMS
    Double_t fP_dc_x_fp;
    Double_t fP_dc_xp_fp;
    Double_t fP_dc_y_fp;
    Double_t fP_dc_yp_fp;

    //HMS
    Double_t fH_dc_x_fp;
    Double_t fH_dc_xp_fp;
    Double_t fH_dc_y_fp;
    Double_t fH_dc_yp_fp;

    //------------ Cerenkov Counter ----------
    //SHMS
    Double_t fP_hgcer_npeSum;
    Double_t fP_ngcer_npeSum;
    
    //HMS
    Double_t fH_cer_npeSum;
    
    //------------ Hodoscope ---------------
    //SHMS
    Double_t fP_hod_goodstarttime;
    Double_t fP_hod_starttime;
    Double_t fP_hod_fpHitsTime;
    Double_t fP_hod_1xnhits;
    Double_t fP_hod_1ynhits;
    Double_t fP_hod_2xnhits;
    Double_t fP_hod_2ynhits;

    //HMS
    Double_t fH_hod_goodstarttime;    
    Double_t fH_hod_starttime;
    Double_t fH_hod_fpHitsTime;

    //--------- Calorimeter ---------------
    //SHMS
    Double_t fP_cal_eprtracknorm;
    Double_t fP_cal_etottracknorm;
    Double_t fP_cal_eprtrack;
    Double_t fP_cal_etrack;
    Double_t fP_cal_etot;

    //HMS
    Double_t fH_cal_eprtracknorm;
    Double_t fH_cal_etottracknorm;
        
    //--------- Trigger ----------------
    //SHMS
    Double_t fT_coin_pTRIG1_ROC1_tdcTimeRaw;
    Double_t fT_coin_pTRIG4_ROC1_tdcTimeRaw;
    Double_t fT_coin_pTRIG1_ROC2_tdcTimeRaw;
    Double_t fT_coin_pTRIG4_ROC2_tdcTimeRaw;

    //HMS
    Double_t fT_coin_hTRIG1_ROC1_tdcTimeRaw;
    Double_t fT_coin_hTRIG4_ROC1_tdcTimeRaw;
    Double_t fT_coin_hTRIG1_ROC2_tdcTimeRaw;
    Double_t fT_coin_hTRIG4_ROC2_tdcTimeRaw;

    //----------- Event Type ---------------
    //Int_t EvtType;
    Double_t EvtType;  // GetLeaf()->GetValue() returns double only

    //==========================================================================
    //                      All branch/Leaf Variables from Simc
    //==========================================================================
    //HMS
    Float_t fHSdelta;
    Float_t fHSxptar;
    Float_t fHSyptar;
    Float_t fHSytar;
    Float_t fHSxfp;
    Float_t fHSxpfp;
    Float_t fHSyfp;
    Float_t fHSypfp;

    //SHMS
    Float_t fPSdelta;
    Float_t fPSxptar;
    Float_t fPSyptar;
    Float_t fPSytar;
    Float_t fPSxfp;
    Float_t fPSxpfp;
    Float_t fPSyfp;
    Float_t fPSypfp;

    Float_t fWeight;
    
    Float_t fW;
    Float_t fEm;
    Float_t fPm;
    Float_t fPmx;
    Float_t fPmy;
    Float_t fPmz;
    Float_t fHcorsi;
    
    ClassDef(CTRun,0)
};

#endif
