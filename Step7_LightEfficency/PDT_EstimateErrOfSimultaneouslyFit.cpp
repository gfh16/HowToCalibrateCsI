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
  double squareterm = pow(x[0], 2)+par[2]*par[4]*x[0];
  double linearterm = (x[0]+par[3]*par[4]);
  double light = par[0]+par[1]*squareterm/linearterm;
  return light;
}
//______________________________________________________________________________



//______________________________________________________________________________

void PDT_EstimateErrOfSimultaneouslyFit()
{
   ofstream FileOut;
   FileOut.open("PDT_ErrofDataPointsToFitLine.dat");
   FileOut<< setw(5) << "*tel" <<"  "<< setw(5) << "csi" <<"  "<< setw(5) << "Z" <<"  "<< setw(5) << "A" <<"  "<< setw(10) << "CsIE(MeV)" <<"  "<< setw(10) << "CsIV-VCal"
         <<"  "<< setw(10) << "CsIV" <<"  "<< setw(10) <<"VCal\n";

  //============================================================================
  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for protons
  //////////////////////////////////////////////////////////////////////////////
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


  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Proton[12][4][12];
  std::vector<double> CsIE_Proton[12][4][12];

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
      CsIE_Proton[telnum][csinum][FileNum].push_back(E);
    }
    FileIn_Proton.close();
  }


  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for deuterons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Deuteron=3;
  std::string * FileIn_name_Deuteron[NFiles_Deuteron];
  FileIn_name_Deuteron[0] = new std::string("../calibrations/WMUdata_Z01_A02.dat");   // WMU data
  FileIn_name_Deuteron[1] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A02.dat"); //DEE points
  FileIn_name_Deuteron[2] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A02.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Deuteron[12][4][3];
  std::vector<double> CsIE_Deuteron[12][4][3];

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of the number of data points for eaPDT_EstimateErrOfSimultaneouslyFit.cppch input file
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
      CsIE_Deuteron[telnum][csinum][FileNum].push_back(E);
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for tritons
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_Triton=2;
  std::string * FileIn_name_Triton[NFiles_Triton];
  FileIn_name_Triton[0] = new std::string("../calibrations/DEEPointsOmitLow_Z01_A03.dat"); //DEE points
  FileIn_name_Triton[1] = new std::string("../calibrations/HiRA_CsI_PunchThrough_Z01_A03.dat");  // punch through points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_Triton[12][4][2];
  std::vector<double> CsIE_Triton[12][4][2];

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
      CsIE_Triton[telnum][csinum][FileNum].push_back(E);
    }
  }
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  /// read fit parameters
  ifstream FileIn;
  FileIn.open("../calibrations/SimultaneouslyFitParPDT.dat");

  std::vector<int> AValues[12][4];
  std::vector<int> ZValues[12][4];
  std::vector<double> par0[12][4];
  std::vector<double> par1[12][4];
  std::vector<double> par2[12][4];
  std::vector<double> par3[12][4];

  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    int ZValue;
    int AValue;
    std::string FitFormula;
    double NumPar;
    double Par0;
    double Par1;
    double Par2;
    double Par3;

    LineStream >> telnum >> csinum >> ZValue >> AValue >> FitFormula >> NumPar >> Par0 >> Par1 >> Par2 >> Par3;

    ZValues[telnum][csinum].push_back(ZValue);
    AValues[telnum][csinum].push_back(AValue);
    par0[telnum][csinum].push_back(Par0);
    par1[telnum][csinum].push_back(Par1);
    par2[telnum][csinum].push_back(Par2);
    par3[telnum][csinum].push_back(Par3);
  }
  FileIn.close();
//______________________________________________________________________________


