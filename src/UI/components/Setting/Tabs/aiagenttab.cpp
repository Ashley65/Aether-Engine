//
// Created by DevAccount on 19/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AIAgentTab.h" resolved


#include "UI/components/Setting/Tabs/aiagenttab.h"

#include "ui_AIAgentTab.h"


AIAgentTab::AIAgentTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::AIAgentTab)
{
    ui->setupUi(this);
}

AIAgentTab::~AIAgentTab()
{
    delete ui;
}