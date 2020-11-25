//______________________________________________________________________________
// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
Double_t func14(double *x, Double_t *par)
{

  Double_t Z = par[14];
  Double_t A = par[15];
  Double_t xx,exp1,exp2,res=1.0;
  Double_t reslog,ene;

  if(Z==0 && A==0)
  {
    return par[12];
  }
  xx = x[0]-par[13];
  bool foffset=false; //this is true for fitting procedure, false for the analysis
  //if xx<0 never reached from data analysis
  if(xx<=0)
  {
    if(foffset)
    {
      xx=x[0];
    }
    else
    {
      return res;
    }
  }

 exp1 = par[2] + par[3] + 1;
 exp2 = 1./exp1;
 reslog = log(1.+ par[9]* Z)*(1.- exp(-par[10]*pow(Z,par[11])))/Z;
 ene = par[6] * reslog * xx ;
 ene = ene + par[7] * Z * sqrt(A) * log(1. + par[8] * reslog  * xx);
 res = pow(ene,exp1) +
       pow((par[4]* pow(Z,par[0]) * pow(A,par[1])),exp1) +
       par[5]*pow(Z,2) * pow(A,par[2]) * pow(ene,par[3]);
 res = pow(res,exp2) - ene + par[12];

 return res;
}
//______________________________________________________________________________



