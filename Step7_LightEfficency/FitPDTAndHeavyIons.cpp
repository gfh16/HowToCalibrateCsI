//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// definition of the fitting formula for proton, deuteron and triton
//// this formula comes from Jerzy Lukasik
//// email: jerzy.lukasik@ifj.edu.pl
////////////////////////////////////////////////////////////////////////////////
double FitJerzy(double *x, double *par)
{
  if(par[1]<=par[2])
  {
    return -1;
  }

  // x[0]--E, x[1]--A
  if(x[1]==101 || x[1]==102 || x[1]==103)
  {
    int A = Int_t (x[1])%100;
    int Z = Int_t (x[1])/100;
    double squareterm = pow(x[0], 2)+par[1]*A*x[0];
    double linearterm = (x[0]+par[2]*A);
    double light = par[0]*squareterm/linearterm;
    return light;
  }
  return 0;
}
//______________________________________________________________________________
//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// deifinition of fitting formula of protons
double fit_proton (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*1*x[0];
  double linearterm = (x[0]+par[2]*1)/par[0];
  double light = squareterm/linearterm;
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// deifinition of fitting formula of deuterons
double fit_deuteron (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*2*x[0];
  double linearterm = (x[0]+par[2]*2)/par[0];
  double light = squareterm/linearterm;
  return light;
}
//______________________________________________________________________________
//// deifinition of fitting formula of tritons
double fit_triton (double *x, double *par)
{
  double squareterm = pow(x[0], 2)+par[1]*3*x[0];
  double linearterm = (x[0]+par[2]*3)/par[0];
  double light = squareterm/linearterm;
  return light;
}
//______________________________________________________________________________



//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper:
//// D.Horn et al, NIM A320(1992) 273-276
////////////////////////////////////////////////////////////////////////////////
double HornFit(double *x, double *par)
{
  // x[0]--E, x[1]--A
  if(x[1]==203 || x[1]==204 || x[1]==206 || x[1]==306 || x[1]==307 || x[1]==308 || x[1]==407 || x[1]==409)
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
  double consterm = par[2]*3*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________
//______________________________________________________________________________
///////////////////////////////////////////////////////
///  definition of fitting function of He4
double fit_He4(double *x, double *par)
{
  double consterm = par[2]*4*pow(2,2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(lineterm/consterm);
  double light = par[0]+par[1]*(x[0]-logterm);
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
void FitPDTAndHeavyIons()
{
  ofstream FileOut;
  FileOut.open("../calibrations/SimultaneouslyFitParForAll.dat");
  FileOut << setw(5) <<"*tel" <<"  "<< setw(5) << "csi" <<"  "<<setw(5)<< "Z" <<"  "<<setw(5)<< "A" <<"  "<< setw(35) <<"Fit Formula"
              <<"  "<<setw(45) << "Par0" <<"  "<< setw(10) <<"Par1"<<"  "<<setw(10)<<"Par2\n";

//==============================================================================
////////////////////////////////////////////////////////////////////////////////
////   retriving data for protons
////////////////////////////////////////////////////////////////////////////////
Int_t NFiles_Proton=11;
std::string * FileIn_name_Proton[NFiles_Proton];
FileIn_name_Proton[0] = new std::string("../calibrations/WMUdata_Z01_A01.dat");   // WMU data
FileIn_name_Proton[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A01.dat"); //DEE points
FileIn_name_Proton[2] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39.0AMeV_gain 200.dat"); // kinematics ponits
FileIn_name_Proton[3] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56.6AMeV_gain 170.dat"); // kinematics ponits
//FileIn_name_Proton[4] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2825_2829_40Ca139.8AMeV_gain 130.dat"); // kinematics ponits
FileIn_name_Proton[4] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4000_4005_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[5] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4021_4022_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[6] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[7] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[8] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[9] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
FileIn_name_Proton[10] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points

////////////////////////////////////////////////////////////////////////////////
///   definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataProton [12][4][NFiles_Proton];
////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Proton[12][4][12];
std::vector<double> errCsIV_Proton[12][4][12];
std::vector<double> CsIE_Proton[12][4][12];
std::vector<double> errCsIE_Proton[12][4][12];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
{
  ifstream FileIn_Proton(FileIn_name_Proton[FileNum]->c_str());
  if(!FileIn_Proton.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Proton[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Proton.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Proton, LineRead);

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

    CsIV_Proton[telnum][csinum][FileNum].push_back(V);
    errCsIV_Proton[telnum][csinum][FileNum].push_back(errV);
    CsIE_Proton[telnum][csinum][FileNum].push_back(E);
    errCsIE_Proton[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataProton[i][j][FileNum] = new TGraphErrors(CsIV_Proton[i][j][FileNum].size(), CsIE_Proton[i][j][FileNum].data(), CsIV_Proton[i][j][FileNum].data(), errCsIE_Proton[i][j][FileNum].data() ,errCsIV_Proton[i][j][FileNum].data());
      DataProton[i][j][FileNum]->SetMarkerColor(2); // black marker for Protons
      DataProton[i][j][FileNum]->SetLineColor(2);
      DataProton[i][j][FileNum]->SetMarkerStyle(20+FileNum);
    }
  }
  FileIn_Proton.close();
 }


 ///////////////////////////////////////////////////////////////////////////////
////   retriving data for deuterons
////////////////////////////////////////////////////////////////////////////////
Int_t NFiles_Deuteron=3;
std::string * FileIn_name_Deuteron[NFiles_Deuteron];
FileIn_name_Deuteron[0] = new std::string("../calibrations/WMUdata_Z01_A02.dat");   // WMU data
FileIn_name_Deuteron[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A02.dat"); //DEE points
FileIn_name_Deuteron[2] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

////////////////////////////////////////////////////////////////////////////////
/// definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataDeuteron[12][4][NFiles_Deuteron];

////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Deuteron[12][4][3];
std::vector<double> errCsIV_Deuteron[12][4][3];
std::vector<double> CsIE_Deuteron[12][4][3];
std::vector<double> errCsIE_Deuteron[12][4][3];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
{
  ifstream FileIn_Deuteron(FileIn_name_Deuteron[FileNum]->c_str());
  if(!FileIn_Deuteron.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Deuteron[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Deuteron.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Deuteron, LineRead);

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

    CsIV_Deuteron[telnum][csinum][FileNum].push_back(V);
    errCsIV_Deuteron[telnum][csinum][FileNum].push_back(errV);
    CsIE_Deuteron[telnum][csinum][FileNum].push_back(E);
    errCsIE_Deuteron[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataDeuteron[i][j][FileNum] = new TGraphErrors(CsIV_Deuteron[i][j][FileNum].size(), CsIE_Deuteron[i][j][FileNum].data(), CsIV_Deuteron[i][j][FileNum].data(), errCsIE_Deuteron[i][j][FileNum].data() ,errCsIV_Deuteron[i][j][FileNum].data());
      DataDeuteron[i][j][FileNum]->SetMarkerColor(3); // black marker for Deuterons
      DataDeuteron[i][j][FileNum]->SetLineColor(3);
      DataDeuteron[i][j][FileNum]->SetMarkerStyle(25+FileNum);
    }
  }
  FileIn_Deuteron.close();
}


////////////////////////////////////////////////////////////////////////////////
////   retriving data for tritons
////////////////////////////////////////////////////////////////////////////////
Int_t NFiles_Triton=2;
std::string * FileIn_name_Triton[NFiles_Triton];
FileIn_name_Triton[0] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A03.dat"); //DEE points
FileIn_name_Triton[1] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

////////////////////////////////////////////////////////////////////////////////
/// definition of TGraphErrors, TMultiGraph, TLengend
TGraphErrors * DataTriton[12][4][NFiles_Triton];

////////////////////////////////////////////////////////////////////////////////
///  definition of variables to read the input data files
std::vector<double> CsIV_Triton[12][4][2];
std::vector<double> errCsIV_Triton[12][4][2];
std::vector<double> CsIE_Triton[12][4][2];
std::vector<double> errCsIE_Triton[12][4][2];

////////////////////////////////////////////////////////////////////////////////
///  definition of the number of data points for each input file
for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
{
  ifstream FileIn_Triton(FileIn_name_Triton[FileNum]->c_str());
  if(!FileIn_Triton.is_open())
  {
    printf("Error: file%s not found\n", FileIn_name_Triton[FileNum]->c_str());
    return;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///    Loop, to read each input data file
  while(!FileIn_Triton.eof())
  {
    std::string LineRead;
    std::getline(FileIn_Triton, LineRead);

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

    CsIV_Triton[telnum][csinum][FileNum].push_back(V);
    errCsIV_Triton[telnum][csinum][FileNum].push_back(errV);
    CsIE_Triton[telnum][csinum][FileNum].push_back(E);
    errCsIE_Triton[telnum][csinum][FileNum].push_back(errE);
  }

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      DataTriton[i][j][FileNum] = new TGraphErrors(CsIV_Triton[i][j][FileNum].size(), CsIE_Triton[i][j][FileNum].data(), CsIV_Triton[i][j][FileNum].data(), errCsIE_Triton[i][j][FileNum].data() ,errCsIV_Triton[i][j][FileNum].data());
      DataTriton[i][j][FileNum]->SetMarkerColor(6); // black marker for Tritons
      DataTriton[i][j][FileNum]->SetLineColor(6);
      DataTriton[i][j][FileNum]->SetMarkerStyle(25+FileNum);
    }
  }
  FileIn_Triton.close();
}


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
  std::vector<double> CsIV_He3[12][4][2];
  std::vector<double> errCsIV_He3[12][4][2];
  std::vector<double> CsIE_He3[12][4][2];
  std::vector<double> errCsIE_He3[12][4][2];

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
  std::vector<double> CsIV_He6[12][4][2];
  std::vector<double> errCsIV_He6[12][4][2];
  std::vector<double> CsIE_He6[12][4][2];
  std::vector<double> errCsIE_He6[12][4][2];

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
  std::vector<double> CsIV_Li6[12][4][2];
  std::vector<double> errCsIV_Li6[12][4][2];
  std::vector<double> CsIE_Li6[12][4][2];
  std::vector<double> errCsIE_Li6[12][4][2];

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
  std::vector<double> CsIV_Li7[12][4][2];
  std::vector<double> errCsIV_Li7[12][4][2];
  std::vector<double> CsIE_Li7[12][4][2];
  std::vector<double> errCsIE_Li7[12][4][2];

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
  std::vector<double> CsIV_Li8[12][4][2];
  std::vector<double> errCsIV_Li8[12][4][2];
  std::vector<double> CsIE_Li8[12][4][2];
  std::vector<double> errCsIE_Li8[12][4][2];

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
  std::vector<double> CsIV_Be7[12][4][2];
  std::vector<double> errCsIV_Be7[12][4][2];
  std::vector<double> CsIE_Be7[12][4][2];
  std::vector<double> errCsIE_Be7[12][4][2];

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
  std::vector<double> CsIV_Be9[12][4][2];
  std::vector<double> errCsIV_Be9[12][4][2];
  std::vector<double> CsIE_Be9[12][4][2];
  std::vector<double> errCsIE_Be9[12][4][2];

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
  //// create a multigraph to draw all the Hydrogen isotopes
  TMultiGraph * multiHydrogen[12][4];
  //////////////////////////////////////////////////////////////////////////////
  ////// creating a multigraph to draw all the Heavy ../calibrations
  TMultiGraph * multiHeavyIons[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      //========================================================================
      multiHeavyIons[i][j] = new TMultiGraph();
      //////////////////////////////////////////////////////////////////////////
      ///   Add data for protons
      for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataProton[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///  Add data for deuteron
      for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataDeuteron[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///   Add data for triton
      for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
      {
        multiHeavyIons[i][j]->Add(DataTriton[i][j][FileNum]);
      }

      //========================================================================
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
////////////////////////////////////////////////////////////////////////////////
  ////   Put all the dataset together
  std::vector<double> CsIV_Hydrogen[12][4];
  std::vector<double> errCsIV_Hydrogen[12][4];
  std::vector<double> CsIE_Hydrogen[12][4];
  std::vector<double> errCsIE_Hydrogen[12][4];
  std::vector<double> ZA_Hydrogen[12][4];
  std::vector<double> errZA_Hydrogen[12][4];

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
      ////////////////////////////////////////////////////////////////////////////
      ////   add Proton data
     for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
     {
       for(int k=0; k< CsIV_Proton[i][j][FileNum].size(); k++)
       {
         CsIV_Hydrogen[i][j].push_back(CsIV_Proton[i][j][FileNum][k]);
         errCsIV_Hydrogen[i][j].push_back(errCsIV_Proton[i][j][FileNum][k]);
         CsIE_Hydrogen[i][j].push_back(CsIE_Proton[i][j][FileNum][k]);
         errCsIE_Hydrogen[i][j].push_back(errCsIE_Proton[i][j][FileNum][k]);
         ZA_Hydrogen[i][j].push_back(101);
         errZA_Hydrogen[i][j].push_back(0);
       }
     }

     ////////////////////////////////////////////////////////////////////////////
     ////   add Deuteron data
     for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
     {
       for(int k=0; k< CsIV_Deuteron[i][j][FileNum].size(); k++)
       {
         CsIV_Hydrogen[i][j].push_back(CsIV_Deuteron[i][j][FileNum][k]);
         errCsIV_Hydrogen[i][j].push_back(errCsIV_Deuteron[i][j][FileNum][k]);
         CsIE_Hydrogen[i][j].push_back(CsIE_Deuteron[i][j][FileNum][k]);
         errCsIE_Hydrogen[i][j].push_back(errCsIE_Deuteron[i][j][FileNum][k]);
         ZA_Hydrogen[i][j].push_back(102);
         errZA_Hydrogen[i][j].push_back(0);
       }
      }

    ///////////////////////////////////////////////////////////////////////////
    ////   add Triton data
    for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
    {
      for(int k=0; k< CsIV_Triton[i][j][FileNum].size(); k++)
      {
        CsIV_Hydrogen[i][j].push_back(CsIV_Triton[i][j][FileNum][k]);
        errCsIV_Hydrogen[i][j].push_back(errCsIV_Triton[i][j][FileNum][k]);
        CsIE_Hydrogen[i][j].push_back(CsIE_Triton[i][j][FileNum][k]);
        errCsIE_Hydrogen[i][j].push_back(errCsIE_Triton[i][j][FileNum][k]);
        ZA_Hydrogen[i][j].push_back(103);
        errZA_Hydrogen[i][j].push_back(0);
      }
    }

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
 TGraph2DErrors * TotGraphHydrogen[12][4];
 TGraph2DErrors * TotGraphHeavyIons[12][4];

 for(int i=0; i<12; i++)
 {
   for(int j=0; j<4; j++)
   {
     if(CsIV_Hydrogen[i][j].size()==0) continue;
     TotGraphHydrogen[i][j] = new TGraph2DErrors(CsIV_Hydrogen[i][j].size(), CsIE_Hydrogen[i][j].data(), ZA_Hydrogen[i][j].data(), CsIV_Hydrogen[i][j].data(), errCsIE_Hydrogen[i][j].data(),  errZA_Hydrogen[i][j].data(), errCsIV_Hydrogen[i][j].data());
     TotGraphHydrogen[i][j]->SetName(Form("2DTEL%02d_CsI_%02d", i, j));
     TotGraphHydrogen[i][j]->SetTitle(Form("2DHydrogen_TEL%02d_CsI_%02d", i, j));
     TotGraphHydrogen[i][j]->SetMarkerStyle(20);

     if(CsIV_HeavyIons[i][j].size()==0) continue;
     TotGraphHeavyIons[i][j] = new TGraph2DErrors(CsIV_HeavyIons[i][j].size(), CsIE_HeavyIons[i][j].data(), ZA_HeavyIons[i][j].data(), CsIV_HeavyIons[i][j].data(), errCsIE_HeavyIons[i][j].data(), 0, errCsIV_HeavyIons[i][j].data());
     TotGraphHeavyIons[i][j]->SetName(Form("TEL%02d_CsI_%02d", i, j));
     TotGraphHeavyIons[i][j]->SetTitle(Form("HeavyIons_TEL%02d_CsI_%02d", i, j));
     TotGraphHeavyIons[i][j]->SetMarkerStyle(20);
   }
 }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  //// Fit Hydrogen isotopes Light(V)-Energy(MeV) with the Jerzy Lukasik formula
  TF2 * fHydrogen = new TF2("fHydrogen",FitJerzy, 0, 500, 100, 500, 3);
  fHydrogen->SetParameters(0.01,10,1);
  TF1 * fProton = new TF1("fProton", fit_proton, 0, 500, 3);
  TF1 * fDeuteron = new TF1("fDeuteron", fit_deuteron, 0, 500, 3);
  TF1 * fTriton = new TF1("fTriton", fit_triton, 0, 500, 3);
  fProton->SetLineColor(2);
  fDeuteron->SetLineColor(3);
  fTriton->SetLineColor(6);

  /////////////////////////////////////////////////////////////////////////
  /////  Fit Heavy Ions Light(V)-Energy(MeV) with the Horn formula
  TF2 *fHeavyIon= new TF2("fHeavyIon",HornFit,0,500,200,500,3);
  fHeavyIon->SetParameters(0.2,0.1,0.1);
  TF1 * fHe3 = new TF1("fHe3",fit_He3,0,500,3);
  TF1 * fHe4 = new TF1("fHe4",fit_He4,0,500,3);
  TF1 * fHe6 = new TF1("fHe6",fit_He6,0,500,3);
  TF1 * fLi6 = new TF1("fLi6",fit_Li6,0,500,3);
  TF1 * fLi7 = new TF1("fHe3",fit_Li7,0,500,3);
  TF1 * fLi8 = new TF1("fHe3",fit_Li8,0,500,3);
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
    //==========================================================================
      if(CsIV_Hydrogen[i][j].size()==0) continue;
      TotGraphHydrogen[i][j]->Fit("fHydrogen");
      fProton->SetParameters(fHydrogen->GetParameters());
      fDeuteron->SetParameters(fHydrogen->GetParameters());
      fTriton->SetParameters(fHydrogen->GetParameters());
      //////////////////////////////////////////////////////////////////////////
      /// retrive the fit Parameters
      double par0 = fHydrogen->GetParameter(0);
      double par1 = fHydrogen->GetParameter(1);
      double par2 = fHydrogen->GetParameter(2);
      int Z_Hydrogen;
      int A_Hydrogen;
      for(int k=0; k<ZA_Hydrogen[i][j].size();k++)
      {
        Z_Hydrogen = (int) ZA_Hydrogen[i][j][k]/100;
        A_Hydrogen = (int) ZA_Hydrogen[i][j][k]%100;
        if(ZA_Hydrogen[i][j][k]==ZA_Hydrogen[i][j][k+1]) continue;
        FileOut << setw(5) << i <<"  "<< setw(5) << j <<"  "<<setw(5)<< Z_Hydrogen <<"  "<<setw(5)<< A_Hydrogen <<"  "<< setw(50)<< "[0].(pow(x,2)+[1].A.x)/(x+[2].A)"<<"  "<<setw(35) << par0 <<"  "<< setw(10) << par1 <<"  "<<setw(10)<< par2 <<endl;
      }

   //===========================================================================
      if(CsIV_HeavyIons[i][j].size()==0) continue;
      TotGraphHeavyIons[i][j]->Fit("fHeavyIon");
      fHe3->SetParameters(fHeavyIon->GetParameters());
      fHe4->SetParameters(fHeavyIon->GetParameters());
      fHe6->SetParameters(fHeavyIon->GetParameters());
      fLi6->SetParameters(fHeavyIon->GetParameters());
      fLi7->SetParameters(fHeavyIon->GetParameters());
      fLi8->SetParameters(fHeavyIon->GetParameters());
      fBe7->SetParameters(fHeavyIon->GetParameters());
      fBe9->SetParameters(fHeavyIon->GetParameters());

      //////////////////////////////////////////////////////////////////////////
      /// retrive the fit parameters for Heavy Ions
      double par3 = fHeavyIon->GetParameter(0);
      double par4 = fHeavyIon->GetParameter(1);
      double par5 = fHeavyIon->GetParameter(2);
      int Z_HeavyIons;
      int A_HeavyIons;
      for(int k=0; k<ZA_HeavyIons[i][j].size();k++)
      {
        Z_HeavyIons = (int) ZA_HeavyIons[i][j][k]/100;
        A_HeavyIons = (int) ZA_HeavyIons[i][j][k]%100;
        if(ZA_HeavyIons[i][j][k]==ZA_HeavyIons[i][j][k+1]) continue;
        FileOut << setw(5) << i <<"  "<< setw(5) << j <<"  "<<setw(5)<< Z_HeavyIons <<"  "<<setw(5)<< A_HeavyIons <<"  "<< setw(35)<< "[0]+[1].(x-[2].A.pow(Z,2).log(fabs((x+[2].A.pow(Z,2))/([2].A.pow(Z,2))))" <<"  "<<setw(12) << par3 <<"  "<< setw(10) << par4 <<"  "<<setw(10)<< par5 <<endl;
      }
    }
  }
//______________________________________________________________________________

}
