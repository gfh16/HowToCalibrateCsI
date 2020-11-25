void macro_GenerateLightEfficiencyCurves()
{
  int Z=4;
  int A=7;

  ifstream FileIn(Form("calibrations/DEEFIT_Z%02d_A%02d.dat", Z, A));
  ofstream FileOut(Form("calibrations/LightEfficiency_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(10) << "*tel" << setw(10) << "numcsi" << setw(20) << "AZ2/E" << setw(20) << "Leff\n";

  std::vector<double> VoltageValues[12][4];
  std::vector<double> EnergyValues[12][4];
  ROOT::Math::Interpolator SplineInterpolator[12][4];


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
    double V;
    double err_V;
    double E;
    double err_E;

    LineStream>>numtel>>numcsi>>V>>err_V>>E>>err_E;

    VoltageValues[numtel][numcsi].push_back(V);
    EnergyValues[numtel][numcsi].push_back(E);
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      SplineInterpolator[i][j].SetData(EnergyValues[i][j],VoltageValues[i][j]);
    }
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
       int NumSteps=20;
       for(int k=0; k<NumSteps; k++) {
         double Energy = EnergyValues[i][j][0]+ (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*(k+1)/NumSteps - (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*0.5/NumSteps;
         FileOut << setw(10) << i << setw(10) << j << setw(20) << A*pow(Z,2)/Energy << setw(20) << SplineInterpolator[i][j].Deriv(Energy) << endl;
       }
    }
  }

  FileIn.close();
  FileOut.close();



}
