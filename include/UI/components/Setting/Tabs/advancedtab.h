//
// Created by DevAccount on 20/10/2025.
//

#ifndef AETHER_ENGINE_ADVANCEDTAB_H
#define AETHER_ENGINE_ADVANCEDTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class AdvancedTab;
}

QT_END_NAMESPACE

class AdvancedTab : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedTab(QWidget* parent = nullptr);
    ~AdvancedTab() override;

private:
    Ui::AdvancedTab* ui;
};


#endif //AETHER_ENGINE_ADVANCEDTAB_H