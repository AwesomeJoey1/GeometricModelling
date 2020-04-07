#include <QGlWidget>
#include "glwidget.h"
#include <QtGui>
#include <GL/glu.h>
#include "mainwindow.h"
#include <vector>
#include <iostream>
using namespace std;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    doIntersection       = false;
	doSelfIntersection	 = false;
	doCkSegment			 = true;
    epsilon_draw         = (float)0.05;
    epsilon_intersection = (float)0.000005;


    // Hier Punkte hinzufügen (schönere Startpositionen!)
	points.addPoint(-1.00, -0.7);
	points.addPoint(-0.75, -0.3);
	points.addPoint(-0.50, -0.5);
	points.addPoint(-0.25, -0.7);
	points.addPoint(0.00, -0.5);

    points.addPoint( 0.25,  0.5);
    points.addPoint( 0.50,  0.5);
    points.addPoint( 0.75,  0.5);
    points.addPoint( 1.00,  0.5);
}

GLWidget::~GLWidget()
{
	bezier1->~Bezier();
	bezier2->~Bezier();
}

void GLWidget::paintGL()
{
    // clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Koordinatensystem
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f( 1.0, 0.0);
    glVertex2f( 0.0,-1.0);
    glVertex2f( 0.0, 1.0);
    glEnd();
    glColor3f(1.0,0.0,0.0);

    // Punkte
    glPointSize(7.0);
    glBegin(GL_POINTS);
    for (int i=0; i<points.getCount(); i++) {
        glVertex2f(points.getPointX(i),points.getPointY(i));
    }
	
    glEnd();

    // Hüllpolygone zeichnen
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_STRIP);
    for (int i=0; i<5; i++) {
        glVertex2f(points.getPointX(i),points.getPointY(i));
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (int i=5; i<points.getCount(); i++) {
        glVertex2f(points.getPointX(i),points.getPointY(i));
    }
    glEnd();

    // Kurve
    glColor3f(1.0,1.0,1.0);
    // AUFGABE: Hier Kurve zeichnen
    // dabei epsilon_draw benutzen
	/*glBegin(GL_LINE_STRIP);
	int numPoints = points.getCount()-5;
	float b1x = points.getPointX(0);
	float b1y = points.getPointY(0);
	float b2x, b2y;

	for (float i = 0; i < 1; i+=epsilon_draw) {
		b2x = 0.0;
		b2y = 0.0;
		for (int j = 0; j <= numPoints; j++) {
			b2x += (int)curve->binomialCoeff(4, j) * pow(1 - i, (float)numPoints - j) * pow(i, j) * points.getPointX(j);
			b2y += (int)curve->binomialCoeff(4, j) * pow(1 - i, (float)numPoints - j) * pow(i, j) * points.getPointY(j);
		}
		glVertex2f(b2x, b2y);

		b1x = b2x;
		b1y = b2y;
	}
	glVertex2f(points.getPointX(numPoints), points.getPointY(numPoints));

	glEnd();*/

	// _______________________NEW_______________________________________
	glBegin(GL_LINE_STRIP);
	//bezier1->deletePointers();
	//bezier2->deletePointers();
	delete bezier1;
	delete bezier2;
	bezier1 = new Bezier(points.getRange(0, 5).getPointList());
	bezier2 = new Bezier(points.getRange(5, points.getCount()).getPointList());
	vector<QPointF>* p = new vector<QPointF>();
	vector<QPointF>* r = new vector<QPointF>();
	bezier1->calculateBezier(&points.getRange(0, 5).getPointList(), epsilon_draw, 0.5, 5, p);
	bezier2->calculateBezier(&points.getRange(5, points.getCount()).getPointList(), epsilon_draw, 0.5, 5, r);
	bezier1->CkPoints = *p;
	bezier2->CkPoints = *r;
	for (int i = 0; i < p->size(); i++) {
		glVertex2f(p->at(i).x(), p->at(i).y());
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < r->size(); i++) {
		glVertex2f(r->at(i).x(), r->at(i).y());
	}

	glEnd();
	
    // Schnittpunkte zeichnen
    if (doIntersection) {
        glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
        // AUFGABE: Hier Schnitte zeichnen
        // dabei epsilon_intersection benutzen
		QList<QPointF> intersections = bezier1->intersect(&bezier2->getControlPoints(), epsilon_intersection);	
		for (int i = 0; i < intersections.length(); i++) {
			glVertex2f(intersections[i].x(), intersections[i].y());
			}
		glEnd();
    }
	if (doSelfIntersection) {
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		// AUFGABE: Hier Selbstschnitte zeichnen
		// dabei epsilon_intersection benutzen
		QList<QPointF> selfIntersections1 = bezier1->selfIntersect(epsilon_intersection);
		for (int i = 0; i < selfIntersections1.size(); i++) {
			glVertex2f(selfIntersections1[i].x(), selfIntersections1[i].y());
		}
		glEnd();

		glBegin(GL_POINTS);
		QList<QPointF> selfIntersections2 = bezier2->selfIntersect(epsilon_intersection);
		for (int i = 0; i < selfIntersections2.size(); i++) {
			glVertex2f(selfIntersections2[i].x(), selfIntersections2[i].y());
		}
		glEnd();
	}

	if (doCkSegment) {
		glColor3f(0.0, 1.0, 1.0);
		Points newSegControlPoints;
		bool extendFirst = true;
		bool extendSecond = false;
		if (extendFirst == true) {
			glBegin(GL_LINE_STRIP);
			newSegControlPoints = bezier1->addCkSegment(newPoint, epsilon_draw);

			vector<QPointF> newCurve1 = bezier1->CkPoints;
			for (int i = 0; i < newCurve1.size(); i++) {
				glVertex2f(newCurve1[i].x(), newCurve1[i].y());
			}
			glEnd();
		}
		else if (extendSecond == true) {
			glBegin(GL_LINE_STRIP);
			newSegControlPoints = bezier2->addCkSegment(newPoint, epsilon_draw);

			vector<QPointF> newCurve2 = bezier2->CkPoints;
			for (int i = 0; i < newCurve2.size(); i++) {
				glVertex2f(newCurve2[i].x(), newCurve2[i].y());
			}

			glEnd();
		}

		glPointSize(7.0);

		glBegin(GL_POINTS);
		for (int i = 0; i < newSegControlPoints.getCount(); i++) {
			glVertex2f(newSegControlPoints.getPointX(i), newSegControlPoints.getPointY(i));
		}
		glEnd();

		// Hüllpolygone zeichnen
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i<newSegControlPoints.getCount(); i++) {
			glVertex2f(newSegControlPoints.getPointX(i), newSegControlPoints.getPointY(i));
		}
		glEnd();
		/*
		glColor3f(1.0, 0, 0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < bezier1->TEST.size(); i++) {
			glVertex2f(bezier1->TEST[i].x(), bezier1->TEST[i].y());
		}
		glEnd();

		glBegin(GL_POINTS);
		for (int i = 0; i < bezier1->TEST.size(); i++) {
			glVertex2f(bezier1->TEST[i].x(), bezier1->TEST[i].y());
		}
		glEnd();*/
	}
    
	delete p, r;
}


