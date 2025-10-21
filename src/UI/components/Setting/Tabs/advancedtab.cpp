//
// Created by DevAccount on 20/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AdvancedTab.h" resolved


#include "UI/components/Setting/Tabs/advancedtab.h"

#include "ui_AdvancedTab.h"


AdvancedTab::AdvancedTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::AdvancedTab)
{
    ui->setupUi(this);
}

AdvancedTab::~AdvancedTab()
{
    delete ui;
}