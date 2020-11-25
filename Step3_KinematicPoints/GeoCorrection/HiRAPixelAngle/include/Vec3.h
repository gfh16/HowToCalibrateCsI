#ifndef VEC3_H
#define VEC3_H

class Vec3 {
private:
	double x, y, z;

public:
	// constructors
	Vec3(double x=0.0, double y=0.0, double z=0.0);

	// operators
	double& operator [] (int i);
	bool operator == (const Vec3& v) const;
	bool operator != (const Vec3& v) const;
	Vec3 operator - ();
	Vec3& operator += (const Vec3& v);
	Vec3& operator -= (const Vec3& v);
	Vec3& operator *= (const double scalar);
	Vec3& operator /= (const double scalar);
	friend Vec3 operator + (const Vec3&, const Vec3&);
	friend Vec3 operator - (const Vec3&, const Vec3&);
	friend Vec3 operator * (const Vec3&, const double);
	friend Vec3 operator * (const double, const Vec3&);
	friend Vec3 operator / (const Vec3&, const double);

	// some linear algebra
	double norm() const;
	void normalize(double goalNorm=1.0);
	friend double dot(const Vec3&, const Vec3&);
	friend Vec3 cross(const Vec3&, const Vec3&);
	friend double angleBetween(const Vec3&, const Vec3&);
	friend double angleDegBetween(const Vec3&, const Vec3&);
	friend double distanceBetween(const Vec3&, const Vec3&);
	friend double determinant(const Vec3&, const Vec3&, const Vec3&);

	// spherical coordinates
	double r(); // radial distance
	double theta(); // polar angle
	double thetaDeg();
	double phi(double splittingDeg=180, char direction='-'); // azimuthal angle
	double phiDeg(double splittingDeg=180, char direction='-');

	// others
	// friend Vec3 make_Vec3(double x, double y, double z);
};

#endif