void GLWidget::initializeGL()
{
    resizeGL(width(),height());
}

void GLWidget::resizeGL(int width, int height)
{
    aspectx=1.0;
    aspecty=1.0;
    if (width>height) {
        aspectx=float(width)/height;
    }
    else {
        aspecty=float(height)/width;
    }
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-aspectx,aspectx,-aspecty,aspecty);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

QPointF GLWidget::transformPosition(QPoint p)
{
    return QPointF((2.0*p.x()/width() - 1.0)*aspectx,-(2.0*p.y()/height() - 1.0)*aspecty);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint pos = event->pos();
        QPointF posF = transformPosition(pos);
        points.setPointX(clickedPoint,posF.x());
        points.setPointY(clickedPoint,posF.y());
        update();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint pos = event->pos();
        QPointF posF = transformPosition(pos);
        clickedPoint = points.getClosestPoint(posF.x(),posF.y());
        points.setPointX(clickedPoint,posF.x());
        points.setPointY(clickedPoint,posF.y());
        update();
    }

	if (event->buttons() & Qt::RightButton) {
		QPoint pos = event->pos();
		QPointF posF = transformPosition(pos);
		newPoint.setX(posF.x());
		newPoint.setY(posF.y());
		update();
	}
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *)
{
}

void GLWidget::setIntersection(int state)
{
    doIntersection = (state == Qt::Checked);
    update();
}

void GLWidget::setSelfIntersection(int state)
{
    doSelfIntersection = (state == Qt::Checked);
    update();
}

void GLWidget::setEpsilonDraw(double value)
{
    epsilon_draw = value;
}

void GLWidget::setEpsilonIntersection(double value)
{
    epsilon_intersection = value;
}
