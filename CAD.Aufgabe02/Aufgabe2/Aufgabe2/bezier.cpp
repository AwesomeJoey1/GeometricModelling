#include "bezier.h"
#include <algorithm>
#include <iostream>

/*
* ------------------------PUBLIC------------------------
*/
Bezier::Bezier() {}

Bezier::Bezier(QList<QPointF> initPolygon) {
	controlPoints = initPolygon;
}
Bezier::~Bezier() {
}

void Bezier::initTriangleMatrix(QList<QPointF> points, vector<vector<QPointF>>* triangleMatrix) {
	QList<QPointF>::iterator it;
	int i = 0;
	// Is the matrix square
	for (it = points.begin(); it != points.end(); it++) {
		triangleMatrix->at(i).at(i) = QPointF(0, 0);
		triangleMatrix->at(i).at(0).setX(it->x());
		triangleMatrix->at(i).at(0).setY(it->y());

		i++;
	}

	//cout << "TriangleMatrix size at [0]: " << triangleMatrix->size() << " x " << triangleMatrix->at(0).size() << endl;
	//cout << "TriangleMatrix size at last item: " << triangleMatrix->size() << " x " << triangleMatrix->at(points.length()-1).size() << endl;

}

// Returns Points of a Bezier Curve
/* @args:	pointlist:	points, 
			k:			recursion depth
			epsilon:	abort criterion
*/
void Bezier::calculateBezier(QList<QPointF>* pointlist, float epsilon, float t, int k, vector<QPointF>* finalPoints)
{
	QList<QPointF>* an = new QList<QPointF>();
	QList<QPointF>* a2n = new QList<QPointF>();
	int n = pointlist->length() - 1;
	vector<vector<QPointF>>* triangleMatrix = new vector<vector<QPointF>>(pointlist->size(), vector<QPointF>(pointlist->size()));
	initTriangleMatrix(*pointlist, triangleMatrix);

	//printVector(triangleMatrix, triangleMatrix->size());

	QPointF maxSecDeriv = getMaxSecDeriv(*pointlist);

	if (k == 0 || (((n * (n-1) * maxSecDeriv.x()) < epsilon) && ((n * (n - 1) * maxSecDeriv.y()) < epsilon))) {
		for (int c = 0; c < pointlist->length(); c++) {
			finalPoints->push_back(pointlist->at(c));
		}
	}
	else {
		// Calculate triangleMatrix, but only diagonal values (a0....an) and last row values (an...a2n) are important
		an->append(triangleMatrix->at(0).at(0)); // a0
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				QPointF a = triangleMatrix->at(i - 1).at(j - 1);
				QPointF b = triangleMatrix->at(i).at(j - 1);
				QPointF bezierPoint = (1 - t)*a + t * b;
				// last row values
				if (i == n) {
					a2n->push_front(bezierPoint);
				}
				// diagonal values
				if (i == j) {
					an->append(bezierPoint);
				}
				//cout << "Points length: " << pointlist.length() << endl;
				//cout << "Matrix sizes: " << triangleMatrix->size() << " " << triangleMatrix->at(0).size() << " " << triangleMatrix->at(triangleMatrix->size()-1).size() << endl;
				triangleMatrix->at(i).at(j) = bezierPoint;
			}
		}
		a2n->append(triangleMatrix->at(n).at(0)); // a2n
												  //printVector(triangleMatrix, pointlist.length());
		calculateBezier(an, epsilon, t, k - 1, finalPoints);
		calculateBezier(a2n, epsilon, t, k - 1, finalPoints);
		delete an, a2n, triangleMatrix;
	}
}

/*
* ------------------------------INTERSECTION------------------------------------
*/

// Check for intersections with another curve
QList<QPointF> Bezier::intersect(QList<QPointF>* bezierPoints, float epsilon) {
	calculateIntersections(&getControlPoints(), bezierPoints, epsilon);
	return intersectionPoints;
}

