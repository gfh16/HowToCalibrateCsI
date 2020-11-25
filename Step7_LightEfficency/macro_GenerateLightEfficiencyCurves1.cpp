double TF1Derivative(TF1 * theFunc, double x, double step = 0.001)
{
   return (theFunc->Eval(x-2*step)-8*theFunc->Eval(x-step)+8*theFunc->Eval(x+step)-theFunc->Eval(x-2*step))/(12*step);
}

void macro_GenerateLightEfficiencyCurves1()
{
  int Z=1;
  int A=1;

  ifstream FileIn("calibrations/DEEFITPointsFinal.dat");
  ofstream FileOut(Form("calibrations/LightEfficiencyData_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(10) << "*tel" << setw(10) << "numcsi" << setw(10) << "Z" << setw(10) << "A" << setw(20) << "AZ2/E" << setw(20) << "Leff\n";

  std::vector<double> VoltageValues[12][4];
  std::vector<double> EnergyValues[12][4];
  std::vector<double> ZValues[12][4];
  std::vector<double> AValues[12][4];
  //ROOT::Math::Interpolator SplineInterpolator[12][4];

  TGraph * LightEnergyGraph [12][4];

  TGraph * LightEfficiencyGraph [12][4];
  std::vector<double> LightEfficiencyGraphData[12][4];
  std::vector<double> StoppingPowerGraphData[12][4];

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
       int NumSteps=20;
       for(int k=0; k<NumSteps; k++) {
         double Energy = EnergyValues[i][j][0]+ (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*(k+1)/NumSteps - (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*0.5/NumSteps;
         double Derivative = TF1Derivative(FitFunc,Energy);
         LightEfficiencyGraphData[i][j].push_back(Derivative);
         StoppingPowerGraphData[i][j].push_back(Z*Z*A/Energy);
         FileOut << setw(10) << i << setw(10) << j << setw(10) << Z << setw(10) << A << setw(20) << A*pow(Z,2)/Energy << setw(20) << Derivative << endl;
       }
    }
  }

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      LightEfficiencyGraph[i][j] = new TGraph(StoppingPowerGraphData[i][j].size(), StoppingPowerGraphData[i][j].data(), LightEfficiencyGraphData[i][j].data());
      LightEfficiencyGraph[i][j]->Draw("AL");
      gPad->Modified();
      gPad->Update();
      getchar();
    }
  }

  FileIn.close();
  FileOut.close();



}
