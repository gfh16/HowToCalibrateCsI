//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// deifinition of fitting formula of protons
double fit_proton (double *x, double *par)
{
  double exponent = (1+par[2])/(1+par[3]);
  double light = par[0]+par[1]*pow(x[0],exponent);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// deifinition of fitting formula of deuterons
double fit_deuteron (double *x, double *par)
{
  double exponent = (2+par[2])/(2+par[3]);
  double light = par[0]+par[1]*pow(x[0],exponent);
  return light;
}
//______________________________________________________________________________
//// deifinition of fitting formula of tritons
double fit_triton (double *x, double *par)
{
  double exponent = (3+par[2])/(3+par[3]);
  double light = par[0]+par[1]*pow(x[0],exponent);
  return light;
}
//______________________________________________________________________________

int RetrieveCalibrationPoints(const char * file_name, int num_tel, int num_csi, double ** X, double ** Y, double ** errX, double ** errY)
{
    ifstream FileIn(file_name);
    if(!FileIn.is_open())
    {
      printf("Error: file%s not found\n", file_name);
      return 0;
    }
    
    std::vector <double> *CsIV = new std::vector<double>;
    std::vector <double> *errCsIV = new std::vector<double>;
    std::vector <double> *CsIE = new std::vector<double>;
    std::vector <double> *errCsIE = new std::vector<double>;
    
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
      double V;
      double errV;
      double E;
      double errE;

      LineStream >> telnum >> csinum >> V >> errV >> E >> errE; 
      
      if(telnum!=num_tel || num_csi!=csinum) continue;

      CsIV->push_back(V);
      errCsIV->push_back(errV);
      CsIE->push_back(E);
      errCsIE->push_back(errE);
      
      NRead++;
    }
    
    *X=CsIE->data();
    *Y=CsIV->data();
    *errX=errCsIE->data();
    *errY=errCsIV->data();
    
    return NRead;
}

int RetrieveFitParameters(const char * file_name, int num_tel, int num_csi, int Z, int A, double ** Parameters)
{
    ifstream FileIn(file_name);
    if(!FileIn.is_open())
    {
      printf("Error: file%s not found\n", file_name);
      return 0;
    }
        
    std::vector <double> *TheParamaterVector = new std::vector<double>;
    
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
      int Zread;
      int Aread;
      std::string Formula;
      int num_par;
      
      LineStream >> telnum >> csinum >> Zread >> Aread >> Formula >> num_par; 
                  
      if(telnum!=num_tel || num_csi!=csinum || Z!=Zread || A!=Aread) continue;

      for(int i=0; i< num_par; i++) {
        double AParameter;
	LineStream>>AParameter;
        TheParamaterVector->push_back(AParameter);
	NRead++;
      }  
    }
    
    *Parameters=TheParamaterVector->data();
    
    return NRead;
}

//______________________________________________________________________________

