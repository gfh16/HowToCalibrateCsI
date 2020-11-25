#include "include/HiRACsICalibration.h"

const int csi_gain_setting=170;

void macro_CsIDEEProfiling()
{
  TFile * FileIn = new TFile("data/HiRA_DECal_CsIRaw_Pixelization.root");
  TFile * FileInCuts = new TFile("data/HiRA_DECal_CsIRaw_Cuts.root");

  // Suggested values
  // Z=1 A=1 Low Energy: 13.5 MeV > E > 7 MeV
  // Z=1 A=1 Mid Energy: 7 MeV > E > 3 MeV
  // Z=1 A=2 Low Energy: 19 MeV > E > 10 MeV
  // Z=1 A=2 Mid Energy: 10 MeV > E > 6 MeV
  // Z=1 A=3 Low Energy: 23.5 MeV > E > 12 MeV
  // Z=1 A=3 Mid Energy: 12 MeV > E > 8 MeV
  // Z=2 A=3 Low Energy: 51 MeV > E > 30 MeV
  // Z=2 A=3 Mid Energy: 30 MeV > E > 15 MeV
  // Z=2 A=4 Low Energy: 59 MeV > E > 35 MeV
  // Z=2 A=4 Mid Energy: 35 MeV > E > 25 MeV
 
 // for proton at low energy in CsI
/*  int Z=1;
  int A=1;
  double ELossmax=13.5;
  double ELossmin=7;
  int NSamples=0;
  int BinStep=5; // change this value for low or mid energy
*/

// for deutron at low energy in CsI
/*  int Z=1;
  int A=2;
  double ELossmax=19;
  double ELossmin=10;
  int NSamples=0;
  int BinStep=5;
*/

// for triton at low energy in CsI
/*  int Z=1;
  int A=3;
  double ELossmax=23.5;
  double ELossmin=12;
  int NSamples=0;
  int BinStep=5;
*/
 
// for 3He at low energy in CsI
/*  int Z=2;
  int A=3;
  double ELossmax=51;
  double ELossmin=40;
  int NSamples=0;
  int BinStep=8;
*/

// for 4He at low energy in CsI
/*  int Z=2;
  int A=4;
  double ELossmax=59;
  double ELossmin=45;
  int NSamples=0;
  int BinStep=8;
*/
  
// for proton at midenergy in CsI
/*  int Z=1;
  int A=1;
  double ELossmax=7;
  double ELossmin=3;
  int NSamples=0;
  int BinStep=20; // change this value for low or mid energy
*/

/*
// for deutron at midenergy in CsI
  int Z=1;
  int A=2;
  double ELossmax=10;
  double ELossmin=4.5;
  int NSamples=0;
  int BinStep=20;
*/

// for triton at midenergy in CsI
  int Z=1;
  int A=3;
  double ELossmax=12;
  double ELossmin=5.5;
  int NSamples=0;
  int BinStep=20;


/* 
// for 3He at midenergy in CsI
  int Z=2;
  int A=3;
  double ELossmax=40;
  double ELossmin=15;
  int NSamples=0;
  int BinStep=35;
*/


// for 4He at midenergy in CsI
 /* int Z=2;
  int A=4;
  double ELossmax=45;
  double ELossmin=25;
  int NSamples=0;
  int BinStep=35;
*/


  std::string FileOutTag("MidEnergy");
// std::string FileOutTag("LowEnergy");
  
  ofstream FileOut(Form("calibrations/HiRA_CsI_DEEProfiling%s_Z%02d_A%02d.dat", FileOutTag.c_str(), Z, A));
  FileOut << setw(5) << "*tel  " << setw(7) << "numcsi " << setw(10) << "CsI (ch) " << setw(10) << "err CsI (ch) " << setw(10) << "CsI (V) " << setw(10) << "err CsI (V) " << setw(10) << "Si (MeV) " << setw(10) << "err Si (MeV)\n";

  double CsIch[6000];
  double CsIV[6000];
  double err_CsIch[6000];
  double err_CsIV[6000];
  double ESi[6000];
  double err_ESi[6000];

  double Ycheck[6000];
  double errYcheck[6000];

  HiRACsICalibrationManager CsICalibrationModule;
  CsICalibrationModule.LoadPulserInfo(Form("calibrations/HiRA_CsI_Pulser_%dsetting.dat",csi_gain_setting));
  /////////////////////

  TCanvas * c1 = new TCanvas("c1","",800,600);

  for(int i=0; i<12; i++)
  {
    for (int j=0; j<4; j++)
    {
      NSamples=0;
      TH2D * DECalCsIRawHist=(TH2D*)FileIn->Get(Form("DECal_ERaw_%02d_%02d",i,j));
      if(DECalCsIRawHist==0) continue;
      TCutG * ParticleCut=(TCutG*)FileInCuts->Get(Form("DECal_ERaw_%02d_%02d_Z%02d_A%02d",i,j,Z,A));
      if(ParticleCut==0) continue;

      for(int k=0; k<DECalCsIRawHist->GetNbinsX(); k+=BinStep)
      {
        TH1D ProjSi(Form("ProjSi%d",k), "", 1000,0,100);
        DECalCsIRawHist->ProjectionY(Form("ProjSi%d",k),k,k+2,Form("[DECal_ERaw_%02d_%02d_Z%02d_A%02d]",i,j,Z,A));

        double ESiapprox=ProjSi.GetBinCenter(ProjSi.GetMaximumBin());
      	double err_ESiapprox=ProjSi.GetRMS();

        if(err_ESiapprox==0) continue;
      	if(ProjSi.Integral(ProjSi.FindBin(ESiapprox-err_ESiapprox),ProjSi.FindBin(ESiapprox+err_ESiapprox))<50) continue;

      	ProjSi.Fit("gaus","0", "", ESiapprox-err_ESiapprox, ESiapprox+err_ESiapprox);
      	TF1 * fit_result = ProjSi.GetFunction("gaus");

      	//gPad->Modified();
      	//gPad->Update();
      	//getchar();

      	double ESi=fit_result->GetParameter(1);
      	double errESi=fit_result->GetParError(1);

      	if(errESi>1) continue;

      	if(ESi>=ELossmin && ESi<=ELossmax) {
          CsIch[NSamples]=DECalCsIRawHist->GetXaxis()->GetBinCenter(k+1);
      	  err_CsIch[NSamples]=0.5;
      	  CsIV[NSamples]=CsICalibrationModule.GetVoltageValue(CsIch[NSamples], i, j);
      	  err_CsIV[NSamples]=CsICalibrationModule.GetVoltageValue(CsIch[NSamples]+err_CsIch[NSamples], i, j)-CsIV[NSamples];

      	  Ycheck[NSamples]=ESi;
      	  errYcheck[NSamples]=errESi;

          FileOut << setw(5) << i << "  " << setw(7) << j << "  " << setw(10) << CsIch[NSamples] << "  " << setw(10) << err_CsIch[NSamples] << "  " <<
      	  setw(10) << CsIV[NSamples] << "  " << setw(10) << err_CsIV[NSamples] << "  " << setw(10) << ESi << "  " << setw(10) << errESi <<endl;
      	  NSamples++;

        }
      }

      DECalCsIRawHist->Draw("colz");
      DECalCsIRawHist->GetXaxis()->SetRangeUser(ParticleCut->GetXaxis()->GetXmin(),ParticleCut->GetXaxis()->GetXmax());
      DECalCsIRawHist->GetYaxis()->SetRangeUser(ParticleCut->GetYaxis()->GetXmin(),ParticleCut->GetYaxis()->GetXmax());
      ParticleCut->Draw("*L SAME");
      TGraphErrors CheckGraph(NSamples, CsIch, Ycheck, 0, errYcheck);
      CheckGraph.SetMarkerStyle(20);
      CheckGraph.Draw("PE SAME");
      gPad->SetLogz(1);
      gPad->Modified();
      gPad->Update();
 //     c1->Print(Form("pictures/4HeLowEnergy/HiRA_CsI_DEEProfiling%s_Z%02d_A%02d_%02d_%02d.png", FileOutTag.c_str(), Z, A, i, j));
      c1->Print(Form("pictures/t%s/HiRA_CsI_DEEProfiling%s_Z%02d_A%02d_%02d_%02d.png", FileOutTag.c_str(),FileOutTag.c_str(), Z, A, i, j));
      // to change the pictures path here
      //getchar();
    }
  }

  return;
}
