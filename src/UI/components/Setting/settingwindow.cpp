//
// Created by DevAccount on 14/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWindow.h" resolved

#include <UI/components/Setting/settingwindow.h>
#include "../resources/ui/ui_SettingWindow.h"


SettingWindow::SettingWindow(QWidget* parent) :
    QWidget(parent), ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    while (ui -> tabWidget ->count() > 0)
        ui -> tabWidget ->removeTab(0);

    QList<TabInfo> tabs = {
        { "simulation", "Simulation", ":/icons/Lucide/icons/gauge.svg" },
        { "physics", "Physics Engine", ":/icons/Lucide/icons/cpu.svg" },
        { "drone", "Drone Settings", ":/icons/Lucide/icons/rocket.svg" },
        { "ai", "AI Agent", ":/icons/Lucide/icons/zap.svg" },
        { "hardware", "Hardware/HIL", ":/icons/Lucide/icons/harddrive.svg" },
        { "communication", "Communication", ":/icons/Lucide/icons/radio.svg" },
        { "environment", "Environment", ":/icons/Lucide/icons/globe.svg" },
        { "visualization", "Visualization", ":/icons/Lucide/icons/eye.svg" },
        { "advanced", "Advanced", ":/icons/Lucide/icons/settings.svg" }
    };

    for (const auto& tab : tabs) {
        QWidget* page = new QWidget();
        ui->tabWidget->addTab(page, QIcon(tab.iconPath), tab.label);
    }

}

SettingWindow::~SettingWindow()
{
    delete ui;
}