void Step7_Fit_3th_DEEFitLine()
{
   const int NUMTEL=20;
   //////////////////////////////////////////////////////////////////////////////
   /// read raw data
   TFile * FileInDEE = new TFile("/mnt/analysis/e15190/dellaqui/HiRA_CsI_Calibrations/output/DEEFITData_gain170.root");
   TTree * tree = (TTree*)FileInDEE->Get("h1");
   TH2F * DEERawHist = new TH2F ("DEERawHist","DEERawHist",3000,0,3000,4000,0,150);

   TCanvas * c1 =new TCanvas("c1","",1024,768);
   c1->SetLogz(1);
   tree->Draw("desipgf:fastpg>>DEERawHist",Form("numtel==%d",NUMTEL),"colz");


   /////////////////////////////////////////////////////////////////////////////
   /// Draw DEEFIT line
   ifstream FileInPar("../data/DEEFITParameters.dat");
   double par0[12][4];
   double par1[12][4];
   double par2[12][4];
   double par3[12][4];
   double par4[12][4];
   double par5[12][4];
   double par6[12][4];
   double par7[12][4];
   double par8[12][4];
   double par9[12][4];
   double par10[12][4];
   double par11[12][4];
   double par12[12][4];
   double par13[12][4];

   while (FileInPar.is_open() && !FileInPar.eof())
  {
    std::string LineRead;
    std::getline(FileInPar, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;

    int ntel;
    int mf;
    int npar;
    double chi2;

    LineStream >> ntel >> mf >> npar ;
    numtel = ntel/4; // take integer
    numcsi = ntel%4;
    if(ntel!=NUMTEL) continue;

    LineStream >> par0[numtel][numcsi] >> par1[numtel][numcsi] >> par2[numtel][numcsi] >> par3[numtel][numcsi];
    LineStream >> par4[numtel][numcsi] >> par5[numtel][numcsi] >> par6[numtel][numcsi] >> par7[numtel][numcsi];
    LineStream >> par8[numtel][numcsi] >> par9[numtel][numcsi] >> par10[numtel][numcsi] >> par11[numtel][numcsi];
    LineStream >> par12[numtel][numcsi] >> par13[numtel][numcsi] >> chi2;
  }

  //////////////////////////////////////////////////////////////////////////////
  //// creating TF1
  TF1 * fDEELineZ1 = new TF1("fDEELineZ1",func14,0,3000,16);
  TF1 * fDEELineZ2 = new TF1("fDEELineZ2",func14,0,3000,16);
  TF1 * fDEELineZ3 = new TF1("fDEELineZ3",func14,0,3000,16);
  TF1 * fDEELineZ4 = new TF1("fDEELineZ4",func14,0,3000,16);
  TF1 * fDEELineZ5 = new TF1("fDEELineZ5",func14,0,3000,16);
  fDEELineZ1->SetNpx(400);
  fDEELineZ2->SetNpx(400);
  fDEELineZ3->SetNpx(400);
  fDEELineZ4->SetNpx(400);
  fDEELineZ5->SetNpx(400);
  fDEELineZ1->SetLineWidth(3);
  fDEELineZ2->SetLineWidth(3);
  fDEELineZ3->SetLineWidth(3);
  fDEELineZ4->SetLineWidth(3);
  fDEELineZ5->SetLineWidth(3);

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if((4*i+j)!=NUMTEL) continue;
      fDEELineZ1->SetParameter(0,par0[i][j]);
      fDEELineZ1->SetParameter(1,par1[i][j]);
      fDEELineZ1->SetParameter(2,par2[i][j]);
      fDEELineZ1->SetParameter(3,par3[i][j]);
      fDEELineZ1->SetParameter(4,par4[i][j]);
      fDEELineZ1->SetParameter(5,par5[i][j]);
      fDEELineZ1->SetParameter(6,par6[i][j]);
      fDEELineZ1->SetParameter(7,par7[i][j]);
      fDEELineZ1->SetParameter(8,par8[i][j]);
      fDEELineZ1->SetParameter(9,par9[i][j]);
      fDEELineZ1->SetParameter(10,par10[i][j]);
      fDEELineZ1->SetParameter(11,par11[i][j]);
      fDEELineZ1->SetParameter(12,par12[i][j]);
      fDEELineZ1->SetParameter(13,par13[i][j]);

      fDEELineZ2->SetParameter(0,par0[i][j]);
      fDEELineZ2->SetParameter(1,par1[i][j]);
      fDEELineZ2->SetParameter(2,par2[i][j]);
      fDEELineZ2->SetParameter(3,par3[i][j]);
      fDEELineZ2->SetParameter(4,par4[i][j]);
      fDEELineZ2->SetParameter(5,par5[i][j]);
      fDEELineZ2->SetParameter(6,par6[i][j]);
      fDEELineZ2->SetParameter(7,par7[i][j]);
      fDEELineZ2->SetParameter(8,par8[i][j]);
      fDEELineZ2->SetParameter(9,par9[i][j]);
      fDEELineZ2->SetParameter(10,par10[i][j]);
      fDEELineZ2->SetParameter(11,par11[i][j]);
      fDEELineZ2->SetParameter(12,par12[i][j]);
      fDEELineZ2->SetParameter(13,par13[i][j]);

      fDEELineZ3->SetParameter(0,par0[i][j]);
      fDEELineZ3->SetParameter(1,par1[i][j]);
      fDEELineZ3->SetParameter(2,par2[i][j]);
      fDEELineZ3->SetParameter(3,par3[i][j]);
      fDEELineZ3->SetParameter(4,par4[i][j]);
      fDEELineZ3->SetParameter(5,par5[i][j]);
      fDEELineZ3->SetParameter(6,par6[i][j]);
      fDEELineZ3->SetParameter(7,par7[i][j]);
      fDEELineZ3->SetParameter(8,par8[i][j]);
      fDEELineZ3->SetParameter(9,par9[i][j]);
      fDEELineZ3->SetParameter(10,par10[i][j]);
      fDEELineZ3->SetParameter(11,par11[i][j]);
      fDEELineZ3->SetParameter(12,par12[i][j]);
      fDEELineZ3->SetParameter(13,par13[i][j]);

      fDEELineZ4->SetParameter(0,par0[i][j]);
      fDEELineZ4->SetParameter(1,par1[i][j]);
      fDEELineZ4->SetParameter(2,par2[i][j]);
      fDEELineZ4->SetParameter(3,par3[i][j]);
      fDEELineZ4->SetParameter(4,par4[i][j]);
      fDEELineZ4->SetParameter(5,par5[i][j]);
      fDEELineZ4->SetParameter(6,par6[i][j]);
      fDEELineZ4->SetParameter(7,par7[i][j]);
      fDEELineZ4->SetParameter(8,par8[i][j]);
      fDEELineZ4->SetParameter(9,par9[i][j]);
      fDEELineZ4->SetParameter(10,par10[i][j]);
      fDEELineZ4->SetParameter(11,par11[i][j]);
      fDEELineZ4->SetParameter(12,par12[i][j]);
      fDEELineZ4->SetParameter(13,par13[i][j]);

      fDEELineZ5->SetParameter(0,par0[i][j]);
      fDEELineZ5->SetParameter(1,par1[i][j]);
      fDEELineZ5->SetParameter(2,par2[i][j]);
      fDEELineZ5->SetParameter(3,par3[i][j]);
      fDEELineZ5->SetParameter(4,par4[i][j]);
      fDEELineZ5->SetParameter(5,par5[i][j]);
      fDEELineZ5->SetParameter(6,par6[i][j]);
      fDEELineZ5->SetParameter(7,par7[i][j]);
      fDEELineZ5->SetParameter(8,par8[i][j]);
      fDEELineZ5->SetParameter(9,par9[i][j]);
      fDEELineZ5->SetParameter(10,par10[i][j]);
      fDEELineZ5->SetParameter(11,par11[i][j]);
      fDEELineZ5->SetParameter(12,par12[i][j]);
      fDEELineZ5->SetParameter(13,par13[i][j]);

      cout<< i << setw(5) << j <<setw(10)<< par0[i][j] <<setw(10)<<par13[i][j]<<endl;

      gStyle->SetPalette(kPigeon);
      gStyle->SetOptStat(0);

      DEERawHist->Draw("COLZ");
      DEERawHist->SetTitle("");
      DEERawHist->GetXaxis()->SetRangeUser(100,3000);
      DEERawHist->GetYaxis()->SetRangeUser(0,120);
      DEERawHist->GetXaxis()->SetLabelSize(0.05);
      DEERawHist->GetXaxis()->SetTitleSize(0.05);
      DEERawHist->GetYaxis()->SetLabelSize(0.05);
      DEERawHist->GetYaxis()->SetTitleSize(0.05);
      DEERawHist->GetXaxis()->SetTitleOffset(0.93);
      DEERawHist->GetXaxis()->SetTitle("E_{res} (ch)");
      DEERawHist->GetYaxis()->SetTitle("#DeltaE (MeV)");
      DEERawHist->GetXaxis()->CenterTitle(true);
      DEERawHist->GetYaxis()->CenterTitle(true);

      // Z=1 proton
      fDEELineZ1->SetParameter(14,1);
      fDEELineZ1->SetParameter(15,1);
      TLatex * Label1 = new TLatex(2300,fDEELineZ1->Eval(2300)+0.5,"^{1}H");
      Label1->Draw("SAME");
      Label1->SetTextAngle(-0.5);
      Label1->SetTextFont(42);
      Label1->SetTextColor(kRed);
      fDEELineZ1->Draw("SAME");

      // Z=2 A=4
      fDEELineZ2->SetParameter(14,2);
      fDEELineZ2->SetParameter(15,4);
      TLatex * Label2 = new TLatex(2300,fDEELineZ2->Eval(2300)+0.5,"^{4}He");
      Label2->Draw("SAME");
      Label2->SetTextAngle(-2.6);
      Label2->SetTextFont(42);
      Label2->SetTextColor(kRed);
      fDEELineZ2->Draw("SAME");

      // Z=3 A=7
      fDEELineZ3->SetParameter(14,3);
      fDEELineZ3->SetParameter(15,7);
      TLatex * Label3 = new TLatex(2300,fDEELineZ3->Eval(2300)+0.5,"^{7}Li");
      Label3->SetTextAngle(-8);
      Label3->SetTextFont(42);
      Label3->SetTextColor(kRed);
      Label3->Draw("SAME");
      fDEELineZ3->Draw("SAME");

      // Z=4 A=7
      fDEELineZ4->SetParameter(14,4);
      fDEELineZ4->SetParameter(15,7);
      TLatex * Label4 = new TLatex(2300,fDEELineZ4->Eval(2300)+0.5,"^{7}Be");
      Label4->Draw("SAME");
      Label4->SetTextFont(42);
      Label4->SetTextAngle(-12.5);
      Label4->SetTextColor(kRed);
      fDEELineZ4->Draw("SAME");

      // Z=5 A=10
      fDEELineZ5->SetParameter(14,5);
      fDEELineZ5->SetParameter(15,10);
      fDEELineZ5->SetLineStyle(2);
      TLatex * Label5 = new TLatex(2300,fDEELineZ5->Eval(2300)+0.5,"^{10}B");
      Label5->Draw("SAME");
      Label5->SetTextFont(42);
      Label5->SetTextAngle(-18);
      Label5->SetTextColor(kRed);
      fDEELineZ5->Draw("SAME");
      c1->Print(Form("figure_DEEId_TEL%02d_CSI%02d.png",i,j));
    }
  }





}
