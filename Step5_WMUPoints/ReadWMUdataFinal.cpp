
void ReadWMUdataFinal()
{
  double errCsIVPecentage = 0.01;
  ifstream FileIn("./output/WMUdata.dat");

  std::string FileOutTag("WMUdata");

  ofstream FileOutProtons;
  FileOutProtons.open(Form("../calibrations/%s_Z01_A01.dat", FileOutTag.c_str()));
  FileOutProtons << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"CsIV (V)"<<"  "<<setw(10)<<"err_CsIV"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";

  ofstream FileOutDeuterons;
  FileOutDeuterons.open(Form("../calibrations/%s_Z01_A02.dat", FileOutTag.c_str()));
  FileOutDeuterons << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"CsIV (V)"<<"  "<<setw(10)<<"err_CsIV"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";

  ofstream FileOut4He;
  FileOut4He.open(Form("../calibrations/%s_Z02_A04.dat", FileOutTag.c_str()));
  FileOut4He << setw(5) <<"*telnum" <<"  "<< setw(10) << "csinum" <<"  "<<setw(10)<<"CsIV (V)"<<"  "<<setw(10)<<"err_CsIV"<< setw(10) << "Energy(MeV)" <<"  "<<setw(10)<<"err_Energy"<<" "<<setw(5)<<"Z"<<"  "<<setw(5)<<"A\n";

  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::stringstream LineStream(LineRead);

    int HiRANum;
    int TelNum;
    int CsINum;
    int ANum;
    int ZNum;
    double ECsI;
    double errECsI;
    double CsIV;
    double errCsIV;


    LineStream >> HiRANum >>TelNum >> CsINum >> ANum >> ZNum >> ECsI  >> CsIV ;
    errCsIV = errCsIVPecentage * CsIV;
    errECsI = 0;

    if(HiRANum!=10) continue;

    if(ZNum==1 && ANum==1)
    {
       FileOutProtons<< setw(5) << 5 <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< CsIV/1000 <<"  "<<setw(10)<< errCsIV/1000 << setw(10) << ECsI <<"  "<<setw(10)<< errECsI <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }

    if(ZNum==1 && ANum==2)
    {
       FileOutDeuterons<< setw(5) << 5 <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< CsIV/1000 <<"  "<<setw(10)<< errCsIV/1000 << setw(10) << ECsI <<"  "<<setw(10)<< errECsI <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }

    if(ZNum==2 && ANum==4)
    {
       FileOut4He<< setw(5) << 5 <<"  "<< setw(10) << CsINum <<"  "<<setw(10)<< CsIV/1000 <<"  "<<setw(10)<<  errCsIV/1000 << setw(10) << ECsI <<"  "<<setw(10)<< errECsI <<setw(5)<< ZNum <<"  "<<setw(5)<< ANum << endl;
    }
  }
  FileIn.close();
  FileOutProtons.close();
  FileOutDeuterons.close();
  FileOut4He.close();
}
