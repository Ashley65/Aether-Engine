//
// Created by DevAccount on 20/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_droneTab.h" resolved


#include "UI/components/Setting/Tabs/dronetab.h"

#include "ui_droneTab.h"


droneTab::droneTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::droneTab)
{
    ui->setupUi(this);
}

droneTab::~droneTab()
{
    delete ui;
}