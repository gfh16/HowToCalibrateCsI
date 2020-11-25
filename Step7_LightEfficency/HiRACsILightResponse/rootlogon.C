{
  gROOT->ProcessLine(".L LISETools/nuclear_masses.cpp");
  gROOT->ProcessLine(".L LISETools/EnergyLossModule.cpp");
  gROOT->ProcessLine(".L HiRACsICalibration.cpp");
  
  gROOT->ProcessLine(".L VEDALOSS/libvedaloss.so");
  gROOT->ProcessLine(".L VEDALOSS/TLoss.cc");
}
