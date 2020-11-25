#include "include/EnergyLossModule.h"

//par[0]=Z
//par[1]=A
double GetEnergyResidualFromELossSi(double *x, double *par)
{
  EnergyLossModule LISEModule;
  double SiThickness_um=1537;
  double CsIMylarThickness=2.076;
  double Eresidual=LISEModule.GetResidualEnergy(par[0],par[1],x[0],"Si",SiThickness_um);
  return Eresidual-LISEModule.GetEnergyLoss(par[0],par[1],Eresidual,"Mylar",CsIMylarThickness);
}

void macro_SimpleELossSimulationCheck()
{
  TF1 * func_protons = new TF1("func_protons",GetEnergyResidualFromELossSi,2,100,2);
  func_protons->SetParameters(1,1);
  TF1 * func_alphas = new TF1("func_alphas",GetEnergyResidualFromELossSi,2,100,2);
  func_alphas->SetParameters(2,4);

  func_protons->SetLineColor(kRed);
  func_alphas->SetLineColor(kBlue);

  func_protons->Draw("");
  func_alphas->Draw("same");
}
