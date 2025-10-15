/********************************************************************************
** Form generated from reading UI file 'settingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWINDOW_H
#define UI_SETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *SettingWindow)
    {
        if (SettingWindow->objectName().isEmpty())
            SettingWindow->setObjectName("SettingWindow");
        SettingWindow->resize(1075, 736);
        tabWidget = new QTabWidget(SettingWindow);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 0, 1051, 741));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        tabWidget->setTabPosition(QTabWidget::TabPosition::West);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());

        retranslateUi(SettingWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SettingWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingWindow)
    {
        SettingWindow->setWindowTitle(QCoreApplication::translate("SettingWindow", "SettingWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SettingWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SettingWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWindow: public Ui_SettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