//______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  /// calculate the distance from the points to the fit line
  std::vector<double> CsIE[12][4];
  std::vector<double> ErrOfDataPointsToFitLine[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      for(int k=0; k<ZValues[i][j].size(); k++)
      {
        double par[5];
        par[0] = par0[i][j][k];
        par[1] = par1[i][j][k];
        par[2] = par2[i][j][k];
        par[3] = par3[i][j][k];
        par[4] = AValues[i][j][k];

        ////////////////////////////////////////////////////////////////////////
        /// calculation for protons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==1)
        {
          for(int FileNum=0; FileNum<NFiles_Proton; FileNum++)
          {
            for(int h=0; h<CsIV_Proton[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Proton[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Proton[i][j][FileNum][h], par);
              double VRelative = CsIV_Proton[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 1 <<"  "<< setw(10) << CsIE_Proton[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Proton[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for deuterons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==2)
        {
          for(int FileNum=0; FileNum<NFiles_Deuteron; FileNum++)
          {
            if(CsIV_Deuteron[i][j][FileNum].size()==0) continue;
            for(int h=0; h<CsIV_Deuteron[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Deuteron[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Deuteron[i][j][FileNum][h], par);
              double VRelative = CsIV_Deuteron[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 2 <<"  "<< setw(10) << CsIE_Deuteron[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Deuteron[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for Tritons
        if(ZValues[i][j][k]==1 && AValues[i][j][k]==3)
        {
          for(int FileNum=0; FileNum<NFiles_Triton; FileNum++)
          {
            for(int h=0; h<CsIV_Triton[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_Triton[i][j][FileNum][h]);
              double VCal = FitJerzy(&CsIE_Triton[i][j][FileNum][h], par);
              double VRelative = CsIV_Triton[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 1 <<"  "<< setw(5) << 3 <<"  "<< setw(10) << CsIE_Triton[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_Triton[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }
      //========================================================================
      }
    }
  }
  FileOut.close();
//______________________________________________________________________________


//______________________________________________________________________________
  ////////////////////////////////////////////////////////////////////////////////
  ////  Read data from FileOut
  ifstream FileRead;
  FileRead.open("PDT_ErrofDataPointsToFitLine.dat");

  std::vector<int> Zread[12][4];
  std::vector<int> Aread[12][4];
  std::vector<double> CsIEread[12][4];
  std::vector<double> CsIV_VCalread[12][4];
  std::vector<double> PecentageCsIV_VCalread[12][4];

  while(FileRead.is_open() && !FileRead.eof())
  {
    std::string LineRead;
    std::getline(FileRead, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    int ZValue;
    int AValue;
    double E;
    double errV;
    double csiV;
    double Vcal;
    double pecentage;


    LineStream >> telnum >> csinum >> ZValue >> AValue >> E >> errV >> csiV >> Vcal;
    pecentage = errV/Vcal*100;

    Zread[telnum][csinum].push_back(ZValue);
    Aread[telnum][csinum].push_back(AValue);
    CsIEread[telnum][csinum].push_back(E);
    CsIV_VCalread[telnum][csinum].push_back(errV);
    PecentageCsIV_VCalread[telnum][csinum].push_back(pecentage);
  }
  FileRead.close();
//______________________________________________________________________________


//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// retrieve data into protons, deuterons, and tritons
  std::vector<double> CsIEread_proton[12][4];
  std::vector<double> CsIV_VCalread_proton[12][4];
  std::vector<double> Pecentage_proton[12][4];
  std::vector<double> CsIEread_deuteron[12][4];
  std::vector<double> CsIV_VCalread_deuteron[12][4];
  std::vector<double> Pecentage_deuteron[12][4];
  std::vector<double> CsIEread_triton[12][4];
  std::vector<double> CsIV_VCalread_triton[12][4];
  std::vector<double> Pecentage_triton[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
       if(CsIEread[i][j].size()==0) continue;
       for(int k=0; k<CsIEread[i][j].size(); k++)
       {
         if((Zread[i][j][k]==1) && Aread[i][j][k]==1)
         {
           CsIEread_proton[i][j].push_back(CsIEread[i][j][k]);
           CsIV_VCalread_proton[i][j].push_back(CsIV_VCalread[i][j][k]);
           Pecentage_proton[i][j].push_back(PecentageCsIV_VCalread[i][j][k]);
         }

         if((Zread[i][j][k]==1) && Aread[i][j][k]==2)
         {
           CsIEread_deuteron[i][j].push_back(CsIEread[i][j][k]);
           CsIV_VCalread_deuteron[i][j].push_back(CsIV_VCalread[i][j][k]);
           Pecentage_deuteron[i][j].push_back(PecentageCsIV_VCalread[i][j][k]);
         }

          if((Zread[i][j][k]==1) && Aread[i][j][k]==3)
         {
           CsIEread_triton[i][j].push_back(CsIEread[i][j][k]);
           CsIV_VCalread_triton[i][j].push_back(CsIV_VCalread[i][j][k]);
           Pecentage_triton[i][j].push_back(PecentageCsIV_VCalread[i][j][k]);
         }
       }
     }
   }
//______________________________________________________________________________


//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// create graphs
   TMultiGraph * multigraph[12][4];
   TGraph * graph_proton[12][4];
   TGraph * graph_deuteron[12][4];
   TGraph * graph_triton[12][4];

   for(int i=0; i<12; i++)
   {
     for(int j=0; j<4; j++)
     {
       if(i!=5) continue;
       multigraph[i][j] = new TMultiGraph();
       /////////////////////////////////////////////////////////////////////////
       //// create graph for protons
       graph_proton[i][j] = new TGraph(CsIEread_proton[i][j].size(),CsIEread_proton[i][j].data(), Pecentage_proton[i][j].data());
       graph_proton[i][j]->SetMarkerStyle(25);
       graph_proton[i][j]->SetMarkerColor(kRed);
       multigraph[i][j]->Add(graph_proton[i][j]);

       /////////////////////////////////////////////////////////////////////////
       //// create graph for deuterons
       graph_deuteron[i][j] = new TGraph(CsIEread_deuteron[i][j].size(),CsIEread_deuteron[i][j].data(), Pecentage_deuteron[i][j].data());
       graph_deuteron[i][j]->SetMarkerStyle(25);
       graph_deuteron[i][j]->SetMarkerColor(kGreen);
       multigraph[i][j]->Add(graph_deuteron[i][j]);

       /////////////////////////////////////////////////////////////////////////
       //// create graph for tritons
       graph_triton[i][j] = new TGraph(CsIEread_triton[i][j].size(),CsIEread_triton[i][j].data(), Pecentage_triton[i][j].data());
       graph_triton[i][j]->SetMarkerStyle(25);
       graph_triton[i][j]->SetMarkerColor(kBlue);
       multigraph[i][j]->Add(graph_triton[i][j]);
     }
   }
//______________________________________________________________________________


//______________________________________________________________________________
   /////////////////////////////////////////////////////////////////////////////
   ///// Draw
   TCanvas *c1 = new TCanvas("c1","",1200,800);
   for(int i=0; i<12; i++)
   {

     for(int j=0; j<4; j++)
     {
       if(i!=5) continue;

       multigraph[i][j]->Draw("AP");


       gPad->Modified();
       gPad->Update();
       getchar();
     }
   }











//______________________________________________________________________________
}
