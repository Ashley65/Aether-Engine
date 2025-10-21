//
// Created by DevAccount on 16/10/2025.
//

#ifndef AETHER_ENGINE_SIMULATIONTAB_H
#define AETHER_ENGINE_SIMULATIONTAB_H
#pragma once
#include <QWidget>
#include <QVariantMap>


QT_BEGIN_NAMESPACE

namespace Ui { class SimulationTab; }

QT_END_NAMESPACE

class SimulationTab : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationTab(QWidget* parent = nullptr);
    ~SimulationTab() override;

    //Load and refresh UI data
    void loadSettings(const QVariantMap& params, bool force);

    bool isLoading() const;
    bool isLoaded() const { return m_isLoaded; }

private slots:
    void onRealTimeSliderChanged(int value);


private:
    void applyParams(const QVariantMap& params);

    double sliderToFactor(int sliderValue) const; // maps 1..100 -> 0.1..10.0
    int factorToSlider(double factor) const;

    Ui::SimulationTab* ui;
    bool m_isLoaded = false;
    QVariantMap m_cachedParams_se;
};


#endif //AETHER_ENGINE_SIMULATIONTAB_H