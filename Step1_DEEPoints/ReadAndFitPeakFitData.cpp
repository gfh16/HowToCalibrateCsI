
void ReadAndFitPeakFitData()
{
  const int TELNUM=12;
  const int STRIPNUM=32;

  ifstream FileIn("crosby/PeakFit.dat");
  
  ofstream FileOutOdd;
  FileOutOdd.open("figures/odd/FitParameters_Odd.dat");
  FileOutOdd<< setw(5) <<"*tel" <<setw(10)<<"strip"<<setw(10)<< "par[0]"<<"  "<<setw(15)<< "err_par[0]" <<"  "<<setw(15)<<"par[1]"<<"  "<<setw(15)<<"err_par[1]\n";
  
  ofstream FileOutEven;
  FileOutEven.open("figures/even/FitParameters_Even.dat");
  FileOutEven<< setw(5) <<"*tel" <<setw(10)<<"strip"<<setw(10)<< "par[0]"<<"  "<<setw(15)<< "err_par[0]" <<"  "<<setw(15)<<"par[1]"<<"  "<<setw(15)<<"err_par[1]\n";
  
  int npoints[TELNUM][STRIPNUM];
  for(int i=0; i<TELNUM; i++)
  {
    for(int j=0; j<STRIPNUM; j++)
    {
      npoints[i][j]=0;
    }
  }

  //----- for each telescope strip, there are four points, energy values: 5.40430,6.02532,6.52852,8.57606 MeV -----------
  double Epoints[4]={5.40430,6.02532,6.52852,8.57606};  
  double err_Epoints[4]={0,      0,      0,      0};
  double Center[TELNUM][STRIPNUM][4];
  double err_Center[TELNUM][STRIPNUM][4];
  double Energy[TELNUM][STRIPNUM][4];
  double err_Energy[TELNUM][STRIPNUM][4];
  while(FileIn.is_open() && !FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);
    
    int F0_over_B1;
    int telnum;
    int stripnum;
    
    LineStream >> F0_over_B1 >> telnum >> stripnum;
    if(F0_over_B1!=0) continue;
    LineStream >> Center[telnum][stripnum][npoints[telnum][stripnum]] >> err_Center[telnum][stripnum][npoints[telnum][stripnum]];
       
    Energy[telnum][stripnum][npoints[telnum][stripnum]]=Epoints[npoints[telnum][stripnum]];
    err_Energy[telnum][stripnum][npoints[telnum][stripnum]]=err_Epoints[npoints[telnum][stripnum]];
          
    npoints[telnum][stripnum]++;
  }

  //---- Creating graphs -----------------------------
  TGraphErrors * PeakFit[TELNUM][STRIPNUM];
  for(int i=0; i<TELNUM; i++)
  {
    for(int j=0; j<STRIPNUM; j++)
    {
      PeakFit[i][j]=new TGraphErrors(npoints[i][j], Center[i][j], Energy[i][j], err_Center[i][j], err_Energy[i][j]);
      PeakFit[i][j]->SetMarkerStyle(20);
      PeakFit[i][j]->SetMarkerColor(kBlue);
      PeakFit[i][j]->SetMarkerSize(1.2);
    }
  }

  //------- Take several telescopes, for odd and even strips (not 0, 15, 16, 31 strip), do linear fit --------
  TCanvas *c1=new TCanvas("c1","",800,600);
  for(int i=0; i<TELNUM; i++)
  {
    if((2*i)<TELNUM)
    {
      for(int j=0; j<STRIPNUM; j++)
      {
        if(4*j+1<STRIPNUM)
        {
          PeakFit[2*i][4*j+1]->Draw("AP");
          PeakFit[2*i][4*j+1]->SetTitle(Form("Tele%02d_Strip%02d", 2*i, 4*j+1));
          PeakFit[2*i][4*j+1]->GetXaxis()->SetTitle("Energy in Ch");
          PeakFit[2*i][4*j+1]->GetXaxis()->CenterTitle(true);
          PeakFit[2*i][4*j+1]->GetXaxis()->SetTitleSize(0.05);
          PeakFit[2*i][4*j+1]->GetXaxis()->SetLabelSize(0.05);
          PeakFit[2*i][4*j+1]->GetYaxis()->SetTitle("Energy in MeV");
          PeakFit[2*i][4*j+1]->GetYaxis()->CenterTitle(true);
          PeakFit[2*i][4*j+1]->GetYaxis()->SetTitleSize(0.05);
          PeakFit[2*i][4*j+1]->GetYaxis()->SetLabelSize(0.05);
      
          TF1 *fit_func = new TF1(Form("fit_func%02d_%02d", 2*i, 4*j+1), "[0]*x+[1]", 800, 1500);
          fit_func->SetParameters(1,0);
          PeakFit[2*i][4*j+1]->Fit(fit_func,"R");
          fit_func->Draw("same");
          double par0 = fit_func->GetParameter(0);;
          double err_par0 = fit_func->GetParError(0);
          double par1 = fit_func->GetParameter(1);;
          double err_par1 = fit_func->GetParError(1); 
          FileOutOdd<< setw(5) << 2*i <<setw(5)<< 4*j+1 <<setw(15)<< par0 <<"  "<<setw(15)<< err_par0 <<"  "<<setw(15)<< par1 <<"  "<<setw(15)<< err_par1<<endl; 
                  
          gPad->Modified();
          gPad->Update();
     //   getchar();
      
          c1->Print(Form("figures/odd/PeakFit_%02d_%02d.png", 2*i, 4*j+1));        
        }
        
        if(4*j+2<STRIPNUM)
        {
          PeakFit[2*i][4*j+2]->Draw("AP");
          PeakFit[2*i][4*j+2]->SetTitle(Form("Tele%02d_Strip%02d", 2*i, 4*j+2));
          PeakFit[2*i][4*j+2]->GetXaxis()->SetTitle("Energy in Ch");
          PeakFit[2*i][4*j+2]->GetXaxis()->CenterTitle(true);
          PeakFit[2*i][4*j+2]->GetXaxis()->SetTitleSize(0.05);
          PeakFit[2*i][4*j+2]->GetXaxis()->SetLabelSize(0.05);
          PeakFit[2*i][4*j+2]->GetYaxis()->SetTitle("Energy in MeV");
          PeakFit[2*i][4*j+2]->GetYaxis()->CenterTitle(true);
          PeakFit[2*i][4*j+2]->GetYaxis()->SetTitleSize(0.05);
          PeakFit[2*i][4*j+2]->GetYaxis()->SetLabelSize(0.05);
      
          TF1 *fit_func = new TF1(Form("fit_func%02d_%02d", 2*i, 4*j+2), "[0]*x+[1]", 800, 1500);
          fit_func->SetParameters(1,0);
          PeakFit[2*i][4*j+2]->Fit(fit_func,"R");
          fit_func->Draw("same");
          double par0 = fit_func->GetParameter(0);;
          double err_par0 = fit_func->GetParError(0);
          double par1 = fit_func->GetParameter(1);;
          double err_par1 = fit_func->GetParError(1); 
          FileOutEven<< setw(5) << 2*i <<setw(5)<< 4*j+2 <<setw(15)<< par0 <<"  "<<setw(15)<< err_par0 <<"  "<<setw(15)<< par1 <<"  "<<setw(15)<< err_par1<<endl; 
                  
          gPad->Modified();
          gPad->Update();
     //   getchar();
       
          c1->Print(Form("figures/even/PeakFit_%02d_%02d.png", 2*i, 4*j+2));   
        }     
      }   
    }           
  }
}
