#include "Nuclear_Masses/nuclear_masses.h"
#include "include/RelativisticKinematics.h"
#include "include/HiRACsICalibration.h"

const int Z_target = 1;
const int A_target = 1;
const double target_thickness =116.19; //um (9.8 mg/cm2)
const int Z_beam = 20;


/*
//---- For Run2013 - Run 2037
const int A_beam = 40;
const double E_projectile = 39; //MeV/u
const int csi_gain_setting=200;
const int FirstRun = 2013;
const int LastRun = 2037;
const double tilt_angle =0.; //degF
const int IntegralCut=150;
*/

/*
//---- For Run2312 - Run 2312
const int A_beam = 40;
const double E_projectile = 56.6; //MeV/u   err: +/- 0.5%
const int csi_gain_setting=170;
const int FirstRun = 2312;
const int LastRun = 2312;
const double tilt_angle =0.; //degF
const int IntegralCut=50;
*/

/*
  //---- For Run2825 - Run 2829
  const int A_beam = 40;
  const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
  const int csi_gain_setting=130;
  const int FirstRun = 2825;
  const int LastRun = 2829;
  const double tilt_angle =0.; //degF
  const int IntegralCut=50;
*/

/*
  //---- For Run4000 - Run 4005
  const int A_beam = 48;
  const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
  const int csi_gain_setting=170;
  const int FirstRun = 4000;
  const int LastRun = 4005;
  const double tilt_angle =0.; //degF
  const int IntegralCut=100;
*/

/*
//---- For Run4021 - Run 4022
const int A_beam = 48;
const double E_projectile = 139.8; //MeV/u    err: +/- 0.2%
const int csi_gain_setting=170;
const int FirstRun = 4021;
const int LastRun = 4022;
const double tilt_angle =0.; //degF
const int IntegralCut=50;
*/


/*
//---- For Run4034 - Run 4037
const int A_beam = 48;
const double E_projectile =28; //MeV/u      err: +/- 0.5%
const int csi_gain_setting=170;
const int FirstRun = 4034;
const int LastRun = 4037;
const double tilt_angle =0.; //degF
const int IntegralCut=100;
*/

/*
//---- For Run4332 - Run4332
const int A_beam = 48;
const double E_projectile = 56.6; //MeV/u    err: +/- 0.5%
const int csi_gain_setting=170;
const int FirstRun = 4332;
const int LastRun = 4332;
const double tilt_angle =0.; //degF
const int IntegralCut=150;
*/

/*
//---- For Run4577 - Run4584
const int A_beam = 48;
const double E_projectile = 28; //MeV/u      err: +/- 0.5%
const int csi_gain_setting=170;
const int FirstRun = 4577;
const int LastRun = 4584;
const double tilt_angle =30.; //degF
const int IntegralCut=300;
*/


//---- For Run4585 - Run4589
const int A_beam = 48;
const double E_projectile = 56.6; //MeV/u     err: +/- 0.5%
const int csi_gain_setting=170;
const int FirstRun = 4585;
const int LastRun = 4589;
const double tilt_angle =30.; //degF
const int IntegralCut=150;




// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
double KinematicLine(double *x, double *par)
{
  RelativisticKinematics KinematicModule;
  double DegToRad = TMath::Pi()/180.;

  double TheoreticalEnergy=KinematicModule.GetEnergyTwoBodyRecoil(x[0]*DegToRad, par[0], par[1], par[2], par[3]);

  return TheoreticalEnergy;
}

// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
// par[4] = target_thickness um
// par[5] = target_tilt_angle deg
// par[6] = SnPb thickness
// par[7] = Mylar thickness
double KinematicLineCorrected(double * x, double * par) {
  EnergyLossModule LISECalc;
  double DegToRad = TMath::Pi()/180.;
  char target_material[]="CH2";

  double TheoreticalEinc=par[0]*par[1];
  double InteractionPoint=(par[4]/2.)/cos(par[5]*DegToRad);
  double CorrectedEinc=TheoreticalEinc-LISECalc.GetEnergyLoss(Z_beam, A_beam, TheoreticalEinc, target_material, InteractionPoint);
  double CrossedTarget=(par[4]/2.)/cos((x[0]-par[5])*DegToRad);

  par[0]=CorrectedEinc/par[1];
  double TheoreticalEnergy=KinematicLine(x, par);

  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, TheoreticalEnergy, target_material, CrossedTarget);
  DegradedEnergy=TheoreticalEnergy-EnergyLoss;
  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, DegradedEnergy, "SnPb", par[6]);
  DegradedEnergy=DegradedEnergy-EnergyLoss;
  EnergyLoss=LISECalc.GetEnergyLoss(1, 1, DegradedEnergy, "Mylar", par[7]);
  DegradedEnergy=DegradedEnergy-EnergyLoss;

  return DegradedEnergy;
}

