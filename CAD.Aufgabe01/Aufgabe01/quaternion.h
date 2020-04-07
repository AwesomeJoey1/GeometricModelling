////////////////////////////////////////////////////////////////////
//
//	Georg Umlauf, (c) 2012
//
////////////////////////////////////////////////////////////////////
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "vec.h"

class Quaternion {
private:
	float x[4];

public:
	// constructors/destructors
	Quaternion();									// default constructor
	Quaternion(float s, float a, float b, float c);
	~Quaternion();

	Quaternion operator*(const Quaternion&);
	Quaternion operator*(const float&);
	Quaternion operator*(const int&);
	Quaternion operator+(const Quaternion&);
	Quaternion operator-(const Quaternion&);


	void setQuaternion(float quat[4]);
	Quaternion getQuaternion();
	void conjugate();
	void normalize();
	Quaternion multiplicate(Quaternion p);
	float dotProduct(Quaternion q);
	CVec4f getVector();
	CVec3f getImaginary();
};


#endif