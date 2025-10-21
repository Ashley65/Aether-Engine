//
// Created by DevAccount on 20/10/2025.
//

#ifndef AETHER_ENGINE_DRONETAB_H
#define AETHER_ENGINE_DRONETAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class droneTab;
}

QT_END_NAMESPACE

class droneTab : public QWidget
{
    Q_OBJECT

public:
    explicit droneTab(QWidget* parent = nullptr);
    ~droneTab() override;

private:
    Ui::droneTab* ui;
};


#endif //AETHER_ENGINE_DRONETAB_H