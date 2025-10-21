//
// Created by DevAccount on 20/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CommunicationTab.h" resolved


#include "UI/components/Setting/Tabs/communicationtab.h"

#include "ui_CommunicationTab.h"


CommunicationTab::CommunicationTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::CommunicationTab)
{
    ui->setupUi(this);
}

CommunicationTab::~CommunicationTab()
{
    delete ui;
}