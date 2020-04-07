////////////////////////////////////////////////////////////////////
//
//	Georg Umlauf, (c) 2012
//
////////////////////////////////////////////////////////////////////

#include "quaternion.h"
#include "math.h"
#include <iostream>

Quaternion::Quaternion()
{
	for (int i=0; i<4; i++) x[i]=0;	
}

Quaternion::~Quaternion()
{
}

Quaternion::Quaternion(float s, float a, float b, float c) {
	x[0] = s;
	x[1] = a;
	x[2] = b;
	x[3] = c;
}

void Quaternion::setQuaternion(float quat[4])
{
	for (int i = 0; i<4; i++) x[i] = quat[i];
}

Quaternion Quaternion::getQuaternion() {
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion &quat) {
	Quaternion q;

	q.x[0] = x[0] * quat.x[0] - x[1] * quat.x[1] - x[2] * quat.x[2] - x[3] * quat.x[3];
	q.x[1] = x[0] * quat.x[1] + quat.x[0] * x[1] + x[2] * quat.x[3] - quat.x[2] * x[3];
	q.x[2] = x[0] * quat.x[2] + quat.x[0] * x[2] + x[3] * quat.x[1] - quat.x[3] * x[1];
	q.x[3] = x[0] * quat.x[3] + quat.x[0] * x[3] + x[1] * quat.x[2] - quat.x[1] * x[2];

	return q;
}

Quaternion Quaternion::operator*(const float &i) {
	Quaternion q;

	q.x[0] = x[0] * i;
	q.x[1] = x[1] * i;
	q.x[2] = x[2] * i;
	q.x[3] = x[3] * i;

	return q;
}

Quaternion Quaternion::operator*(const int &i) {
	Quaternion q;

	q.x[0] = x[0] * i;
	q.x[1] = x[1] * i;
	q.x[2] = x[2] * i;
	q.x[3] = x[3] * i;

	return q;
}

Quaternion Quaternion::operator+(const Quaternion &quat) {
	Quaternion q;

	q.x[0] = x[0] + quat.x[0];
	q.x[1] = x[1] + quat.x[1];
	q.x[2] = x[2] + quat.x[2];
	q.x[3] = x[3] + quat.x[3];

	return q;
}

Quaternion Quaternion::operator-(const Quaternion &quat) {
	Quaternion q;

	q.x[0] = x[0] - quat.x[0];
	q.x[1] = x[1] - quat.x[1];
	q.x[2] = x[2] - quat.x[2];
	q.x[3] = x[3] -	quat.x[3];

	return q;
}

void Quaternion::conjugate() {
	x[0] = x[0];
	x[1] = -x[1];
	x[2] = -x[2];
	x[3] = -x[3];

}

void Quaternion::normalize() {
	float d;

	d = sqrt(
		x[0] * x[0] +
		x[1] * x[1] +
		x[2] * x[2] +
		x[3] * x[3]);

	x[0] /= d;
	x[1] /= d;
	x[2] /= d;
	x[3] /= d;

}

Quaternion Quaternion::multiplicate(Quaternion p) {// q p q'
	Quaternion conjugatedQ;
	conjugatedQ = *this;
	conjugatedQ.conjugate();

	Quaternion res = (*this) * p * conjugatedQ;

	return res;
}

float Quaternion::dotProduct(Quaternion q) {
	return x[0]*q.x[0] + x[1]*q.x[1] + x[2]*q.x[2];
}

CVec4f Quaternion::getVector() {
	CVec4f vector;
	vector(0) = x[1];
	vector(1) = x[2];
	vector(2) = x[3];
	vector(3) = 0;

	return vector;
}

CVec3f Quaternion::getImaginary() {
	CVec3f imaginaryPart;
	imaginaryPart(0) = x[1];
	imaginaryPart(1) = x[2];
	imaginaryPart(2) = x[3];

	return imaginaryPart;
}