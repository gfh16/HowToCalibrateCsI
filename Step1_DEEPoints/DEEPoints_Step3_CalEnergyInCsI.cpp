#include "include/EnergyLossModule.h"

void macro_CsIPIDCalibrationPointsFromProfiling()
{
  int Z=1;
  int A=3;
  int LiseModel=1;

//   std::string FileOutTag("LowEnergy");
  std::string FileOutTag("MidEnergy");
   
  ifstream FileIn(Form("calibrations/HiRA_CsI_DEEProfiling%s_Z%02d_A%02d.dat", FileOutTag.c_str(), Z, A));

  ofstream FileOut(Form("calibrations/HiRA_CsI_DEE%s_Z%02d_A%02d.dat", FileOutTag.c_str(), Z, A));
  FileOut << setw(5) << "*tel  " << setw(7) << "numcsi " << setw(10) << "CsI V " << setw(10) << "err CsI V " << setw(10) << "energy " << setw(10) << "err energy"<< setw(10) << "ESi (MeV) " << setw(10) << "err ESi (MeV)\n";

  double CsIch[6000];
  double CsIE[6000];
  double CsIV[6000];
  double err_CsIE[6000];
  double err_CsIch[6000];
  double err_CsIV[6000];

  // Energy Loss Module
  double TelSiThickness[12];
  TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
  TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
  TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
  double CsIMylarThickness=2.076;
  /////////////////////

  EnergyLossModule LISEModule;

  while (!FileIn.eof()) {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;
    double CsIch;
    double errCsIch;
    double CsIV;
    double errCsIV;
    double ESi;
    double errESi;

    LineStream >> numtel>> numcsi;
    LineStream >> CsIch >> errCsIch >> CsIV >> errCsIV >> ESi >> errESi;

    double Eresidual=LISEModule.GetResidualEnergy(Z,A,ESi,"Si",TelSiThickness[numtel],LiseModel);
    double EresidualOnCsI=Eresidual-LISEModule.GetEnergyLoss(Z,A,Eresidual,"Mylar",CsIMylarThickness,LiseModel);
    double CsIE=EresidualOnCsI;
    double EresidualMax=LISEModule.GetResidualEnergy(Z,A,ESi+errESi,"Si",TelSiThickness[numtel],LiseModel);
    double EresidualOnCsIMax=EresidualMax-LISEModule.GetEnergyLoss(Z,A,EresidualMax,"Mylar",CsIMylarThickness,LiseModel);
    double err_CsIE=fabs(EresidualOnCsIMax-EresidualOnCsI);

    printf("Tel %02d CsI %02d: ESi=%.3f -> ECsI=%.3f\n", numtel, numcsi, ESi, CsIE);

    FileOut << setw(5) << numtel << "  " << setw(7) << numcsi << "  " << setw(10) << CsIV << "  " << setw(10) << errCsIV << "  " <<
	  setw(10) << CsIE << "  " << setw(10) << err_CsIE << setw(10) << ESi << "  " << setw(10) << errESi << endl;
  }

  return;
}
