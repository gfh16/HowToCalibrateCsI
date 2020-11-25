#include "TMath.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include <sstream>


void PulserPeakFinder()
{
  TFile myRootFile("/mnt/analysis/e16042/dellaqui/HiRA_Calibrations/output/CsIEnergySpectra_HiRA_0136.root"); // Currently Contains TEL00-TEL03
  ofstream FileOut("PulserPeak.dat");

  FileOut << setw(10) <<  "*tel "  << setw(10) << "CsI " << setw(10) << "Point Num " << setw(10) << "Voltage " << setw(10)<< "Channel " << endl;

  //TEL00_CSI00 - TEL00_CSI03

  int NumTele = 4;
  int NumCsI = 4;
  int Steps = 31;

  TH1D* myHistCsI[NumTele*NumCsI];
  double ChannelStep[steps];

  //Retrieve the histograms

  for(int i=0; i< NumTele; ++i)
    {
      for(int j=0; j<NumCsI; ++j)
	{
	  myHistCsI[i*4+j]=(TH1D*)myRootFile.Get(Form("TEl%02d_CSI%02d",i,j));
	}
    }

  //Retrieving Pulser Peaks
						 
						 
						
