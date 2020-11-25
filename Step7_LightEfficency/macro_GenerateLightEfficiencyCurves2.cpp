std::vector <double> ParticleEnergy; //MeV/u
std::vector <double> LiseELoss[NUM_MODELS];   //MeV/micron
std::vector <double> ParticleEnergyRange; //MeV/u
std::vector <double> LiseRange[NUM_RANGE_MODELS]; //micron

double Emax; //MeV/u
double Emin; //MeV/u
double ERangeMax; //MeV/u
double ERangeMin; //MeV/u
double RangeMin[NUM_RANGE_MODELS]; //micron
double RangeMax[NUM_RANGE_MODELS]; //micron

ROOT::Math::Interpolator SplineInterpolator[NUM_MODELS];

nuclear_masses *NucData=new nuclear_masses("/Nuclear_Masses/masses.conf");

double TF1Derivative(TF1 * theFunc, double x, double step = 0.001)
{
   return (theFunc->Eval(x-2*step)-8*theFunc->Eval(x-step)+8*theFunc->Eval(x+step)-theFunc->Eval(x-2*step))/(12*step);
}
//_______________________________________________________________________________
//______________________________________________
int LoadEnergyLossFile(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while reading energy loss file\n");
    return -1;
  }

  ParticleEnergy.clear();

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    double energy;
    double eloss;

    for(int i=0; i<NUM_MODELS; i++) {
      LineStream >> energy >> eloss;
      LiseELoss[i].push_back(eloss);
    }

    ParticleEnergy.push_back(energy);

    NRead++;
  }

  Emin=ParticleEnergy[0];
  Emax=ParticleEnergy[ParticleEnergy.size()-1];

  for(int i=0; i<NUM_MODELS; i++) {
    SplineInterpolator[i].SetData(ParticleEnergy,LiseELoss[i]);
  }

  return NRead;
}

void macro_GenerateLightEfficiencyCurves2()
{
  int Z=4;
  int A=7;
  const int LISEModel=1;

  ifstream FileIn("/calibrations/DEEFITPointsFinal.dat");
  ofstream FileOut(Form("/calibrations/LightEfficiencyData_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(10) << "*tel" << setw(10) << "numcsi" << setw(10) << "Z" << setw(10) << "A" << setw(20) << "-dE/dx (MeV/um)" << setw(20) << "Leff\n";

  std::vector<double> VoltageValues[12][4];
  std::vector<double> EnergyValues[12][4];
  std::vector<double> ZValues[12][4];
  std::vector<double> AValues[12][4];
  //ROOT::Math::Interpolator SplineInterpolator[12][4];

  TGraph * LightEnergyGraph [12][4];

  TGraph * LightEfficiencyGraph [12][4];
  std::vector<double> LightEfficiencyGraphData[12][4];
  std::vector<double> StoppingPowerGraphData[12][4];


  if(LoadEnergyLossFile(Form("/input/LISE_ELoss_Z%02d_A%02d_%s.dat", Z, A, "CsI"))<=0) {
    printf("Error: information not present for Z=%d A=%d material=%s\n", Z, A, "CsI");
    return;
  }


  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;
    int Zread;
    int Aread;
    double V;
    double err_V;
    double E;
    double err_E;

    LineStream >> numtel >> numcsi >> Zread >> Aread >> V >> err_V >> E >> err_E;
    if(Zread!=Z || Aread!=A) continue;

    VoltageValues[numtel][numcsi].push_back(V);
    EnergyValues[numtel][numcsi].push_back(E);
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      LightEnergyGraph[i][j]= new TGraph(EnergyValues[i][j].size(),EnergyValues[i][j].data(),VoltageValues[i][j].data());
      //LightEnergyGraph[i][j]->Draw("A*");
      //LightEnergyGraph[i][j]->Fit("pol5");
      //gPad->Modified();
      //gPad->Update();
      //getchar();
    }
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
       LightEnergyGraph[i][j]->Fit("pol5");
       TF1 * FitFunc = LightEnergyGraph[i][j]->GetFunction("pol5");
       TF1 * FitFuncDerivative = new TF1("FitFuncDerivative","pol4",0,2000);
       FitFuncDerivative->SetParameter(0,FitFunc->GetParameter(1));
       FitFuncDerivative->SetParameter(1,2*FitFunc->GetParameter(2));
       FitFuncDerivative->SetParameter(2,3*FitFunc->GetParameter(3));
       FitFuncDerivative->SetParameter(3,4*FitFunc->GetParameter(4));
       FitFuncDerivative->SetParameter(4,5*FitFunc->GetParameter(5));
       int NumSteps=20;
       for(int k=0; k<NumSteps; k++) {
         double Energy = EnergyValues[i][j][0]+ (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*(k+1)/NumSteps - (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*0.5/NumSteps;
         double Derivative = FitFuncDerivative->Eval(Energy);
         LightEfficiencyGraphData[i][j].push_back(Derivative);
         StoppingPowerGraphData[i][j].push_back(Z*Z*A/Energy);
         FileOut << setw(10) << i << setw(10) << j << setw(10) << Z << setw(10) << A << setw(20) << SplineInterpolator[LISEModel].Eval(Energy*NucData->get_mass_Z_A_uma(Z,A)) << setw(20) << Derivative << endl;
       }
    }
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      LightEfficiencyGraph[i][j] = new TGraph(StoppingPowerGraphData[i][j].size(), StoppingPowerGraphData[i][j].data(), LightEfficiencyGraphData[i][j].data());
      LightEfficiencyGraph[i][j]->Draw("AL");
      gPad->Modified();
      gPad->Update();
      //getchar();
    }
  }

  FileIn.close();
  FileOut.close();



}
