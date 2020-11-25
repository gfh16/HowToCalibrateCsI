
void Step2_DEEFITPoints_2nd_ExractPointsForEachParticle()
{
  int Z=4;
  int A=9;
  int NumOfPoints=20;

  std::string FileOutTag("InVoltage");
//  std::string FileOutTag("InChannel");

  ifstream FileIn("calibrations/DEEFITPointsFullInfo_Tel11_01.dat");
  ofstream FileOut(Form("calibrations/DEEPoints%s_Z%02d_A%02d.dat",FileOutTag.c_str(),Z, A));
  FileOut << setw(5) << "*tel" << setw(10) << "numcsi" << setw(15) << Form("CsI%s",FileOutTag.c_str()) << setw(20) << Form("errCsI%s",FileOutTag.c_str()) << setw(15) <<"CsIE"<< setw(15)<<"errCsIE\n";

  std::vector<double> LightOutput[12][4];
  std::vector<double> EnergyValues[12][4];
  std::vector<double> errLightOutput[12][4];
  std::vector<double> errEnergyValues[12][4];

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
    double Ch;
    double err_Ch;
    double V;
    double err_V;
    double E;
    double err_E;
    double ESi;
    double errESi;

    LineStream >> numtel >> numcsi >> Zread >> Aread >> Ch >> err_Ch >> V >> err_V >> E >> err_E >> ESi >> errESi;
    if(Zread!=Z || Aread!=A) continue;

    LightOutput[numtel][numcsi].push_back(V);
    EnergyValues[numtel][numcsi].push_back(E);
    errLightOutput[numtel][numcsi].push_back(err_V);
    errEnergyValues[numtel][numcsi].push_back(err_E);

  }

  double energy[12][4];
  double light[12][4];
  double err_energy[12][4];
  double err_light[12][4];

  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(EnergyValues[i][j].size()==0) continue;
      int Estart = EnergyValues[i][j].front()+2;
      int Eend = EnergyValues[i][j].back();
      int Estep = (int)floor((EnergyValues[i][j].back()-EnergyValues[i][j].front())/NumOfPoints);

      for(int k=Estart; k<Eend; k+=Estep)
      {
        for(int h=0; h<(EnergyValues[i][j].size()); h++)
        {
           if( (EnergyValues[i][j][h]>(k-1)) && (EnergyValues[i][j][h]<(k+1)))
           {
             energy[i][j] =   EnergyValues[i][j][h];
             light[i][j]= LightOutput[i][j][h];
             err_energy[i][j]=errEnergyValues[i][j][h];
             err_light[i][j]=errLightOutput[i][j][h];
           }
        }
        FileOut << setw(5) << i << setw(10) << j << setw(15) <<  light[i][j] << setw(15) << err_light[i][j] << setw(15) << energy[i][j] << setw(15) << err_energy[i][j] << endl;
      }
    }
  }
  FileIn.close();
  FileOut.close();
}
