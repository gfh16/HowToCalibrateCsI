//_______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// definition of Fermi Function to
double FermiFunc(double *x, double *par)
{
  return par[0]/(exp((x[0]-par[1])/par[2])+1);
}
//_______________________________________________________________________________


//_______________________________________________________________________________
void ToGetPunchThroughPoints()
{
  int Z=1;
  int A=2;

  TFile * FileIn = new TFile("../data/HiRA_DECal_CsIRaw_Pixelization.root");
  TFile * FileInCuts = new TFile("../data/HiRA_DECal_CsIRaw_Cuts.root");

  TH2D * DECalCsIRawHist[12][4];
  TCutG * ParticleCut[12][4];
  TH1D * ProjOneParticle[12][4];
  TH1D * ProjAllParticles[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      //////////////////////////////////////////////////////////////////////////
      /// reading raw data and cut file
      DECalCsIRawHist[i][j] = (TH2D*)FileIn->Get(Form("DECal_ERaw_%02d_%02d",i,j));
      ParticleCut[i][j] =(TCutG*)FileInCuts->Get(Form("DECal_ERaw_%02d_%02d_Z%02d_A%02d",i,j,Z,A));
      if(ParticleCut[i][j]==0 || DECalCsIRawHist[i][j]==0) continue;

      //////////////////////////////////////////////////////////////////////////
      /// make projection to X axis
      ProjOneParticle[i][j] = DECalCsIRawHist[i][j]->ProjectionX("ProjCsI",1, -1, Form("[DECal_ERaw_%02d_%02d_Z%02d_A%02d]",i,j,Z,A));
      ProjOneParticle[i][j]->SetTitle(Form("Projection_%02d_%02d_%02d_%02d",i,j,Z,A));
      ProjOneParticle[i][j]->GetXaxis()->SetRangeUser(500,1500);
  //    ProjOneParticle[i][j]->GetYaxis()->SetRangeUser(0,10000);

      ProjAllParticles[i][j] = DECalCsIRawHist[i][j]->ProjectionX();
      ProjAllParticles[i][j]->SetTitle(Form("DECal_ERaw_%02d_%02d",i,j));
      ProjAllParticles[i][j]->GetXaxis()->SetRangeUser(500,1500);
//      ProjAllParticles[i][j]->GetYaxis()->SetRangeUser(0,10000);

      //////////////////////////////////////////////////////////////////////////
      /// Fit with Fermi Function
      TF1 * fitfunc = new TF1("fitfunc",FermiFunc,1050,1075,3);
      fitfunc->SetParameters(100,100,10);

      ProjOneParticle[i][j]->Fit("fitfunc");

      TCanvas * c1 = new TCanvas("c1","",1400,500);
      c1->Divide(2,1);
      gPad->SetLogz(1);

      c1->cd(1);
      DECalCsIRawHist[i][j]->Draw("colz");
      DECalCsIRawHist[i][j]->GetXaxis()->SetRangeUser(ParticleCut[i][j]->GetXaxis()->GetXmin(),ParticleCut[i][j]->GetXaxis()->GetXmax());
      DECalCsIRawHist[i][j]->GetYaxis()->SetRangeUser(0,6);
      ParticleCut[i][j]->Draw("*L SAME");
      ParticleCut[i][j]->SetLineColor(kRed);
      ParticleCut[i][j]->SetLineWidth(2);
      ParticleCut[i][j]->SetMarkerColor(kBlue);
      ParticleCut[i][j]->SetMarkerSize(1.5);

      c1->cd(2);
      ProjOneParticle[i][j]->Draw();

      gPad->Modified();
      gPad->Update();
      getchar();

    }
  }

}
