#ifndef HIRA_H
#define HIRA_H

#include <array>

#include "Vec3.h"

class HiRA {
private:
	const int numOfEF = 32;
	const int numOfEB = 32;
	const double totalWidthOfEF = 64.0; // mm
	const double totalWidthOfEB = 64.0; // mm
	const double widthPerStripOfEF = totalWidthOfEF / numOfEF; // mm
	const double widthPerStripOfEB = totalWidthOfEB / numOfEB; // mm

	int teleNum;
	Vec3 origin;
		// assume to be parallel to zHiRA !!doubtful
		// assume to be at the center of EF !!doubtful
		// assume to be measured from the point of interaction !!doubtful
	Vec3 xUnit, yUnit, zUnit;
		// A local coordinate system is set up for each HiRA as below:
		//  +-----------------+
		//  |        y        |
		//  |       /|\       |
		//  |        |        |
		//  |        |        |
		//  |        O----->x |
		//  |                 |
		//  |                 |
		//  |                 |
		//  +-----------------+   (facing Si detector; CsI behind)

public:
	// constructors
	HiRA();
	HiRA(int teleNum, std::array<Vec3, 4> romerArmData);

	//
	Vec3 stripNumToGlobalPos(int EF, int EB);

	// operators
	HiRA& operator = (const HiRA& hira);

	// get functions
	Vec3 get_origin();
	Vec3 get_xUnit();
	Vec3 get_yUnit();
	Vec3 get_zUnit();
};

#endif