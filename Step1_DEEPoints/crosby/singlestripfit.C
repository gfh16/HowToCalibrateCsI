#include "TMath.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include <sstream>

//Create fitting function

void singlestripfit()
{
  const int NumTel=10;
  const int NumStrip=29;
  const bool FrontBack=1; //F=0, B=1
  double xpeakst[4];
  xpeakst[0]=888;
  xpeakst[1]=974;
  xpeakst[2]=1051;
  xpeakst[3]=1349;
  
  TFile myRootFile("/mnt/analysis/e15190/dellaqui/HiRA_Calibrations/output/StripEnergySpectra_HiRA_4761.root");
  ofstream FileOut("SingleStrip_PeakFit.dat");
  ofstream FileOutg("SingleStrip_LinearFit.dat");
   
  FileOut << setw(10) << "*F(0)/B(1) " << setw(10) << "tel "  << setw(10) << "strip " << setw(15) << "center (1) " << setw(15) << "error (1) " << endl;
  FileOutg << setw(10) << "*F(0)/B(1) " << setw(10) << "tel " << setw(10) << "strip " << setw(15) << "Intercepts " << setw(15) << "Slope " << endl;

  TCanvas* c1 = new TCanvas("c1","",800,600);
  c1->SetLogy(true);
  TCanvas* c2 = new TCanvas("c2","",800,600);
  
  double xpoints[4] = {5.40430,6.02532,6.52852,8.57606};
  
  TH1D * HistToProcess;
  if(FrontBack==0) {
    HistToProcess=(TH1D*)myRootFile.Get(Form("TEL%02d_EF%02d",NumTel,NumStrip));
  } else {
    HistToProcess=(TH1D*)myRootFile.Get(Form("TEL%02d_EB%02d",NumTel,NumStrip));
  }
  HistToProcess->SetDirectory(0);
  
  //fitting histograms for front strips
  c1->cd();
  HistToProcess->GetXaxis()->SetRange(500,1800);
  // HistToProcess->Rebin(2);
  HistToProcess->Draw();
  c1->Modified();
  c1->Update();
  getchar();
	  
  double cent[4];
  double err_cent[4];
  for(int p=0; p<4; ++p)
    {     
      double center = xpeakst[p];

      HistToProcess->Draw();
      if(HistToProcess->Integral(HistToProcess->GetXaxis()->FindBin(center-10), HistToProcess->GetXaxis()->FindBin(center+10))) HistToProcess->Fit("gaus","","",center-10,center+10);
      c1->Modified();
      c1->Update();
      getchar();

      TF1* myFunc = HistToProcess->GetFunction("gaus");
      cent[p] = myFunc->GetParameter(1);
      err_cent[p] = myFunc->GetParError(1);

      if(myFunc==0) continue;

      FileOut << setw(10) << FrontBack << setw(10) << NumTel << setw(10) << NumStrip << setw(15) << myFunc->GetParameter(1) << setw(15) << myFunc->GetParError(1) << endl;
  }

  c2->cd();
  TGraphErrors* g = new TGraphErrors(4,cent, xpoints,err_cent,0);
  g->Fit("pol1","","",900);
  g->SetTitle(Form("TEL%02d_EF%02d",NumTel,NumStrip));
  g->Draw("APE*");
  c2->Modified();
  c2->Update();
  //getchar();

  TF1* myLFunc = g->GetFunction("pol1");
  FileOutg << setw(10) << FrontBack << setw(10) << NumTel << setw(10) << NumStrip << setw(15) << myLFunc->GetParameter(0) << setw(15) << myLFunc->GetParameter(1) << endl;
  
  FileOut.close();
  FileOutg.close();
  myRootFile.Close();
  
  return;
}
