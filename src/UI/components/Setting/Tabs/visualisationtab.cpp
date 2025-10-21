//
// Created by DevAccount on 20/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VisualisationTab.h" resolved

#include "UI/components/Setting/Tabs/visualisationtab.h"
#include "../resources/ui/settingComponents/ui_visualisationtab.h"


VisualisationTab::VisualisationTab(QWidget* parent) :
    QWidget(parent), ui(new Ui::VisualisationTab)
{
    ui->setupUi(this);
}

VisualisationTab::~VisualisationTab()
{
    delete ui;
}