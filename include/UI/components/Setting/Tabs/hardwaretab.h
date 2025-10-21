//
// Created by DevAccount on 19/10/2025.
//

#ifndef AETHER_ENGINE_HARDWARETAB_H
#define AETHER_ENGINE_HARDWARETAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class HardwareTab;
}

QT_END_NAMESPACE

class HardwareTab : public QWidget
{
    Q_OBJECT

public:
    explicit HardwareTab(QWidget* parent = nullptr);
    ~HardwareTab() override;

private:
    Ui::HardwareTab* ui;
};


#endif //AETHER_ENGINE_HARDWARETAB_H