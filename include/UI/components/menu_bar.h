//
// Created by DevAccount on 09/10/2025.
//

#ifndef OPENWORLD_MENU_BAR_H
#define OPENWORLD_MENU_BAR_H
#pragma once
#include <QMenuBar>
#include <QPushButton>
#include <QString>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    private:
        QWidget* windowButtonWidget;
        QPushButton* maximizeBtn; // Store as member
        QPoint dragPosition;
        bool dragging = false;
        void addWindowButtons();
        void updateMaximizeIcon();


    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        bool eventFilter(QObject* watched, QEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;


    public:
        explicit MenuBar(QWidget *parent = nullptr);

        void addTitle();
        enum class EnvironmentType { Drone, Space, Rover };
        enum class ThemeType { Dark, Light };
        void fileMenu();
        void missionMenu();
        void viewMenu();
        void environmentMenu();
        void logMenu();
        void helpMenu();
        void setTheme(ThemeType theme);


    signals:
        // File
        void newMission();
        void loadReplayRecording();
        void saveLogRecording();
        void exitApplication();
        void openSettings();

        // Mission
        void startSimulationRequested();
        void pauseSimulationRequested();
        void stopSimulationRequested();
        void restartSimulationRequested();
        void toggleAIControlRequested(bool enabled);
        void returnToBaseRequested();

        // View
        void toggle3DView(bool visible);
        void toggleGraphs(bool visible);
        void toggleMinimap(bool visible);
        void themeChanged(ThemeType theme);
        void resetUILayout();

        // Environment
        void switchEnvironmentRequested(EnvironmentType env);
        void openEnvironmentSettings();

        // Logs
        void showSystemLogsRequested();
        void showAIDecisionsRequested();
        void showAnomalyLogsRequested();
        void exportLogsRequested();

        // Help
        void openDocumentationRequested();
        void showShortcutsRequested();
        void showAboutRequested();
        void showDiagnosticsRequested();
};



#endif //OPENWORLD_MENU_BAR_H