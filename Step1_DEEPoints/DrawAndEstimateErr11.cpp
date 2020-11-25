
void DrawAndEstimateErr()
{
   const int TelNum=12;
   const int StripNum=32;
   
   ifstream FileInOdd("figures/odd/FitParameters_Odd.dat");
   ifstream FileInEven("figures/even/FitParameters_Even.dat");
   
   //----- Read data of odd strips ------------------------
 
   double OddPar0[TelNum][StripNum]     = {{0}};
   double err_OddPar0[TelNum][StripNum] = {{0}};
   double OddPar1[TelNum][StripNum]     = {{0}}; 
   double err_OddPar1[TelNum][StripNum] = {{0}};
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
     LineStream >> OddPar0[telnum][stripnum] >> err_OddPar0[telnum][stripnum] >> OddPar1[telnum][stripnum] >> err_OddPar1[telnum][stripnum];
     cout<< telnum << setw(5) << stripnum << setw(15) << OddPar0[telnum][stripnum] << setw(15) << OddPar1[telnum][stripnum] << endl;
        
   }  
 /*
     //----- Read data of even strips ------------------------
   double EvenPar0[TelNum][StripNum]     = {{0}};
   double err_EvenPar0[TelNum][StripNum] = {{0}};
   double EvenPar1[TelNum][StripNum]     = {{0}}; 
   double err_EvenPar1[TelNum][StripNum] = {{0}};
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
     LineStream >> EvenPar0[telnum][stripnum] >> err_EvenPar0[telnum][stripnum] >> EvenPar1[telnum][stripnum] >> err_EvenPar1[telnum][stripnum];   
   }
*/   

}



