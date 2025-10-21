//
// Created by DevAccount on 20/10/2025.
//

#ifndef AETHER_ENGINE_VISUALISATIONTAB_H
#define AETHER_ENGINE_VISUALISATIONTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class VisualisationTab;
}

QT_END_NAMESPACE

class VisualisationTab : public QWidget
{
    Q_OBJECT

public:
    explicit VisualisationTab(QWidget* parent = nullptr);
    ~VisualisationTab() override;

private:
    Ui::VisualisationTab* ui;
};


#endif //AETHER_ENGINE_VISUALISATIONTAB_H