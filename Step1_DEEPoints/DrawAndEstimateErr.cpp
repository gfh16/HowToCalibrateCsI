
void DrawAndEstimateErr()
{
   const int TelNum=12;
   const int StripNum=32;
   
   ifstream FileInOdd("figures/odd/FitParameters_Odd.dat");
   ifstream FileInEven("figures/even/FitParameters_Even.dat");
   
   //----- Read data of odd strips ------------------------
   int npoints_odd[TelNum][StripNum];
   for(int i=0; i<TelNum; i++)
   {
     for(int j=0; j<StripNum; j++)
     {
       npoints_odd[i][j]=0;
     }
   }
   double OddPar0[TelNum][StripNum][100];
   double err_OddPar0[TelNum][StripNum][100];
   double OddPar1[TelNum][StripNum][100]; 
   double err_OddPar1[TelNum][StripNum][100];
   while(FileInOdd.is_open() && !FileInOdd.eof())
   {
     std::string LineRead;
     std::getline(FileInOdd, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int stripnum;
     
     LineStream >> telnum >> stripnum;
     LineStream >> OddPar0[telnum][stripnum][npoints_odd[telnum][stripnum]] >> err_OddPar0[telnum][stripnum][npoints_odd[telnum][stripnum]] >> OddPar1[telnum][stripnum][npoints_odd[telnum][stripnum]] >> err_OddPar1[telnum][stripnum][npoints_odd[telnum][stripnum]];
     if(OddPar0[telnum][stripnum][npoints_odd[telnum][stripnum]]==0) continue; 
 
 //cout<< telnum << setw(5) << stripnum << setw(15) << OddPar0[telnum][stripnum][npoints_odd[telnum][stripnum]] << setw(15) << OddPar1[telnum][stripnum][npoints_odd[telnum][stripnum]] << endl;
   
     npoints_odd[telnum][stripnum]++;
     
         
   }
   
     //----- Read data of even strips ------------------------
   int npoints_even[TelNum][StripNum];
   for(int i=0; i<TelNum; i++)
   {
     for(int j=0; j<StripNum; j++)
     {
       npoints_even[i][j]=0;
     }
   }
   double EvenPar0[TelNum][StripNum][100];
   double err_EvenPar0[TelNum][StripNum][100];
   double EvenPar1[TelNum][StripNum][100]; 
   double err_EvenPar1[TelNum][StripNum][100];
   while(FileInEven.is_open() && !FileInEven.eof())
   {
     std::string LineRead;
     std::getline(FileInEven, LineRead);

     if(LineRead.empty()) continue;
     if(LineRead.find('*')==0) continue;

     std::istringstream LineStream(LineRead);
     
     int telnum;
     int stripnum;
     
     LineStream >> telnum >> stripnum;
     LineStream >> EvenPar0[telnum][stripnum][npoints_even[telnum][stripnum]] >> err_EvenPar0[telnum][stripnum][npoints_even[telnum][stripnum]] >> EvenPar1[telnum][stripnum][npoints_even[telnum][stripnum]] >> err_EvenPar1[telnum][stripnum][npoints_even[telnum][stripnum]];
     if(EvenPar0[telnum][stripnum][npoints_even[telnum][stripnum]]==0) continue;
     
     npoints_even[telnum][stripnum]++;
     
          
   }

   //------- To estimate the errors for odd strips ------------
  int Nsamples_odd[TelNum][StripNum];
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<StripNum; j++)
    {
      Nsamples_odd[i][j]=0;
    }
  }
  
  TGraph * graph1[TelNum][StripNum]; 
  TCanvas * c1=new TCanvas("c1","", 800, 600);
  
  double E_odd[TelNum][StripNum][100];
  double err_E_odd[TelNum][StripNum][100];
  double Relative_err_odd[TelNum][StripNum][100];
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<StripNum; j++)
    {
      //----- for odd strips -------------------
      if(npoints_odd[i][j]!=0)
      {
        //---- The range of ADCs for silicon : 1200 CH ----------      
        for(int k=0; k<12000; k+=200)
        {
           E_odd[i][j][Nsamples_odd[i][j]]= OddPar0[i][j][0] * k + OddPar1[i][j][0];
           if( E_odd[i][j][Nsamples_odd[i][j]]<0 )  continue;          
           err_E_odd[i][j][Nsamples_odd[i][j]] = sqrt( (k*k) * (err_OddPar0[i][j][0]) * (err_OddPar0[i][j][0]) + (err_OddPar1[i][j][0]) * (err_OddPar1[i][j][0]));
           Relative_err_odd[i][j][Nsamples_odd[i][j]] = err_E_odd[i][j][Nsamples_odd[i][j]] / E_odd[i][j][Nsamples_odd[i][j]];
          
           Nsamples_odd[i][j]++;         
        }       
        graph1[i][j] = new TGraph(Nsamples_odd[i][j], E_odd[i][j], Relative_err_odd[i][j]);  
        graph1[i][j]->SetTitle(Form("Relative_Error%02d_%02d", i, j));
        graph1[i][j]->GetXaxis()->SetLabelSize(0.05);
        graph1[i][j]->GetXaxis()->SetTitleSize(0.05);
        graph1[i][j]->GetXaxis()->SetTitle("E (MeV)");
        graph1[i][j]->GetXaxis()->CenterTitle(1);
        graph1[i][j]->GetYaxis()->SetLabelSize(0.05);
        graph1[i][j]->GetYaxis()->SetTitleSize(0.05);
        graph1[i][j]->GetYaxis()->SetTitle("#sigma_{E}/E");
        graph1[i][j]->GetYaxis()->CenterTitle(1);
        graph1[i][j]->SetMarkerStyle(20);
        graph1[i][j]->SetMarkerColor(kRed);
        graph1[i][j]->Draw("AP");
      
        gPad->Modified();
        gPad->Update();
  //    getchar();
        
        c1->Print(Form("figures/odd_err/RelativeError_%02d_%02d.png", i, j));                     
      }            
    }   
  }


  //------- To estimate the errors for even strips ------------
  int Nsamples_even[TelNum][StripNum];
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<StripNum; j++)
    {
      Nsamples_even[i][j]=0;
    }
  }
  
  TGraph * graph2[TelNum][StripNum]; 
  TCanvas * c2=new TCanvas("c2","", 800, 600);
  
  double E_even[TelNum][StripNum][100];
  double err_E_even[TelNum][StripNum][100];
  double Relative_err_even[TelNum][StripNum][100];
  for(int i=0; i<TelNum; i++)
  {
    for(int j=0; j<StripNum; j++)
    {
      //----- for even strips -------------------
      if(npoints_even[i][j]!=0)
      {
        //---- The range of ADCs for silicon : 1200 CH ----------      
        for(int k=0; k<12000; k+=200)
        {
           E_even[i][j][Nsamples_even[i][j]]= EvenPar0[i][j][0] * k + EvenPar1[i][j][0];
           if( E_even[i][j][Nsamples_even[i][j]]<0 )  continue;          
           err_E_even[i][j][Nsamples_even[i][j]] = sqrt( (k*k) * (err_EvenPar0[i][j][0]) * (err_EvenPar0[i][j][0]) + (err_EvenPar1[i][j][0]) * (err_EvenPar1[i][j][0]));
           Relative_err_even[i][j][Nsamples_even[i][j]] = err_E_even[i][j][Nsamples_even[i][j]] / E_even[i][j][Nsamples_even[i][j]];
          
           Nsamples_even[i][j]++;         
        }       
        graph2[i][j] = new TGraph(Nsamples_even[i][j], E_even[i][j], Relative_err_even[i][j]);  
        graph2[i][j]->SetTitle(Form("Relative_Error%02d_%02d", i, j));
        graph2[i][j]->GetXaxis()->SetLabelSize(0.05);
        graph2[i][j]->GetXaxis()->SetTitleSize(0.05);
        graph2[i][j]->GetXaxis()->SetTitle("E (MeV)");
        graph2[i][j]->GetXaxis()->CenterTitle(1);
        graph2[i][j]->GetYaxis()->SetLabelSize(0.05);
        graph2[i][j]->GetYaxis()->SetTitleSize(0.05);
        graph2[i][j]->GetYaxis()->SetTitle("#sigma_{E}/E");
        graph2[i][j]->GetYaxis()->CenterTitle(1);
        graph2[i][j]->SetMarkerStyle(20);
        graph2[i][j]->SetMarkerColor(kRed);
        graph2[i][j]->Draw("AP");
      
        gPad->Modified();
        gPad->Update();
  //    getchar();
        
        c2->Print(Form("figures/even_err/RelativeError_%02d_%02d.png", i, j));                     
      }
    }
  }
}
