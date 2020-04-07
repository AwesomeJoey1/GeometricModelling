#include "bspline.h"
#include "qdebug.h"

BSpline::BSpline(){}

BSpline::BSpline(Points controlPoints, Knots knots, int n) {
	this->_points = controlPoints;
	this->_knots = knots;
	this->_n = n;
}

BSpline::~BSpline(){}

bool BSpline::insertPoint(float t) {

	int r = getIntervall(t);
	//qDebug() << "Intervall: [" << r << ", " << r + 1 << "]";

	return deBoor(t, r);

}

bool BSpline::deBoor(float t, int r) {
	int n = _n;
	float alpha = 0.0;
	_newControlPoints.clear();

	for (int i = r - n; i < r; i++) { 
		// Test for valid intervall with respect to the counter index
		if (n + i + 1 >= _knots.getCount() || i < 0) {
			qDebug() << "Cannot insert Point";
			return false;
		}

		float x_i = _knots.getValue(i+1);
		float x_in = _knots.getValue(i + n + 1);

			alpha = (t - x_i) / (x_in - x_i);

		// take last point if index is at the end of the control points
		if (i >= _points.getCount() - 1) {
			_newControlPoints.addPoint(_points.getPointX(i), _points.getPointY(i));
		}	
		// otherwise calculate the new points
		else {
			float x = (1 - alpha) * _points.getPointX(i) + alpha* _points.getPointX(i+1);
			float y = (1 - alpha) * _points.getPointY(i) + alpha* _points.getPointY(i+1);

			_newControlPoints.addPoint(x, y);
		}
	}

	// delete old points from r-n+1 to r
	for (int i = r - n + 1; i < r; i++) {
		_points.removePointAt(r-n+1);
	}

	// insert new points at old position
	int pointCount = 0;
	for (int i = r - n + 1; pointCount < _newControlPoints.getCount(); ++i, ++pointCount) {
		_points.insertPointAt(i, QPointF(_newControlPoints.getPointX(pointCount), _newControlPoints.getPointY(pointCount)));
	}
	return true;

}

void BSpline::toBezier(QList<QList<QPointF>> &bezierParts) {
	bezierParts.clear();
	// increase multiplicity of all knots to get the bezier representation of the single bezier parts
	// the corresponding b-splines behave just like bernstein polynomials on the intervals
	for (int i = _points.getCount(); i >= _n; i--) {
	//for (int i = _n; i <= _points.getCount()-1; i++) {
		for (int j = 0; j < _n - 1; j++) {
			float t = _knots.getValue(i);
			insertPoint(t);
			_knots.insertKnot(t);
		}
	}

	// building the single bezier parts
	for (int i = _n-1; i < _points.getCount() - _n; i += _n) {
		QList<QPointF> part;
		for (int j = 0; j <= _n; j++) {
			part.append(QPointF(_points.getPointX(i + j), _points.getPointY(i + j)));
		}
		bezierParts.append(part);
	}
}

int BSpline::getIntervall(float t) {

	int r = _knots.getCount() - 1;

	for (int i = _knots.getCount() - 1; i > 0; i--) {
		float knotValue = _knots.getValue(i);
		if (t < knotValue) {
			r--;
		}
	}

	for (int i = _points.getCount() - 1; i > 0; i--) {
		float last_r = _knots.getValue(r - 1);
		float current_r = _knots.getValue(r);
		if (r > _points.getCount() && last_r == current_r) {
			r--;
		}
	}

	return r;
}

Points BSpline::getControlPoints() {
	return this->_points;
}

Points BSpline::getNewPoints() {
	return this->_newControlPoints;
}

void BSpline::updateData(Points points, Knots knots) {
	this->_knots = knots;
	this->_points = points;
}

/* with n= 4 --> m=4. the curve is only defined over [n, m+1]. In this case this would be
*  the intervall [x4, x5]
*/
bool BSpline::isIntervall(qreal mouseX) {
	bool onIntervall = false;
	int n = _n;
	int m = _points.getCount() - 1;

	for (int i = 0; i < _knots.getCount(); i++) {
		if (mouseX < _knots.getPointX(i)) {
			if (i > n && i <= m+1) {
				onIntervall = true;
			}
			break;
		}
	}
	return onIntervall;
}
