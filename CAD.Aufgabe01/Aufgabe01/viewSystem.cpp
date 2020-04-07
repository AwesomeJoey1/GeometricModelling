////////////////////////////////////////////////////////////////////
//
//	Georg Umlauf, (c) 2012
//
////////////////////////////////////////////////////////////////////


#include "viewSystem.h"
#include <iostream>

viewSystem::viewSystem()
{
	RotMode = VIEW_QUATERNION_MODE;
	//RotMode = VIEW_MATRIX_MODE;
}

viewSystem::viewSystem(const float eye[4], const float dir[4], const float up[4], float f)
{
	F = f;

	EyePoint.setData(eye);
	ViewDir .setData(dir);
	ViewUp  .setData(up);

	RotMode = VIEW_QUATERNION_MODE;
	RotMode = VIEW_MATRIX_MODE;
}

viewSystem::viewSystem(const CVec4f eye, const CVec4f dir, const CVec4f up, float f)
{
	F        = f;
	EyePoint = eye;
	ViewDir  = dir;
	ViewUp   = up;
	RotMode  = VIEW_QUATERNION_MODE;
	//RotMode = VIEW_MATRIX_MODE;
}

viewSystem::~viewSystem()
{
}

void viewSystem::setData(const float eye[4], const float dir[4], const float up[4], float f)
{
	viewSystem buf(eye,dir,up,f);
	*this = buf;
}

void viewSystem::setData(const CVec4f eye, const CVec4f dir, const CVec4f up, float f)
{
	viewSystem buf(eye,dir,up,f);
	*this = buf;
}

void viewSystem::setMode(MatrixMode mode)
{
	RotMode = mode;
}
void viewSystem::Zoom(float f)
{
	F+=f;
}

void viewSystem::lerp(Quaternion a, Quaternion b, float t) {
	Quaternion quat;

	//a.normalize();
	//b.normalize();

	quat = a*(1 - t) + b*t;
	quat.normalize();

	Rotate(quat);
}

void viewSystem::slerp(Quaternion imagQuat1, Quaternion imagQuat2, float t) {
	imagQuat1.normalize();
	imagQuat2.normalize();

	float dot = imagQuat1.dotProduct(imagQuat2);

	float theta_0 = acos(dot);
	float theta = theta_0 * t;

	Quaternion quat = imagQuat2 - imagQuat1*dot;

	quat.normalize();

	Rotate(imagQuat1*cos(theta) + quat*sin(theta));

}

void viewSystem::nlerp(Quaternion imagQuat1, Quaternion imagQuat2, float t) {
	imagQuat1.normalize();
	imagQuat2.normalize();

	float dot = imagQuat1.dotProduct(imagQuat2);

	float theta_0 = acos(dot);
	float theta = theta_0 * t;

	Quaternion quat = imagQuat2 - imagQuat1*dot;

	quat.normalize();

	Quaternion quat2 = imagQuat1*cos(theta) + quat*sin(theta);
	quat2.normalize();

	Rotate(quat2);
}

void viewSystem::RotateX(float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		{
			CMat4f Rot;
			float c = cos(angle);
			float s = sin(angle);

			Rot(1,1) = c; Rot(1,2) = -s; 
			Rot(2,1) = s; Rot(2,2) =  c;

			Rotate(Rot);
			
			break;
		}
	case VIEW_QUATERNION_MODE: 
		{
			// AUFGABE02
			float q[4];
			Quaternion quat;

			float vectorValue = sin(angle/2);
			float scalarValue = cos(angle/2);
			CVec3f n;
			n(0) = 1;
			n(1) = 0;
			n(2) = 0;
			n *= vectorValue;

			q[0] = scalarValue;
			q[1] = n(0);
			q[2] = n(1);
			q[3] = n(2);

			quat.setQuaternion(q);
			Rotate(quat);
			break;
		}
	}	
}

void viewSystem::RotateY(float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		{
			CMat4f Rot;
			float c = cos(angle);
			float s = sin(angle);

			Rot(0,0) =  c; Rot(0,2) = s; 
			Rot(2,0) = -s; Rot(2,2) = c; 
			
			Rotate(Rot);break;
		}
	case VIEW_QUATERNION_MODE: 
		{
			// AUFGABE02
			float q[4];
			Quaternion quat;

			float vectorValue = sin(angle/2);
			float scalarValue = cos(angle/2);
			CVec3f n;
			n(0) = 0;
			n(1) = 1;
			n(2) = 0;
			n *= vectorValue;

			q[0] = scalarValue;
			q[1] = n(0);
			q[2] = n(1);
			q[3] = n(2);

			quat.setQuaternion(q);
			Rotate(quat);
			break;
		}
	}	
}

