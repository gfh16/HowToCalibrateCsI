#include "../include/Vec3.h"
#include "../include/HiRA.h"
#include "../include/HiRAArray.h"

#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


/***PRIVATE***/
std::array<Vec3, 4> HiRAArray::getRomerArmData(int teleNum, std::string inputFileName) {
	std::ifstream inputFile(inputFileName.c_str());
	std::array<Vec3, 4> result;

	std::string line_buff, buff;
	int hira_buff;
	std::stringstream ss_buff;
	std::string goalLine = "HiRA " + std::to_string(teleNum);
	while (inputFile.is_open() && !inputFile.eof()) {
		std::getline(inputFile, line_buff);
		if (line_buff == goalLine) {
			// getting coordinates of A, B, C, D
			for (int i = 0; i < 4; ++i) {
				double x, y, z;
				std::getline(inputFile, line_buff);
				ss_buff.clear();
				ss_buff.str(line_buff);
				ss_buff >> buff >> x >> y >> z;
				result[i] = Vec3(x, y, z);
			}
			inputFile.close();
			break;
		}
	}

	return result;
}

/***PUBLIC***/

// constructors
HiRAArray::HiRAArray() {
	for (int teleNum = 0; teleNum < numOfHiRA; ++teleNum) {
		std::array<Vec3, 4> romerArmData = getRomerArmData(teleNum);
		HiRA hira(teleNum, romerArmData);
		arrayOfHiRAs[teleNum] = hira;
	}
}

// operators
HiRA& HiRAArray::operator [] (int teleNum) {
	return arrayOfHiRAs[teleNum];
}
