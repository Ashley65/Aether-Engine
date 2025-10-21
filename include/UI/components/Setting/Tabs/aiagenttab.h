//
// Created by DevAccount on 19/10/2025.
//

#ifndef AETHER_ENGINE_AIAGENTTAB_H
#define AETHER_ENGINE_AIAGENTTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class AIAgentTab;
}

QT_END_NAMESPACE

class AIAgentTab : public QWidget
{
    Q_OBJECT

public:
    explicit AIAgentTab(QWidget* parent = nullptr);
    ~AIAgentTab() override;

private:
    Ui::AIAgentTab* ui;
};


#endif //AETHER_ENGINE_AIAGENTTAB_H