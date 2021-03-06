// Filename: CTpidCut.cc
// Description: Look at some Kinematc/Coin distributions (with cut) by looping over each event.
// Author: Latif Kabir < latif@jlab.org >
// Created: Thu Jan  4 17:03:26 2018 (-0500)
// URL: jlab.org/~latif

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TLeaf.h>
#include "Constants.h"

using namespace std;

void CTpidCut()
{
    TString fileName = ROOT_FILE_PATH;
    fileName += "coin_replay_production_1711_1000000.root";
    // fileName += "coin_replay_production_1711_evt7.root";

    Bool_t runNotFound = gSystem->AccessPathName(fileName);
    if(runNotFound)
    {	    
	cout << "Requested file " << fileName << " does NOT exist" <<endl;
	return;
    }
    
    TFile *file = new TFile(fileName);
    TTree *tree = (TTree*)file->Get("T");    
    //tree->Print();

    //----------------- Kinematic Histograms ------------------------------
    TH1D *h1PgtrBeta = new TH1D("P.gtr.beta", "P.gtr.beta; #beta ", 500, 0, 2);
    TH1D *h1PkinPrimaryW2 = new TH1D("P.kin.primary.W", "P.kin.primary.W; W", 400, 0.8, 1.6);
    TH1D *h1PkinPrimaryQ2 = new TH1D("P.kin.primary.Q2", "P.kin.primary.Q2; Q^{2}", 500, 0, 2);
    TH1D *h1PkinPrimaryNu = new TH1D("P.kin.primary.nu", "P.kin.primary.nu; #nu", 500, 0, 2);

    TH1D *h1HgtrBeta = new TH1D("H.gtr.beta", "H.gtr.beta; #beta", 500, 0, 2);
    TH1D *h1HkinSecondaryPmiss = new TH1D("H.kin.secondary.pmiss", "H.kin.secondary.pmiss; p_{m}", 600, -0.1, 0.5);
    TH1D *h1HkinSecondaryPmiss_x = new TH1D("H.kin.secondary.pmiss_x", "H.kin.secondary.pmiss_x; p_{m x}", 600, -0.1, 0.5);
    TH1D *h1HkinSecondaryEmiss = new TH1D("H.kin.secondary.emiss", "H.kin.secondary.emiss; E_{m}", 600, -0.3, 0.3);

    //----------------------- Histogram for coincidence time ----------------------------
    TH1D *h1PcointimeROC1 = new TH1D("SHMS ROC1_tdcTimeRaw*0.1 difference","SHMS ROC1_tdcTimeRaw*0.1 difference; cointime [ns]", 200, -20, 20);
    TH1D *h1PcointimeROC2 = new TH1D("SHMS ROC2_tdcTimeRaw*0.1 difference","SHMS ROC2_tdcTimeRaw*0.1 difference; cointime [ns]", 300, -15, 15);
    TH1D *h1HcointimeROC1 = new TH1D("HMS ROC1_tdcTimeRaw*0.1 difference","HMS ROC1_tdcTimeRaw*0.1 difference; cointime [ns]", 400, -40, 40);
    TH1D *h1HcointimeROC2 = new TH1D("HMS ROC2_tdcTimeRaw*0.1 difference","HMS ROC2_tdcTimeRaw*0.1 difference; cointime [ns]", 400, -40, 40);

    //Kinematics
    Double_t PgtrBeta;
    Double_t PkinPrimaryW;
    Double_t PkinPrimaryQ2;
    Double_t PkinPrimaryNu;
    
    Double_t HgtrBeta;        
    Double_t HkinSecondaryPmiss;
    Double_t HkinSecondaryPmiss_x;
    Double_t HkinSecondaryEmiss;

    //Detector Response
    Double_t PcalEprTrackNorm;
    Double_t PcalEtotTrackNorm;
    Double_t PhgcerNpeSum;
    Double_t HcerNpeSum;

    //Trigger 
    Double_t TcoinpTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC2_tdcTimeRaw;
    
    Double_t TcoinhTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC2_tdcTimeRaw;
        
    //Int_t EvtType;
    Double_t EvtType;  // GetLeaf()->GetValue() returns double only
    
    tree->SetBranchAddress("P.gtr.beta", &PgtrBeta);    
    tree->SetBranchAddress("P.kin.primary.W", &PkinPrimaryW);
    tree->SetBranchAddress("P.kin.primary.Q2", &PkinPrimaryQ2);
    tree->SetBranchAddress("P.kin.primary.nu", &PkinPrimaryNu);
    
    tree->SetBranchAddress("H.gtr.beta", &HgtrBeta);
    tree->SetBranchAddress("H.kin.secondary.pmiss", &HkinSecondaryPmiss);
    tree->SetBranchAddress("H.kin.secondary.pmiss_x", &HkinSecondaryPmiss);
    tree->SetBranchAddress("H.kin.secondary.pmiss_x", &HkinSecondaryPmiss_x);
    tree->SetBranchAddress("H.kin.secondary.emiss", &HkinSecondaryEmiss);

    tree->SetBranchAddress("P.cal.eprtracknorm", &PcalEprTrackNorm);
    tree->SetBranchAddress("P.cal.etottracknorm", &PcalEtotTrackNorm);
    tree->SetBranchAddress("P.hgcer.npeSum", &PhgcerNpeSum);
    tree->SetBranchAddress("H.cer.npeSum", &HcerNpeSum);
    
    tree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &TcoinpTRIG1_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &TcoinpTRIG4_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &TcoinpTRIG1_ROC2_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &TcoinpTRIG4_ROC2_tdcTimeRaw);

    tree->SetBranchAddress("T.coin.hTRIG1_ROC1_tdcTimeRaw", &TcoinhTRIG1_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG4_ROC1_tdcTimeRaw", &TcoinhTRIG4_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG1_ROC2_tdcTimeRaw", &TcoinhTRIG1_ROC2_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG4_ROC2_tdcTimeRaw", &TcoinhTRIG4_ROC2_tdcTimeRaw);
       
    //tree->SetBranchAddress("fEvtHdr.fEvtType", &EvtData);  // This branch has some problem at this moment, SetBranchAddress() does not work. It's a nested branch.

    Int_t nEvents = tree->GetEntries();
    cout << "Number of events: "<< nEvents <<endl;

    //Naively correction for path length and focal length
    Double_t pROC1Offset = 320;
    Double_t pROC2Offset = 320;
    Double_t hROC1Offset = -2915;
    Double_t hROC2Offset = -3600;
    
    for (Int_t event = 0; event < nEvents; ++event)
    {
	if(event%10000 == 0)
	    cout << (Int_t)(100*event/nEvents) <<" % Done"<< endl;

	tree->GetEntry(event);

	EvtType = tree->GetLeaf("fEvtHdr.fEvtType")->GetValue();

	// ----- Coincidence events cut ------
	if(EvtType != 7) // EvtType 7 is coincidene events only
	    continue;

        //----- PID Cut -------
	if( !(PgtrBeta > 0.5 && PgtrBeta < 1.5                       // e- beta cut
	      && HgtrBeta > 0.6 &&  HgtrBeta < 0.8                   // Proton beta cut
	      && PhgcerNpeSum > 0.1 && HcerNpeSum < 0.1              // Cerenkov counter cut for e- and proton
	      && PcalEtotTrackNorm > 0.8 && PcalEtotTrackNorm < 1.5  // SHMS Calorimeter cut 
	      && PcalEprTrackNorm > 0.2) 	                     // SHMS calorimeter cut       
	    )
	    continue;
	
	h1PgtrBeta->Fill(PgtrBeta);
	h1PkinPrimaryW2->Fill(PkinPrimaryW);
	h1PkinPrimaryQ2->Fill(PkinPrimaryQ2);
	h1PkinPrimaryNu->Fill(PkinPrimaryNu);
	
	h1HgtrBeta->Fill(HgtrBeta);
	h1HkinSecondaryPmiss->Fill(HkinSecondaryPmiss);
	h1HkinSecondaryEmiss->Fill(HkinSecondaryEmiss);
	h1HkinSecondaryPmiss_x->Fill(HkinSecondaryPmiss_x);

	h1PcointimeROC1->Fill((TcoinpTRIG1_ROC1_tdcTimeRaw - TcoinpTRIG4_ROC1_tdcTimeRaw + pROC1Offset)*0.1); // 0.1 to convert to ns
	h1PcointimeROC2->Fill((TcoinpTRIG1_ROC2_tdcTimeRaw - TcoinpTRIG4_ROC2_tdcTimeRaw + pROC2Offset)*0.1);
	h1HcointimeROC1->Fill((TcoinhTRIG1_ROC1_tdcTimeRaw - TcoinhTRIG4_ROC1_tdcTimeRaw + hROC1Offset)*0.1);
	h1HcointimeROC2->Fill((TcoinhTRIG1_ROC2_tdcTimeRaw - TcoinhTRIG4_ROC2_tdcTimeRaw + hROC2Offset)*0.1);		
    }

    TCanvas *c1 = new TCanvas("c1","SHMS Kinematic Distribution");
    c1->Divide(2,2);
    c1->cd(1);
    h1PgtrBeta->Draw();
    c1->cd(2);
    h1PkinPrimaryW2->Draw();
    c1->cd(3);
    h1PkinPrimaryQ2->Draw();
    c1->cd(4);
    h1PkinPrimaryNu->Draw();
    
    TCanvas *c2 = new TCanvas("c2","HMS Kinematic Distribution");
    c2->Divide(2,2);
    c2->cd(1);
    h1HgtrBeta->Draw();
    c2->cd(2);
    h1HkinSecondaryPmiss->Draw();
    c2->cd(3);
    h1HkinSecondaryEmiss->Draw();
    c2->cd(4);
    h1HkinSecondaryPmiss_x->Draw();

    TCanvas *c3 = new TCanvas("c3", "Coincidencd Time");
    c3->Divide(2,2);
    c3->cd(1);
    h1PcointimeROC1->Draw();
    c3->cd(2);
    h1PcointimeROC2->Draw();
    c3->cd(3);
    h1HcointimeROC1->Draw();
    c3->cd(4);
    h1HcointimeROC2->Draw();    
}
