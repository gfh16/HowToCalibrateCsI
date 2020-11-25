#include "TMath.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include <sstream>

//Create fitting function

void stripfit()
{
  TFile myRootFile("/mnt/analysis/e15190/dellaqui/HiRA_Calibrations/output/StripEnergySpectra_HiRA_4761.root");
  ofstream FileOut("PeakFit.dat");
  ofstream FileOutg("LinearFit.dat");
   
  FileOut << setw(10) << "*F(0)/B(1) " << setw(10) << "tel "  << setw(10) << "strip " << setw(15) << "center (1) " << setw(15) << "error (1) " << endl;
  FileOutg << setw(10) << "*F(0)/B(1) " << setw(10) << "tel " << setw(10) << "strip " << setw(15) << "Intercepts " << setw(15) << "Slope " << endl;

  TCanvas* c1 = new TCanvas("c1","",800,600);
  c1->SetLogy(true);
  TCanvas* c2 = new TCanvas("c2","",800,600);
  
  int NumTele = 12;
  int NumStrip = 32;
  double xpoints[4] = {5.40430,6.02532,6.52852,8.57606};
  
  const int NumberOfStrips = NumTele*NumStrip;
  TH1D* myHistStripFront[NumberOfStrips];
  TH1D* myHistStripBack[NumberOfStrips];
  
  //Retrieve histograms from file
  
  for(int i=0; i<NumTele; ++i)
    {
      for(int j=0; j<NumStrip; ++j)
	{
	  myHistStripFront[i*32+j]=(TH1D*)myRootFile.Get(Form("TEL%02d_EF%02d",i,j));
	  myHistStripBack[i*32+j]=(TH1D*)myRootFile.Get(Form("TEL%02d_EB%02d",i,j));
	}
    }
  
  //fitting histograms for front strips
  
  for(int i=0; i<NumTele; ++i)
    {
      for(int j=0; j<NumStrip; ++j)
	{
	  c1->cd();
	  myHistStripFront[i*32+j]->GetXaxis()->SetRange(500,1800);
	  // myHistStripFront[i*32+j]->Rebin(2);
	  myHistStripFront[i*32+j]->Draw();
	  
	  // use TSpectrum to find peak candidates
	  	 
	  TSpectrum *s = new TSpectrum(6);
	  int nfound = s->Search(myHistStripFront[i*32+j],4, "", .10);
	  double_t *xpeaks = s->GetPositionX();
	  double *first_peak = std::min_element(xpeaks,xpeaks+5);
	  int position = myHistStripFront[i*32+j]->GetXaxis()->FindBin(*first_peak);
	  myHistStripFront[i*32+j]->GetXaxis()->SetRange(position+25,1800);
 	  myHistStripFront[i*32+j]->Draw();
	 	  
	  c1->Update();
	  //getchar();

	  TSpectrum *st = new TSpectrum(5);
	  int nfoundt = st->Search(myHistStripFront[i*32+j],3.1,"",.10);
	  double_t *xpeakst = st->GetPositionX();
	  std::sort(xpeakst, xpeakst+5);
	  double cent[5];
	  double err_cent[5];
	  
	  if(nfoundt<5) {
	    printf("Warning: something is wrong with tel %02d stripf %02d\n", i, j);
	    getchar();
	    continue;
	  }
	  
	  int NPointsUsed=0;
	  for(int p=0; p< nfoundt; ++p)
	    {
	      if(p==1) continue; //I don't use the second peak
	      
	      double center = xpeakst[p];

	      myHistStripFront[i*32+j]->Draw();
	      myHistStripFront[i*32+j]->Fit("gaus","","",center-10,center+10);
	      c1->Modified();
	      c1->Update();
	      // getchar();

	      TF1* myFunc = myHistStripFront[i*32+j]->GetFunction("gaus");
	      cent[NPointsUsed] = myFunc->GetParameter(1);
	      err_cent[NPointsUsed] = myFunc->GetParError(1);
		
	      if(myFunc==0) continue;

	      FileOut << setw(10) << 0 << setw(10) << i << setw(10) << j << setw(15) << myFunc->GetParameter(1) << setw(15) << myFunc->GetParError(1) << endl;
	      
	      NPointsUsed++;
	    }
	  
	  c2->cd();
	  TGraphErrors* g = new TGraphErrors(4,cent, xpoints,err_cent,0);
	  g->Fit("pol1","","",900);
	  g->SetTitle(Form("TEL%02d_EF%02d",i,j));
	  g->Draw("APE*");
	  c2->Modified();
	  c2->Update();
	  //getchar();

	  TF1* myLFunc = g->GetFunction("pol1");
	  FileOutg << setw(10) << 0 << setw(10) << i << setw(10) << j << setw(15) << myLFunc->GetParameter(0) << setw(15) << myLFunc->GetParameter(1) << endl;
	}
    }
  
  //fitting histograms for back strips
  
  for(int i=0; i<NumTele; ++i)
    {
      for(int j=0; j<NumStrip; ++j)
	{
	  c1->cd();
	  myHistStripBack[i*32+j]->GetXaxis()->SetRange(500,1800);
	  //myHistStripBack[i*32+j]->Rebin(2);
	  myHistStripBack[i*32+j]->Draw();
	  
	  // use TSpectrum to find peak candidates
	  	  
	  TSpectrum *sb = new TSpectrum(6);
	  int nbfound = sb->Search(myHistStripBack[i*32+j],4, "", .10);
	  double_t *bxpeaks = sb->GetPositionX();
	  double *first_peakb = std::min_element(bxpeaks,bxpeaks+5);
	  int bposition = myHistStripBack[i*32+j]->GetXaxis()->FindBin(*first_peakb);
	  cout << bposition << endl;
	  myHistStripBack[i*32+j]->GetXaxis()->SetRange(bposition+25,1800);
	  myHistStripBack[i*32+j]->Draw();

	  c1->Update();
	  //getchar();
	   
	  TSpectrum *sbt = new TSpectrum(5);
	  int nbtfound = sbt->Search(myHistStripBack[i*32+j],3.1,"",.10);
	  double_t *xpeaksbt = sbt->GetPositionX();
	  std::sort(xpeaksbt, xpeaksbt+5);
	  double centb[5];
	  double err_centb[5];
	  
	  if(nbtfound<5) {
	    printf("Warning: something is wrong with tel %02d stripb %02d\n", i, j);
	    getchar();
	    continue;
	  }
	  
	  int NPointsUsed=0;
	  for(int p=0; p< nbtfound; ++p)
	  {
	      if(p==1) continue; //I don't use the second peak
	      
	      double center = xpeaksbt[p];
	      
	      myHistStripBack[i*32+j]->Draw();
	      myHistStripBack[i*32+j]->Fit("gaus","","",center-10,center+10);
	      c1->Modified();
	      c1->Update();
	      //getchar();
	      
	      TF1* myFunc = myHistStripBack[i*32+j]->GetFunction("gaus");
	      centb[NPointsUsed] = myFunc->GetParameter(1);
	      err_centb[NPointsUsed] = myFunc->GetParError(1);
	      
	      if(myFunc==0) continue;

	      FileOut << setw(10) << 1 << setw(10) << i << setw(10) << j << setw(15) << myFunc->GetParameter(1) << setw(15) << myFunc->GetParError(1) << endl;
	      NPointsUsed++;
	    }
	  
	  c2->cd();
	  TGraphErrors* gr = new TGraphErrors(4,centb, xpoints,err_centb,0);
	  gr->Fit("pol1","","",0,2000);
	  gr->SetTitle(Form("TEL%02d_EB%02d",i,j));
	  gr->Draw("APE*");
	  c2->Modified();
	  c2->Update();
	  //getchar();

	  TF1* myLBFunc = gr->GetFunction("pol1");
	  FileOutg << setw(10) << 1  << setw(10) << i << setw(10) << j << setw(15) << myLBFunc->GetParameter(0) << setw(15) << myLBFunc->GetParameter(1) << endl;
	}
    }
  
  FileOut.close();
  FileOutg.close();
  myRootFile.Close();
  
  return;
}
