// Filename: CTcoinTime.cc
// Description: Calculate coincidence time
// Author: Latif Kabir < latif@jlab.org >
// Created: Thu Jan  4 17:03:26 2018 (-0500)
// URL: jlab.org/~latif

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLeaf.h>
#include <TSystem.h>
#include <TCut.h>
#include "Constants.h"

using namespace std;

void CTcoinTimeRaw(Int_t runNumber,  TString shms_particle, Int_t analyzedEvents)
{
    TString fileName = ROOT_FILE_PATH;
    fileName += "coin_replay_production_";
    fileName += runNumber;
    fileName += "_";
    fileName += analyzedEvents;
    fileName += ".root";

    Bool_t runNotFound = gSystem->AccessPathName(fileName);
    if(runNotFound)
    {	    
	cout << "Requested file " << fileName << " does NOT exist" <<endl;
	return;
    }
    
    TFile *file = new TFile(fileName);
    TTree *tree = (TTree*)file->Get("T");    
    //tree->Print();
    
    Double_t SHMSpartMass; 
    Double_t HMSpartMass;
    Double_t SHMSbetaMin;
    Double_t SHMSbetaMax;
    Double_t HMSbetaMin;
    Double_t HMSbetaMax;
    
    if(shms_particle == "e")
    {
	SHMSpartMass = 0.510998/1000.0; // electron mass in GeV/c^2
	HMSpartMass = 938.27208/1000.0; // proton mass in GeV/c^2	
	cout << "------------> Set SHMS for e and HMS for p <--------------" <<endl;
    }
    else
    {
	SHMSpartMass = 938.27208/1000.0; // proton mass in GeV/c^2 
	HMSpartMass = 0.510998/1000.0; // electron mass in GeV/c^2
	cout << "------------> Set SHMS for p and HMS for e <--------------" <<endl;
    }
    
    //----------------------- Histogram for coincidence time ----------------------------
    TH1D *h1PcointimeROC1 = new TH1D("SHMS ROC1 Corrected Coin Time","SHMS ROC1 Corrected Coin Time; cointime [ns]", 800, -40, 40);
    TH1D *h1PcointimeROC2 = new TH1D("SHMS ROC2 Corrected Coin Time","SHMS ROC2 Corrected Coin Time; cointime [ns]", 800, -40, 40);

    Double_t PgtrP;
    Double_t HgtrP;
    Double_t PgtrBetaMes;    
    Double_t HgtrBetaMes;        
    Double_t PgtrBetaCalc;    
    Double_t HgtrBetaCalc;        
    
    //Detector Response
    Double_t PcalEprTrackNorm;
    Double_t PcalEtotTrackNorm;
    Double_t PhgcerNpeSum;

    Double_t HcalEprTrackNorm;
    Double_t HcalEtotTrackNorm;
    Double_t HcerNpeSum;

    //Hodoscope start time 
    Double_t HhodStartTime;
    Double_t PhodStartTime;
    Double_t PhodStatus;
    Double_t HhodStatus;
    
    Double_t PhodfpHitsTime;
    Double_t HhodfpHitsTime;
        
    //Trigger 
    Double_t TcoinpTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinpTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinpTRIG4_ROC2_tdcTimeRaw;
    
    Double_t TcoinhTRIG1_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC1_tdcTimeRaw;
    Double_t TcoinhTRIG1_ROC2_tdcTimeRaw;
    Double_t TcoinhTRIG4_ROC2_tdcTimeRaw;
        
    Double_t HdcXfp;
    Double_t HdcXpfp;
    Double_t HdcYfp;
    Double_t HdcYpfp;

    Double_t PdcXfp;
    Double_t PdcXpfp;
    Double_t PdcYfp;
    Double_t PdcYpfp;
    Double_t PgtrdP;
    
    tree->SetBranchAddress("P.gtr.p", &PgtrP);    
    tree->SetBranchAddress("P.gtr.dp", &PgtrdP);            
    tree->SetBranchAddress("H.gtr.p", &HgtrP);            
    tree->SetBranchAddress("P.gtr.beta", &PgtrBetaMes);        
    tree->SetBranchAddress("H.gtr.beta", &HgtrBetaMes);

    tree->SetBranchAddress("P.cal.eprtracknorm", &PcalEprTrackNorm);
    tree->SetBranchAddress("P.cal.etottracknorm", &PcalEtotTrackNorm);
    tree->SetBranchAddress("P.hgcer.npeSum", &PhgcerNpeSum);
    
    tree->SetBranchAddress("H.cal.eprtracknorm", &HcalEprTrackNorm);
    tree->SetBranchAddress("H.cal.etottracknorm", &HcalEtotTrackNorm);
    tree->SetBranchAddress("H.cer.npeSum", &HcerNpeSum);

    tree->SetBranchAddress("P.hod.goodstarttime", &PhodStatus);
    tree->SetBranchAddress("P.hod.starttime", &PhodStartTime);
    tree->SetBranchAddress("P.hod.fpHitsTime", &PhodfpHitsTime);
    
    tree->SetBranchAddress("H.hod.goodstarttime", &HhodStatus);    
    tree->SetBranchAddress("H.hod.starttime", &HhodStartTime);    
    tree->SetBranchAddress("H.hod.fpHitsTime", &HhodfpHitsTime);
    
    tree->SetBranchAddress("H.dc.x_fp", &HdcXfp);
    tree->SetBranchAddress("H.dc.xp_fp", &HdcXpfp);
    tree->SetBranchAddress("H.dc.y_fp", &HdcYfp);
    tree->SetBranchAddress("H.dc.yp_fp", &HdcYpfp);    

    tree->SetBranchAddress("P.dc.x_fp", &PdcXfp);
    tree->SetBranchAddress("P.dc.xp_fp", &PdcXpfp);
    tree->SetBranchAddress("P.dc.y_fp", &PdcYfp);
    tree->SetBranchAddress("P.dc.yp_fp", &PdcYpfp);    

    tree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &TcoinpTRIG1_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &TcoinpTRIG4_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &TcoinpTRIG1_ROC2_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &TcoinpTRIG4_ROC2_tdcTimeRaw);

    tree->SetBranchAddress("T.coin.hTRIG1_ROC1_tdcTimeRaw", &TcoinhTRIG1_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG4_ROC1_tdcTimeRaw", &TcoinhTRIG4_ROC1_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG1_ROC2_tdcTimeRaw", &TcoinhTRIG1_ROC2_tdcTimeRaw);
    tree->SetBranchAddress("T.coin.hTRIG4_ROC2_tdcTimeRaw", &TcoinhTRIG4_ROC2_tdcTimeRaw);

    Int_t nEvents = tree->GetEntries();
    cout << "Number of events: "<< nEvents <<endl;

    if(analyzedEvents != -1 && analyzedEvents <= nEvents)
	nEvents = analyzedEvents;
    
    TCut evtCut;
    TCut eBetaCut;
    TCut pBetaCut;
    TCut cerCut; 
    TCut calCut; 
    TCut hodoTimeCut;

     if(shms_particle == "e")
     {   
	eBetaCut = "P.gtr.beta > 0.5 && P.gtr.beta < 1.5";
	pBetaCut = "H.gtr.beta > 0.5 &&  H.gtr.beta < 1.5";
	cerCut= "P.hgcer.npeSum > 0.1 && H.cer.npeSum < 0.1";
	calCut = "P.cal.etottracknorm > 0.8 && P.cal.etottracknorm < 1.5 && P.cal.eprtracknorm  > 0.2";
	hodoTimeCut ="P.hod.goodstarttime == 1 && H.hod.goodstarttime == 1";
     }
     else
     {
	 eBetaCut = "P.gtr.beta > 0.5 && P.gtr.beta < 1.5";
	 pBetaCut = "H.gtr.beta > 0.5 &&  H.gtr.beta < 1.5";
	 cerCut = "P.hgcer.npeSum < 0.1 && H.cer.npeSum > 0.1";
	 calCut = "H.cal.etottracknorm > 0.8 && H.cal.etottracknorm < 1.5 && H.cal.eprtracknorm  > 0.2";
	 hodoTimeCut ="P.hod.goodstarttime == 1 && H.hod.goodstarttime == 1";	 
     }
    
    TCanvas *canvas1 = new TCanvas("canvas1","canvas1");
    tree->Draw("P.hod.starttime >> SHMShodoStartTime",  eBetaCut && pBetaCut && cerCut && calCut && hodoTimeCut);
    TCanvas *canvas2 = new TCanvas("canvas2","canvas2");
    tree->Draw("H.hod.starttime >> HMShodoStartTime",  eBetaCut && pBetaCut && cerCut && calCut && hodoTimeCut);

    TH1D *h1PhodoStartTime = (TH1D*)gDirectory->Get("SHMShodoStartTime");
    TH1D *h1HhodoStartTime = (TH1D*)gDirectory->Get("HMShodoStartTime");
    h1PhodoStartTime->GetXaxis()->SetTitle("SHMS hodo start time [ns]");
    h1HhodoStartTime->GetXaxis()->SetTitle("HMS hodo start time [ns]");

    Double_t pOffset = 4.0; //9.5 + 10;  // in ns
    Double_t hOffset = 335;
    Double_t speedOfLight = 29.9792; // in cm/ns
    
    Double_t SHMScentralPathLen = 18.1*100;  // SHMS Target to focal plane path length converted to cm
    Double_t SHMSpathLength = 18.1*100;      // For now assume that it's same as SHMScentralPathLen
    Double_t HMScentralPathLen = 22*100;     // HMS Target to focal plane path length converted to cm
    Double_t DeltaHMSpathLength;             // For now assume that it's same as HMScentralPathLen

    Double_t SHMScoinCorr = 0.0;
    Double_t HMScoinCorr = 0.0;
    Double_t PhodoStartTimeMean = h1PhodoStartTime->GetMean();
    Double_t HhodoStartTimeMean =  h1HhodoStartTime->GetMean();
    Int_t totEvents = 0;

    Double_t SHMSrawCoinTimeROC1;
    Double_t SHMSrawCoinTimeROC2;
    Double_t HMSrawCoinTimeROC1;
    Double_t HMSrawCoinTimeROC2;

    Double_t SHMScorrCoinTimeROC1;
    Double_t SHMScorrCoinTimeROC2;
    Double_t HMScorrCoinTimeROC1;
    Double_t HMScorrCoinTimeROC2;
        
    cout << "Mean of SHMS Hodoscope start time: "<< PhodoStartTimeMean <<endl;
    cout << "Mean of HMS Hodoscope start time: "<< HhodoStartTimeMean <<endl;
    cout << "Number of events passing PID cut (without looping over events approach): "<<h1PhodoStartTime->GetEntries()<<endl;

    for (Int_t event = 0; event < nEvents; ++event)
    {
	if(event%10000 == 0)
	    cout << (Int_t)(100*event/nEvents) <<" % Done"<< endl;

	tree->GetEntry(event);	

        //----- PID Cut -------
	if(shms_particle == "e")
	{
	    if( !(PgtrBetaMes > 0.5 && PgtrBetaMes < 1.5                       // e- beta cut
		  && HgtrBetaMes > 0.5 &&  HgtrBetaMes < 1.5                   // Proton beta cut
		  && PhgcerNpeSum > 0.1 && HcerNpeSum < 0.1                    // Cerenkov counter cut for e- and proton
		  && PcalEtotTrackNorm > 0.8 && PcalEtotTrackNorm < 1.5        // SHMS Calorimeter cut 
		  && PcalEprTrackNorm > 0.2) 	                               // SHMS calorimeter cut       
		)
		continue;
	}
	else
	{
	    if( !(PgtrBetaMes > 0.5 && PgtrBetaMes < 1.5                       // proton beta cut
		  && HgtrBetaMes > 0.5 &&  HgtrBetaMes < 1.5                   // e beta cut
		  && HcerNpeSum > 0.1 && PhgcerNpeSum < 0.1                    // Cerenkov counter cut for e- and proton
		  && HcalEtotTrackNorm > 0.8 && HcalEtotTrackNorm < 1.5        // HMS Calorimeter cut 
		  && HcalEprTrackNorm > 0.2) 	                               // HMS calorimeter cut       
		)
		continue;
	}

	if(PhodStatus == 0 || HhodStatus ==0)
	    continue;
	
	SHMScorrCoinTimeROC1 = TcoinpTRIG1_ROC1_tdcTimeRaw*0.1 - TcoinpTRIG4_ROC1_tdcTimeRaw*0.1;
	SHMScorrCoinTimeROC2 = TcoinpTRIG1_ROC2_tdcTimeRaw*0.1 - TcoinpTRIG4_ROC2_tdcTimeRaw*0.1; 
	HMScorrCoinTimeROC1 = TcoinhTRIG1_ROC1_tdcTimeRaw*0.1 - TcoinhTRIG4_ROC1_tdcTimeRaw*0.1;
	HMScorrCoinTimeROC2 = TcoinhTRIG1_ROC2_tdcTimeRaw*0.1 - TcoinhTRIG4_ROC2_tdcTimeRaw*0.1;
       		
	h1PcointimeROC1->Fill(SHMScorrCoinTimeROC1); 
	h1PcointimeROC2->Fill(SHMScorrCoinTimeROC2);

	++totEvents;
    }
    cout << "Total number of events passing the PID cuts (looping over events): "<< totEvents <<endl;

    TCanvas *c1 = new TCanvas("c1","Coin Time");
    h1PcointimeROC1->Draw();
    
    TCanvas *c2 = new TCanvas("c2", "Coincidence Time");
    h1PcointimeROC2->Draw();
}
