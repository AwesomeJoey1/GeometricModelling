#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "points.h"
#include "bezier.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent=0);
    ~GLWidget();

public slots:
    void setIntersection       (int    state);
    void setSelfIntersection   (int    state);
    void setEpsilonDraw        (double value);
    void setEpsilonIntersection(double value);

protected:
    void paintGL              ();
    void initializeGL         ();
    void resizeGL             (int width, int height);
    void mouseMoveEvent       (QMouseEvent *event);
    void mousePressEvent      (QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QPointF transformPosition(QPoint p);
	Points  points;
	QPointF newPoint;
	Bezier* bezier1 = new Bezier();
	Bezier* bezier2 = new Bezier();
	float   aspectx, aspecty;
    float   epsilon_draw, epsilon_intersection;
    int     clickedPoint;
	bool    doIntersection, doSelfIntersection, doCkSegment;
};



#endif // GLWIDGET_H
