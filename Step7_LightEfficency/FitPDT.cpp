//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// definition of the fitting formula for proton, deuteron and triton
//// this formula comes from Jerzy Lukasik
//// email: jerzy.lukasik@ifj.edu.pl
////////////////////////////////////////////////////////////////////////////////
double FitJerzy(double *x, double *par)
{
  if(par[2]<=par[3])
  {
    return -1;
  }

  // x[0]--E, x[1]--A
  if(x[1]==101 || x[1]==102 || x[1]==103)
  {
    int A = Int_t (x[1])%100;
    int Z = Int_t (x[1])/100;
    double light = par[0]+par[1]*x[0]*(x[0]+par[2]*A)/(x[0]+par[3]*A);
    return light;
  }
  return 0;
}
//______________________________________________________________________________

double FitFenhai(double *x, double *par)
{
  if(par[2]>=par[3])
  {
    return -1;
  }

  // x[0]--E, x[1]--A
  if(x[1]==101 || x[1]==102 || x[1]==103)
  {
    int A = Int_t (x[1])%100;
    int Z = Int_t (x[1])/100;
    double exponent = (A+par[2])/(A+par[3]);
    double light = par[0]+par[1]*pow(x[0],exponent);
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


//______________________________________________________________________________
void FitPDT()
{

   ofstream FileOut;
   FileOut.open("../calibrations/SimultaneouslyFitParPDT.dat");
   FileOut << setw(5) <<"*tel" <<"  "<< setw(5) << "csi" <<"  "<<setw(5)<< "Z" <<"  "<<setw(5)<< "A" <<"  "<< setw(25) <<"Jerzy's Formula "
               <<"  "<<setw(20)<< "NumPar" << "Par0" <<"  "<< setw(15) <<"Par1"<<"  "<<setw(10)<<"Par2" <<"  "<<setw(10)<<"Par3\n";

  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for protons
  //////////////////////////////////////////////////////////////////////////////
  const Int_t NFiles_Proton=11;
  std::string * FileIn_name_Proton[NFiles_Proton];
  FileIn_name_Proton[0] = new std::string("../calibrations/WMUdataAddOnePecenterrEnergy_Z01_A01.dat");   // WMU data
  FileIn_name_Proton[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A01.dat"); //DEE points
  FileIn_name_Proton[2] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2013_2037_40Ca39.0AMeV_gain 200.dat"); // kinematics ponits
  FileIn_name_Proton[3] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_2312_2312_40Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  //FileIn_name_Proton[4] = new std::string("calibrations/Corrected_HiRA_CsIKinimatics_2825_2829_40Ca139.8AMeV_gain 130.dat"); // kinematics ponits
  FileIn_name_Proton[4] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4000_4005_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[5] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4021_4022_48Ca139.8AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[6] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4034_4037_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[7] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4332_4332_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[8] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4577_4584_48Ca28.0AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[9] = new std::string("../calibrations/Corrected_HiRA_CsIKinimatics_4585_4589_48Ca56.6AMeV_gain 170.dat"); // kinematics ponits
  FileIn_name_Proton[10] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A01.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  ///   definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataProton [12][4][NFiles_Proton];
  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Proton[12][4][NFiles_Proton];
  std::vector<double> errCsIV_Proton[12][4][NFiles_Proton];
  std::vector<double> CsIE_Proton[12][4][NFiles_Proton];
  std::vector<double> errCsIE_Proton[12][4][NFiles_Proton];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
  {
    ifstream FileIn_Proton(FileIn_name_Proton[FileNum]->c_str());
    if(!FileIn_Proton.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Proton[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
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

  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for deuterons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Deuteron=3;
  std::string * FileIn_name_Deuteron[NFiles_Deuteron];
  FileIn_name_Deuteron[0] = new std::string("../calibrations/WMUdataAddOnePecenterrEnergy_Z01_A02.dat");   // WMU data
  FileIn_name_Deuteron[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A02.dat"); //DEE points
  FileIn_name_Deuteron[2] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataDeuteron[12][4][NFiles_Deuteron];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Deuteron[12][4][3];
  std::vector<double> errCsIV_Deuteron[12][4][3];
  std::vector<double> CsIE_Deuteron[12][4][3];
  std::vector<double> errCsIE_Deuteron[12][4][3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
  {
    ifstream FileIn_Deuteron(FileIn_name_Deuteron[FileNum]->c_str());
    if(!FileIn_Deuteron.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Deuteron[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
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


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for tritons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Triton=2;
  std::string * FileIn_name_Triton[NFiles_Triton];
  FileIn_name_Triton[0] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A03.dat"); //DEE points
  FileIn_name_Triton[1] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  /// definition of TGraphErrors, TMultiGraph, TLengend
  TGraphErrors * DataTriton[12][4][NFiles_Triton];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Triton[12][4][2];
  std::vector<double> errCsIV_Triton[12][4][2];
  std::vector<double> CsIE_Triton[12][4][2];
  std::vector<double> errCsIE_Triton[12][4][2];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for each input file
  for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
  {
    ifstream FileIn_Triton(FileIn_name_Triton[FileNum]->c_str());
    if(!FileIn_Triton.is_open())
    {
      printf("Error: file%s not found\n", FileIn_name_Triton[FileNum]->c_str());
      return;
    }

    ////////////////////////////////////////////////////////////////////////////
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
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  //// create a multigraph to draw all the Hydrogen isotopes
  TMultiGraph * multiHydrogen[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      multiHydrogen[i][j] = new TMultiGraph();
      //////////////////////////////////////////////////////////////////////////
      ///   Add data for protons
      for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
      {
        multiHydrogen[i][j]->Add(DataProton[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///  Add data for deuteron
      for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
      {
        multiHydrogen[i][j]->Add(DataDeuteron[i][j][FileNum]);
      }

      //////////////////////////////////////////////////////////////////////////
      ///   Add data for triton
      for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
      {
        multiHydrogen[i][j]->Add(DataTriton[i][j][FileNum]);
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
     if(CsIV_Hydrogen[i][j].size()==0) continue;
     TotGraph[i][j] = new TGraph2DErrors(CsIV_Hydrogen[i][j].size(), CsIE_Hydrogen[i][j].data(), ZA_Hydrogen[i][j].data(), CsIV_Hydrogen[i][j].data(), errCsIE_Hydrogen[i][j].data(),  errZA_Hydrogen[i][j].data(), errCsIV_Hydrogen[i][j].data());
     TotGraph[i][j]->SetName(Form("2DTEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetTitle(Form("2DHydrogen_TEL%02d_CsI_%02d", i, j));
     TotGraph[i][j]->SetMarkerStyle(20);
   }
 }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  ////
  TF2 * fHydrogen = new TF2("fHydrogen",FitFenhai, 0, 1000, 100, 500, 4);
  TF1 * fProton = new TF1("fProton", fit_proton, 0, 1000, 4);
  TF1 * fDeuteron = new TF1("fDeuteron", fit_deuteron, 0, 1000, 4);
  TF1 * fTriton = new TF1("fTriton", fit_triton, 0, 1000, 4);
  fProton->SetLineColor(2);
  fDeuteron->SetLineColor(3);
  fTriton->SetLineColor(6);
  fHydrogen->SetParameters(0.001,0.01,1.5,2);
  fHydrogen->SetParLimits(2,0.5,2);
  fHydrogen->SetParLimits(3,0.6,3);
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  //// Draw
  TCanvas *c1 = new TCanvas("c1");
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
    //   if(i!=5 && (j!=0 || j!=1)) continue;

      if(CsIV_Hydrogen[i][j].size()==0) continue;

      //  TotGraph[i][j]->Draw("AP");
      //  WARNING: Daniele condition, pleas NEVER touch it!
      //  fHydrogen->SetParameters(0.001,0.01,1.5,2);
      //  TotGraph[i][j]->Fit("fHydrogen","WM");
      //--------------------------------------------------
      fHydrogen->SetParameters(0.001,0.01,1.5,2);
      TotGraph[i][j]->Fit("fHydrogen","WM");

      fProton->SetParameters(fHydrogen->GetParameters());
      fDeuteron->SetParameters(fHydrogen->GetParameters());
      fTriton->SetParameters(fHydrogen->GetParameters());

      multiHydrogen[i][j]->Draw("APE");
      multiHydrogen[i][j]->SetName(Form("TEL%02d_CsI_%02d", i, j));
      multiHydrogen[i][j]->SetTitle(Form("Hydrogen_TEL%02d_CsI_%02d", i, j));
      fProton->Draw("SAME");
      fDeuteron->Draw("SAME");
      fTriton->Draw("SAME");

      gPad->Modified();
      gPad->Update();
      getchar();

      //////////////////////////////////////////////////////////////////////////
      /// retrive the fit Parameters
      double par0 = fHydrogen->GetParameter(0);
      double par1 = fHydrogen->GetParameter(1);
      double par2 = fHydrogen->GetParameter(2);
      double par3 = fHydrogen->GetParameter(3);
      int Z;
      int A;
      for(int k=0; k<ZA_Hydrogen[i][j].size();k++)
      {
        Z = (int) ZA_Hydrogen[i][j][k]/100;
        A = (int) ZA_Hydrogen[i][j][k]%100;
        if(ZA_Hydrogen[i][j][k]==ZA_Hydrogen[i][j][k+1]) continue;
        FileOut << setw(5) << i <<"  "<< setw(5) << j <<"  "<<setw(5)<< Z <<"  "<<setw(5)<< A <<"  "<< setw(35)<< Form("[0]+[1].(pow(x,2)+[2].%d.x)/(x+[3].%d)", A,A) << "  "<<setw(15) << 4 <<"  "<< setw(10) << par0 <<"  "<< setw(10) << par1 <<"  "<<setw(10)<< par2 << setw(10) << par3 <<endl;
      }
     }
   }
//______________________________________________________________________________

}
