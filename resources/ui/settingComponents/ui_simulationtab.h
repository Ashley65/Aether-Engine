/********************************************************************************
** Form generated from reading UI file 'simulationtab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONTAB_H
#define UI_SIMULATIONTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationTab
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupSimulationBehavior;
    QVBoxLayout *vb_sim_behavior;
    QHBoxLayout *h_operatingMode;
    QVBoxLayout *v_labels_opMode;
    QLabel *label_opMode;
    QLabel *desc_opMode;
    QComboBox *comboOperatingMode;
    QHBoxLayout *h_timeStep;
    QVBoxLayout *v_labels_timeStep;
    QLabel *label_timeStep;
    QLabel *desc_timeStep;
    QDoubleSpinBox *spinTimeStep;
    QHBoxLayout *h_realTime;
    QVBoxLayout *v_labels_realTime;
    QLabel *label_realTime;
    QLabel *desc_realTime;
    QHBoxLayout *h_realtime_controls;
    QSlider *sliderRealTime;
    QLabel *labelRealTimeValue;
    QHBoxLayout *h_autoSave;
    QVBoxLayout *v_labels_autoSave;
    QLabel *label_autoSave;
    QLabel *desc_autoSave;
    QSpinBox *spinAutoSave;
    QGroupBox *groupMissionDefaults;
    QVBoxLayout *vb_mission_defaults;
    QHBoxLayout *h_defaultEnv;
    QVBoxLayout *v_labels_defaultEnv;
    QLabel *label_defaultEnv;
    QLabel *desc_defaultEnv;
    QComboBox *comboDefaultEnv;
    QHBoxLayout *h_initialAIMode;
    QVBoxLayout *v_labels_initialAI;
    QLabel *label_initialAI;
    QLabel *desc_initialAI;
    QComboBox *comboInitialAIMode;

    void setupUi(QWidget *SimulationTab)
    {
        if (SimulationTab->objectName().isEmpty())
            SimulationTab->setObjectName("SimulationTab");
        SimulationTab->resize(600, 520);
        verticalLayout = new QVBoxLayout(SimulationTab);
        verticalLayout->setObjectName("verticalLayout");
        groupSimulationBehavior = new QGroupBox(SimulationTab);
        groupSimulationBehavior->setObjectName("groupSimulationBehavior");
        vb_sim_behavior = new QVBoxLayout(groupSimulationBehavior);
        vb_sim_behavior->setObjectName("vb_sim_behavior");
        h_operatingMode = new QHBoxLayout();
        h_operatingMode->setObjectName("h_operatingMode");
        v_labels_opMode = new QVBoxLayout();
        v_labels_opMode->setObjectName("v_labels_opMode");
        label_opMode = new QLabel(groupSimulationBehavior);
        label_opMode->setObjectName("label_opMode");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        label_opMode->setFont(font);

        v_labels_opMode->addWidget(label_opMode);

        desc_opMode = new QLabel(groupSimulationBehavior);
        desc_opMode->setObjectName("desc_opMode");
        desc_opMode->setWordWrap(true);

        v_labels_opMode->addWidget(desc_opMode);


        h_operatingMode->addLayout(v_labels_opMode);

        comboOperatingMode = new QComboBox(groupSimulationBehavior);
        comboOperatingMode->addItem(QString());
        comboOperatingMode->addItem(QString());
        comboOperatingMode->addItem(QString());
        comboOperatingMode->setObjectName("comboOperatingMode");

        h_operatingMode->addWidget(comboOperatingMode);


        vb_sim_behavior->addLayout(h_operatingMode);

        h_timeStep = new QHBoxLayout();
        h_timeStep->setObjectName("h_timeStep");
        v_labels_timeStep = new QVBoxLayout();
        v_labels_timeStep->setObjectName("v_labels_timeStep");
        label_timeStep = new QLabel(groupSimulationBehavior);
        label_timeStep->setObjectName("label_timeStep");
        label_timeStep->setFont(font);

        v_labels_timeStep->addWidget(label_timeStep);

        desc_timeStep = new QLabel(groupSimulationBehavior);
        desc_timeStep->setObjectName("desc_timeStep");
        desc_timeStep->setWordWrap(true);

        v_labels_timeStep->addWidget(desc_timeStep);


        h_timeStep->addLayout(v_labels_timeStep);

        spinTimeStep = new QDoubleSpinBox(groupSimulationBehavior);
        spinTimeStep->setObjectName("spinTimeStep");
        spinTimeStep->setDecimals(3);
        spinTimeStep->setMinimum(0.000000000000000);
        spinTimeStep->setMaximum(10.000000000000000);
        spinTimeStep->setSingleStep(0.001000000000000);
        spinTimeStep->setValue(0.016000000000000);

        h_timeStep->addWidget(spinTimeStep);


        vb_sim_behavior->addLayout(h_timeStep);

        h_realTime = new QHBoxLayout();
        h_realTime->setObjectName("h_realTime");
        v_labels_realTime = new QVBoxLayout();
        v_labels_realTime->setObjectName("v_labels_realTime");
        label_realTime = new QLabel(groupSimulationBehavior);
        label_realTime->setObjectName("label_realTime");
        label_realTime->setFont(font);

        v_labels_realTime->addWidget(label_realTime);

        desc_realTime = new QLabel(groupSimulationBehavior);
        desc_realTime->setObjectName("desc_realTime");
        desc_realTime->setWordWrap(true);

        v_labels_realTime->addWidget(desc_realTime);


        h_realTime->addLayout(v_labels_realTime);

        h_realtime_controls = new QHBoxLayout();
        h_realtime_controls->setObjectName("h_realtime_controls");
        sliderRealTime = new QSlider(groupSimulationBehavior);
        sliderRealTime->setObjectName("sliderRealTime");
        sliderRealTime->setMinimum(1);
        sliderRealTime->setMaximum(100);
        sliderRealTime->setValue(10);
        sliderRealTime->setOrientation(Qt::Orientation::Horizontal);

        h_realtime_controls->addWidget(sliderRealTime);

        labelRealTimeValue = new QLabel(groupSimulationBehavior);
        labelRealTimeValue->setObjectName("labelRealTimeValue");
        labelRealTimeValue->setMinimumSize(QSize(48, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Monospace")});
        labelRealTimeValue->setFont(font1);
        labelRealTimeValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        h_realtime_controls->addWidget(labelRealTimeValue);


        h_realTime->addLayout(h_realtime_controls);


        vb_sim_behavior->addLayout(h_realTime);

        h_autoSave = new QHBoxLayout();
        h_autoSave->setObjectName("h_autoSave");
        v_labels_autoSave = new QVBoxLayout();
        v_labels_autoSave->setObjectName("v_labels_autoSave");
        label_autoSave = new QLabel(groupSimulationBehavior);
        label_autoSave->setObjectName("label_autoSave");
        label_autoSave->setFont(font);

        v_labels_autoSave->addWidget(label_autoSave);

        desc_autoSave = new QLabel(groupSimulationBehavior);
        desc_autoSave->setObjectName("desc_autoSave");

        v_labels_autoSave->addWidget(desc_autoSave);


        h_autoSave->addLayout(v_labels_autoSave);

        spinAutoSave = new QSpinBox(groupSimulationBehavior);
        spinAutoSave->setObjectName("spinAutoSave");
        spinAutoSave->setMinimum(0);
        spinAutoSave->setMaximum(86400);
        spinAutoSave->setValue(99);

        h_autoSave->addWidget(spinAutoSave);


        vb_sim_behavior->addLayout(h_autoSave);


        verticalLayout->addWidget(groupSimulationBehavior);

        groupMissionDefaults = new QGroupBox(SimulationTab);
        groupMissionDefaults->setObjectName("groupMissionDefaults");
        vb_mission_defaults = new QVBoxLayout(groupMissionDefaults);
        vb_mission_defaults->setObjectName("vb_mission_defaults");
        h_defaultEnv = new QHBoxLayout();
        h_defaultEnv->setObjectName("h_defaultEnv");
        v_labels_defaultEnv = new QVBoxLayout();
        v_labels_defaultEnv->setObjectName("v_labels_defaultEnv");
        label_defaultEnv = new QLabel(groupMissionDefaults);
        label_defaultEnv->setObjectName("label_defaultEnv");
        label_defaultEnv->setFont(font);

        v_labels_defaultEnv->addWidget(label_defaultEnv);

        desc_defaultEnv = new QLabel(groupMissionDefaults);
        desc_defaultEnv->setObjectName("desc_defaultEnv");

        v_labels_defaultEnv->addWidget(desc_defaultEnv);


        h_defaultEnv->addLayout(v_labels_defaultEnv);

        comboDefaultEnv = new QComboBox(groupMissionDefaults);
        comboDefaultEnv->addItem(QString());
        comboDefaultEnv->addItem(QString());
        comboDefaultEnv->addItem(QString());
        comboDefaultEnv->addItem(QString());
        comboDefaultEnv->setObjectName("comboDefaultEnv");

        h_defaultEnv->addWidget(comboDefaultEnv);


        vb_mission_defaults->addLayout(h_defaultEnv);

        h_initialAIMode = new QHBoxLayout();
        h_initialAIMode->setObjectName("h_initialAIMode");
        v_labels_initialAI = new QVBoxLayout();
        v_labels_initialAI->setObjectName("v_labels_initialAI");
        label_initialAI = new QLabel(groupMissionDefaults);
        label_initialAI->setObjectName("label_initialAI");
        label_initialAI->setFont(font);

        v_labels_initialAI->addWidget(label_initialAI);

        desc_initialAI = new QLabel(groupMissionDefaults);
        desc_initialAI->setObjectName("desc_initialAI");

        v_labels_initialAI->addWidget(desc_initialAI);


        h_initialAIMode->addLayout(v_labels_initialAI);

        comboInitialAIMode = new QComboBox(groupMissionDefaults);
        comboInitialAIMode->addItem(QString());
        comboInitialAIMode->addItem(QString());
        comboInitialAIMode->addItem(QString());
        comboInitialAIMode->setObjectName("comboInitialAIMode");

        h_initialAIMode->addWidget(comboInitialAIMode);


        vb_mission_defaults->addLayout(h_initialAIMode);


        verticalLayout->addWidget(groupMissionDefaults);


        retranslateUi(SimulationTab);

        QMetaObject::connectSlotsByName(SimulationTab);
    } // setupUi

    void retranslateUi(QWidget *SimulationTab)
    {
        SimulationTab->setWindowTitle(QCoreApplication::translate("SimulationTab", "SimulationTab", nullptr));
        groupSimulationBehavior->setTitle(QCoreApplication::translate("SimulationTab", "Simulation Behavior", nullptr));
        label_opMode->setText(QCoreApplication::translate("SimulationTab", "Operating Mode", nullptr));
        desc_opMode->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_opMode->setText(QCoreApplication::translate("SimulationTab", "Choose between pure simulation, hardware testing, or hybrid", nullptr));
        comboOperatingMode->setItemText(0, QCoreApplication::translate("SimulationTab", "Pure Simulation", nullptr));
        comboOperatingMode->setItemText(1, QCoreApplication::translate("SimulationTab", "Hardware-in-the-Loop (HIL)", nullptr));
        comboOperatingMode->setItemText(2, QCoreApplication::translate("SimulationTab", "Hardware Testing", nullptr));

        label_timeStep->setText(QCoreApplication::translate("SimulationTab", "Time Step", nullptr));
        desc_timeStep->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_timeStep->setText(QCoreApplication::translate("SimulationTab", "Fixed simulation time step (smaller = more accurate, slower)", nullptr));
        spinTimeStep->setSuffix(QCoreApplication::translate("SimulationTab", " s", nullptr));
        label_realTime->setText(QCoreApplication::translate("SimulationTab", "Real-Time Factor", nullptr));
        desc_realTime->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_realTime->setText(QCoreApplication::translate("SimulationTab", "Simulation speed multiplier (1.0 = real-time)", nullptr));
        labelRealTimeValue->setText(QCoreApplication::translate("SimulationTab", "1.0x", nullptr));
        label_autoSave->setText(QCoreApplication::translate("SimulationTab", "Auto-Save Interval", nullptr));
        desc_autoSave->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_autoSave->setText(QCoreApplication::translate("SimulationTab", "Automatically save mission state", nullptr));
        spinAutoSave->setSuffix(QCoreApplication::translate("SimulationTab", " s", nullptr));
        groupMissionDefaults->setTitle(QCoreApplication::translate("SimulationTab", "Mission Defaults", nullptr));
        label_defaultEnv->setText(QCoreApplication::translate("SimulationTab", "Default Environment", nullptr));
        desc_defaultEnv->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_defaultEnv->setText(QCoreApplication::translate("SimulationTab", "Starting environment for new missions", nullptr));
        comboDefaultEnv->setItemText(0, QCoreApplication::translate("SimulationTab", "Deep Space", nullptr));
        comboDefaultEnv->setItemText(1, QCoreApplication::translate("SimulationTab", "Earth Orbit", nullptr));
        comboDefaultEnv->setItemText(2, QCoreApplication::translate("SimulationTab", "Mars Transfer", nullptr));
        comboDefaultEnv->setItemText(3, QCoreApplication::translate("SimulationTab", "Drone (Atmospheric)", nullptr));

        label_initialAI->setText(QCoreApplication::translate("SimulationTab", "Initial AI Mode", nullptr));
        desc_initialAI->setStyleSheet(QCoreApplication::translate("SimulationTab", "color: #9aa4b2; font-size: 10px;", nullptr));
        desc_initialAI->setText(QCoreApplication::translate("SimulationTab", "AI behavior when mission starts", nullptr));
        comboInitialAIMode->setItemText(0, QCoreApplication::translate("SimulationTab", "Autonomous", nullptr));
        comboInitialAIMode->setItemText(1, QCoreApplication::translate("SimulationTab", "Manual Control", nullptr));
        comboInitialAIMode->setItemText(2, QCoreApplication::translate("SimulationTab", "Assisted Mode", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SimulationTab: public Ui_SimulationTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONTAB_H
