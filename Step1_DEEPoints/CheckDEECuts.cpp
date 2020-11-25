void CheckDEECuts()
{
  const int Z=2;
  const int A=4;
  
  TFile FileInRaw("data/UsefulHistograms_Merged_4040_4661.root");
  TFile FileInCut("data/HiRA_DECal_CsIRaw_Cuts.root");
 
  TCanvas *c1 =new TCanvas("c1", "", 800, 600);
  c1->SetLogz(1);
  
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      TH2D *DECalCsIRawHist = (TH2D*)FileInRaw.Get(Form("DECal_ERaw_%02d_%02d", i, j));
      if(DECalCsIRawHist==0) continue; 
      
      TCutG * Cut = (TCutG*)FileInCut.Get(Form("DECal_ERaw_%02d_%02d_Z%02d_A%02d", i, j, Z, A));
      Cut->SetLineColor(kRed);
      Cut->SetMarkerColor(kBlue);   
           
      DECalCsIRawHist->Draw("colz"); 
      DECalCsIRawHist->GetXaxis()->SetRangeUser(Cut->GetXaxis()->GetXmin()-100, Cut->GetXaxis()->GetXmax()+100);  
      DECalCsIRawHist->GetYaxis()->SetRangeUser(Cut->GetYaxis()->GetXmin()-10,  Cut->GetYaxis()->GetXmax()+10);  
      Cut->Draw("SAME *L");   
      
      gPad->Modified();
      gPad->Update();
//    getchar();         
      
      c1->Print(Form("pictures/CheckCut/Z%02d_A%02d/CheckCut_%02d_%02d_%02d_%02d.png", Z, A, Z, A, i, j));
    }
  }
}
