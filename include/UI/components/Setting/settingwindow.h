//
// Created by DevAccount on 14/10/2025.
//

#ifndef OPENWORLD_SETTINGWINDOW_H
#define OPENWORLD_SETTINGWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE


namespace Ui
{
    class SettingWindow;
}

QT_END_NAMESPACE

struct TabInfo
{
    QString id;
    QString label;
    QString iconPath;
};

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget* parent = nullptr);
    ~SettingWindow() override;

private:
    Ui::SettingWindow* ui;
};


#endif //OPENWORLD_SETTINGWINDOW_H