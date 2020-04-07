#pragma once
#include <QtOpenGL/QGLWidget>
#include <vector>
#include "points.h"
using namespace std;

class Bezier
{
private:
	float len(QPointF p_point);
	QList<QPointF> controlPoints;
	QPointF getMaxSecDeriv(QList<QPointF> pointlist);
	QList<QPointF> intersectionPoints;
	QList<Points> selfIntersectionPoints;


	bool boundingCut(QList<QPointF>* curve1, QList<QPointF>* curve2);
	QPointF getMin(QList<QPointF>* curvePoints);
	QPointF getMax(QList<QPointF>* curvePoints);
	void printVector(vector<vector<QPointF>>* vector, int rows);

	void selfIntersect(QList<QPointF>* points, float epsilon);
	void getIntersections(float epsilon);

public:
	Bezier();
	Bezier(QList<QPointF> initPolygon);
	~Bezier();
	vector<QPointF> CkPoints;
	void initTriangleMatrix(QList<QPointF> points, vector<vector<QPointF>>* triangleMatrix);
	void calculateBezier(QList<QPointF>* pointlist, float epsilon, float t, int k, vector<QPointF>* finalPoints);
	void printVector(vector<QPointF> vector);
	void printVector(vector<QPointF>* vector);
	void Bezier::printPoints(vector<QPointF>* points2draw);
	QList<QPointF> getControlPoints();
	bool checkAngle(QList<QPointF>* points);
	QList<QPointF> intersect(QList<QPointF>* bezierPoints, float epsilon);
	void calculateIntersections(QList<QPointF>* firstCurvePoints, QList<QPointF>* secondCurvePoints, float epsilon);
	QList<QPointF> selfIntersect(float epsilon);
	Points addCkSegment(QPointF newPoint, float epsilon);

	vector<QPointF> TEST;
};