void viewSystem::RotateZ(float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		{
			CMat4f Rot;
			float c = cos(angle);
			float s = sin(angle);

			Rot(0,0) = c; Rot(0,1) = -s; 
			Rot(1,0) = s; Rot(1,1) =  c; 
			
			Rotate(Rot);
			break;
		}
	case VIEW_QUATERNION_MODE: 
		{
			// AUFGABE02
			float q[4];
			Quaternion quat;

			float vectorValue = sin(angle/2);
			float scalarValue = cos(angle/2);
			CVec3f n;
			n(0) = 0;
			n(1) = 0;
			n(2) = 1;
			n *= vectorValue;

			q[0] = scalarValue;
			q[1] = n(0);
			q[2] = n(1);
			q[3] = n(2);

			quat.setQuaternion(q);
			Rotate(quat);
			break;
		}
	}	
}

void viewSystem::RotateDir(float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		ViewUp = RotationMatrix(ViewDir,angle)*ViewUp;
		break;
	case VIEW_QUATERNION_MODE:
		{
			// AUFGABE02
			float axis[4], view[4];
			Quaternion quat, viewQuat;

			axis[0] = cos(angle / 2);
			axis[1] = ViewDir(0) * sin(angle/2);
			axis[2] = ViewDir(1) * sin(angle/2);
			axis[3] = ViewDir(2) * sin(angle/2);
		
			view[0] = 0;
			view[1] = ViewUp(0);
			view[2] = ViewUp(1);
			view[3] = ViewUp(2);

			quat.setQuaternion(axis);
			viewQuat.setQuaternion(view);

			viewQuat = quat.multiplicate(viewQuat);

			ViewUp = viewQuat.getVector();
			break;
		}
	}	
	ViewUp.normalize();
}

void viewSystem::RotateUp(float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		ViewDir = RotationMatrix(ViewUp,angle)*ViewDir;
		break;
	case VIEW_QUATERNION_MODE: 
		{
			// AUFGABE02
			float axis[4], view[4];
			Quaternion quat, dirQuat;

			axis[0] = cos(angle / 2);
			axis[1] = ViewUp(0) * sin(angle / 2);
			axis[2] = ViewUp(1) * sin(angle / 2);
			axis[3] = ViewUp(2) * sin(angle / 2);

			view[0] = 0;
			view[1] = ViewDir(0);
			view[2] = ViewDir(1);
			view[3] = ViewDir(2);



			quat.setQuaternion(axis);
			dirQuat.setQuaternion(view);


			dirQuat = quat.multiplicate(dirQuat);

			ViewDir = dirQuat.getVector();
			break;
		}
	}	
	ViewDir.normalize();
}

void viewSystem::RotateHor(float angle)
{
	ViewHor = ViewDir.cross(ViewUp);
	ViewHor.normalize();
	
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		{
			CMat4f Rot = RotationMatrix(ViewHor,angle);
			ViewUp     = Rot*ViewUp;  
			ViewDir    = Rot*ViewDir; 

			break;
		}
	case VIEW_QUATERNION_MODE: 
		{
			// AUFGABE02
			Quaternion quat, up, dir;
			float q[4], v1[4], v2[4];

			float vectorValue = sin(angle / 2);
			float scalarValue = cos(angle / 2);

			v1[0] = 0;
			v1[1] = ViewUp(0);
			v1[2] = ViewUp(1);
			v1[3] = ViewUp(2);

			v2[0] = 0;
			v2[1] = ViewDir(0);
			v2[2] = ViewDir(1);
			v2[3] = ViewDir(2);

			CVec3f horMult = ViewHor * vectorValue;
			q[0] = scalarValue;
			q[1] = horMult(0);
			q[2] = horMult(1);
			q[3] = horMult(2);

			up.setQuaternion(v1);
			dir.setQuaternion(v2);
			quat.setQuaternion(q);

			up = quat. multiplicate(up);
			dir = quat.multiplicate(dir);

			ViewUp = up.getVector();
			ViewDir = dir.getVector();

			break;
		}
	}
	ViewUp .normalize();
	ViewDir.normalize();
}

void viewSystem::Rotate(CMat4f mat)
{
	EyePoint = mat * EyePoint;
	ViewDir  = mat * ViewDir;
	ViewUp   = mat * ViewUp;

	ViewDir.normalize();
	ViewUp .normalize();
}

void viewSystem::Rotate(Quaternion quat) 
{
	// Aufgabe 2
	Quaternion eye(0, EyePoint(0), EyePoint(1), EyePoint(2));
	Quaternion dir(0, ViewDir(0), ViewDir(1), ViewDir(2));
	Quaternion up(0, ViewUp(0), ViewUp(1), ViewUp(2));
	
	eye = quat.multiplicate(eye);
	up = quat.multiplicate(up);
	dir = quat.multiplicate(dir);

	EyePoint = eye.getVector();
	ViewUp = up.getVector();
	ViewDir = dir.getVector();
}

void viewSystem::Rotate(CVec4f axis, float angle)
{
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 	
	case VIEW_MATRIX_MODE:  
		Rotate(RotationMatrix(axis,angle));
		break;
	case VIEW_QUATERNION_MODE: 
		// AUFGABE02
		Quaternion quat;
		float q[4];
		
		float scalarValue = cos(angle) / 2;
		float vectorValue = sin(angle) / 2;
		axis *= vectorValue;

		q[0] = scalarValue;
		q[1] = axis(0);
		q[2] = axis(1);
		q[3] = axis(2);

		quat.setQuaternion(q);

		Rotate(quat);
		break;
	}
}

