//
// Created by DevAccount on 16/10/2025.
//

#ifndef AETHER_ENGINE_PHYSICSENGINETAB_H
#define AETHER_ENGINE_PHYSICSENGINETAB_H
#pragma once
#include <QWidget>
#include <QVariantMap>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class PhysicsEngineTab;
}

QT_END_NAMESPACE

class PhysicsEngineTab : public QWidget
{
    Q_OBJECT

public:
    explicit PhysicsEngineTab(QWidget* parent = nullptr);
    ~PhysicsEngineTab() override;
    void loadSettings(const QVariantMap& params, bool force);
    QVariantMap getParams() const;
    void SaveSettings();

    bool isLoading() const;
    bool isLoaded() const { return m_isLoaded; }


private slots:
    void onSliderBarnesHutThreshold(int value);

private:
    Ui::PhysicsEngineTab* ui;
    bool m_isLoaded = false;
    QVariantMap m_cachedParams_PE;
    void applyParams(const QVariantMap& params);

    double sliderToFactor(int sliderValue) const; // maps 1..100 -> 0.1..10.0
    int factorToSlider(double factor) const;

};


#endif //AETHER_ENGINE_PHYSICSENGINETAB_H