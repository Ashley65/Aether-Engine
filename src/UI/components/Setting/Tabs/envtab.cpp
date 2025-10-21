//
// Created by DevAccount on 20/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EnvTab.h" resolved


#include "UI/components/Setting/Tabs/envtab.h"

#include "../resources/ui/settingComponents/ui_envtab.h"


EnvTab::EnvTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::EnvTab)
{
    ui->setupUi(this);
}

EnvTab::~EnvTab()
{
    delete ui;
}