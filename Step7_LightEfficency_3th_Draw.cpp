int RetrieveLightEfficiencyPoints(const char * file_name, int num_tel, int num_csi, double ** X, double ** Y, double ** errX =0, double ** errY =0)
{
    ifstream FileIn(file_name);
    if(!FileIn.is_open())
    {
      printf("Error: file%s not found\n", file_name);
      return 0;
    }

    std::vector <double> *ELoss = new std::vector<double>;
    std::vector <double> *errELoss = new std::vector<double>;
    std::vector <double> *LightEff = new std::vector<double>;
    std::vector <double> *errLightEff = new std::vector<double>;

    int NRead=0;

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn.eof())
    {
      std::string LineRead;
      std::getline(FileIn, LineRead);

      LineRead.assign(LineRead.substr(0, LineRead.find('*')));
      if(LineRead.empty()) continue;
      if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

      std::istringstream LineStream(LineRead);

      int telnum;
      int csinum;
      int  Z;
      int A;
      double energyloss;
      double lighteff;
      double errenergyloss;
      double errlighteff;

      LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff >> errenergyloss >> errlighteff;

      if(telnum!=num_tel || num_csi!=csinum) continue;

      ELoss->push_back(energyloss);
      LightEff->push_back(lighteff);
      errELoss->push_back(errenergyloss);
      errLightEff->push_back(errlighteff);

      NRead++;
    }

    *X=ELoss->data();
    *Y=LightEff->data();
    if(errX) *errX=errELoss->data();
    if(errY) *errY=errLightEff->data();

    FileIn.close();

    return NRead;
}