// par[0] = E_Projectile
// par[1] = M_Projectile uma
// par[2] = M_Target uma
// par[3] = Eecc_Projectile MeV
// par[4] = target_thickness um
// par[5] = target_tilt_angle deg
// par[6] = SnPb thickness
// par[7] = Mylar thickness
// par[8] = Si thickness
// par[9] = CsIMylar thickness
double KinematicLineCsI(double *x, double *par)
{
  EnergyLossModule LISECalc;
  double DegToRad = TMath::Pi()/180.;

  double CorrectedEnergyOnSi=KinematicLineCorrected(x, par);
  double EnergyLoss;
  double DegradedEnergy;
  EnergyLoss=LISECalc.GetEnergyLoss(1,1,CorrectedEnergyOnSi, "Si", par[8]);
  DegradedEnergy=CorrectedEnergyOnSi-EnergyLoss;
  EnergyLoss+=LISECalc.GetEnergyLoss(1,1,DegradedEnergy, "Mylar", par[9]);

  return CorrectedEnergyOnSi-EnergyLoss;
}


void CsIKinematicLineProjection()
{

   TCanvas *c1=new TCanvas("c1","",1200,800);
   c1->Divide(2,1);

   TFile *FileIn=new TFile(Form("output/NewGeo_HiRA_KinematicPlots_%04d_%04d_%02dCa+1H@%.1fAMeV.root",FirstRun, LastRun, A_beam, E_projectile));
   TFile *FileInCut=new TFile(Form("output/NewGeo_HiRA_KinematicPlotsCut_%04d_%04d_%02dCa+1H@%.1fAMeV.root",FirstRun, LastRun, A_beam, E_projectile));

   ofstream FileOut(Form("12KinematicLineProjection/NewGeo_HiRA_CsIKinematics_%4d_%4d_%dCa%.1fAMeV_gain%4d.dat", FirstRun, LastRun, A_beam, E_projectile, csi_gain_setting));
   ofstream FileOutFull(Form("12KinematicLineProjection/NewGeo_HiRA_CsIKinematics_FullInfo_%4d_%4d_%dCa%.1fAMeV_gain%4d.dat", FirstRun, LastRun, A_beam, E_projectile, csi_gain_setting));
   FileOut<<setw(5)<< "*telnum" <<"  "<<setw(5)<< "csinum"<<"  "<<setw(10)<<"CsI V"<<"  "<<setw(15)<<"err_CsI V"<<"  "<<setw(10)<<"energy"<<"  "<<setw(15)<<"err_energy\n";
   FileOutFull<<setw(5)<< "*telnum" <<"  "<<setw(5)<< "csinum"<<"  "<<setw(5)<<"ch"<<"  "<<setw(10)<<"err_ch"<<"  "<<setw(15)<<"theta(deg)"<<"  "<<setw(15)<<"theta_min (deg)"<<"  "<<setw(10)<<"theta_max"<<"  "<<setw(10)<<"energy"<<"  "<<setw(10)<<"err_energy"<<"  "<<setw(10)<<"CsI V"<<"  "<<setw(10)<<"err_CsI V\n";



   double SnPbThickness =18.;
   double MylarThickness =1.47; //um
   double TelSiThickness[12];
   TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
   TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
   TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
   double CsIMylarThickness =2.076; //um
   double UMA_MeV =931.494028;
   nuclear_masses NuclearDatabase("Nuclear_Masses/masses.conf");
   double mass_beam =NuclearDatabase.get_mass_Z_A(Z_beam, A_beam)/UMA_MeV;
   double mass_target =NuclearDatabase.get_mass_Z_A(Z_target, A_target)/UMA_MeV;

   HiRACsICalibrationManager CsICalibrationModule;
   CsICalibrationModule.LoadPulserInfo(Form("calibrations/HiRA_CsI_Pulser_%dsetting.dat",csi_gain_setting));


//---------------------------------------------------------------------------------------------------------
// ***************
// ****************    Begin our analysis here   ***************************************
//---------------------------------------------------------------------------------------------------------


  //------To Read the 2D histograms and cuts from data files -----------------------------
  TH2D *KinPlotCsIRaw[12][4];
  TCutG *mycut[12][4];
  TH1D *ProjCsI[12][4];
  for(int i=0; i<12; i++)
  {
    for(int j=0; j<4; j++)
    {
      KinPlotCsIRaw[i][j]=(TH2D*)FileIn->Get(Form("histKinematicPlots_%02d_%02d",i, j));
      mycut[i][j]=(TCutG*)FileInCut->Get(Form("histKinematicPlots_%02d_%02d_Z%02d_A%02d",i, j, Z_target, A_target));
    //  if(mycut[i][j]==0) continue;
    }
  }

int NSamples=0;
double ECsI_Ch[100];
double err_ECsI_Ch[100];
double ThetaMean[100];
  //-------- To get datas points -------------------------
  for(int TelNum=0; TelNum<12; TelNum++)
  {
    for(int CsINum=0; CsINum<4; CsINum++)
    {
      if(KinPlotCsIRaw[TelNum][CsINum]==0) continue;
      if(mycut[TelNum][CsINum]==0) continue;

      //---- To get the bin of minimumtheta and maximumtheta ---------
      double MinimumTheta=mycut[TelNum][CsINum]->GetXaxis()->GetXmin();
      double MaximumTheta=mycut[TelNum][CsINum]->GetXaxis()->GetXmax();
      int MinimumThetaBin=KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->FindBin(MinimumTheta);
      int MaximumThetaBin=KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->FindBin(MaximumTheta);
      int DeltaThetaBin=MaximumThetaBin - MinimumThetaBin;
      int ThetaBinStep;
      if(DeltaThetaBin>30)
      {
        ThetaBinStep=(MaximumThetaBin-MinimumThetaBin)/5;
      }
      if(DeltaThetaBin>20&& DeltaThetaBin<30)
      {
        ThetaBinStep=(MaximumThetaBin-MinimumThetaBin)/4;
      }
      if(DeltaThetaBin<20)
      {
        ThetaBinStep=(MaximumThetaBin-MinimumThetaBin)/3;
      }

      NSamples=0;
      //----- To project the histograms to Y-axis to get the data points -------
      for(int ThetaBin=MinimumThetaBin; ThetaBin<MaximumThetaBin; ThetaBin+=ThetaBinStep)
      {
        //------ To get the Minimum, Maximum and mean values of theta in each step ----
        double ThetaMin=KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->GetBinCenter(ThetaBin+ThetaBinStep-2);
        double ThetaMax=KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->GetBinCenter(ThetaBin+ThetaBinStep+2);
        ThetaMean[NSamples]=KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->GetBinCenter(ThetaBin+ThetaBinStep);

        //------- definition of the ProjectionY -----------------------------------
        ProjCsI[TelNum][CsINum]=(TH1D*) KinPlotCsIRaw[TelNum][CsINum]->ProjectionY(Form("ProjCsI_%02d_%02d",TelNum, CsINum),ThetaBin+ThetaBinStep-2,ThetaBin+ThetaBinStep+2,Form("[histKinematicPlots_%02d_%02d_Z%02d_A%02d]", TelNum, CsINum, Z_target, A_target));
        ProjCsI[TelNum][CsINum]->SetTitle(Form("CsI Projection %.2f<#theta<%.2f", ThetaMin, ThetaMax));
        ProjCsI[TelNum][CsINum]->Rebin(2);


        // ------- variables of fitting range  ---------------------------
        double ECsIapprox=ProjCsI[TelNum][CsINum]->GetBinCenter(ProjCsI[TelNum][CsINum]->GetMaximumBin());
        double err_ECsIapprox=ProjCsI[TelNum][CsINum]->GetRMS();
        double LowRange= ECsIapprox - err_ECsIapprox;
        double UpRange = ECsIapprox + err_ECsIapprox;
        int LowRangeBin= ProjCsI[TelNum][CsINum]->FindBin(LowRange);
        int UpRangeBin = ProjCsI[TelNum][CsINum]->FindBin(UpRange);

        if(err_ECsIapprox==0) continue;

        //--------Method 1: To get mean values and RMS --------------------------------------------------
        if (ProjCsI[TelNum][CsINum]->Integral()<IntegralCut)
        {
          ECsI_Ch[NSamples]=ProjCsI[TelNum][CsINum]->GetMean();
          err_ECsI_Ch[NSamples]=ProjCsI[TelNum][CsINum]->GetRMS();
          c1->cd(2);
          ProjCsI[TelNum][CsINum]->Draw("hist");
          ProjCsI[TelNum][CsINum]->GetXaxis()->SetRangeUser(ECsIapprox-100,ECsIapprox +100);
        }
        //------- Method 2: Gaussian fit ----------------------------------------------------------------------
        if(ProjCsI[TelNum][CsINum]->Integral()>IntegralCut)
        {
          ProjCsI[TelNum][CsINum]->Fit("gaus","0","",ECsIapprox - err_ECsIapprox, ECsIapprox + err_ECsIapprox);
          TF1 *fit_result=ProjCsI[TelNum][CsINum]->GetFunction("gaus");
          ECsI_Ch[NSamples]=fit_result->GetParameter(1);
          err_ECsI_Ch[NSamples]=fit_result->GetParError(1);
          c1->cd(2);
          ProjCsI[TelNum][CsINum]->Draw("hist");
          ProjCsI[TelNum][CsINum]->GetXaxis()->SetRangeUser(ECsIapprox-100,ECsIapprox +100);
          fit_result->Draw("*L SAME");
          gPad->Modified();
          gPad->Update();
        }

        // ---------- To calculate the voltage ----------------------------------------------
        double CsI_V=CsICalibrationModule.GetVoltageValue(ECsI_Ch[NSamples], TelNum, CsINum);
        double err_CsI_V=CsICalibrationModule.GetVoltageValue(ECsI_Ch[NSamples]+err_ECsI_Ch[NSamples], TelNum, CsINum) - CsI_V;

        // --------- To calculate the energies of particle stop in CsI with LISE -------------
        double par[10];
        par[0]=E_projectile;
        par[1]=mass_beam;
        par[2]=mass_target;
        par[3]=0;
        par[4]=target_thickness;
        par[5]=tilt_angle;
        par[6]=SnPbThickness;
        par[7]=MylarThickness;
        par[8]=TelSiThickness[TelNum];
        par[9]=CsIMylarThickness;
        double EnergyValue = KinematicLineCsI(&ThetaMean[NSamples], par);
        double err_EnergyValue = abs(KinematicLineCsI(&ThetaMax, par) - EnergyValue);
        if(err_EnergyValue>=EnergyValue) continue;  // There may be a limit for emmitting kinematic angles

       FileOut<< setw(5) << TelNum <<"  "<< setw(5) << CsINum<<"  "<< setw(10) <<CsI_V<<"  "<<setw(15)<<err_CsI_V<<"  "<<setw(10)<<EnergyValue<<"  "<<setw(15)<< err_EnergyValue <<"  "<<endl;
       FileOutFull<< setw(5)<< TelNum <<"  "<<setw(5)<< CsINum <<"  "<<setw(5)<< ECsI_Ch[NSamples]<<"  "<<setw(10) << err_ECsI_Ch[NSamples] <<"  "<<setw(15)<< ThetaMean[NSamples] <<"  "<<setw(15)<< ThetaMin <<"  "<<setw(10)<< ThetaMax <<"  "<<setw(10)<<EnergyValue <<"  "<<setw(10)<<err_EnergyValue <<"  "<<setw(10)<< CsI_V<<"  "<<setw(10)<<err_CsI_V<<"  "<<endl;


        //----- Draw in the same canvas ------------------------------------------
        const int N=1;
        Double_t X[N]={ThetaMean[NSamples]};
        Double_t Y[N]={ECsI_Ch[NSamples]};
        c1->cd(1);
        KinPlotCsIRaw[TelNum][CsINum]->Draw("colz");
        KinPlotCsIRaw[TelNum][CsINum]->GetXaxis()->SetRangeUser(ThetaMin - 10, ThetaMax + 10);
        KinPlotCsIRaw[TelNum][CsINum]->GetYaxis()->SetRangeUser(ECsIapprox - 200, ECsIapprox + 300);
        mycut[TelNum][CsINum]->Draw("*L SAME");
        TGraph * gr1=new TGraph(N, X, Y);
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerSize(1.5);
        gr1->SetMarkerColor(kRed);
        gr1->Draw("PE SAME");
        gPad->Modified();
        gPad->Update();
        c1->Print(Form("pictures/Fit_%04d_%04d/ProjCsI_%02d_%02d_%02d_%04d_%04d.png",FirstRun, LastRun, TelNum, CsINum, ThetaBin, FirstRun, LastRun));

        NSamples++;
      }

      TCanvas *c2=new TCanvas("c2","",800,600);
      KinPlotCsIRaw[TelNum][CsINum]->Draw("colz");
      mycut[TelNum][CsINum]->Draw("*L SAME");
      TGraph *gr2=new TGraph(NSamples, ThetaMean, ECsI_Ch);
      gr2->SetMarkerStyle(20);
      gr2->SetMarkerSize(1.5);
      gr2->SetMarkerColor(kRed);
      gr2->Draw("PE SAME");
      gPad->Modified();
      gPad->Update();
      c2->Print(Form("12KinematicLineProjection/DataPoints_%04d_%04d/ProjCsI_%02d_%02d_%04d_%04d.png",FirstRun, LastRun,TelNum, CsINum, FirstRun, LastRun));

    }
  }
  FileIn->Close();
  FileInCut->Close();
  FileOut.close();
  FileOutFull.close();
 // return;

}