// Check recursively for intersections
void Bezier::calculateIntersections(QList<QPointF>* firstCurvePoints, QList<QPointF>* secondCurvePoints, float epsilon) {
	if (boundingCut(firstCurvePoints, secondCurvePoints)) {
		int m = firstCurvePoints->size() - 1;
		int n = secondCurvePoints->size() - 1;
		QPointF maxDiff1 = getMaxSecDeriv(*firstCurvePoints);
		QPointF maxDiff2 = getMaxSecDeriv(*secondCurvePoints);

		bool b1 = (m * (m - 1) * maxDiff1.x() > epsilon &&
			m * (m - 1) * maxDiff1.y() > epsilon);
		bool b2 = (n * (n - 1) * maxDiff2.x() > epsilon) &&
			(n * (n - 1) * maxDiff2.y() > epsilon);
		if (b1) {
			vector<QPointF>* p = new vector<QPointF>();
			calculateBezier(firstCurvePoints, epsilon, 0.5, 1, p);
			int c = p->size() / 2;
			QList<QPointF>* a = new QList<QPointF>();
			QList<QPointF>* b = new QList<QPointF>();
			for (int i = 0; i < p->size(); i++) {
				if (i < c){
					a->append(p->at(i));
				}
				else if (i >= c) {
					b->append(p->at(i));
				}
			}
			calculateIntersections(a, secondCurvePoints, epsilon);
			calculateIntersections(b, secondCurvePoints, epsilon);
			delete p,a,b;
		}
		else if (b2) {
			vector<QPointF>* p = new vector<QPointF>();
			calculateBezier(secondCurvePoints, epsilon, 0.5, 1, p);
			int c = p->size() / 2;
			QList<QPointF>* a = new QList<QPointF>();
			QList<QPointF>* b = new QList<QPointF>();
			for (int i = 0; i < p->size(); i++) {
				if (i < c) {
					a->append(p->at(i));
				}
				else if (i >= c) {
					b->append(p->at(i));
				}
			}
			calculateIntersections(firstCurvePoints, a, epsilon);
			calculateIntersections(firstCurvePoints, b, epsilon);
			delete p,a,b;
		}
		// if flat enough just take the first and last point as definition for a line
		else {
			QPointF intersection;
			QLineF l1 = QLineF(firstCurvePoints->at(0), firstCurvePoints->at(firstCurvePoints->length() - 1));
			QLineF l2 = QLineF(secondCurvePoints->at(0), secondCurvePoints->at(secondCurvePoints->length() - 1));
			QLineF::IntersectType res = l1.intersect(l2, &intersection);

			if (res == QLineF::BoundedIntersection) {
				intersectionPoints.append(intersection);
			}

		}
	}
}

bool Bezier::boundingCut(QList<QPointF>* curve1, QList<QPointF>* curve2) {
	QPointF min1 = getMin(curve1);
	QPointF min2 = getMin(curve2);
	QPointF max1 = getMax(curve1);
	QPointF max2 = getMax(curve2);

	if (min1.x() < max2.x() && max1.x() > min2.x() &&
		min1.y() < max2.y() && max1.y() > min2.y()) {
		return true;
	}
	return false;
}

/*
*-------------------------------------SELF INTERSECTION------------------------------------
*/

QList<QPointF> Bezier::selfIntersect(float epsilon) {
	selfIntersect(&controlPoints, epsilon);
	getIntersections(epsilon);
	return intersectionPoints;
}

void Bezier::selfIntersect(QList<QPointF>* points, float epsilon) {
	bool isCut = checkAngle(points);

	if (isCut == true) {
		vector<QPointF>* splitCurve = new vector<QPointF>();
		calculateBezier(points, epsilon, 0.5, 1, splitCurve);
		int c = splitCurve->size() / 2;

		QList<QPointF>* a = new QList<QPointF>();
		QList<QPointF>* b = new QList<QPointF>();
		for (int i = 0; i < splitCurve->size(); i++) {
			if (i < c) {
				a->append(splitCurve->at(i));
			}
			else if (i >= c) {
				b->append(splitCurve->at(i));
			}
		}
		selfIntersect(a, epsilon);
		selfIntersect(b, epsilon);
		delete a, b;
	}
	else {
		selfIntersectionPoints.append(Points(points));
	}
}

void Bezier::getIntersections(float epsilon) {
	for (int i = 0; i < selfIntersectionPoints.size()-1; i++) {
		for (int j = i+1; j < selfIntersectionPoints.size(); j++) {
			calculateIntersections(&selfIntersectionPoints[i].getPointList(), &selfIntersectionPoints[j].getPointList(), epsilon);
		}
	}
	selfIntersectionPoints.clear();
}

