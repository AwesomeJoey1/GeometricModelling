/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_epsilon_draw;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_epsilon_intersection;
    QFrame *line;
    QCheckBox *checkBox_Intersection;
    QCheckBox *checkBox_SelfIntersection;
    QSpacerItem *verticalSpacer;
    GLWidget *glwidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        MainWindow->setLocale(QLocale(QLocale::German, QLocale::Germany));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        doubleSpinBox_epsilon_draw = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_epsilon_draw->setObjectName(QString::fromUtf8("doubleSpinBox_epsilon_draw"));
        doubleSpinBox_epsilon_draw->setDecimals(3);
        doubleSpinBox_epsilon_draw->setMinimum(0.001000000000000);
        doubleSpinBox_epsilon_draw->setMaximum(10.000000000000000);
        doubleSpinBox_epsilon_draw->setSingleStep(0.010000000000000);
        doubleSpinBox_epsilon_draw->setValue(0.050000000000000);

        verticalLayout->addWidget(doubleSpinBox_epsilon_draw);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        doubleSpinBox_epsilon_intersection = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_epsilon_intersection->setObjectName(QString::fromUtf8("doubleSpinBox_epsilon_intersection"));
        doubleSpinBox_epsilon_intersection->setDecimals(6);
        doubleSpinBox_epsilon_intersection->setMinimum(0.000010000000000);
        doubleSpinBox_epsilon_intersection->setMaximum(1.000000000000000);
        doubleSpinBox_epsilon_intersection->setSingleStep(0.000010000000000);
        doubleSpinBox_epsilon_intersection->setValue(0.000500000000000);

        verticalLayout->addWidget(doubleSpinBox_epsilon_intersection);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        checkBox_Intersection = new QCheckBox(centralWidget);
        checkBox_Intersection->setObjectName(QString::fromUtf8("checkBox_Intersection"));

        verticalLayout->addWidget(checkBox_Intersection);

        checkBox_SelfIntersection = new QCheckBox(centralWidget);
        checkBox_SelfIntersection->setObjectName(QString::fromUtf8("checkBox_SelfIntersection"));

        verticalLayout->addWidget(checkBox_SelfIntersection);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        glwidget = new GLWidget(centralWidget);
        glwidget->setObjectName(QString::fromUtf8("glwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(glwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        horizontalLayout_2->addWidget(glwidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\316\265 f\303\274r Zeichnen:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\316\265 f\303\274r Schnitte:", nullptr));
        checkBox_Intersection->setText(QCoreApplication::translate("MainWindow", "Schnittpunkte", nullptr));
        checkBox_SelfIntersection->setText(QCoreApplication::translate("MainWindow", "Selbstschnitte", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
