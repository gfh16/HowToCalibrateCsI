#ifndef HIRAARRAY_H
#define HIRAARRAY_H

#include "../include/HiRA.h"

#include <string>
#include <array>

#include "Vec3.h"

std::string romerArmDataFileName = "TXT/romerArmData.detector";

class HiRAArray {
private:
	const int numOfHiRA = 12;
	std::array<HiRA, 12> arrayOfHiRAs;


public:
	// constructors
	HiRAArray();

	std::array<Vec3, 4> getRomerArmData(int hira, std::string inputFileName=romerArmDataFileName);
	
	//	operators
	HiRA& operator [] (int teleNum);
};

#endif