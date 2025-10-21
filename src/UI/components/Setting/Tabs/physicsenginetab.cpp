//
// Created by DevAccount on 16/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PhysicsEngineTab.h" resolved

#include "UI/components/Setting/Tabs/physicsenginetab.h"
#include "../../../resources/ui/settingComponents/ui_physicsenginetab.h"
#include <QSettings>
#include <QLocale>
#include <QStringList>
#include <QString>


PhysicsEngineTab::PhysicsEngineTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::PhysicsEngineTab)
{
    ui->setupUi(this);

    // Connect signals to auto-save changes to cache
    connect(ui->comboBoxGravityModel, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        m_cachedParams_PE.insert("GravityModel", text);
    });

    connect(ui->sliderBarnesHutThreshold, &QSlider::valueChanged, this, &PhysicsEngineTab::onSliderBarnesHutThreshold);

    connect(ui->spinSofteningFactor, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value) {
        m_cachedParams_PE.insert("SofteningFactor", value);
    });

    connect(ui->comboBoxODESolver, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        m_cachedParams_PE.insert("ODESolver", text);
    });

    connect(ui->spinAdaptiveError, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value) {
        m_cachedParams_PE.insert("AdaptiveErrorTolerance", value);
    });

    connect(ui->comboBoxGPUDevice, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        m_cachedParams_PE.insert("GPUDevice", text);
    });

    connect(ui->spinBlockSize, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        m_cachedParams_PE.insert("BlockSize", value);
    });

    connect(ui->checkBoxDoublePrecision, &QCheckBox::toggled, this, [this](bool checked) {
        m_cachedParams_PE.insert("DoublePrecision", checked);
    });

    connect(ui->checkBoxEnableCollisions, &QCheckBox::toggled, this, [this](bool checked) {
        m_cachedParams_PE.insert("EnableCollisions", checked);
    });

    connect(ui->comboBoxDetectionMethod, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        m_cachedParams_PE.insert("DetectionMethod", text);
    });
}

PhysicsEngineTab::~PhysicsEngineTab()
{
    delete ui;
}

void PhysicsEngineTab::loadSettings(const QVariantMap& params, bool force)
{
    if (m_isLoaded && !force)
    {
        if (!params.isEmpty())
        {
            for (auto it = params.constBegin(); it != params.constEnd(); ++it)
                m_cachedParams_PE.insert(it.key(), it.value());
        }
        return;
    }

    QSettings PE_settings;
    QVariantMap PE_Source;

    // If params is provided, use it as source; otherwise load from QSettings
    if (!params.isEmpty())
    {
        PE_Source = params;
    }
    else
    {
        // Load from saved settings
        PE_Source.insert("GravityModel", PE_settings.value("physics/gravityModel", "Newtonian (Direct N-body)"));
        PE_Source.insert("BarnesHutTheta", PE_settings.value("physics/barnesHutThreshold", 0.5));
        PE_Source.insert("SofteningFactor", PE_settings.value("physics/softeningFactor", 1e9));
        PE_Source.insert("ODESolver", PE_settings.value("physics/odeSolver", "RKF45 (Adaptive)"));
        PE_Source.insert("AdaptiveErrorTolerance", PE_settings.value("physics/adaptiveError", 1e-6));
        PE_Source.insert("GPUDevice", PE_settings.value("physics/gpuDevice", "NVIDIA GeForce RTX 4060 (8GB)"));
        PE_Source.insert("BlockSize", PE_settings.value("physics/blockSize", 256));
        PE_Source.insert("DoublePrecision", PE_settings.value("physics/doublePrecision", false));
        PE_Source.insert("EnableCollisions", PE_settings.value("physics/enableCollisions", true));
        PE_Source.insert("DetectionMethod", PE_settings.value("physics/detectionMethod", "Continuous (CCD)"));
    }

    // Cache the loaded parameters
    for (auto it = PE_Source.constBegin(); it != PE_Source.constEnd(); ++it)
    {
        m_cachedParams_PE.insert(it.key(), it.value());
    }

    auto get = [&](const QString &key, const QVariant &def) -> QVariant
    {
        return m_cachedParams_PE.contains(key) ? m_cachedParams_PE.value(key) : def;
    };

    auto setComboByText = [&](QComboBox* cb, const QString &text)
    {
        int idx = cb->findText(text);
        if (idx >= 0) cb->setCurrentIndex(idx);
        else {
            cb->addItem(text);
            cb->setCurrentIndex(cb->count() - 1);
        }
    };

    QLocale loc = QLocale::c();

    // Block all signals while loading to prevent overwriting cached values
    ui->comboBoxGravityModel->blockSignals(true);
    ui->sliderBarnesHutThreshold->blockSignals(true);
    ui->spinSofteningFactor->blockSignals(true);
    ui->comboBoxODESolver->blockSignals(true);
    ui->spinAdaptiveError->blockSignals(true);
    ui->comboBoxGPUDevice->blockSignals(true);
    ui->spinBlockSize->blockSignals(true);
    ui->checkBoxDoublePrecision->blockSignals(true);
    ui->checkBoxEnableCollisions->blockSignals(true);
    ui->comboBoxDetectionMethod->blockSignals(true);

    // Apply settings to UI
    setComboByText(ui->comboBoxGravityModel, get("GravityModel", "Newtonian (Direct N-body)").toString());

    double theta = get("BarnesHutTheta", 0.5).toDouble();
    int sliderVal = qBound(1, qRound(theta * 10.0), 20);
    ui->sliderBarnesHutThreshold->setValue(sliderVal);
    ui->labelBarnesHutThreshold->setText(loc.toString(theta, 'f', 1));

    double softening = get("SofteningFactor", 1e9).toDouble();
    ui->spinSofteningFactor->setValue(softening);

    setComboByText(ui->comboBoxODESolver, get("ODESolver", "RKF45 (Adaptive)").toString());

    double tol = get("AdaptiveErrorTolerance", 1e-6).toDouble();
    ui->spinAdaptiveError->setValue(tol);

    setComboByText(ui->comboBoxGPUDevice, get("GPUDevice", "NVIDIA GeForce RTX 4060 (8GB)").toString());

    int blockSize = get("BlockSize", 256).toInt();
    ui->spinBlockSize->setValue(blockSize);

    bool doublePrec = get("DoublePrecision", false).toBool();
    ui->checkBoxDoublePrecision->setChecked(doublePrec);

    bool enableColl = get("EnableCollisions", true).toBool();
    ui->checkBoxEnableCollisions->setChecked(enableColl);

    setComboByText(ui->comboBoxDetectionMethod, get("DetectionMethod", "Continuous (CCD)").toString());

    // Unblock all signals
    ui->comboBoxGravityModel->blockSignals(false);
    ui->sliderBarnesHutThreshold->blockSignals(false);
    ui->spinSofteningFactor->blockSignals(false);
    ui->comboBoxODESolver->blockSignals(false);
    ui->spinAdaptiveError->blockSignals(false);
    ui->comboBoxGPUDevice->blockSignals(false);
    ui->spinBlockSize->blockSignals(false);
    ui->checkBoxDoublePrecision->blockSignals(false);
    ui->checkBoxEnableCollisions->blockSignals(false);
    ui->comboBoxDetectionMethod->blockSignals(false);




    m_isLoaded = true;
}


