void macro_DrawLightEfficencyCurves()
{

  //std::string FileInTag("InVoltage");
  std::string FileInTag("InChannel");

//______________________________________________________________________________
//// Read data
  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Protons
  ifstream FileInProton;
  FileInProton.open(Form("calibrations/LightEfficiencyData%s_Z01_A01.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Proton[12][4];
  std::vector<double> Leff_Proton[12][4];

  while(FileInProton.is_open() && !FileInProton.eof())
  {
    std::string LineRead;
    std::getline(FileInProton, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Proton[telnum][csinum].push_back(energyloss);
    Leff_Proton[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Deuterons
  ifstream FileInDeuteron;
  FileInDeuteron.open(Form("calibrations/LightEfficiencyData%s_Z01_A02.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Deuteron[12][4];
  std::vector<double> Leff_Deuteron[12][4];

  while(FileInDeuteron.is_open() && !FileInDeuteron.eof())
  {
    std::string LineRead;
    std::getline(FileInDeuteron, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Deuteron[telnum][csinum].push_back(energyloss);
    Leff_Deuteron[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Tritons
  ifstream FileInTriton;
  FileInTriton.open(Form("calibrations/LightEfficiencyData%s_Z01_A03.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Triton[12][4];
  std::vector<double> Leff_Triton[12][4];

  while(FileInTriton.is_open() && !FileInTriton.eof())
  {
    std::string LineRead;
    std::getline(FileInTriton, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Triton[telnum][csinum].push_back(energyloss);
    Leff_Triton[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for He3s
  ifstream FileInHe3;
  FileInHe3.open(Form("calibrations/LightEfficiencyData%s_Z02_A03.dat", FileInTag.c_str()));

  std::vector<double> Eloss_He3[12][4];
  std::vector<double> Leff_He3[12][4];

  while(FileInHe3.is_open() && !FileInHe3.eof())
  {
    std::string LineRead;
    std::getline(FileInHe3, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_He3[telnum][csinum].push_back(energyloss);
    Leff_He3[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for He4s
  ifstream FileInHe4;
  FileInHe4.open(Form("calibrations/LightEfficiencyData%s_Z02_A04.dat", FileInTag.c_str()));

  std::vector<double> Eloss_He4[12][4];
  std::vector<double> Leff_He4[12][4];

  while(FileInHe4.is_open() && !FileInHe4.eof())
  {
    std::string LineRead;
    std::getline(FileInHe4, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_He4[telnum][csinum].push_back(energyloss);
    Leff_He4[telnum][csinum].push_back(lighteff);
  }


  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for He6s
  ifstream FileInHe6;
  FileInHe6.open(Form("calibrations/LightEfficiencyData%s_Z02_A06.dat", FileInTag.c_str()));

  std::vector<double> Eloss_He6[12][4];
  std::vector<double> Leff_He6[12][4];

  while(FileInHe6.is_open() && !FileInHe6.eof())
  {
    std::string LineRead;
    std::getline(FileInHe6, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_He6[telnum][csinum].push_back(energyloss);
    Leff_He6[telnum][csinum].push_back(lighteff);
  }


  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Li6s
  ifstream FileInLi6;
  FileInLi6.open(Form("calibrations/LightEfficiencyData%s_Z03_A06.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Li6[12][4];
  std::vector<double> Leff_Li6[12][4];

  while(FileInLi6.is_open() && !FileInLi6.eof())
  {
    std::string LineRead;
    std::getline(FileInLi6, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Li6[telnum][csinum].push_back(energyloss);
    Leff_Li6[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Li7s
  ifstream FileInLi7;
  FileInLi7.open(Form("calibrations/LightEfficiencyData%s_Z03_A07.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Li7[12][4];
  std::vector<double> Leff_Li7[12][4];

  while(FileInLi7.is_open() && !FileInLi7.eof())
  {
    std::string LineRead;
    std::getline(FileInLi7, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Li7[telnum][csinum].push_back(energyloss);
    Leff_Li7[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Li8s
  ifstream FileInLi8;
  FileInLi8.open(Form("calibrations/LightEfficiencyData%s_Z03_A08.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Li8[12][4];
  std::vector<double> Leff_Li8[12][4];

  while(FileInLi8.is_open() && !FileInLi8.eof())
  {
    std::string LineRead;
    std::getline(FileInLi8, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Li8[telnum][csinum].push_back(energyloss);
    Leff_Li8[telnum][csinum].push_back(lighteff);
  }


  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Be7s
  ifstream FileInBe7;
  FileInBe7.open(Form("calibrations/LightEfficiencyData%s_Z04_A07.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Be7[12][4];
  std::vector<double> Leff_Be7[12][4];

  while(FileInBe7.is_open() && !FileInBe7.eof())
  {
    std::string LineRead;
    std::getline(FileInBe7, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Be7[telnum][csinum].push_back(energyloss);
    Leff_Be7[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for Be9s
  ifstream FileInBe9;
  FileInBe9.open(Form("calibrations/LightEfficiencyData%s_Z04_A09.dat", FileInTag.c_str()));

  std::vector<double> Eloss_Be9[12][4];
  std::vector<double> Leff_Be9[12][4];

  while(FileInBe9.is_open() && !FileInBe9.eof())
  {
    std::string LineRead;
    std::getline(FileInBe9, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_Be9[telnum][csinum].push_back(energyloss);
    Leff_Be9[telnum][csinum].push_back(lighteff);
  }


  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for B10s
  ifstream FileInB10;
  FileInB10.open(Form("calibrations/LightEfficiencyData%s_Z05_A10.dat", FileInTag.c_str()));

  std::vector<double> Eloss_B10[12][4];
  std::vector<double> Leff_B10[12][4];

  while(FileInB10.is_open() && !FileInB10.eof())
  {
    std::string LineRead;
    std::getline(FileInB10, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_B10[telnum][csinum].push_back(energyloss);
    Leff_B10[telnum][csinum].push_back(lighteff);
  }

  //////////////////////////////////////////////////////////////////////////////
  //// retrive data for C12s
  ifstream FileInC12;
  FileInC12.open(Form("calibrations/LightEfficiencyData%s_Z06_A12.dat", FileInTag.c_str()));

  std::vector<double> Eloss_C12[12][4];
  std::vector<double> Leff_C12[12][4];

  while(FileInC12.is_open() && !FileInC12.eof())
  {
    std::string LineRead;
    std::getline(FileInC12, LineRead);

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

    LineStream >> telnum >> csinum >> Z >> A >> energyloss >> lighteff;

    Eloss_C12[telnum][csinum].push_back(energyloss);
    Leff_C12[telnum][csinum].push_back(lighteff);
  }

  FileInProton.close();
  FileInDeuteron.close();
  FileInTriton.close();
  FileInHe3.close();
  FileInHe4.close();
  FileInHe6.close();
  FileInLi6.close();
  FileInLi7.close();
  FileInLi8.close();
  FileInBe7.close();
  FileInBe9.close();
  FileInB10.close();
  FileInC12.close();
//______________________________________________________________________________

//______________________________________________________________________________
/// create graphs
  TMultiGraph * multigraph[12][4];
  TGraph * graph_Proton[12][4];
  TGraph * graph_Deuteron[12][4];
  TGraph * graph_Triton[12][4];
  TGraph * graph_He3[12][4];
  TGraph * graph_He4[12][4];
  TGraph * graph_He6[12][4];
  TGraph * graph_Li6[12][4];
  TGraph * graph_Li7[12][4];
  TGraph * graph_Li8[12][4];
  TGraph * graph_Be7[12][4];
  TGraph * graph_Be9[12][4];
  TGraph * graph_B10[12][4];
  TGraph * graph_C12[12][4];

  TLegend * legend[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      //if(i!=5 || j!=0) continue;

      multigraph[i][j] = new TMultiGraph();

      graph_Proton[i][j] = new TGraph(Eloss_Proton[i][j].size(), Eloss_Proton[i][j].data(), Leff_Proton[i][j].data());
      graph_Deuteron[i][j] = new TGraph(Eloss_Deuteron[i][j].size(), Eloss_Deuteron[i][j].data(), Leff_Deuteron[i][j].data());
      graph_Triton[i][j] = new TGraph(Eloss_Triton[i][j].size(), Eloss_Triton[i][j].data(), Leff_Triton[i][j].data());
      graph_He3[i][j] = new TGraph(Eloss_He3[i][j].size(), Eloss_He3[i][j].data(), Leff_He3[i][j].data());
      graph_He4[i][j] = new TGraph(Eloss_He4[i][j].size(), Eloss_He4[i][j].data(), Leff_He4[i][j].data());
      graph_He6[i][j] = new TGraph(Eloss_He6[i][j].size(), Eloss_He6[i][j].data(), Leff_He6[i][j].data());
      graph_Li6[i][j] = new TGraph(Eloss_Li6[i][j].size(), Eloss_Li6[i][j].data(), Leff_Li6[i][j].data());
      graph_Li7[i][j] = new TGraph(Eloss_Li7[i][j].size(), Eloss_Li7[i][j].data(), Leff_Li7[i][j].data());
      graph_Li8[i][j] = new TGraph(Eloss_Li8[i][j].size(), Eloss_Li8[i][j].data(), Leff_Li8[i][j].data());
      graph_Be7[i][j] = new TGraph(Eloss_Be7[i][j].size(), Eloss_Be7[i][j].data(), Leff_Be7[i][j].data());
      graph_Be9[i][j] = new TGraph(Eloss_Be9[i][j].size(), Eloss_Be9[i][j].data(), Leff_Be9[i][j].data());
      graph_B10[i][j] = new TGraph(Eloss_B10[i][j].size(), Eloss_B10[i][j].data(), Leff_B10[i][j].data());
      graph_C12[i][j] = new TGraph(Eloss_C12[i][j].size(), Eloss_C12[i][j].data(), Leff_C12[i][j].data());

      printf("sizep=%zu sized=%zu sizet=%zu\n", Eloss_Proton[i][j].size(),Eloss_Deuteron[i][j].size(), Eloss_Triton[i][j].size());

      graph_Proton[i][j]->SetLineColor(kRed);
      graph_Deuteron[i][j]->SetLineColor(kRed);
      graph_Triton[i][j]->SetLineColor(kRed);
      graph_He3[i][j]->SetLineColor(kGreen+1);
      graph_He4[i][j]->SetLineColor(kGreen+1);
      graph_He6[i][j]->SetLineColor(kGreen+1);
      graph_Li6[i][j]->SetLineColor(kAzure+1);
      graph_Li7[i][j]->SetLineColor(kAzure+1);
      graph_Li8[i][j]->SetLineColor(kAzure+1);
      graph_Be7[i][j]->SetLineColor(kMagenta);
      graph_Be9[i][j]->SetLineColor(kMagenta);
      graph_B10[i][j]->SetLineColor(kBlue);
      graph_C12[i][j]->SetLineColor(kOrange);

      graph_Proton[i][j]->SetLineWidth(2);
      graph_Deuteron[i][j]->SetLineWidth(2);
      graph_Triton[i][j]->SetLineWidth(2);
      graph_He3[i][j]->SetLineWidth(2);
      graph_He4[i][j]->SetLineWidth(2);
      graph_He6[i][j]->SetLineWidth(2);
      graph_Li6[i][j]->SetLineWidth(2);
      graph_Li7[i][j]->SetLineWidth(2);
      graph_Li8[i][j]->SetLineWidth(2);
      graph_Be7[i][j]->SetLineWidth(2);
      graph_Be9[i][j]->SetLineWidth(2);
      graph_B10[i][j]->SetLineWidth(2);
      graph_C12[i][j]->SetLineWidth(2);
      graph_B10[i][j]->SetLineStyle(2);
      graph_C12[i][j]->SetLineStyle(2);

      multigraph[i][j]->Add(graph_Proton[i][j]);
      multigraph[i][j]->Add(graph_Deuteron[i][j]);
      multigraph[i][j]->Add(graph_Triton[i][j]);
      multigraph[i][j]->Add(graph_He3[i][j]);
      multigraph[i][j]->Add(graph_He4[i][j]);
      multigraph[i][j]->Add(graph_He6[i][j]);
      multigraph[i][j]->Add(graph_Li6[i][j]);
      multigraph[i][j]->Add(graph_Li7[i][j]);
      multigraph[i][j]->Add(graph_Li8[i][j]);
      multigraph[i][j]->Add(graph_Be7[i][j]);
      multigraph[i][j]->Add(graph_Be9[i][j]);
      multigraph[i][j]->Add(graph_B10[i][j]);
      multigraph[i][j]->Add(graph_C12[i][j]);

      legend[i][j] = new TLegend(0.3,0.2,0.7,0.4);
      legend[i][j]->SetBorderSize(0);
      legend[i][j]->SetNColumns(4);
      legend[i][j]->AddEntry(graph_Proton[i][j],"^{1}H","l");
      legend[i][j]->AddEntry(graph_Deuteron[i][j],"^{2}H","l");
      legend[i][j]->AddEntry(graph_Triton[i][j],"^{3}H","l");
      legend[i][j]->AddEntry(graph_He3[i][j],"^{3}He","l");
      legend[i][j]->AddEntry(graph_He4[i][j],"^{4}He","l");
      legend[i][j]->AddEntry(graph_He6[i][j],"^{6}He","l");
      legend[i][j]->AddEntry(graph_Li6[i][j],"^{6}Li","l");
      legend[i][j]->AddEntry(graph_Li7[i][j],"^{7}Li","l");
      legend[i][j]->AddEntry(graph_Li8[i][j],"^{8}Li","l");
      legend[i][j]->AddEntry(graph_Be7[i][j],"^{7}Be","l");
      legend[i][j]->AddEntry(graph_Be9[i][j],"^{9}Be","l");
      legend[i][j]->AddEntry(graph_B10[i][j],"^{10}B","l");
      legend[i][j]->AddEntry(graph_C12[i][j],"^{12}C","l");
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
  //// Draw
  TCanvas * c1 = new TCanvas("c1","", 1024, 768);
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(i!=5 || j!=0) continue;
      gPad->SetLogx(1);
      multigraph[i][j]->Draw("AC");
      multigraph[i][j]->SetTitle(Form("HiRATel%02d_%02d",i,j));
      //multigraph[i][j]->GetYaxis()->SetRangeUser(0.0015,0.012);
      multigraph[i][j]->GetXaxis()->SetLabelSize(0.05);
      multigraph[i][j]->GetYaxis()->SetLabelSize(0.05);
      multigraph[i][j]->GetXaxis()->SetTitleSize(0.05);
      multigraph[i][j]->GetYaxis()->SetTitleSize(0.05);
      multigraph[i][j]->GetXaxis()->SetTitle("-dE/dx (MeV/#mum)");
      multigraph[i][j]->GetYaxis()->SetTitle("dL/dE (a.u.)");
      multigraph[i][j]->GetXaxis()->CenterTitle(true);
      multigraph[i][j]->GetYaxis()->CenterTitle(true);


      //legend[i][j]->Draw("SAME");

      gPad->Modified();
      gPad->Update();
      getchar();
    }
  }
//______________________________________________________________________________

}
