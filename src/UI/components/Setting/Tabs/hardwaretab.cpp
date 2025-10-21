//
// Created by DevAccount on 19/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_HardwareTab.h" resolved

#include "UI/components/Setting/Tabs/hardwaretab.h"
#include "ui_HardwareTab.h"


HardwareTab::HardwareTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::HardwareTab)
{
    ui->setupUi(this);
}

HardwareTab::~HardwareTab()
{
    delete ui;
}