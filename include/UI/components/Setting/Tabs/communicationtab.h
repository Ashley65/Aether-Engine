//
// Created by DevAccount on 20/10/2025.
//

#ifndef AETHER_ENGINE_COMMUNICATIONTAB_H
#define AETHER_ENGINE_COMMUNICATIONTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class CommunicationTab;
}

QT_END_NAMESPACE

class CommunicationTab : public QWidget
{
    Q_OBJECT

public:
    explicit CommunicationTab(QWidget* parent = nullptr);
    ~CommunicationTab() override;

private:
    Ui::CommunicationTab* ui;
};


#endif //AETHER_ENGINE_COMMUNICATIONTAB_H