#include "../include/Vec3.h"
#include "../include/HiRA.h"

/***PRIVATE***/


/***PUBLIC***/

// constructors
HiRA::HiRA() {}

HiRA::HiRA(int teleNum, std::array<Vec3, 4> romerArmData) {
	// Romer arm's convention:
	//  +----[0]----+
	//  |           |
	//  |          [1]
	//  |           |
	// [3]          |
	//  |           |
	//  +----[2]----+   (facing Si detector; CsI behind)
	//
	// aliases: [0]-A, [1]-B, [2]-C, [3]-D

	for (int i = 0; i < 4; ++i) origin += romerArmData[i];
	origin /= 4.0;
	zUnit = origin; // !!doubtful
	Vec3 vUpright = romerArmData[0] - romerArmData[2]; // assume to be parallel to the vertical side of HiRA
	yUnit = vUpright;
	xUnit = cross(zUnit, yUnit);

	// Vec3 vSlanted = romerArmData[1] - romerArmData[3];

	xUnit.normalize();
	yUnit.normalize();
	zUnit.normalize();
}

//
Vec3 HiRA::stripNumToGlobalPos(int EF, int EB) {
	//     EF=0
	//      +-------------+
	//      |             |
	//      |             |
	//      |             |
	//      |             |
	//      |             |
	//      |             |
	// EB=0 +-------------+ EB=0   (facing Si detector; CsI behind)
	//     EF=0

	double posX = (EF + 0.5 )*widthPerStripOfEF - 0.5*totalWidthOfEF;
	double posY = (EB + 0.5 )*widthPerStripOfEF - 0.5*totalWidthOfEF;

	return origin + posX*xUnit + posY*yUnit;
}

// operators
HiRA& HiRA::operator = (const HiRA& hira) {
	this->origin = hira.origin;
	this->xUnit = hira.xUnit;
	this->yUnit = hira.yUnit;
	this->zUnit = hira.zUnit;
	return *this;
}

// get functions
Vec3 HiRA::get_origin() {return origin;}
Vec3 HiRA::get_xUnit() {return xUnit;}
Vec3 HiRA::get_yUnit() {return yUnit;}
Vec3 HiRA::get_zUnit() {return zUnit;}