void Step6_LightResponse_3th_Draw()
{

  //std::string FileInTag("InVoltage");
  std::string FileInTag("InChannel");

  TCanvas * c1 = new TCanvas ("c1","",800,600);

  const int NumTel=5;
  const int NumCsI=0;

  std::string FileIn_Z01_A01(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z01_A01.dat", FileInTag.c_str()));
  std::string FileIn_Z01_A02(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z01_A02.dat", FileInTag.c_str()));
  std::string FileIn_Z01_A03(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z01_A03.dat", FileInTag.c_str()));
  std::string FileIn_Z02_A03(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z02_A03.dat", FileInTag.c_str()));
  std::string FileIn_Z02_A04(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z02_A04.dat", FileInTag.c_str()));
  std::string FileIn_Z02_A06(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z02_A06.dat", FileInTag.c_str()));
  std::string FileIn_Z03_A06(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z03_A06.dat", FileInTag.c_str()));
  std::string FileIn_Z03_A07(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z03_A07.dat", FileInTag.c_str()));
  std::string FileIn_Z03_A08(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z03_A08.dat", FileInTag.c_str()));
  std::string FileIn_Z04_A07(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z04_A07.dat", FileInTag.c_str()));
  std::string FileIn_Z04_A09(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z04_A09.dat", FileInTag.c_str()));
  std::string FileIn_Z05_A10(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z05_A10.dat", FileInTag.c_str()));
  std::string FileIn_Z06_A12(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z06_A12.dat", FileInTag.c_str()));
  std::string FileIn_Z07_A14(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z07_A14.dat", FileInTag.c_str()));
  std::string FileIn_Z08_A16(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z08_A16.dat", FileInTag.c_str()));
  std::string FileIn_Z09_A19(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z09_A19.dat", FileInTag.c_str()));
  std::string FileIn_Z10_A20(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyData%s_Z10_A20.dat", FileInTag.c_str()));

  std::string FileIn_Z01_A01_WMU(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyDataWMU%s_Z01_A01.dat", FileInTag.c_str()));
  std::string FileIn_Z02_A04_WMU(Form("/projects/hira/guan/HiRACsILightResponse/data/LightEfficiencyDataWMU%s_Z02_A04.dat", FileInTag.c_str()));

  double * ELoss_Z01_A01;
  double * ELoss_Z01_A02;
  double * ELoss_Z01_A03;
  double * ELoss_Z02_A03;
  double * ELoss_Z02_A04;
  double * ELoss_Z02_A06;
  double * ELoss_Z03_A06;
  double * ELoss_Z03_A07;
  double * ELoss_Z03_A08;
  double * ELoss_Z04_A07;
  double * ELoss_Z04_A09;
  double * ELoss_Z05_A10;
  double * ELoss_Z06_A12;
  double * ELoss_Z07_A14;
  double * ELoss_Z08_A16;
  double * ELoss_Z09_A19;
  double * ELoss_Z10_A20;

  double * ELoss_Z01_A01_WMU;
  double * ELoss_Z02_A04_WMU;

  double * LightEff_Z01_A01;
  double * LightEff_Z01_A02;
  double * LightEff_Z01_A03;
  double * LightEff_Z02_A03;
  double * LightEff_Z02_A04;
  double * LightEff_Z02_A06;
  double * LightEff_Z03_A06;
  double * LightEff_Z03_A07;
  double * LightEff_Z03_A08;
  double * LightEff_Z04_A07;
  double * LightEff_Z04_A09;
  double * LightEff_Z05_A10;
  double * LightEff_Z06_A12;
  double * LightEff_Z07_A14;
  double * LightEff_Z08_A16;
  double * LightEff_Z09_A19;
  double * LightEff_Z10_A20;

  double * LightEff_Z01_A01_WMU;
  double * LightEff_Z02_A04_WMU;

  double * errELoss_Z01_A01;
  double * errELoss_Z01_A02;
  double * errELoss_Z01_A03;
  double * errELoss_Z02_A03;
  double * errELoss_Z02_A04;
  double * errELoss_Z02_A06;
  double * errELoss_Z03_A06;
  double * errELoss_Z03_A07;
  double * errELoss_Z03_A08;
  double * errELoss_Z04_A07;
  double * errELoss_Z04_A09;
  double * errELoss_Z05_A10;
  double * errELoss_Z06_A12;
  double * errELoss_Z07_A14;
  double * errELoss_Z08_A16;
  double * errELoss_Z09_A19;
  double * errELoss_Z10_A20;

  double * errLightEff_Z01_A01;
  double * errLightEff_Z01_A02;
  double * errLightEff_Z01_A03;
  double * errLightEff_Z02_A03;
  double * errLightEff_Z02_A04;
  double * errLightEff_Z02_A06;
  double * errLightEff_Z03_A06;
  double * errLightEff_Z03_A07;
  double * errLightEff_Z03_A08;
  double * errLightEff_Z04_A07;
  double * errLightEff_Z04_A09;
  double * errLightEff_Z05_A10;
  double * errLightEff_Z06_A12;
  double * errLightEff_Z07_A14;
  double * errLightEff_Z08_A16;
  double * errLightEff_Z09_A19;
  double * errLightEff_Z10_A20;


  double * errLightEffUp_Z01_A01_WMU;
  double * errLightEffUp_Z02_A04_WMU;
  double * errLightEffDown_Z01_A01_WMU;
  double * errLightEffDown_Z02_A04_WMU;

  //Retrieve data from files
  const int NPoints_Z01_A01 = RetrieveLightEfficiencyPoints(FileIn_Z01_A01.c_str(), NumTel, NumCsI, &ELoss_Z01_A01, &LightEff_Z01_A01);
  const int NPoints_Z01_A02 = RetrieveLightEfficiencyPoints(FileIn_Z01_A02.c_str(), NumTel, NumCsI, &ELoss_Z01_A02, &LightEff_Z01_A02);
  const int NPoints_Z01_A03 = RetrieveLightEfficiencyPoints(FileIn_Z01_A03.c_str(), NumTel, NumCsI, &ELoss_Z01_A03, &LightEff_Z01_A03);
  const int NPoints_Z02_A03 = RetrieveLightEfficiencyPoints(FileIn_Z02_A03.c_str(), NumTel, NumCsI, &ELoss_Z02_A03, &LightEff_Z02_A03);
  const int NPoints_Z02_A04 = RetrieveLightEfficiencyPoints(FileIn_Z02_A04.c_str(), NumTel, NumCsI, &ELoss_Z02_A04, &LightEff_Z02_A04);
  const int NPoints_Z02_A06 = RetrieveLightEfficiencyPoints(FileIn_Z02_A06.c_str(), NumTel, NumCsI, &ELoss_Z02_A06, &LightEff_Z02_A06);
  const int NPoints_Z03_A06 = RetrieveLightEfficiencyPoints(FileIn_Z03_A06.c_str(), NumTel, NumCsI, &ELoss_Z03_A06, &LightEff_Z03_A06);
  const int NPoints_Z03_A07 = RetrieveLightEfficiencyPoints(FileIn_Z03_A07.c_str(), NumTel, NumCsI, &ELoss_Z03_A07, &LightEff_Z03_A07);
  const int NPoints_Z03_A08 = RetrieveLightEfficiencyPoints(FileIn_Z03_A08.c_str(), NumTel, NumCsI, &ELoss_Z03_A08, &LightEff_Z03_A08);
  const int NPoints_Z04_A07 = RetrieveLightEfficiencyPoints(FileIn_Z04_A07.c_str(), NumTel, NumCsI, &ELoss_Z04_A07, &LightEff_Z04_A07);
  const int NPoints_Z04_A09 = RetrieveLightEfficiencyPoints(FileIn_Z04_A09.c_str(), NumTel, NumCsI, &ELoss_Z04_A09, &LightEff_Z04_A09);
  const int NPoints_Z05_A10 = RetrieveLightEfficiencyPoints(FileIn_Z05_A10.c_str(), NumTel, NumCsI, &ELoss_Z05_A10, &LightEff_Z05_A10);
  const int NPoints_Z06_A12 = RetrieveLightEfficiencyPoints(FileIn_Z06_A12.c_str(), NumTel, NumCsI, &ELoss_Z06_A12, &LightEff_Z06_A12);
  const int NPoints_Z07_A14 = RetrieveLightEfficiencyPoints(FileIn_Z07_A14.c_str(), NumTel, NumCsI, &ELoss_Z07_A14, &LightEff_Z07_A14);
  const int NPoints_Z08_A16 = RetrieveLightEfficiencyPoints(FileIn_Z08_A16.c_str(), NumTel, NumCsI, &ELoss_Z08_A16, &LightEff_Z08_A16);
  const int NPoints_Z09_A19 = RetrieveLightEfficiencyPoints(FileIn_Z09_A19.c_str(), NumTel, NumCsI, &ELoss_Z09_A19, &LightEff_Z09_A19);
  const int NPoints_Z10_A20 = RetrieveLightEfficiencyPoints(FileIn_Z10_A20.c_str(), NumTel, NumCsI, &ELoss_Z10_A20, &LightEff_Z10_A20);

  const int NPoints_Z01_A01_WMU = RetrieveLightEfficiencyPoints(FileIn_Z01_A01_WMU.c_str(), NumTel, NumCsI, &ELoss_Z01_A01_WMU, &LightEff_Z01_A01_WMU, &errLightEffUp_Z01_A01_WMU, &errLightEffDown_Z01_A01_WMU);
  const int NPoints_Z02_A04_WMU = RetrieveLightEfficiencyPoints(FileIn_Z02_A04_WMU.c_str(), NumTel, NumCsI, &ELoss_Z02_A04_WMU, &LightEff_Z02_A04_WMU, &errLightEffUp_Z02_A04_WMU, &errLightEffDown_Z02_A04_WMU);

  //______________________________________________________________________________
  /// create graphs
  TMultiGraph * multigraph=new TMultiGraph();
  TGraph * graph_Z01_A01=new TGraph(NPoints_Z01_A01, ELoss_Z01_A01, LightEff_Z01_A01);
  TGraph * graph_Z01_A02=new TGraph(NPoints_Z01_A02, ELoss_Z01_A02, LightEff_Z01_A02);
  TGraph * graph_Z01_A03=new TGraph(NPoints_Z01_A03, ELoss_Z01_A03, LightEff_Z01_A03);
  TGraph * graph_Z02_A03=new TGraph(NPoints_Z02_A03, ELoss_Z02_A03, LightEff_Z02_A03);
  TGraph * graph_Z02_A04=new TGraph(NPoints_Z02_A04, ELoss_Z02_A04, LightEff_Z02_A04);
  TGraph * graph_Z02_A06=new TGraph(NPoints_Z02_A06, ELoss_Z02_A06, LightEff_Z02_A06);
  TGraph * graph_Z03_A06=new TGraph(NPoints_Z03_A06, ELoss_Z03_A06, LightEff_Z03_A06);
  TGraph * graph_Z03_A07=new TGraph(NPoints_Z03_A07, ELoss_Z03_A07, LightEff_Z03_A07);
  TGraph * graph_Z03_A08=new TGraph(NPoints_Z03_A08, ELoss_Z03_A08, LightEff_Z03_A08);
  TGraph * graph_Z04_A07=new TGraph(NPoints_Z04_A07, ELoss_Z04_A07, LightEff_Z04_A07);
  TGraph * graph_Z04_A09=new TGraph(NPoints_Z04_A09, ELoss_Z04_A09, LightEff_Z04_A09);
  TGraph * graph_Z05_A10=new TGraph(NPoints_Z05_A10, ELoss_Z05_A10, LightEff_Z05_A10);
  TGraph * graph_Z06_A12=new TGraph(NPoints_Z06_A12, ELoss_Z06_A12, LightEff_Z06_A12);
  TGraph * graph_Z07_A14=new TGraph(NPoints_Z07_A14, ELoss_Z07_A14, LightEff_Z07_A14);
  TGraph * graph_Z08_A16=new TGraph(NPoints_Z08_A16, ELoss_Z08_A16, LightEff_Z08_A16);
  TGraph * graph_Z09_A19=new TGraph(NPoints_Z09_A19, ELoss_Z09_A19, LightEff_Z09_A19);
  TGraph * graph_Z10_A20=new TGraph(NPoints_Z10_A20, ELoss_Z10_A20, LightEff_Z10_A20);

  TGraph * graph_Z01_A01_WMU=new TGraph(NPoints_Z01_A01_WMU, ELoss_Z01_A01_WMU, LightEff_Z01_A01_WMU);
  TGraph * graph_Z02_A04_WMU=new TGraph(NPoints_Z02_A04_WMU, ELoss_Z02_A04_WMU, LightEff_Z02_A04_WMU);
  TGraph * shade_Z01_A01_WMU = new TGraph(2*NPoints_Z01_A01_WMU);
  TGraph * shade_Z02_A04_WMU = new TGraph(2*NPoints_Z02_A04_WMU);

  for (int i=0;i<NPoints_Z01_A01_WMU;i++) {
    shade_Z01_A01_WMU->SetPoint(i,ELoss_Z01_A01_WMU[i],LightEff_Z01_A01_WMU[i]+errLightEffUp_Z01_A01_WMU[i]);
    shade_Z01_A01_WMU->SetPoint(NPoints_Z01_A01_WMU+i,ELoss_Z01_A01_WMU[NPoints_Z01_A01_WMU-i-1],LightEff_Z01_A01_WMU[NPoints_Z01_A01_WMU-i-1]-errLightEffDown_Z01_A01_WMU[NPoints_Z01_A01_WMU-i-1]);
  }
  for (int i=0;i<NPoints_Z02_A04_WMU;i++) {
    shade_Z02_A04_WMU->SetPoint(i,ELoss_Z02_A04_WMU[i],LightEff_Z02_A04_WMU[i]+errLightEffUp_Z02_A04_WMU[i]);
    shade_Z02_A04_WMU->SetPoint(NPoints_Z02_A04_WMU+i,ELoss_Z02_A04_WMU[NPoints_Z02_A04_WMU-i-1],LightEff_Z02_A04_WMU[NPoints_Z02_A04_WMU-i-1]-errLightEffDown_Z02_A04_WMU[NPoints_Z02_A04_WMU-i-1]);
  }
  shade_Z01_A01_WMU->SetFillColor(kRed-7);
  shade_Z02_A04_WMU->SetFillColor(kGreen);

  multigraph->Add(graph_Z01_A01);
  multigraph->Add(graph_Z01_A02);
  multigraph->Add(graph_Z01_A03);
  multigraph->Add(graph_Z02_A03);
  multigraph->Add(graph_Z02_A04);
  multigraph->Add(graph_Z02_A06);
  multigraph->Add(graph_Z03_A06);
  multigraph->Add(graph_Z03_A07);
  multigraph->Add(graph_Z03_A08);
  multigraph->Add(graph_Z04_A07);
  multigraph->Add(graph_Z04_A09);
  multigraph->Add(graph_Z05_A10);
  multigraph->Add(graph_Z06_A12);
  multigraph->Add(graph_Z07_A14);
  multigraph->Add(graph_Z08_A16);
  multigraph->Add(graph_Z09_A19);
  multigraph->Add(graph_Z10_A20);

  graph_Z01_A01->SetLineWidth(2);
  graph_Z01_A02->SetLineWidth(2);
  graph_Z01_A03->SetLineWidth(2);
  graph_Z02_A03->SetLineWidth(2);
  graph_Z02_A04->SetLineWidth(2);
  graph_Z02_A06->SetLineWidth(2);
  graph_Z03_A06->SetLineWidth(2);
  graph_Z03_A07->SetLineWidth(2);
  graph_Z03_A08->SetLineWidth(2);
  graph_Z04_A07->SetLineWidth(2);
  graph_Z04_A09->SetLineWidth(2);
  graph_Z05_A10->SetLineWidth(2);
  graph_Z06_A12->SetLineWidth(2);
  graph_Z07_A14->SetLineWidth(2);
  graph_Z08_A16->SetLineWidth(2);
  graph_Z09_A19->SetLineWidth(2);
  graph_Z10_A20->SetLineWidth(2);

  graph_Z01_A01_WMU->SetLineWidth(2);
  graph_Z02_A04_WMU->SetLineWidth(2);

  graph_Z01_A01->SetLineColor(kRed);
  graph_Z01_A02->SetLineColor(kRed);
  graph_Z01_A03->SetLineColor(kRed);
  graph_Z02_A03->SetLineColor(kGreen+1);
  graph_Z02_A04->SetLineColor(kGreen+1);
  graph_Z02_A06->SetLineColor(kGreen+1);
  graph_Z03_A06->SetLineColor(kAzure+1);
  graph_Z03_A07->SetLineColor(kAzure+1);
  graph_Z03_A08->SetLineColor(kAzure+1);
  graph_Z04_A07->SetLineColor(kMagenta);
  graph_Z04_A09->SetLineColor(kMagenta);
  graph_Z05_A10->SetLineColor(kBlue);
  graph_Z06_A12->SetLineColor(kOrange+1);
  graph_Z07_A14->SetLineColor(kCyan+1);
  graph_Z08_A16->SetLineColor(kTeal+1);
  graph_Z09_A19->SetLineColor(kViolet+1);
  graph_Z10_A20->SetLineColor(kPink+2);

  graph_Z06_A12->SetLineStyle(2);
  graph_Z07_A14->SetLineStyle(2);
  graph_Z08_A16->SetLineStyle(2);
  graph_Z09_A19->SetLineStyle(2);
  graph_Z10_A20->SetLineStyle(2);

//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
  //// Draw
  gPad->SetLogx(1);
  multigraph->Draw("AC");
  shade_Z01_A01_WMU->Draw("f");
  shade_Z02_A04_WMU->Draw("f");
  multigraph->SetTitle("");
  multigraph->GetYaxis()->SetRangeUser(2,9);
  multigraph->GetXaxis()->SetLabelSize(0.05);
  multigraph->GetYaxis()->SetLabelSize(0.05);
  multigraph->GetXaxis()->SetTitleSize(0.05);
  multigraph->GetYaxis()->SetTitleSize(0.05);
  multigraph->GetXaxis()->SetTitle("-dE/dx (MeV/#mum)");
  multigraph->GetYaxis()->SetTitle("dL/dE (a.u.)");
  multigraph->GetXaxis()->CenterTitle(true);
  multigraph->GetYaxis()->CenterTitle(true);

  TLatex * Label_Z01_A01= new TLatex (0.0010,5.1,"^{1}H");
  TLatex * Label_Z01_A02= new TLatex (0.0014,5.8,"^{2}H");
  TLatex * Label_Z01_A03= new TLatex (0.0020,6.26,"^{3}H");
  TLatex * Label_Z02_A03= new TLatex (0.0052,6.96,"^{3}He");
  TLatex * Label_Z02_A04= new TLatex (0.009,7.61,"^{4}He");
  TLatex * Label_Z02_A06= new TLatex (0.016,7.93,"^{6}He");
  TLatex * Label_Z03    = new TLatex (0.035,8.4,"^{6,7,8}Li");
  TLatex * Label_Z04    = new TLatex (0.085,7.71,"^{7,9}Be");
  TLatex * Label_Z05    = new TLatex (0.13,7.15,"^{10}B");
  TLatex * Label_Z06    = new TLatex (0.18,6.58,"^{12}C");
  TLatex * Label_Z07    = new TLatex (0.25,5.63,"^{14}N");
  TLatex * Label_Z08    = new TLatex (0.32,5.01,"^{16}O");
  TLatex * Label_Z09    = new TLatex (0.43,4.41,"^{19}F");
  TLatex * Label_Z10    = new TLatex (0.53,3.90,"^{20}Ne");

  TLatex * Label_Z01_A01_WMU = new TLatex (0.013,6.07,"^{1}H WMU");
  TLatex * Label_Z02_A04_WMU = new TLatex (0.025,4.17,"^{4}He WMU");

  Label_Z01_A01->SetTextColor(kRed);
  Label_Z01_A02->SetTextColor(kRed);
  Label_Z01_A03->SetTextColor(kRed);
  Label_Z02_A03->SetTextColor(kGreen+1);
  Label_Z02_A04->SetTextColor(kGreen+1);
  Label_Z02_A06->SetTextColor(kGreen+1);
  Label_Z03    ->SetTextColor(kAzure+1);
  Label_Z04    ->SetTextColor(kMagenta);
  Label_Z05    ->SetTextColor(kBlue);
  Label_Z06    ->SetTextColor(kOrange+1);
  Label_Z07    ->SetTextColor(kCyan+1);
  Label_Z08    ->SetTextColor(kTeal+1);
  Label_Z09    ->SetTextColor(kViolet+1);
  Label_Z10    ->SetTextColor(kPink+2);

  Label_Z01_A01_WMU->SetTextColor(kRed-7);
  Label_Z02_A04_WMU->SetTextColor(kGreen);

  Label_Z01_A01->Draw("same");
  Label_Z01_A02->Draw("same");
  Label_Z01_A03->Draw("same");
  Label_Z02_A03->Draw("same");
  Label_Z02_A04->Draw("same");
  Label_Z02_A06->Draw("same");
  Label_Z03    ->Draw("same");
  Label_Z04    ->Draw("same");
  Label_Z05    ->Draw("same");
  Label_Z06    ->Draw("same");
  Label_Z07    ->Draw("same");
  Label_Z08    ->Draw("same");
  Label_Z09    ->Draw("same");
  Label_Z10    ->Draw("same");
  Label_Z01_A01_WMU->Draw("same");
  Label_Z02_A04_WMU->Draw("same");

  gPad->Modified();
  gPad->Update();

  c1->Print(Form("figure_LightEfficiencyCurves_TEL%02d_CSI%02d.png",NumTel,NumCsI));
  c1->Print(Form("figure_LightEfficiencyCurves_TEL%02d_CSI%02d.pdf",NumTel,NumCsI));
//______________________________________________________________________________

}
