#ifndef POINTS_H
#define POINTS_H
#include <QList>
#include <QPointF>

class Points
{
public:
    Points();
	Points(QList<QPointF>* points);
	Points getRange(int from, int to);
    void  addPoint (float x, float y);
	QList<QPointF> getPointList();
    float getPointX(int   i);
    float getPointY(int   i);
    void  setPointX(int   i, float x);
    void  setPointY(int   i, float y);
    int   getCount ();
    int   getClosestPoint (float x, float y);
    void  moveClosestPoint(float x, float y, float tox, float toy);

private:
    QList<QPointF> pointlist;
};

#endif // POINTS_H