bool Bezier::checkAngle(QList<QPointF>* points) {
	QList<QPointF> diff;
	float diffX, diffY;

	for (int i = 0; i < points->size()-1; i++) {
		diffX = points->at(i + 1).x() - points->at(i).x();
		diffY = points->at(i + 1).y() - points->at(i).y();
		diff.append(QPointF(diffX, diffY));
	}

	float angle = 0.0;
	float tmp;
	QLineF l1, l2;
	QPointF origin = QPointF(0, 0);

	// Building hodograph
	for (int i = 0; i < diff.size()-1; i++) {
		l1 = QLineF(origin, diff[i]);
		l2 = QLineF(origin, diff[i + 1]);

		tmp = l1.angleTo(l2);

		if (tmp > 180) {
			tmp = 360 - tmp;
		}

		angle += tmp;
		if (angle > 180) {
			return true;
		}
	}
	return false;
}

/*
*------------------------------------------Ck Übergang-------------------
*/

Points Bezier::addCkSegment(QPointF newPoint, float epsilon) {
	vector<QPointF>* finalPoints = new vector<QPointF>();
	calculateBezier(&controlPoints, epsilon, 2, 1, finalPoints);

	TEST = *finalPoints;

	Points newSeg;
	QPointF p = controlPoints[controlPoints.size() - 1]; // add the last point
	newSeg.addPoint(p.x(), p.y());
	int c = finalPoints->size() / 2;
	// add Points to the new Segment
	for (int i = finalPoints->size() - 2; i > c; i--) {
		newSeg.addPoint(finalPoints->at(i).x(), finalPoints->at(i).y());
	}
	newSeg.addPoint(newPoint.x(), newPoint.y()); // aaand now the new Point

	CkPoints.clear();
	calculateBezier(&newSeg.getPointList(), epsilon, 0.5, 5, &CkPoints);

	return newSeg;
}

float Bezier::len(QPointF p_point)
{
	return sqrt(pow(p_point.x(), 2) + pow(p_point.y(), 2));
}

QPointF Bezier::getMaxSecDeriv(QList<QPointF> pointlist) {
	QPointF max;
	for (int i = 0; i < pointlist.size() - 2; i++) {
		float x = fabs(pointlist.at(i + 2).x() - 2 * pointlist.at(i + 1).x() + pointlist.at(i).x());
		float y = fabs(pointlist.at(i + 2).y() - 2 * pointlist.at(i + 1).y() + pointlist.at(i).y());
		max.setX(max.x() > x ? max.x() : x);
		max.setY(max.y() > y ? max.y() : y);
	}
	return max;
}

void Bezier::printVector(vector<QPointF> vector) {
	cout << "Printing vector..." << endl;
	cout << "Vector = {";
	for (int i = 0; i < vector.size(); i++) {
		 cout << "" << vector[i].x() << "," << vector[i].y() << "\t\r";
	}
}

void Bezier::printVector(vector<QPointF>* vector) {
	cout << "Vector = {";
	for (int i = 0; i < vector->size()-1; i++) {
		cout << "" << vector->at(i).x() << "," << vector->at(i).y() << "\t\r";
	}	
}

void Bezier::printVector(vector<vector<QPointF>>* vector, int cols) {
	cout << "Vector = Size: " << vector->size() - 1 << ": " << "{\n";
	for (int i = 0; i < vector->size(); i++) {
		for (int j = 0; j < cols; j++) {
			cout << "" << vector->at(i).at(j).x() << "," << vector->at(i).at(j).y() << "\t";
		}
		cout << "\n";
	}
}

void Bezier::printPoints(vector<QPointF>* points2draw) {
	cout << "Number of Points: " << points2draw->size() << endl;
	printVector(points2draw);
}

QList<QPointF> Bezier::getControlPoints() {
	return controlPoints;
}

QPointF Bezier::getMin(QList<QPointF>* curvePoints) {
	QPointF min(1.0, 1.0);
	for (int i = 0; i < curvePoints->length(); i++) {
		min.setX(min.x() < curvePoints->at(i).x() ? min.x() : curvePoints->at(i).x());
		min.setY(min.y() < curvePoints->at(i).y() ? min.y() : curvePoints->at(i).y());
	}

	return min;
}
QPointF Bezier::getMax(QList<QPointF>* curvePoints) {
	QPointF max(-1.0, -1.0);
	for (int i = 0; i < curvePoints->length(); i++) {
		max.setX(max.x() > curvePoints->at(i).x() ? max.x() : curvePoints->at(i).x());
		max.setY(max.y() > curvePoints->at(i).y() ? max.y() : curvePoints->at(i).y());
	}

	return max;
}