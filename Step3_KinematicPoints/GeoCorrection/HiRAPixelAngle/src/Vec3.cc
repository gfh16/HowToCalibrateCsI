#include "../include/Vec3.h"

#include <iostream>
#include <cmath>

/***PRIVATE***/


/***PUBLIC***/

// constructors
Vec3::Vec3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// operators
double& Vec3::operator [] (int i) {
	switch(i) {
		case 0: return this->x;
		case 1: return this->y;
		case 2: return this->z;
		default: printf("ERROR: index invalid in double Vec3::operator() (int i)");
	}

	return this->x;
}

bool Vec3::operator == (const Vec3&v) const {
	return (v.x == this->x && v.y == this->y && v.z == this->z);
}

bool Vec3::operator != (const Vec3& v) const {
	return !(*this == v);
}

Vec3 Vec3::operator - () {
	return Vec3(-this->x, -this->y, -this->z);
}

Vec3& Vec3::operator += (const Vec3& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vec3& Vec3::operator -= (const Vec3& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vec3& Vec3::operator *= (const double scalar) {
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

Vec3& Vec3::operator /= (const double scalar) {
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

Vec3 operator + (const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

Vec3 operator - (const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

Vec3 operator * (const Vec3& v, const double scalar) {
	return Vec3(v.x*scalar, v.y*scalar, v.z*scalar);
}

Vec3 operator * (const double scalar, const Vec3& v) {
	return v * scalar;
}

Vec3 operator / (const Vec3& v, const double scalar) {
	return Vec3(v.x/scalar, v.y/scalar, v.z/scalar);
}

// some linear algebra
double Vec3::norm() const {
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vec3::normalize(double goalNorm) {
	if (norm() != 0.0) *this *= goalNorm / norm();
}

double dot(const Vec3& v1, const Vec3& v2) {
	return v1.x*v2.x, v1.y*v2.y, v1.z*v2.z;
}

Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return Vec3(
			v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x
		);
}

double angleBetween(const Vec3& v1, const Vec3& v2) {
	double normProd = v1.norm() * v2.norm();
	if (normProd == 0.0) return 0.0;
	else return acos(dot(v1, v2) / normProd);
}

double angleDegBetween(const Vec3& v1, const Vec3& v2) {
	return angleBetween(v1, v2) * 180/M_PI;
}

double distanceBetween(const Vec3& v1, const Vec3& v2) {
	return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2) + pow(v1.z-v2.z, 2));
}

double determinant(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
	double result = 0.0;
	result += v1.x * v2.y * v3.z;
	result += v2.x * v3.y * v1.z;
	result += v3.x * v1.y * v2.z;
	result -= v3.x * v2.y * v1.z;
	result -= v1.x * v3.y * v2.z;
	result -= v2.x * v1.y * v3.z;
	return result;
}

// spherical coordinates
double Vec3::r() {
	return norm();
}

double Vec3::theta() {
	return (norm() == 0) ? 0.0 : acos(this->z / norm());
}

double Vec3::thetaDeg() {
	return theta() * 180.0/M_PI;
}

double Vec3::phi(double splittingDeg, char direction) {
	if (splittingDeg == 180.0 && direction == '-') return atan2(this->y, this->x);
	else if (this->x == 0.0 && this->y == 0.0) return 0.0;
	else {
		double inclusive = splittingDeg * M_PI/180;
		double low = (direction == '+') ? splittingDeg : splittingDeg-360;
		low *= M_PI/180;
		double upp = low + 2*M_PI;

		double atan2Rad = atan2(this->y, this->x);
		if (atan2Rad > low && atan2Rad < upp) return atan2Rad;
		else if (atan2Rad < low) return atan2Rad + 2*M_PI;
		else if (atan2Rad > upp) return atan2Rad - 2*M_PI;
		else return inclusive;
	}
}

double Vec3::phiDeg(double splittingDeg, char direction) {
	return phi(splittingDeg, direction) * 180/M_PI;
}

// others
// Vec3 make_Vec3(double x, double y, double z) {
// 	return Vec(x, y, z);
// }