void figure_pdt_calibration()
{
  TCanvas * c1 = new TCanvas ("c1","",800,600);
  TCanvas * c2 = new TCanvas ("c2","",800,600);
  
  const int NumTel=5;
  const int NumCsI=0;
   
  const Int_t NFiles_Proton=11;
  std::string * FileIn_name_Proton[NFiles_Proton];
  FileIn_name_Proton[0] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/WMUdataAddOnePecenterrEnergy_Z01_A01.dat");   // WMU data
  FileIn_name_Proton[1] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/DEEPointsOmitLow_Z01_A01.dat"); //DEE points
  FileIn_name_Proton[2] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39.0AMeV_gain 200.dat"); // kinematics ponits
  FileIn_name_Proton[3] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[4] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4000_4005_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[5] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4021_4022_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[6] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[7] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[8] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[9] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[10] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points
  int NumPoints_Proton[NFiles_Proton];
  
  const Int_t NFiles_Deuteron=3;
  std::string * FileIn_name_Deuteron[NFiles_Deuteron];
  FileIn_name_Deuteron[0] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/WMUdataAddOnePecenterrEnergy_Z01_A02.dat");   // WMU data
  FileIn_name_Deuteron[1] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/DEEPointsOmitLow_Z01_A02.dat"); //DEE points
  FileIn_name_Deuteron[2] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points
  int NumPoints_Deuteron[NFiles_Deuteron];
  
  const Int_t NFiles_Triton=2;
  std::string * FileIn_name_Triton[NFiles_Triton];
  FileIn_name_Triton[0] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/DEEPointsOmitLow_Z01_A03.dat"); //DEE points
  FileIn_name_Triton[1] = new std::string("/projects/hira/guan/HiRACsILightResponse/data/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points
  int NumPoints_Triton[NFiles_Triton];
  
  double * FitParameters_Proton;
  double * FitParameters_Deuteron;
  double * FitParameters_Triton;
  
  const int NumParameters_Proton=RetrieveFitParameters("/projects/hira/guan/HiRACsILightResponse/calibrations/SimultaneouslyFitParPDT.dat", NumTel, NumCsI, 1, 1, &FitParameters_Proton);
  const int NumParameters_Deuteron=RetrieveFitParameters("/projects/hira/guan/HiRACsILightResponse/calibrations/SimultaneouslyFitParPDT.dat", NumTel, NumCsI, 1, 2, &FitParameters_Deuteron);
  const int NumParameters_Triton=RetrieveFitParameters("/projects/hira/guan/HiRACsILightResponse/calibrations/SimultaneouslyFitParPDT.dat", NumTel, NumCsI, 1, 3, &FitParameters_Triton);
  
  TF1 * FitProton = new TF1 ("FitProton", fit_proton, 0, 198, NumParameters_Proton);
  FitProton->SetParameters(FitParameters_Proton);
  TF1 * FitDeuteron = new TF1 ("FitDeuteron", fit_deuteron, 0, 263, NumParameters_Deuteron);
  FitDeuteron->SetParameters(FitParameters_Deuteron);
  TF1 * FitTriton = new TF1 ("FitTriton", fit_triton, 0, 312, NumParameters_Triton);
  FitTriton->SetParameters(FitParameters_Triton);
  TF1 * FitProton_AfterPunch = new TF1 ("FitProton", fit_proton, 198, 2000, NumParameters_Proton);
  FitProton_AfterPunch->SetParameters(FitParameters_Proton);
  TF1 * FitDeuteron_AfterPunch = new TF1 ("FitDeuteron", fit_deuteron, 263, 2000, NumParameters_Deuteron);
  FitDeuteron_AfterPunch->SetParameters(FitParameters_Deuteron);
  TF1 * FitTriton_AfterPunch = new TF1 ("FitTriton", fit_triton, 312, 2000, NumParameters_Triton);
  FitTriton_AfterPunch->SetParameters(FitParameters_Triton);
  
  double * CsIV_Proton[NFiles_Proton];
  double * errCsIV_Proton[NFiles_Proton];
  double * CsIE_Proton[NFiles_Proton];
  double * errCsIE_Proton[NFiles_Proton];
  double * CsIV_Deuteron[NFiles_Deuteron];
  double * errCsIV_Deuteron[NFiles_Deuteron];
  double * CsIE_Deuteron[NFiles_Deuteron];
  double * errCsIE_Deuteron[NFiles_Deuteron]; 
  double * CsIV_Triton[NFiles_Triton];
  double * errCsIV_Triton[NFiles_Triton];
  double * CsIE_Triton[NFiles_Triton];
  double * errCsIE_Triton[NFiles_Triton];
  
  TGraphErrors * DataProton[NFiles_Proton];
  TGraphErrors * DataDeuteron[NFiles_Deuteron];
  TGraphErrors * DataTriton[NFiles_Triton];
  
  TGraphErrors * DataProtonInsert[NFiles_Proton];
  TGraphErrors * DataDeuteronInsert[NFiles_Deuteron];
  TGraphErrors * DataTritonInsert[NFiles_Triton];
    
  TMultiGraph * Graph = new TMultiGraph();
  TMultiGraph * TheInsertGraph = new TMultiGraph ();
    
  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
  {
    NumPoints_Triton[FileNum] = RetrieveCalibrationPoints(FileIn_name_Triton[FileNum]->c_str(), NumTel, NumCsI, &CsIE_Triton[FileNum], &CsIV_Triton[FileNum], &errCsIV_Triton[FileNum], &errCsIV_Triton[FileNum]);
    if(NumPoints_Triton[FileNum]==0) continue;
    DataTriton[FileNum] = new TGraphErrors(NumPoints_Triton[FileNum], CsIE_Triton[FileNum], CsIV_Triton[FileNum], errCsIV_Triton[FileNum], errCsIV_Triton[FileNum]);
    DataTriton[FileNum]->SetMarkerColor(kBlue);
    DataTriton[FileNum]->SetLineColor(kBlue);
    DataTriton[FileNum]->SetMarkerStyle(20+FileNum);
    DataTriton[FileNum]->SetMarkerSize(1.3);
    DataTritonInsert[FileNum] = new TGraphErrors(NumPoints_Triton[FileNum], CsIE_Triton[FileNum], CsIV_Triton[FileNum], errCsIV_Triton[FileNum], errCsIV_Triton[FileNum]);
    DataTritonInsert[FileNum]->SetMarkerColor(kBlue);
    DataTritonInsert[FileNum]->SetLineColor(kBlue);
    DataTritonInsert[FileNum]->SetMarkerStyle(20+FileNum);
    DataTritonInsert[FileNum]->SetMarkerSize(1.3);
    Graph->Add(DataTriton[FileNum]);
    TheInsertGraph->Add(DataTritonInsert[FileNum]);
  }  
  for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
  {
    NumPoints_Deuteron[FileNum] = RetrieveCalibrationPoints(FileIn_name_Deuteron[FileNum]->c_str(), NumTel, NumCsI, &CsIE_Deuteron[FileNum], &CsIV_Deuteron[FileNum], &errCsIV_Deuteron[FileNum], &errCsIV_Deuteron[FileNum]);
    if(NumPoints_Deuteron[FileNum]==0) continue;
    DataDeuteron[FileNum] = new TGraphErrors(NumPoints_Deuteron[FileNum], CsIE_Deuteron[FileNum], CsIV_Deuteron[FileNum], errCsIV_Deuteron[FileNum], errCsIV_Deuteron[FileNum]);
    DataDeuteron[FileNum]->SetMarkerColor(kGreen);
    DataDeuteron[FileNum]->SetLineColor(kGreen);
    DataDeuteron[FileNum]->SetMarkerStyle(20+FileNum);
    DataDeuteron[FileNum]->SetMarkerSize(1.3);
    DataDeuteronInsert[FileNum] = new TGraphErrors(NumPoints_Deuteron[FileNum], CsIE_Deuteron[FileNum], CsIV_Deuteron[FileNum], errCsIV_Deuteron[FileNum], errCsIV_Deuteron[FileNum]);
    DataDeuteronInsert[FileNum]->SetMarkerColor(kGreen);
    DataDeuteronInsert[FileNum]->SetLineColor(kGreen);
    DataDeuteronInsert[FileNum]->SetMarkerStyle(20+FileNum);
    DataDeuteronInsert[FileNum]->SetMarkerSize(1.3);
    Graph->Add(DataDeuteron[FileNum]);
    TheInsertGraph->Add(DataDeuteronInsert[FileNum]);
  }
  for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
  {
    NumPoints_Proton[FileNum] = RetrieveCalibrationPoints(FileIn_name_Proton[FileNum]->c_str(), NumTel, NumCsI, &CsIE_Proton[FileNum], &CsIV_Proton[FileNum], &errCsIV_Proton[FileNum], &errCsIV_Proton[FileNum]);
    if(NumPoints_Proton[FileNum]==0) continue;
    DataProton[FileNum] = new TGraphErrors(NumPoints_Proton[FileNum], CsIE_Proton[FileNum], CsIV_Proton[FileNum], errCsIV_Proton[FileNum], errCsIV_Proton[FileNum]);
    DataProton[FileNum]->SetMarkerColor(kRed);
    DataProton[FileNum]->SetLineColor(kRed);
    DataProton[FileNum]->SetMarkerStyle(20+FileNum);
    DataProton[FileNum]->SetMarkerSize(1.3);
    DataProtonInsert[FileNum] = new TGraphErrors(NumPoints_Proton[FileNum], CsIE_Proton[FileNum], CsIV_Proton[FileNum], errCsIV_Proton[FileNum], errCsIV_Proton[FileNum]);
    DataProtonInsert[FileNum]->SetMarkerColor(kRed);
    DataProtonInsert[FileNum]->SetLineColor(kRed);
    DataProtonInsert[FileNum]->SetMarkerStyle(20+FileNum);
    DataProtonInsert[FileNum]->SetMarkerSize(1.3);
    Graph->Add(DataProton[FileNum]);
    TheInsertGraph->Add(DataProtonInsert[FileNum]);
  }
  
  //Drawing
  c1->cd();
  Graph->Draw("APE");
  TAxis * XAxis = Graph->GetXaxis();
  TAxis * YAxis = Graph->GetYaxis();
  XAxis->SetLabelSize(0.05);
  XAxis->SetTitleSize(0.05);
  XAxis->CenterTitle(true);
  YAxis->SetLabelSize(0.05);
  YAxis->SetTitleSize(0.05);
  YAxis->CenterTitle(true); 
  XAxis->SetTitle("E (MeV)");
  YAxis->SetTitle("Light Output (V)");
  YAxis->SetNdivisions(6,5,0);
  XAxis->SetLimits(0,330);
    
  FitProton->SetLineColor(kRed);
  FitDeuteron->SetLineColor(kGreen);
  FitTriton->SetLineColor(kBlue);
  FitProton->SetLineWidth(2);
  FitDeuteron->SetLineWidth(2);
  FitTriton->SetLineWidth(2);
  
  FitTriton->Draw("SAME");
  FitDeuteron->Draw("SAME");
  FitProton->Draw("SAME");
  
  FitProton_AfterPunch->SetLineColor(kRed);
  FitDeuteron_AfterPunch->SetLineColor(kGreen);
  FitTriton_AfterPunch->SetLineColor(kBlue);
  FitProton_AfterPunch->SetLineWidth(2);
  FitDeuteron_AfterPunch->SetLineWidth(2);
  FitTriton_AfterPunch->SetLineWidth(2);
  FitProton_AfterPunch->SetLineStyle(2);
  FitDeuteron_AfterPunch->SetLineStyle(2);
  FitTriton_AfterPunch->SetLineStyle(2);
  
  FitTriton_AfterPunch->Draw("SAME");
  FitDeuteron_AfterPunch->Draw("SAME");
  FitProton_AfterPunch->Draw("SAME");
  
  TLegend * legendario = new TLegend(0.12,0.4,0.4,0.85);
  legendario->SetBorderSize(0);
  if(NumPoints_Proton[0]) legendario->AddEntry(DataProton[0],"^{1}H WMU","P");
  if(NumPoints_Proton[1]) legendario->AddEntry(DataProton[1],"^{1}H ELoss Table","P");
  if(NumPoints_Proton[2]) legendario->AddEntry(DataProton[2],"^{40}Ca+^{1}H @ 39 MeV/u","P");
  if(NumPoints_Proton[3]) legendario->AddEntry(DataProton[3],"^{40}Ca+^{1}H @ 56.6 MeV/u","P");
  if(NumPoints_Proton[4]) legendario->AddEntry(DataProton[4],"^{40}Ca+^{1}H @ 139.8 MeV/u","P");
  if(NumPoints_Proton[5]) legendario->AddEntry(DataProton[5],"^{48}Ca+^{1}H @ 139.8 MeV/u","P");
  if(NumPoints_Proton[6]) legendario->AddEntry(DataProton[6],"^{40}Ca+^{1}H @ 28 MeV/u","P");
  if(NumPoints_Proton[7]) legendario->AddEntry(DataProton[7],"^{40}Ca+^{1}H @ 56.6 MeV/u","P");
  if(NumPoints_Proton[8]) legendario->AddEntry(DataProton[8],"^{48}Ca+^{1}H @ 28 MeV/u","P");
  if(NumPoints_Proton[9]) legendario->AddEntry(DataProton[9],"^{48}Ca+^{1}H @ 56.6 MeV/u","P");
  if(NumPoints_Proton[10]) legendario->AddEntry(DataProton[10],"^{1}H Punch-Through","P");
  if(NumPoints_Deuteron[0]) legendario->AddEntry(DataDeuteron[0],"^{2}H WMU","P");
  if(NumPoints_Deuteron[1]) legendario->AddEntry(DataDeuteron[1],"^{2}H ELoss Table","P");
  if(NumPoints_Deuteron[2]) legendario->AddEntry(DataDeuteron[2],"^{2}H Punch-Through","P");
  if(NumPoints_Triton[0]) legendario->AddEntry(DataTriton[0],"^{2}H ELoss Table","P");
  if(NumPoints_Triton[1]) legendario->AddEntry(DataTriton[1],"^{2}H Punch-Through","P");
  legendario->Draw("SAME");
  
  //Drawing low energy zoom
  c2->cd();
  //TPad * TheInsert = new TPad("TheInsert", "", 0.58,0.11,0.90,0.52);
  //TheInsert->Draw("SAME");
  //TheInsert->cd();
  TheInsertGraph->Draw("APE");
  TAxis * XAxisInsert = TheInsertGraph->GetXaxis();
  TAxis * YAxisInsert = TheInsertGraph->GetYaxis();
  XAxisInsert->SetLabelSize(0.05);
  XAxisInsert->SetTitleSize(0.05);
  XAxisInsert->CenterTitle(true);
  YAxisInsert->SetLabelSize(0.05);
  YAxisInsert->SetTitleSize(0.05);
  YAxisInsert->CenterTitle(true); 
  YAxisInsert->SetNdivisions(6,1,0);
  XAxisInsert->SetNdivisions(6,1,0);
  XAxisInsert->SetLimits(0,55);
  YAxisInsert->SetRangeUser(0,0.30);
  
  XAxisInsert->SetTitle("E (MeV)");
  YAxisInsert->SetTitle("Light Output (V)");
  
  TLine * discr_line = new TLine (10,0,10,0.3);
  discr_line->SetLineStyle(2);
  discr_line->Draw("SAME");
  
  TLatex * wmu_label = new TLatex (9,0.08,"Region Constrained by WMU data");
  wmu_label->SetTextColor(kOrange+2);
  wmu_label->SetTextSize(0.04);
  wmu_label->SetTextFont(42);
  wmu_label->SetTextAngle(90);
  wmu_label->Draw("SAME");
  
  TPave * shadowed_region = new TPave(0,0,10,0.299);
  shadowed_region->SetBorderSize(0);
  shadowed_region->SetFillColorAlpha(kYellow-9,0.30);
  shadowed_region->Draw("SAME");
  
  TLegend * legendario_zoom = new TLegend(0.7,0.12,0.88,0.40);
  legendario_zoom->SetBorderSize(0);
  legendario_zoom->AddEntry(FitTriton,"triton","L");
  legendario_zoom->AddEntry(FitDeuteron,"deuteron","L");
  legendario_zoom->AddEntry(FitProton,"proton","L");

  legendario_zoom->Draw("SAME");
  
  FitTriton->Draw("SAME");
  FitDeuteron->Draw("SAME");
  FitProton->Draw("SAME");
  
  gPad->RedrawAxis();
  
  c1->Print("figure_pdt_calibration.png");
  c2->Print("figure_pdt_calibration_zoom.png");
  c1->Print("figure_pdt_calibration.pdf");
  c2->Print("figure_pdt_calibration_zoom.pdf");
  
}
