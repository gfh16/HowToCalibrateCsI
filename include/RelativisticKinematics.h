#ifndef RELATIVISTICKINEMATICS_H
#define RELATIVISTICKINEMATICS_H

class RelativisticKinematics
{
public:

  RelativisticKinematics();
  ~RelativisticKinematics();
  
  Double_t GetEnergyTwoBodyEjectile(Double_t polar_angle, Double_t E_Projectile, Double_t M_Projectile, Double_t M_Target, Double_t EStar_Projectile=0, Double_t EStar_target=0);
  Double_t GetEnergyTwoBodyRecoil(Double_t polar_angle, Double_t E_Projectile, Double_t M_Projectile, Double_t M_Target, Double_t EStar_Projectile=0, Double_t EStar_target=0);
  
};

#endif
