//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper:
//// D.Horn et al, NIM A320(1992) 273-276
////////////////////////////////////////////////////////////////////////////////
double HornFit(double *x, double *par)
{
  // x[0]--E, x[1]--A
  if(x[1]==203 || x[1]==204 || x[1]==206)
  {
    int A = Int_t(x[1])%100;
    int Z = Int_t(x[1])/100;
    double consterm_par2 = (par[3]+par[4])*A*pow(Z,2);
    double consterm_par3 = par[4]*A*pow(Z,2);
    double consterm_par4 = par[2]*A*pow(Z,2);
    double logterm = consterm_par4*log(fabs((x[0]+consterm_par4)/consterm_par4));
    double light = par[0]+par[1]*(x[0]*((x[0]+consterm_par2)/(x[0]+consterm_par3))-logterm);
    return light;
  }
  if(x[1]==206 || x[1]==306 || x[1]==307 || x[1]==308 || x[1]==407 || x[1]==409)
  {
    int A = Int_t(x[1])%100;
    int Z = Int_t(x[1])/100;
    double consterm = par[2]*A*pow(Z,2);
    double lineterm = x[0]+consterm;
    double logterm = consterm*log(abs(lineterm/consterm));
    double light = par[0]+par[1]*(x[0]-logterm);
    return light;
  }
  return 0;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of 3He
double fit_He3(double *x, double *par)
{
  double consterm_par2 = (par[3]+par[4])*3*pow(2,2);
  double consterm_par3 = par[4]*3*pow(2,2);
  double consterm_par4 = par[2]*3*pow(2,2);
  double logterm = consterm_par4*log(fabs((x[0]+consterm_par4)/consterm_par4));
  double light = par[0]+par[1]*(x[0]*((x[0]+consterm_par2)/(x[0]+consterm_par3))-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of He4
double fit_He4(double *x, double *par)
{
  double consterm_par2 = (par[3]+par[4])*4*pow(2,2);
  double consterm_par3 = par[4]*4*pow(2,2);
  double consterm_par4 = par[2]*4*pow(2,2);
  double logterm = consterm_par4*log(fabs((x[0]+consterm_par4)/consterm_par4));
  double light = par[0]+par[1]*(x[0]*((x[0]+consterm_par2)/(x[0]+consterm_par3))-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of He6
double fit_He6(double *x, double *par)
{
  double consterm = par[2]*6*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of Li6
double fit_Li6(double *x, double *par)
{
  double consterm = par[2]*6*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of Li7
double fit_Li7(double *x, double *par)
{
  double consterm = par[2]*7*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of Li8
double fit_Li8(double *x, double *par)
{
  double consterm = par[2]*8*pow(3,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of Be7
double fit_Be7(double *x, double *par)
{
  double consterm = par[2]*7*pow(4,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of Be9
double fit_Be9(double *x, double *par)
{
  double consterm = par[2]*9*pow(4,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________



//------------------------------------------------------------------------------
void FitHorn()
{
  ofstream FileOut;
  FileOut.open("../calibrations/SimultaneouslyFitParHeavyIons.dat");
  FileOut << setw(5) <<"*tel" <<"  "<< setw(5) << "csi" <<"  "<<setw(5)<< "Z" <<"  "<<setw(5)<< "A" <<"  "<< setw(35) <<"Horn's Formula"
              <<"  "<<setw(45) << "Par0" <<"  "<< setw(10) <<"Par1"<<"  "<<setw(10)<<"Par2\n";

  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He3
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He3=1;
  std::string * FileIn_name_He3[NFiles_He3];
  FileIn_name_He3[0] = new std::string("../calibrations/DEEPoints_Z02_A03.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe3[12][4][NFiles_He3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He3[12][4][1];
  std::vector<double> errCsIV_He3[12][4][1];
  std::vector<double> CsIE_He3[12][4][1];
  std::vector<double> errCsIE_He3[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
  {
    ifstream FileIn_He3(FileIn_name_He3[FileNum]->c_str());
    if(!FileIn_He3.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He3[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_He3.eof())
    {
      std::string LineRead;
      std::getline(FileIn_He3, LineRead);

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

      CsIV_He3[telnum][csinum][FileNum].push_back(V);
      errCsIV_He3[telnum][csinum][FileNum].push_back(errV);
      CsIE_He3[telnum][csinum][FileNum].push_back(E);
      errCsIE_He3[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe3[i][j][FileNum] = new TGraphErrors(CsIV_He3[i][j][FileNum].size(), CsIE_He3[i][j][FileNum].data(), CsIV_He3[i][j][FileNum].data(), errCsIE_He3[i][j][FileNum].data() ,errCsIV_He3[i][j][FileNum].data());
        DataHe3[i][j][FileNum]->SetMarkerColor(1); // black marker for He3s
        DataHe3[i][j][FileNum]->SetLineColor(1);
        DataHe3[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He3.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He4
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He4=2;
  std::string * FileIn_name_He4[NFiles_He4];
  FileIn_name_He4[0] = new std::string("../calibrations/DEEPoints_Z02_A04.dat"); //DEE points
  FileIn_name_He4[1] = new std::string("../calibrations/WMUdata_Z02_A04.dat");

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe4[12][4][NFiles_He4];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He4[12][4][2];
  std::vector<double> errCsIV_He4[12][4][2];
  std::vector<double> CsIE_He4[12][4][2];
  std::vector<double> errCsIE_He4[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
  {
    ifstream FileIn_He4(FileIn_name_He4[FileNum]->c_str());
    if(!FileIn_He4.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He4[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_He4.eof())
    {
      std::string LineRead;
      std::getline(FileIn_He4, LineRead);

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

      CsIV_He4[telnum][csinum][FileNum].push_back(V);
      errCsIV_He4[telnum][csinum][FileNum].push_back(errV);
      CsIE_He4[telnum][csinum][FileNum].push_back(E);
      errCsIE_He4[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe4[i][j][FileNum] = new TGraphErrors(CsIV_He4[i][j][FileNum].size(), CsIE_He4[i][j][FileNum].data(), CsIV_He4[i][j][FileNum].data(), errCsIE_He4[i][j][FileNum].data() ,errCsIV_He4[i][j][FileNum].data());
        DataHe4[i][j][FileNum]->SetMarkerColor(2); // black marker for He4s
        DataHe4[i][j][FileNum]->SetLineColor(2);
        DataHe4[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He4.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He6=1;
  std::string * FileIn_name_He6[NFiles_He6];
  FileIn_name_He6[0] = new std::string("../calibrations/DEEPoints_Z02_A06.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataHe6[12][4][NFiles_He6];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He6[12][4][1];
  std::vector<double> errCsIV_He6[12][4][1];
  std::vector<double> CsIE_He6[12][4][1];
  std::vector<double> errCsIE_He6[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
  {
    ifstream FileIn_He6(FileIn_name_He6[FileNum]->c_str());
    if(!FileIn_He6.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_He6[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_He6.eof())
    {
      std::string LineRead;
      std::getline(FileIn_He6, LineRead);

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

      CsIV_He6[telnum][csinum][FileNum].push_back(V);
      errCsIV_He6[telnum][csinum][FileNum].push_back(errV);
      CsIE_He6[telnum][csinum][FileNum].push_back(E);
      errCsIE_He6[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataHe6[i][j][FileNum] = new TGraphErrors(CsIV_He6[i][j][FileNum].size(), CsIE_He6[i][j][FileNum].data(), CsIV_He6[i][j][FileNum].data(), errCsIE_He6[i][j][FileNum].data() ,errCsIV_He6[i][j][FileNum].data());
        DataHe6[i][j][FileNum]->SetMarkerColor(3); // black marker for He6s
        DataHe6[i][j][FileNum]->SetLineColor(3);
        DataHe6[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_He6.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li6=1;
  std::string * FileIn_name_Li6[NFiles_Li6];
  FileIn_name_Li6[0] = new std::string("../calibrations/DEEPoints_Z03_A06.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi6[12][4][NFiles_Li6];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li6[12][4][1];
  std::vector<double> errCsIV_Li6[12][4][1];
  std::vector<double> CsIE_Li6[12][4][1];
  std::vector<double> errCsIE_Li6[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
  {
    ifstream FileIn_Li6(FileIn_name_Li6[FileNum]->c_str());
    if(!FileIn_Li6.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li6[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li6.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li6, LineRead);

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

      CsIV_Li6[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li6[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li6[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li6[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi6[i][j][FileNum] = new TGraphErrors(CsIV_Li6[i][j][FileNum].size(), CsIE_Li6[i][j][FileNum].data(), CsIV_Li6[i][j][FileNum].data(), errCsIE_Li6[i][j][FileNum].data() ,errCsIV_Li6[i][j][FileNum].data());
        DataLi6[i][j][FileNum]->SetMarkerColor(4); // black marker for Li6s
        DataLi6[i][j][FileNum]->SetLineColor(4);
        DataLi6[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_Li6.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li7
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li7=1;
  std::string * FileIn_name_Li7[NFiles_Li7];
  FileIn_name_Li7[0] = new std::string("../calibrations/DEEPoints_Z03_A07.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi7[12][4][NFiles_Li7];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li7[12][4][1];
  std::vector<double> errCsIV_Li7[12][4][1];
  std::vector<double> CsIE_Li7[12][4][1];
  std::vector<double> errCsIE_Li7[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
  {
    ifstream FileIn_Li7(FileIn_name_Li7[FileNum]->c_str());
    if(!FileIn_Li7.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li7[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li7.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li7, LineRead);

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

      CsIV_Li7[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li7[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li7[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li7[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi7[i][j][FileNum] = new TGraphErrors(CsIV_Li7[i][j][FileNum].size(), CsIE_Li7[i][j][FileNum].data(), CsIV_Li7[i][j][FileNum].data(), errCsIE_Li7[i][j][FileNum].data() ,errCsIV_Li7[i][j][FileNum].data());
        DataLi7[i][j][FileNum]->SetMarkerColor(6); // black marker for Li7s
        DataLi7[i][j][FileNum]->SetLineColor(6);
        DataLi7[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_Li7.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Li8
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Li8=1;
  std::string * FileIn_name_Li8[NFiles_Li8];
  FileIn_name_Li8[0] = new std::string("../calibrations/DEEPoints_Z03_A08.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataLi8[12][4][NFiles_Li8];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Li8[12][4][1];
  std::vector<double> errCsIV_Li8[12][4][1];
  std::vector<double> CsIE_Li8[12][4][1];
  std::vector<double> errCsIE_Li8[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
  {
    ifstream FileIn_Li8(FileIn_name_Li8[FileNum]->c_str());
    if(!FileIn_Li8.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Li8[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Li8.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Li8, LineRead);

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

      CsIV_Li8[telnum][csinum][FileNum].push_back(V);
      errCsIV_Li8[telnum][csinum][FileNum].push_back(errV);
      CsIE_Li8[telnum][csinum][FileNum].push_back(E);
      errCsIE_Li8[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataLi8[i][j][FileNum] = new TGraphErrors(CsIV_Li8[i][j][FileNum].size(), CsIE_Li8[i][j][FileNum].data(), CsIV_Li8[i][j][FileNum].data(), errCsIE_Li8[i][j][FileNum].data() ,errCsIV_Li8[i][j][FileNum].data());
        DataLi8[i][j][FileNum]->SetMarkerColor(7); // black marker for Li8s
        DataLi8[i][j][FileNum]->SetLineColor(7);
        DataLi8[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_Li8.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Be7
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Be7=1;
  std::string * FileIn_name_Be7[NFiles_Be7];
  FileIn_name_Be7[0] = new std::string("../calibrations/DEEPoints_Z04_A07.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataBe7[12][4][NFiles_Be7];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Be7[12][4][1];
  std::vector<double> errCsIV_Be7[12][4][1];
  std::vector<double> CsIE_Be7[12][4][1];
  std::vector<double> errCsIE_Be7[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
  {
    ifstream FileIn_Be7(FileIn_name_Be7[FileNum]->c_str());
    if(!FileIn_Be7.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Be7[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Be7.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Be7, LineRead);

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

      CsIV_Be7[telnum][csinum][FileNum].push_back(V);
      errCsIV_Be7[telnum][csinum][FileNum].push_back(errV);
      CsIE_Be7[telnum][csinum][FileNum].push_back(E);
      errCsIE_Be7[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataBe7[i][j][FileNum] = new TGraphErrors(CsIV_Be7[i][j][FileNum].size(), CsIE_Be7[i][j][FileNum].data(), CsIV_Be7[i][j][FileNum].data(), errCsIE_Be7[i][j][FileNum].data() ,errCsIV_Be7[i][j][FileNum].data());
        DataBe7[i][j][FileNum]->SetMarkerColor(9); // black marker for Be7s
        DataBe7[i][j][FileNum]->SetLineColor(9);
        DataBe7[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_Be7.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for Be9
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Be9=1;
  std::string * FileIn_name_Be9[NFiles_Be9];
  FileIn_name_Be9[0] = new std::string("../calibrations/DEEPoints_Z04_A09.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataBe9[12][4][NFiles_Be9];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Be9[12][4][1];
  std::vector<double> errCsIV_Be9[12][4][1];
  std::vector<double> CsIE_Be9[12][4][1];
  std::vector<double> errCsIE_Be9[12][4][1];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
  {
    ifstream FileIn_Be9(FileIn_name_Be9[FileNum]->c_str());
    if(!FileIn_Be9.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Be9[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///    Loop, to read each input data file
    while(!FileIn_Be9.eof())
    {
      std::string LineRead;
      std::getline(FileIn_Be9, LineRead);

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

      CsIV_Be9[telnum][csinum][FileNum].push_back(V);
      errCsIV_Be9[telnum][csinum][FileNum].push_back(errV);
      CsIE_Be9[telnum][csinum][FileNum].push_back(E);
      errCsIE_Be9[telnum][csinum][FileNum].push_back(errE);
    }

    for(int i=0; i<12; i++)
    {
      for(int j=0; j<4; j++)
      {
        DataBe9[i][j][FileNum] = new TGraphErrors(CsIV_Be9[i][j][FileNum].size(), CsIE_Be9[i][j][FileNum].data(), CsIV_Be9[i][j][FileNum].data(), errCsIE_Be9[i][j][FileNum].data() ,errCsIV_Be9[i][j][FileNum].data());
        DataBe9[i][j][FileNum]->SetMarkerColor(11); // black marker for Be9s
        DataBe9[i][j][FileNum]->SetLineColor(11);
        DataBe9[i][j][FileNum]->SetMarkerStyle(25+FileNum);
      }
    }
    FileIn_Be9.close();
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  ////// creating a multigraph to draw all the Heavy ../calibrations
  TMultiGraph * multiHeavyIons[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      multiHeavyIons[i][j] = new TMultiGraph();
      //////////////////////////////////////////////////////////////////////////
      ///// add He3 data
      for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe3[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add He4 data
      for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe4[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add He6 data
      for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataHe6[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Li6 data
      for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi6[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Li7 data
      for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi7[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Li8 data
      for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataLi8[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Be7 data
      for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataBe7[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///// add Be9 data
      for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataBe9[i][j][FileNum]);
      }
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
  /// Put all the dataset together
  std::vector<double> CsIV_HeavyIons[12][4];
  std::vector<double> errCsIV_HeavyIons[12][4];
  std::vector<double> CsIE_HeavyIons[12][4];
  std::vector<double> errCsIE_HeavyIons[12][4];
  std::vector<double> ZA_HeavyIons[12][4];
  std::vector<double> errZA_HeavyIons[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      //////////////////////////////////////////////////////////////////////////
      ////   add He3 data
      for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
      {
        for(int k=0; k< CsIV_He3[i][j][FileNum].size(); k++)
        {
          CsIV_HeavyIons[i][j].push_back(CsIV_He3[i][j][FileNum][k]);
          errCsIV_HeavyIons[i][j].push_back(errCsIV_He3[i][j][FileNum][k]);
          CsIE_HeavyIons[i][j].push_back(CsIE_He3[i][j][FileNum][k]);
          errCsIE_HeavyIons[i][j].push_back(errCsIE_He3[i][j][FileNum][k]);
          ZA_HeavyIons[i][j].push_back(203);
          errZA_HeavyIons[i][j].push_back(0);
        }
      }

      //////////////////////////////////////////////////////////////////////////
      ////   add He4 data
      for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
      {
        for(int k=0; k< CsIV_He4[i][j][FileNum].size(); k++)
        {
          CsIV_HeavyIons[i][j].push_back(CsIV_He4[i][j][FileNum][k]);
          errCsIV_HeavyIons[i][j].push_back(errCsIV_He4[i][j][FileNum][k]);
          CsIE_HeavyIons[i][j].push_back(CsIE_He4[i][j][FileNum][k]);
          errCsIE_HeavyIons[i][j].push_back(errCsIE_He4[i][j][FileNum][k]);
          ZA_HeavyIons[i][j].push_back(204);
          errZA_HeavyIons[i][j].push_back(0);
        }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add He6 data
       for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
       {
         for(int k=0; k< CsIV_He6[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_He6[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_He6[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_He6[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_He6[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(206);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add Li6 data
       for(int FileNum=0; FileNum<NFiles_Li6; FileNum++)
       {
         for(int k=0; k< CsIV_Li6[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_Li6[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_Li6[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_Li6[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_Li6[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(306);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add Li7 data
       for(int FileNum=0; FileNum<NFiles_Li7; FileNum++)
       {
         for(int k=0; k< CsIV_Li7[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_Li7[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_Li7[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_Li7[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_Li7[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(307);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add Li8 data
       for(int FileNum=0; FileNum<NFiles_Li8; FileNum++)
       {
         for(int k=0; k< CsIV_Li8[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_Li8[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_Li8[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_Li8[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_Li8[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(308);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add Be7 data
       for(int FileNum=0; FileNum<NFiles_Be7; FileNum++)
       {
         for(int k=0; k< CsIV_Be7[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_Be7[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_Be7[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_Be7[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_Be7[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(407);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }

       /////////////////////////////////////////////////////////////////////////
       ////   add Be9 data
       for(int FileNum=0; FileNum<NFiles_Be9; FileNum++)
       {
         for(int k=0; k< CsIV_Be9[i][j][FileNum].size(); k++)
         {
           CsIV_HeavyIons[i][j].push_back(CsIV_Be9[i][j][FileNum][k]);
           errCsIV_HeavyIons[i][j].push_back(errCsIV_Be9[i][j][FileNum][k]);
           CsIE_HeavyIons[i][j].push_back(CsIE_Be9[i][j][FileNum][k]);
           errCsIE_HeavyIons[i][j].push_back(errCsIE_Be9[i][j][FileNum][k]);
           ZA_HeavyIons[i][j].push_back(409);
           errZA_HeavyIons[i][j].push_back(0);
         }
       }
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
 ///////////////////////////////////////////////////////////////////////////////
 /////   Draw all the data set in the same 2D Graphs
 TGraph2DErrors * TotGraph[12][4];
 for(int i=0; i<12; i++)
 {
   for(int j=0; j<4; j++)
   {
     if(CsIV_HeavyIons[i][j].size()==0) continue;
     TotGraph[i][j] = new TGraph2DErrors(CsIV_HeavyIons[i][j].size(), CsIE_HeavyIons[i][j].data(), ZA_HeavyIons[i][j].data(), CsIV_HeavyIons[i][j].data(), errCsIE_HeavyIons[i][j].data(), 0, errCsIV_HeavyIons[i][j].data());
     TotGraph[i][j]->SetName(Form("TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetTitle(Form("HeavyIons_TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetMarkerStyle(20);
   }
 }
//______________________________________________________________________________


//______________________________________________________________________________
  /////////////////////////////////////////////////////////////////////////
  /////  Fit Heavy Ions Light(V)-Energy(MeV) with the Horn formula
  TF2 *fHeavyIon= new TF2("fHeavyIon",HornFit,0,500,200,500,5);
  fHeavyIon->SetParameters(0.001,0.01,0.1,0.1,0.1);
  fHeavyIon->SetParLimits(3,0,5);
  fHeavyIon->SetParLimits(4,0,5);

  TF1 * fHe3 = new TF1("fHe3",fit_He3,0,500,5);
  TF1 * fHe4 = new TF1("fHe4",fit_He4,0,500,5);
  TF1 * fHe6 = new TF1("fHe6",fit_He6,0,500,3);
  TF1 * fLi6 = new TF1("fLi6",fit_Li6,0,500,3);
  TF1 * fLi7 = new TF1("fLi7",fit_Li7,0,500,3);
  TF1 * fLi8 = new TF1("fLi8",fit_Li8,0,500,3);
  TF1 * fBe7 = new TF1("fBe7",fit_Be7,0,500,3);
  TF1 * fBe9 = new TF1("fBe9",fit_Be9,0,500,3);

  fHe3->SetLineColor(1);
  fHe4->SetLineColor(2);
  fHe6->SetLineColor(3);
  fLi6->SetLineColor(4);
  fLi7->SetLineColor(6);
  fLi8->SetLineColor(7);
  fBe7->SetLineColor(9);
  fBe9->SetLineColor(11);
//______________________________________________________________________________


//______________________________________________________________________________
  ///// Draw
  TCanvas *c1 = new TCanvas("c1","",1200,800);
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(CsIV_HeavyIons[i][j].size()==0) continue;

      TotGraph[i][j]->Fit("fHeavyIon");

      fHe3->SetParameters(fHeavyIon->GetParameters());
      fHe4->SetParameters(fHeavyIon->GetParameters());
      fHe6->SetParameters(fHeavyIon->GetParameters());
      fLi6->SetParameters(fHeavyIon->GetParameters());
      fLi7->SetParameters(fHeavyIon->GetParameters());
      fLi8->SetParameters(fHeavyIon->GetParameters());
      fBe7->SetParameters(fHeavyIon->GetParameters());
      fBe9->SetParameters(fHeavyIon->GetParameters());

      multiHeavyIons[i][j]->SetTitle(Form("TEL%02d_CSI%02d",i,j));
      multiHeavyIons[i][j]->Draw("AP");
      fHe3->Draw("SAME");
      fHe4->Draw("SAME");
      fHe6->Draw("SAME");
      fLi6->Draw("SAME");
      fLi7->Draw("SAME");
      fLi8->Draw("SAME");
      fBe7->Draw("SAME");
      fBe9->Draw("SAME");

      gPad->Modified();
      gPad->Update();
      getchar();

      //////////////////////////////////////////////////////////////////////////
      /// retrive the fit parameters
      double par0 = fHeavyIon->GetParameter(0);
      double par1 = fHeavyIon->GetParameter(1);
      double par2 = fHeavyIon->GetParameter(2);
      int Z;
      int A;
      for(int k=0; k<ZA_HeavyIons[i][j].size();k++)
      {
        Z = (int) ZA_HeavyIons[i][j][k]/100;
        A = (int) ZA_HeavyIons[i][j][k]%100;
        if(ZA_HeavyIons[i][j][k]==ZA_HeavyIons[i][j][k+1]) continue;
        FileOut << setw(5) << i <<"  "<< setw(5) << j <<"  "<<setw(5)<< Z <<"  "<<setw(5)<< A <<"  "<< setw(35)<< "[0]+[1].(x-[2].A.pow(Z,2).log(fabs((x+[2].A.pow(Z,2))/([2].A.pow(Z,2))))" <<"  "<<setw(15) << par0 <<"  "<< setw(10) << par1 <<"  "<<setw(10)<< par2 <<endl;
      }
    }
  }
//______________________________________________________________________________

}
