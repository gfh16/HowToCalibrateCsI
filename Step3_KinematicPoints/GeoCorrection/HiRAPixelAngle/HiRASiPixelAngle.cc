#include "include/Vec3.h"
#include "src/Vec3.cc"
#include "include/HiRA.h"
#include "src/HiRA.cc"
#include "include/HiRAArray.h"
#include "src/HiRAArray.cc"

#include <iostream>
#include <array>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>

// suspected shift of beam position on the target
// inferred from I:/projects/hira/fanurs/2018Fall_CsILightResponse/KinematicsShiftOfBeamInMarch/14030C_camPic1.jpg
const Vec3 beamCenter(-0.92901, -2.33632, 0.0);
const std::array<Vec3, 4> beamCorners = { // not rectangular at all; just for error estimation
		Vec3(-6.59545, -6.84356, 0.0),
		Vec3(2.4328, -1.23363, 0.0),
		Vec3(2.76361, 8.34597, 0.0),
		Vec3(-4.6244, 1.06823, 0.0)};

int HiRASiPixelAngle() {
	auto t1 = std::chrono::high_resolution_clock::now();

	std::ofstream ff("./TXT/pixelAngle.dat");
	ff << "Tele EF EB theta(degree) phi(degree)" << std::endl;
	ff << std::fixed;

	std::ofstream ff_err("./TXT/pixelAngleWithError.dat");
	ff_err << "Tele EF EB theta(degree) thetaE(degree)   phi(degree) phiE(degree)" << std::endl;
	ff_err << std::fixed;
	
	HiRAArray hiraArray;
	Vec3 globalPos, correctedGlobalPos;
	for (int tele = 0; tele < 12; ++tele) {
		HiRA hira = hiraArray[tele];
		for (int EF = 0; EF < 32; ++EF)
		for (int EB = 0; EB < 32; ++EB) {
			globalPos = hira.stripNumToGlobalPos(EF, EB);

			/* account for shift in beam position on the target */
			correctedGlobalPos = globalPos - beamCenter;

			double theta = correctedGlobalPos.thetaDeg();
			double phi = correctedGlobalPos.phiDeg(360);
			ff << std::setw(sizeof("Tele")-1) << std::setprecision(0) << tele;
			ff << std::setw(sizeof("EF")) << EF;
			ff << std::setw(sizeof("EB")) << EB;
			ff << std::setw(sizeof("theta(degree)")) << std::setprecision(4) << theta;
			ff << std::setw(sizeof("phi(degree)")) << std::setprecision(3) << phi << std::endl;

			/* error estimation */
			double thetaE = 0.0;
			double phiE = 0.0;
			double weight;
			for (int i = 0; i < 4; ++i) {
				correctedGlobalPos = globalPos - beamCorners[i];
				switch (i) {
					case 0: weight = 1.0; break;
					case 1: weight = 0.8; break;
					case 2: weight = 0.5; break;
					case 3: weight = 0.5; break;
				}
				thetaE += weight * abs(correctedGlobalPos.thetaDeg() - theta);
				phiE += weight * abs(correctedGlobalPos.phiDeg(360) - phi);
			}
			thetaE /= 2.8;
			phiE /= 2.8;
			ff_err << std::setw(sizeof("Tele")-1) << std::setprecision(0) << tele;
			ff_err << std::setw(sizeof("EF")) << EF;
			ff_err << std::setw(sizeof("EB")) << EB;
			ff_err << std::setw(sizeof("theta(degree)")) << std::setprecision(4) << theta;
			ff_err << std::setw(sizeof("thetaE(degree)")) << std::setprecision(4) << thetaE;
			ff_err << "  ";
			ff_err << std::setw(sizeof("phi(degree)")) << std::setprecision(3) << phi;
			ff_err << std::setw(sizeof("phiE(degree)")) << std::setprecision(3) << phiE << std::endl;
		}
	}

	ff.close();
	ff_err.close();

	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Took "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms.\n";

	return 0;
}
