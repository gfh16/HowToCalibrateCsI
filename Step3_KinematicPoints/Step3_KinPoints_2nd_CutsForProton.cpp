void CsIKinematicHistogramCutForProtons()
{
  const int FirstRun=4585;
  const int LastRun=4589;
  const double E_projectile=56.6; //MeV
  const int Z_beam=20;
  const int A_beam=48;

  std::string path_to_file (Form("output/NewGeo_HiRA_KinematicPlots_%4d_%4d_%2dCa+1H@%.1fAMeV.root",FirstRun,LastRun,A_beam,E_projectile));
  TFile * FileIn = new TFile(path_to_file.c_str());

  TFile * fileout = new TFile(Form("output/NewGeo_HiRA_KinematicPlotsCut_%4d_%4d_%2dCa+1H@%.1fAMeV.root",FirstRun,LastRun,A_beam,E_projectile), "UPDATE");

  TIter next(FileIn->GetListOfKeys());
  TKey *key;

  while ((key = (TKey*)next()))
  {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH2D")) continue;
    TH2D *hist = (TH2D*)key->ReadObj();

    std::string HistName(hist->GetName());
  //  if(HistName.find("DECal_ERaw")==std::string::npos) continue;


  std::string CutName;
  printf("Please Draw cut on protons\n");
  CutName.assign(HistName+Form("_Z%02d_A%02d",1,1));



    if(fileout->Get(CutName.c_str()) || CutName.empty()) continue; //cut already existing

    hist->Draw("colz");
    gPad->SetLogz(kTRUE);

    TCutG * mycut = (TCutG*)gPad->WaitPrimitive("CUTG");

    mycut->SetName(CutName.c_str());

    printf("%s cut created\n", CutName.c_str());
    printf("S - save the cut\nR - retry\nF - skip this cut\nD - delete a cut\nE - exit\n");
    char input;
    input=getchar();
    getchar();
    printf("you typed %c\n", input);
    if (input=='S' || input=='s')
    {
      fileout->WriteTObject(mycut, mycut->GetName());
      fileout->WriteTObject(hist, hist->GetName());
      printf ("%s cut saved to file\n", CutName.c_str());
    }
    else if (input == 'F' || input == 'f')
    {

    }
    else if (input == 'D' || input == 'd')
    {
      printf("Please type the cut to delete: \n");
      std::string CutToDelete;
      std::cin>>CutToDelete;
      CutToDelete.append(";*");
      fileout->Delete(CutToDelete.c_str());
      printf("deleted %s cut\n", CutToDelete.c_str());
      std::cin.get();
    }
    else if (input == 'E' || input == 'e')
    {
      printf("Goodbye\n");
      fileout->Close();
      return;
    }
  }
  fileout->Close();
  return;


}
