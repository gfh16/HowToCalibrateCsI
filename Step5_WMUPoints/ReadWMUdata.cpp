
void ReadWMUdata()
{
  int Z=1;
  int A=1;

  ifstream FileIn("DATA/WMUDataFullIn.dat");

  ofstream FileOut;
  FileOut.open(Form("../calibrations/WMUData_Z%02d_A%02d.dat", Z, A));
  FileOut << setw(5) <<"*tel" << setw(5) << "csi" <<setw(15)<< "CsICh"<<"  "<<setw(15)<< "errCsICh" <<
          << setw(15)<< "CsIV(V)"<<"  "<<setw(15)<< "errCsIV(V)" << setw(15)<< "CsIE(MeV)" <<"  "<<setw(15)<<"errCsIE(MeV)\n";

  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::stringstream LineStream(LineRead);

    int TelNum;
    int CsINum;
    int ANum;
    int ZNum;
    double Ch;
    double errCh;
    double CsIV;
    double errCsIV;
    double ECsI;
    double errECsI;

    LineStream >> TelNum >> CsINum  >> ANum >> ZNum >> ZNum >> Ch >> errCh >> CsIV >> errCsIV >> ECsI>>errECsI;
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
