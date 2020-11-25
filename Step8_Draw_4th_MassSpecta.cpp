void Step7_Fit_4th_MassSpectra()
{
  TCanvas * c1 = new TCanvas("c1","",800,600);

  TChain * TheData = new TChain ("E15190");
  TheData->Add("/mnt/analysis/e15190/dellaqui/data/HiRA/CalibratedData_4[5-6]??.root");

  const int Statistics=100000000;

  TH1D * HistZ1 = new TH1D ("HistZ1","",600,0,15);
  TH1D * HistZ2 = new TH1D ("HistZ2","",600,0,15);
  TH1D * HistZ3 = new TH1D ("HistZ3","",600,0,15);
  TH1D * HistZ4 = new TH1D ("HistZ4","",600,0,15);
  TH1D * HistZ5 = new TH1D ("HistZ5","",600,0,15);

  TheData->Draw("HiRA.fA>>HistZ1", "HiRA.fZId==1 && HiRA.fAId>0","",Statistics);
  TheData->Draw("HiRA.fA>>HistZ2", "HiRA.fZId==2 && HiRA.fAId>0","",Statistics);
  TheData->Draw("HiRA.fA>>HistZ3", "HiRA.fZId==3 && HiRA.fAId>0","",Statistics);
  TheData->Draw("HiRA.fA>>HistZ4", "HiRA.fZId==4 && HiRA.fAId>0","",Statistics);
  TheData->Draw("HiRA.fA>>HistZ5", "HiRA.fZId==5 && HiRA.fAId>0","",Statistics);

  HistZ1->SetLineColor(kRed);
  HistZ2->SetLineColor(kBlue);
  HistZ3->SetLineColor(kGreen);
  HistZ4->SetLineColor(kMagenta);
  HistZ5->SetLineColor(kAzure-2);
  HistZ1->SetFillColor(kRed);
  HistZ2->SetFillColor(kBlue);
  HistZ3->SetFillColor(kGreen);
  HistZ4->SetFillColor(kMagenta);
  HistZ5->SetFillColor(kAzure-2);

  HistZ1->SetLineWidth(2);
  HistZ2->SetLineWidth(2);
  HistZ3->SetLineWidth(2);
  HistZ4->SetLineWidth(2);
  HistZ5->SetLineWidth(2);

  c1->SetLogy(true);
  HistZ1->Draw("L");
  HistZ3->Draw("L SAME");
  HistZ2->Draw("L SAME");
  HistZ4->Draw("L SAME");
  HistZ5->Draw("L SAME");

  gPad->RedrawAxis();

  gStyle->SetOptStat(0);

  HistZ1->GetXaxis()->SetLabelSize(0.05);
  HistZ1->GetXaxis()->SetTitleSize(0.05);
  HistZ1->GetYaxis()->SetLabelSize(0.05);
  HistZ1->GetYaxis()->SetTitleSize(0.05);
  HistZ1->GetXaxis()->SetTitle("Mass distribution");
  HistZ1->GetYaxis()->SetTitle("counts");
  HistZ1->GetXaxis()->CenterTitle(true);
  HistZ1->GetYaxis()->CenterTitle(true);

  double YRangeMax = 1E7;
  HistZ1->GetYaxis()->SetRangeUser(1,YRangeMax);

  TLegend * legendario = new TLegend(0.75,0.55,0.89,0.85);
  legendario->AddEntry(HistZ1, "Z = 1", "F");
  legendario->AddEntry(HistZ2, "Z = 2", "F");
  legendario->AddEntry(HistZ3, "Z = 3", "F");
  legendario->AddEntry(HistZ4, "Z = 4", "F");
  legendario->AddEntry(HistZ5, "Z = 5", "F");
  legendario->SetBorderSize(0);
  legendario->Draw("SAME");

  TLine * lineA1 = new TLine(1,1,1,YRangeMax);
  TLine * lineA2 = new TLine(2,1,2,YRangeMax);
  TLine * lineA3 = new TLine(3,1,3,YRangeMax);
  TLine * lineA4 = new TLine(4,1,4,YRangeMax);
  TLine * lineA6 = new TLine(6,1,6,YRangeMax);
  TLine * lineA7 = new TLine(7,1,7,YRangeMax);
  TLine * lineA8 = new TLine(8,1,8,YRangeMax);
  TLine * lineA9 = new TLine(9,1,9,YRangeMax);
  TLine * lineA10 = new TLine(10,1,10,YRangeMax);
  TLine * lineA11 = new TLine(11,1,11,YRangeMax);

  lineA1 ->SetLineStyle(2);
  lineA2 ->SetLineStyle(2);
  lineA3 ->SetLineStyle(2);
  lineA4 ->SetLineStyle(2);
  lineA6 ->SetLineStyle(2);
  lineA7 ->SetLineStyle(2);
  lineA8 ->SetLineStyle(2);
  lineA9 ->SetLineStyle(2);
  lineA10->SetLineStyle(2);
  lineA11->SetLineStyle(2);

  TLatex * label_Z1_A01 = new TLatex(1.10, 2.42E6, "^{1}H");
  TLatex * label_Z1_A02 = new TLatex(2.10, 772024, "^{2}H");
  TLatex * label_Z1_A03 = new TLatex(3.10, 342644, "^{3}H");
  TLatex * label_Z2_A03 = new TLatex(3.36, 73869, "^{3}He");
  TLatex * label_Z2_A04 = new TLatex(4.10, 246102, "^{4}He");
  TLatex * label_Z2_A06 = new TLatex(6.23, 1825, "^{6}He");
  TLatex * label_Z3_A06 = new TLatex(5.59, 4638, "^{6}Li");
  TLatex * label_Z3_A07 = new TLatex(7.10, 4780, "^{7}Li");
  TLatex * label_Z3_A08 = new TLatex(8.10, 786, "^{8}Li");
  TLatex * label_Z4_A07 = new TLatex(7.10, 567, "^{7}Be");
  TLatex * label_Z4_A09 = new TLatex(9.10, 179, "^{9}Be");
  TLatex * label_Z4_A10 = new TLatex(10.20,79.32, "^{10}Be");
  TLatex * label_Z5_A08 = new TLatex(8    ,11.11, "^{8}B");
  TLatex * label_Z5_A10 = new TLatex(10.40,27.8, "^{10}B");
  TLatex * label_Z5_A11 = new TLatex(11.47,37.65, "^{11}B");

  label_Z1_A01->SetTextColor(kRed);
  label_Z1_A02->SetTextColor(kRed);
  label_Z1_A03->SetTextColor(kRed);
  label_Z2_A03->SetTextColor(kBlue);
  label_Z2_A04->SetTextColor(kBlue);
  label_Z2_A06->SetTextColor(kBlue);
  label_Z3_A06->SetTextColor(kGreen);
  label_Z3_A07->SetTextColor(kGreen);
  label_Z3_A08->SetTextColor(kGreen);
  label_Z4_A07->SetTextColor(kMagenta);
  label_Z4_A09->SetTextColor(kMagenta);
  label_Z4_A10->SetTextColor(kMagenta);
  label_Z5_A08->SetTextColor(kAzure-2);
  label_Z5_A10->SetTextColor(kAzure-2);
  label_Z5_A11->SetTextColor(kAzure-2);

  label_Z1_A01->SetTextAlign(21);
  label_Z1_A02->SetTextAlign(21);
  label_Z1_A03->SetTextAlign(21);
  label_Z2_A03->SetTextAlign(21);
  label_Z2_A04->SetTextAlign(21);
  label_Z2_A06->SetTextAlign(21);
  label_Z3_A06->SetTextAlign(21);
  label_Z3_A07->SetTextAlign(21);
  label_Z3_A08->SetTextAlign(21);
  label_Z4_A07->SetTextAlign(21);
  label_Z4_A09->SetTextAlign(21);
  label_Z4_A10->SetTextAlign(21);
  label_Z5_A08->SetTextAlign(21);
  label_Z5_A10->SetTextAlign(21);
  label_Z5_A11->SetTextAlign(21);

  label_Z1_A01->SetTextFont(42);
  label_Z1_A02->SetTextFont(42);
  label_Z1_A03->SetTextFont(42);
  label_Z2_A03->SetTextFont(42);
  label_Z2_A04->SetTextFont(42);
  label_Z2_A06->SetTextFont(42);
  label_Z3_A06->SetTextFont(42);
  label_Z3_A07->SetTextFont(42);
  label_Z3_A08->SetTextFont(42);
  label_Z4_A07->SetTextFont(42);
  label_Z4_A09->SetTextFont(42);
  label_Z4_A10->SetTextFont(42);
  label_Z5_A08->SetTextFont(42);
  label_Z5_A10->SetTextFont(42);
  label_Z5_A11->SetTextFont(42);

  label_Z1_A01->Draw("SAME");
  label_Z1_A02->Draw("SAME");
  label_Z1_A03->Draw("SAME");
  label_Z2_A03->Draw("SAME");
  label_Z2_A04->Draw("SAME");
  label_Z2_A06->Draw("SAME");
  label_Z3_A06->Draw("SAME");
  label_Z3_A07->Draw("SAME");
  label_Z3_A08->Draw("SAME");
  label_Z4_A07->Draw("SAME");
  label_Z4_A09->Draw("SAME");
  label_Z4_A10->Draw("SAME");
  label_Z5_A08->Draw("SAME");
  label_Z5_A10->Draw("SAME");
  label_Z5_A11->Draw("SAME");

  /*
  HistZ1->Scale(1./HistZ1->Integral());
  HistZ2->Scale(1./HistZ2->Integral());
  HistZ3->Scale(1./HistZ3->Integral());
  HistZ4->Scale(1./HistZ4->Integral());
  HistZ5->Scale(1./HistZ5->Integral());

  TGraph * GraphZ1 = new TGraph(HistZ1);
  TGraph * GraphZ2 = new TGraph(HistZ2);
  TGraph * GraphZ3 = new TGraph(HistZ3);
  TGraph * GraphZ4 = new TGraph(HistZ4);
  TGraph * GraphZ5 = new TGraph(HistZ5);

  GraphZ1->SetTitle("Z=1");
  GraphZ2->SetTitle("Z=2");
  GraphZ3->SetTitle("Z=3");
  GraphZ4->SetTitle("Z=4");
  GraphZ5->SetTitle("Z=5");

  TMultiGraph * TheGraphTotal = new TMultiGraph ();
  TheGraphTotal->Add(GraphZ1);
  TheGraphTotal->Add(GraphZ2);
  TheGraphTotal->Add(GraphZ3);
  TheGraphTotal->Add(GraphZ4);
  TheGraphTotal->Add(GraphZ5);

  TheGraphTotal->Draw("AL");
  TheGraphTotal->GetXaxis()->SetLabelSize(0.05);
  TheGraphTotal->GetXaxis()->SetTitleSize(0.05);
  TheGraphTotal->GetYaxis()->SetLabelSize(0.05);
  TheGraphTotal->GetYaxis()->SetTitleSize(0.05);
  TheGraphTotal->GetYaxis()->SetTitle("counts");
  TheGraphTotal->GetXaxis()->SetTitle("Mass Spectrum (a.u.)");
  TheGraphTotal->GetYaxis()->SetRangeUser(1,1E6);

  TheGraphTotal->Draw("a fb l3d");
  */

  gPad->Modified();
  gPad->Update();

  c1->Print("figure_MassSpectra.pdf");
  c1->Print("figure_MassSpectra.png");

}
