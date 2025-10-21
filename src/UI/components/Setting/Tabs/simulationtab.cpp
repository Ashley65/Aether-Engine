//
// Created by DevAccount on 16/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SimulationTab.h" resolved


#include "UI/components/Setting/Tabs/simulationtab.h"

#include "../resources/ui/settingComponents/ui_simulationtab.h"
#include <QSettings>
#include <QLocale>


SimulationTab::SimulationTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::SimulationTab)
{
    ui->setupUi(this);

    // Wiring the real-time slider to update the label
    connect(ui->sliderRealTime, &QSlider::valueChanged, this, &SimulationTab::onRealTimeSliderChanged);

    // Update the slider
    onRealTimeSliderChanged(ui->sliderRealTime->value());


}

SimulationTab::~SimulationTab()
{
    delete ui;
}

void SimulationTab::onRealTimeSliderChanged(int value)
{
    double factor = sliderToFactor(value);
    // format with one decimal and monospace look consistent with design
    ui->labelRealTimeValue->setText(QLocale::c().toString(factor, 'f', 1) + "x");
}

double SimulationTab::sliderToFactor(int sliderValue) const
{
    // slider range 1..100 maps to 0.1..10.0 (logarithmic could be used; linear here)
    const double minF = 0.1;
    const double maxF = 10.0;
    const double t = (sliderValue - 1) / 99.0;
    return minF + t * (maxF - minF);
}

int SimulationTab::factorToSlider(double factor) const
{
    const double minF = 0.1;
    const double maxF = 10.0;
    double t = (factor - minF) / (maxF - minF);
    return qBound(1, int(qRound(1 + t * 99.0)), 100);
}

void SimulationTab::applyParams(const QVariantMap& params)
{
    if (params.contains("operatingMode")) {
        ui->comboOperatingMode->setCurrentText(params.value("operatingMode").toString());
    }
    if (params.contains("timeStep")) {
        ui->spinTimeStep->setValue(params.value("timeStep").toDouble());
    }
    if (params.contains("realTimeFactor")) {
        double f = params.value("realTimeFactor").toDouble();
        ui->sliderRealTime->setValue(factorToSlider(f));
        onRealTimeSliderChanged(ui->sliderRealTime->value());
    }
    if (params.contains("autoSave")) {
        ui->spinAutoSave->setValue(params.value("autoSave").toInt());
    }
    if (params.contains("defaultEnv")) {
        ui->comboDefaultEnv->setCurrentText(params.value("defaultEnv").toString());
    }
    if (params.contains("initialAIMode")) {
        ui->comboInitialAIMode->setCurrentText(params.value("initialAIMode").toString());
    }
}


void SimulationTab::loadSettings(const QVariantMap& params, bool force)
{
    if (m_isLoaded && !force) {
        if (!params.isEmpty()) {
            for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
                m_cachedParams_se.insert(it.key(), it.value());
            }
        }
        return;
    }

    // try to load persisted settings if params do not provide them
    QSettings s;
    QVariantMap merged = params;

    if (!merged.contains("operatingMode")) merged.insert("operatingMode", s.value("simulation/operatingMode", ui->comboOperatingMode->currentText()));
    if (!merged.contains("timeStep")) merged.insert("timeStep", s.value("simulation/timeStep", ui->spinTimeStep->value()));
    if (!merged.contains("realTimeFactor")) merged.insert("realTimeFactor", s.value("simulation/realTimeFactor", sliderToFactor(ui->sliderRealTime->value())));
    if (!merged.contains("autoSave")) merged.insert("autoSave", s.value("simulation/autoSave", ui->spinAutoSave->value()));
    if (!merged.contains("defaultEnv")) merged.insert("defaultEnv", s.value("simulation/defaultEnv", ui->comboDefaultEnv->currentText()));
    if (!merged.contains("initialAIMode")) merged.insert("initialAIMode", s.value("simulation/initialAIMode", ui->comboInitialAIMode->currentText()));

    applyParams(merged);

    // store merged for future merges and mark loaded
    m_cachedParams_se = merged;
    m_isLoaded = true;
}
