//
// Created by DevAccount on 20/10/2025.
//

#ifndef AETHER_ENGINE_ENVTAB_H
#define AETHER_ENGINE_ENVTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class EnvTab;
}

QT_END_NAMESPACE

class EnvTab : public QWidget
{
    Q_OBJECT

public:
    explicit EnvTab(QWidget* parent = nullptr);
    ~EnvTab() override;

private:
    Ui::EnvTab* ui;
};


#endif //AETHER_ENGINE_ENVTAB_H