#pragma once

#include "points.h"
#include "knots.h"

class BSpline {
public:
	BSpline();
	BSpline(Points controlPoints, Knots knots, int n);
	~BSpline();

	bool insertPoint(float t);
	bool deBoor(float t, int r);
	void toBezier(QList<QList<QPointF>> &bezierParts);
	int getIntervall(float t);
	Points getControlPoints();
	Points getNewPoints();
	void updateData(Points points, Knots knots);
	bool isIntervall(qreal mouseX);

private:
	Points _points;
	Points _newControlPoints;
	Knots _knots;
	int _n;
};

