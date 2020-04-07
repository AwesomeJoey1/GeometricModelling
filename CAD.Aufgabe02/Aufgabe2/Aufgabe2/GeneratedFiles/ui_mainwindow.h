/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 400);
        MainWindow->setLocale(QLocale(QLocale::German, QLocale::Germany));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        doubleSpinBox_epsilon_draw = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_epsilon_draw->setObjectName(QStringLiteral("doubleSpinBox_epsilon_draw"));
        doubleSpinBox_epsilon_draw->setDecimals(3);
        doubleSpinBox_epsilon_draw->setMinimum(0.001);
        doubleSpinBox_epsilon_draw->setMaximum(10);
        doubleSpinBox_epsilon_draw->setSingleStep(0.01);
        doubleSpinBox_epsilon_draw->setValue(0.05);

        verticalLayout->addWidget(doubleSpinBox_epsilon_draw);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        doubleSpinBox_epsilon_intersection = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_epsilon_intersection->setObjectName(QStringLiteral("doubleSpinBox_epsilon_intersection"));
        doubleSpinBox_epsilon_intersection->setDecimals(6);
        doubleSpinBox_epsilon_intersection->setMinimum(1e-5);
        doubleSpinBox_epsilon_intersection->setMaximum(1);
        doubleSpinBox_epsilon_intersection->setSingleStep(1e-5);
        doubleSpinBox_epsilon_intersection->setValue(0.0005);

        verticalLayout->addWidget(doubleSpinBox_epsilon_intersection);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        checkBox_Intersection = new QCheckBox(centralWidget);
        checkBox_Intersection->setObjectName(QStringLiteral("checkBox_Intersection"));

        verticalLayout->addWidget(checkBox_Intersection);

        checkBox_SelfIntersection = new QCheckBox(centralWidget);
        checkBox_SelfIntersection->setObjectName(QStringLiteral("checkBox_SelfIntersection"));

        verticalLayout->addWidget(checkBox_SelfIntersection);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        glwidget = new GLWidget(centralWidget);
        glwidget->setObjectName(QStringLiteral("glwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(glwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        horizontalLayout_2->addWidget(glwidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\316\265 f\303\274r Zeichnen:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\316\265 f\303\274r Schnitte:", Q_NULLPTR));
        checkBox_Intersection->setText(QApplication::translate("MainWindow", "Schnittpunkte", Q_NULLPTR));
        checkBox_SelfIntersection->setText(QApplication::translate("MainWindow", "Selbstschnitte", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
