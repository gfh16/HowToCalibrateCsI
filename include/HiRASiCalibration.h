#ifndef HIRASICALIBRATION_h
#define HIRASICALIBRATION_h

typedef struct HiRASiCalibration_
{
  int numtel=-1;
  int numstrip;
  bool   FB;
  double intercept;
  double slope; 

} HiRASiCalibration;

#endif