void PhysicsEngineTab::SaveSettings()
{
    QSettings PE_settings;

    PE_settings.setValue("physics/gravityModel", ui->comboBoxGravityModel->currentText());
    PE_settings.setValue("physics/barnesHutThreshold", sliderToFactor(ui->sliderBarnesHutThreshold->value()));
    PE_settings.setValue("physics/softeningFactor", ui->spinSofteningFactor->value());
    PE_settings.setValue("physics/odeSolver", ui->comboBoxODESolver->currentText());
    PE_settings.setValue("physics/adaptiveError", ui->spinAdaptiveError->value());
    PE_settings.setValue("physics/gpuDevice", ui->comboBoxGPUDevice->currentText());
    PE_settings.setValue("physics/blockSize", ui->spinBlockSize->value());
    PE_settings.setValue("physics/doublePrecision", ui->checkBoxDoublePrecision->isChecked());
    PE_settings.setValue("physics/enableCollisions", ui->checkBoxEnableCollisions->isChecked());
    PE_settings.setValue("physics/detectionMethod", ui->comboBoxDetectionMethod->currentText());

    // Update cached params
    m_cachedParams_PE.insert("GravityModel", ui->comboBoxGravityModel->currentText());
    m_cachedParams_PE.insert("BarnesHutTheta", sliderToFactor(ui->sliderBarnesHutThreshold->value()));
    m_cachedParams_PE.insert("SofteningFactor", ui->spinSofteningFactor->value());
    m_cachedParams_PE.insert("ODESolver", ui->comboBoxODESolver->currentText());
    m_cachedParams_PE.insert("AdaptiveErrorTolerance", ui->spinAdaptiveError->value());
    m_cachedParams_PE.insert("GPUDevice", ui->comboBoxGPUDevice->currentText());
    m_cachedParams_PE.insert("BlockSize", ui->spinBlockSize->value());
    m_cachedParams_PE.insert("DoublePrecision", ui->checkBoxDoublePrecision->isChecked());
    m_cachedParams_PE.insert("EnableCollisions", ui->checkBoxEnableCollisions->isChecked());
    m_cachedParams_PE.insert("DetectionMethod", ui->comboBoxDetectionMethod->currentText());
}


void PhysicsEngineTab::onSliderBarnesHutThreshold(int value)
{
    double factor = sliderToFactor(value);
    // update visible label
    ui->labelBarnesHutThreshold->setText(QLocale::c().toString(factor, 'f', 1));
    // cache the numeric value for later use / saving
    m_cachedParams_PE.insert("BarnesHutTheta", factor);
}

void PhysicsEngineTab::applyParams(const QVariantMap& params)
{
}

double PhysicsEngineTab::sliderToFactor(int sliderValue) const
{
    // slider uses steps of 0.1 -> convert to factor (e.g. 5 -> 0.5)
    return static_cast<double>(sliderValue) * 0.1;
}

int PhysicsEngineTab::factorToSlider(double factor) const
{
    return qBound(1, qRound(factor * 10.0), 100);
}