void viewSystem::Translate(CVec4f vec)
{
	EyePoint += vec;
}

CVec4f viewSystem::Project(CVec4f Point)
{	// central projection of Point
	CMat4f M;
	M(2,2) = 0.0;
	M(3,2) = -(1/F);
	Point  = M*(Point*(1/(1-Point(2)/F)));	// re-normalization
	return Point;
}

CMat4f viewSystem::getTransform1()
{
	CMat4f M; 
	// AUFGABE01

	M = Inverse(getTransform2());

	return M;
}

CMat4f viewSystem::getTransform2()
{
	CMat4f M;
	ViewHor = ViewDir.cross(ViewUp);

	// AUFGABE01

	M(0, 0) = ViewHor(0);
	M(0, 1) = ViewUp(0);
	M(0, 2) = ViewDir(0);
	M(0, 3) = -EyePoint(0);
	M(1, 0) = ViewHor(1);
	M(1, 1) = ViewUp(1);
	M(1, 2) = ViewDir(1);
	M(1, 3) = -EyePoint(1);
	M(2, 0) = ViewHor(2);
	M(2, 1) = ViewUp(2);
	M(2, 2) = ViewDir(2);
	M(2, 3) = -EyePoint(2);
	M(3, 0) = 0;
	M(3, 1) = 0;
	M(3, 2) = 0;
	M(3, 3) = 1;

	return M;
}

CMat4f viewSystem::RotationMatrix(CVec4f axis, float angle)
{
	CMat4f Rot;
	
	switch (RotMode) {
	case VIEW_FORMULA_MODE: 
		{
			float c = cos(angle);
			float s = sin(angle);

			Rot(0,0) = axis(0)*axis(0)*(1-c) +         c; 
			Rot(0,1) = axis(0)*axis(1)*(1-c) - axis(2)*s; 
			Rot(0,2) = axis(0)*axis(2)*(1-c) + axis(1)*s; 
			Rot(1,0) = axis(1)*axis(0)*(1-c) + axis(2)*s;
			Rot(1,1) = axis(1)*axis(1)*(1-c) +         c;
			Rot(1,2) = axis(1)*axis(2)*(1-c) - axis(0)*s;
			Rot(2,0) = axis(2)*axis(0)*(1-c) - axis(1)*s; 
			Rot(2,1) = axis(2)*axis(1)*(1-c) + axis(0)*s; 
			Rot(2,2) = axis(2)*axis(2)*(1-c) +         c;
		
			break;
		}
	case VIEW_MATRIX_MODE: 
		{
			float d = sqrt(axis(0)*axis(0)+axis(1)*axis(1));
			float a = axis(0)/d;
			float b = axis(1)/d;

			CMat4f Rot1;
			if (d) {
				Rot1(0,0) = a; Rot1(1,0) = -b;
				Rot1(0,1) = b; Rot1(1,1) =  a;
			}

			CMat4f Rot2;
			Rot2(0,0) =  axis(2); Rot2(2,0) =  d;
			Rot2(0,2) = -d;       Rot2(2,2) =  axis(2);

			CMat4f Rot3;
			Rot3(0,0) =  cos(angle); Rot3(1,0) =  sin(angle);
			Rot3(0,1) = -sin(angle); Rot3(1,1) =  cos(angle);
	
			CMat4f Rot4(Rot2);
			Rot4(2,0) = Rot2(0,2); Rot4(0,2) = Rot2(2,0);

			CMat4f Rot5(Rot1);
			Rot5(1,0) = Rot1(0,1); Rot5(0,1) = Rot1(1,0); 
	
			Rot = Rot5*Rot4*Rot3*Rot2*Rot1;
			break;
		}
	case VIEW_QUATERNION_MODE:
		std::cerr << "Error in rotation mode: For quaternions no rotation matrix required.\n";
		break;
	}
	
	return Rot;
}

CMat4f viewSystem::Inverse(CMat4f M)
// Berechnet die Inverse einer 4x4 Matrix M der Art 
//             | A a |
//             | 0 1 |
// mit einer orthonormalen 3x3 Matrix A. 
// Die Inverse ist dann gegeben durch
//             | A^T -A^t*a |
//             |  0     1   |
{
	float Mat[4][4];
	CVec4f a;
	for (int i=0; i<4; i++) for (int j=0; j<4; j++) Mat[i][j]=M(i,j);
	for (int i=0; i<3; i++) { Mat[i][3]=0; a(i)=M(i,3); }
	for (int i=0; i<3; i++) for (int j=0; j<i; j++) { float x=Mat[i][j]; Mat[i][j]=Mat[j][i]; Mat[j][i]=x; }
	CMat4f tmp(Mat);
	a = tmp*a;
	for (int i=0; i<3; i++) tmp(i,3)=-a(i);

	return tmp;
}
