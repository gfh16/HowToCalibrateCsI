//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
/// definition of Horn formula to fitting isotopes from Z=2 to Z=4
/// this formula is given in the following paper:
//// D.Horn et al, NIM A320(1992) 273-276
////////////////////////////////////////////////////////////////////////////////
double HornFit(double *x, double *par)
{
  // Z=par[3], A=par[4]
  double consterm = par[2]*par[4]*pow(par[3],2);
  double lineterm = x[0]+consterm;
  double logterm = consterm*log(abs(lineterm/consterm));
  double light = par[0]+par[1]*(x[0]-logterm);
  return light;
}
//______________________________________________________________________________



//______________________________________________________________________________

void AllIsotopes_EstimateErrOfSimultaneouslyFit()
{

   ofstream FileOut;
   FileOut.open("HeavyIons_ErrofDataPointsToFitLine.dat");
   FileOut<< setw(5) << "*tel" <<"  "<< setw(5) << "csi" <<"  "<< setw(5) << "Z" <<"  "<< setw(5) << "A" <<"  "<< setw(10) << "CsIE(MeV)" <<"  "<< setw(10) << "CsIV-VCal"
          <<"  "<< setw(10) << "CsIV" <<"  "<< setw(10) << "VCal\n";

  //______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He3
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He3=1;
  std::string * FileIn_name_He3[NFiles_He3];
  FileIn_name_He3[0] = new std::string("../calibrations/DEEPoints_Z02_A03.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He3[12][4][2];
  std::vector<double> CsIE_He3[12][4][2];

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
      CsIE_He3[telnum][csinum][FileNum].push_back(E);
    }
    FileIn_He3.close();
  }

    //______________________________________________________________________________
    //////////////////////////////////////////////////////////////////////////////
    ////   retriving data for He4
    //////////////////////////////////////////////////////////////////////////////
    Int_t NFiles_He4=2;
    std::string * FileIn_name_He4[NFiles_He4];
    FileIn_name_He4[0] = new std::string("../calibrations/DEEPoints_Z02_A04.dat"); //DEE points
    FileIn_name_He4[1] = new std::string("../calibrations/WMUdata_Z02_A04.dat");

    //////////////////////////////////////////////////////////////////////////////
    ///  definition of variables to read the input data files
    std::vector<double> CsIV_He4[12][4][2];
    std::vector<double> CsIE_He4[12][4][2];

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
       CsIE_He4[telnum][csinum][FileNum].push_back(E);
     }
     FileIn_He4.close();
   }

  //______________________________________________________________________________
  //////////////////////////////////////////////////////////////////////////////
  ////   retriving data for He6
  //////////////////////////////////////////////////////////////////////////////
  Int_t NFiles_He6=1;
  std::string * FileIn_name_He6[NFiles_He6];
  FileIn_name_He6[0] = new std::string("../calibrations/DEEPoints_Z02_A06.dat"); //DEE points

  //////////////////////////////////////////////////////////////////////////////
  ///  definition of variables to read the input data files
  std::vector<double> CsIV_He6[12][4][2];
  std::vector<double> CsIE_He6[12][4][2];

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
      CsIE_He6[telnum][csinum][FileNum].push_back(E);
    }
    FileIn_He6.close();
  }

//______________________________________________________________________________


//______________________________________________________________________________
   //////////////////////////////////////////////////////////////////////////////
   /// read fit parameters
   ifstream FileIn;
   FileIn.open("../calibrations/SimultaneouslyFitParForAll.dat");

   std::vector<int> AValues[12][4];
   std::vector<int> ZValues[12][4];
   std::vector<double> par0[12][4];
   std::vector<double> par1[12][4];
   std::vector<double> par2[12][4];

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
     double Par0;
     double Par1;
     double Par2;

     LineStream >> telnum >> csinum >> ZValue >> AValue >> FitFormula >> Par0 >> Par1 >> Par2;

     ZValues[telnum][csinum].push_back(ZValue);
     AValues[telnum][csinum].push_back(AValue);
     par0[telnum][csinum].push_back(Par0);
     par1[telnum][csinum].push_back(Par1);
     par2[telnum][csinum].push_back(Par2);
   }
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
        par[3] = ZValues[i][j][k];
        par[4] = AValues[i][j][k];


        ////////////////////////////////////////////////////////////////////////
        /// calculation for He3s
        if(ZValues[i][j][k]==2 && AValues[i][j][k]==3)
        {
          for(int FileNum=0; FileNum<NFiles_He3; FileNum++)
          {
            for(int h=0; h<CsIV_He3[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_He3[i][j][FileNum][h]);
              double VCal = HornFit(&CsIE_He3[i][j][FileNum][h], par);
              double VRelative = CsIV_He3[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 2 <<"  "<< setw(5) << 3 <<"  "<< setw(10) << CsIE_He3[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_He3[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for He4s
        if(ZValues[i][j][k]==2 && AValues[i][j][k]==4)
        {
          for(int FileNum=0; FileNum<NFiles_He4; FileNum++)
          {
            if(CsIV_He4[i][j][FileNum].size()==0) continue;
            for(int h=0; h<CsIV_He4[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_He4[i][j][FileNum][h]);
              double VCal = HornFit(&CsIE_He4[i][j][FileNum][h], par);
              double VRelative = CsIV_He4[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 2 <<"  "<< setw(5) << 4 <<"  "<< setw(10) << CsIE_He4[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_He4[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }

        ////////////////////////////////////////////////////////////////////////
        /// calculation for He6s
        if(ZValues[i][j][k]==2 && AValues[i][j][k]==6)
        {
          for(int FileNum=0; FileNum<NFiles_He6; FileNum++)
          {
            for(int h=0; h<CsIV_He6[i][j][FileNum].size(); h++)
            {
              CsIE[i][j].push_back(CsIE_He6[i][j][FileNum][h]);
              double VCal = HornFit(&CsIE_He6[i][j][FileNum][h], par);
              double VRelative = CsIV_He6[i][j][FileNum][h] - VCal;
              ErrOfDataPointsToFitLine[i][j].push_back(VRelative);
              FileOut<< setw(5) << i <<"  "<< setw(5) << j <<"  "<< setw(5) << 2 <<"  "<< setw(5) << 6 <<"  "<< setw(10) << CsIE_He6[i][j][FileNum][h] <<"  "<< setw(10)
                     << VRelative <<"  "<< setw(10) << CsIV_He6[i][j][FileNum][h] <<"  "<< setw(10) << VCal <<endl;
            }
          }
        }
      //========================================================================
      }
    }
  }






}
