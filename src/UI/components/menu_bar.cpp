//
// Created by DevAccount on 09/10/2025.
//

#include <UI/components/menu_bar.h>
#include <QAction>
#include <qboxlayout.h>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>

#include "UI/components/main_window.h"


MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent)
{
    addTitle();

    fileMenu();
    missionMenu();
    viewMenu();
    environmentMenu();
    logMenu();
    helpMenu();
    addWindowButtons();
    setStyleSheet(
    "QMenuBar {"
    "  background: #232b36;"
    "  border: none;"
    "  padding: 0 12px;"
    "  height: 32px;"
    "}"
    "QMenuBar::item {"
    "  color: #eaf1fb;"
    "  padding: 0 18px;"
    "  font-size: 14px;"
    "  background: transparent;"
    "}"
    "QMenuBar::item:selected {"
    "  background: #2d3642;"
    "  color: #eaf1fb;"
    "}"
    "QLabel#titleLabel {"
    "  color: #3fa6ff;"
    "  font-weight: bold;"
    "  font-size: 15px;"
    "  padding-left: 4px;"
    "}"

);



}

void MenuBar::addTitle()
{
    QLabel* titleLabel = new QLabel("Open World ", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #222;"
        "    font-weight: bold;"
        "    font-size: 11px;"
        "    padding-right: 10px;"
        "}"
    );

    this->setCornerWidget(titleLabel, Qt::TopLeftCorner);
}


void MenuBar::addWindowButtons()
{

    windowButtonWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(windowButtonWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    QPushButton* minimizeBtn = new QPushButton("-", windowButtonWidget);
    maximizeBtn = new QPushButton("□", windowButtonWidget); // Store as member
    QPushButton* closeBtn = new QPushButton("×", windowButtonWidget);

    layout->addWidget(minimizeBtn);
    layout->addWidget(maximizeBtn);
    layout->addWidget(closeBtn);

    connect(minimizeBtn, &QPushButton::clicked, [this]() {
        QWidget* win = window();
        QRect startRect = win->geometry();
        QRect endRect = QRect(startRect.x(), startRect.y() + startRect.height() / 2, startRect.width(), 0);

        QPropertyAnimation* anim = new QPropertyAnimation(win, "geometry");
        anim->setDuration(250);
        anim->setStartValue(startRect);
        anim->setEndValue(endRect);

        connect(anim, &QPropertyAnimation::finished, [win, anim]() {
            win->setWindowState(Qt::WindowMinimized);
            anim->deleteLater();
        });

        anim->start();
    });
    connect(maximizeBtn, &QPushButton::clicked, [this]() {
        main_window* win = qobject_cast<main_window*>(window());
        if (!win) return;
        if (win->isMaximized()) {
            win->setWindowState(Qt::WindowMaximized);
            win->animationStep(false); // Restore to default/original size
        } else {
            win->animationStep(true);  // Maximize to fullscreen
        }
        updateMaximizeIcon();
    });
    connect(closeBtn, &QPushButton::clicked, [this]() {
        window()->close();
    });


    window()->installEventFilter(this);
    updateMaximizeIcon();

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setCornerWidget(windowButtonWidget, Qt::TopRightCorner);

    QString buttonStyle =
    "QPushButton {"
    "    background: transparent;"
    "    border: none;"
    "    color: #222;"
    "    font-size: 16px;"
    "    padding: 2px 8px;"
    "    min-width: 30px;"
    "}"
    "QPushButton:hover {"
    "    background: #a8c0ff;"
    "}";

    minimizeBtn->setStyleSheet(buttonStyle);
    maximizeBtn->setStyleSheet(buttonStyle);
    closeBtn->setStyleSheet(buttonStyle + "QPushButton:hover { background: #ff4444; color: white; }");
}

bool MenuBar::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == window() && event->type() == QEvent::WindowStateChange) {
        updateMaximizeIcon();
    }
    return QMenuBar::eventFilter(watched, event);
}

void MenuBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QWidget* win = window();
        if (win->isMaximized() || win->isMinimized()) {
            win->showNormal();
            QCoreApplication::processEvents();
            // Align window top-center to cursor
            QPoint cursorPos = event->globalPos();
            int winWidth = win->width();
            QPoint newTopLeft = cursorPos - QPoint(winWidth / 2, 0);
            win->move(newTopLeft);
        }
        dragPosition = event->globalPos() - win->frameGeometry().topLeft();
        dragging = true;
        event->accept();
    }
    QMenuBar::mousePressEvent(event);
}


void MenuBar::mouseMoveEvent(QMouseEvent* event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        window()->move(event->globalPos() - dragPosition);
        event->accept();
    }
    QMenuBar::mouseMoveEvent(event);
}

void MenuBar::mouseReleaseEvent(QMouseEvent* event)
{
    dragging = false;
    QMenuBar::mouseReleaseEvent(event);
}

void MenuBar::updateMaximizeIcon()
{
    if (window()->isMaximized())
        maximizeBtn->setText("❐"); // Use restore icon
    else
        maximizeBtn->setText("□"); // Use maximize icon
}

void MenuBar::setTheme(ThemeType theme)
{
    QString darkStyle =
       "QMenuBar { background: #232b36; border: none; padding: 0 12px; height: 32px; }"
       "QMenuBar::item { color: #eaf1fb; padding: 0 18px; font-size: 14px; background: transparent; }"
       "QMenuBar::item:selected { background: #2d3642; color: #eaf1fb; }"
       "QLabel#titleLabel { color: #3fa6ff; font-weight: bold; font-size: 15px; padding-left: 4px; }"
       "QLabel#statusLabel { color: #6fffb0; font-size: 13px; padding-right: 8px; }";

    QString lightStyle =
        "QMenuBar { background: #f5f7fa; border: none; padding: 0 12px; height: 32px; }"
        "QMenuBar::item { color: #232b36; padding: 0 18px; font-size: 14px; background: transparent; }"
        "QMenuBar::item:selected { background: #eaf1fb; color: #232b36; }"
        "QLabel#titleLabel { color: #3fa6ff; font-weight: bold; font-size: 15px; padding-left: 4px; }"
        "QLabel#statusLabel { color: #2ecc71; font-size: 13px; padding-right: 8px; }";

    setStyleSheet(theme == ThemeType::Dark ? darkStyle : lightStyle);
}


void MenuBar::fileMenu()
{
    // File Menu
    QMenu* fileMenu = addMenu(tr("&File"));
    QAction* newMissionAction = fileMenu->addAction(tr("&New Mission"));
    connect(newMissionAction, &QAction::triggered, this, &MenuBar::newMission);
    QAction* loadReplayAction = fileMenu->addAction(tr("&Load Replay/Recording"));
    connect(loadReplayAction, &QAction::triggered, this, &MenuBar::loadReplayRecording);
    QAction* saveLogAction = fileMenu->addAction(tr("&Save Log/Recording"));
    connect(saveLogAction, &QAction::triggered, this, &MenuBar::saveLogRecording);
    fileMenu->addSeparator();
    QAction* settingsAction = fileMenu->addAction(tr("&Settings"));
    connect(settingsAction, &QAction::triggered, this, &MenuBar::openSettings);
    QAction* exitAction = fileMenu->addAction(tr("E&xit"));
    connect(exitAction, &QAction::triggered, this, &MenuBar::exitApplication);
}

void MenuBar::missionMenu()
{
    QMenu* missionMenu = addMenu(tr("&Mission"));
    QAction* startAction = missionMenu->addAction(tr("&Start Simulation"));
    connect(startAction, &QAction::triggered, this, &MenuBar::startSimulationRequested);
    QAction* pauseAction = missionMenu->addAction(tr("&Pause Simulation"));
    connect(pauseAction, &QAction::triggered, this, &MenuBar::pauseSimulationRequested);
    QAction* stopAction = missionMenu->addAction(tr("&Stop Simulation"));
    connect(stopAction, &QAction::triggered, this, &MenuBar::stopSimulationRequested);
    QAction* restartAction = missionMenu->addAction(tr("&Restart Simulation"));
    connect(restartAction, &QAction::triggered, this, &MenuBar::restartSimulationRequested);
    missionMenu->addSeparator();
    QAction* toggleAIAction = missionMenu->addAction(tr("Toggle &AI Control"));
    toggleAIAction->setCheckable(true);
    connect(toggleAIAction, &QAction::toggled, this, &MenuBar::toggleAIControlRequested);
    QAction* returnToBaseAction = missionMenu->addAction(tr("&Return to Base"));
    connect(returnToBaseAction, &QAction::triggered, this, &MenuBar::returnToBaseRequested);
}

void MenuBar::viewMenu()
{
    QMenu* viewMenu = addMenu(tr("&View"));
    QAction* toggle3DAction = viewMenu->addAction(tr("Toggle &3D View"));
    toggle3DAction->setCheckable(true);
    connect(toggle3DAction, &QAction::toggled, this, &MenuBar::toggle3DView);
    QAction* toggleGraphsAction = viewMenu->addAction(tr("Toggle &Graphs"));
    toggleGraphsAction->setCheckable(true);
    connect(toggleGraphsAction, &QAction::toggled, this, &MenuBar::toggleGraphs);
    QAction* toggleMinimapAction = viewMenu->addAction(tr("Toggle &Minimap"));
    toggleMinimapAction->setCheckable(true);
    connect(toggleMinimapAction, &QAction::toggled, this, &MenuBar::toggleMinimap);
    viewMenu->addSeparator();
    QMenu* themeSubMenu = viewMenu->addMenu(tr("&Theme"));
    QAction* darkThemeAction = themeSubMenu->addAction(tr("&Dark"));
    QAction* lightThemeAction = themeSubMenu->addAction(tr("&Light"));
    connect(darkThemeAction, &QAction::triggered, this, [this]() { setTheme(ThemeType::Dark); });
    connect(lightThemeAction, &QAction::triggered, this, [this]() { setTheme(ThemeType::Light); });

    viewMenu->addSeparator();
    QAction* resetUILayoutAction = viewMenu->addAction(tr("&Reset UI Layout"));
    connect(resetUILayoutAction, &QAction::triggered, this, &MenuBar::resetUILayout);
}

void MenuBar::environmentMenu()
{
    QMenu* environmentMenu = addMenu(tr("&Environment"));
    QAction* droneAction = environmentMenu->addAction(tr("&Drone"));
    connect(droneAction, &QAction::triggered, this, [this]() { switchEnvironmentRequested(EnvironmentType::Drone); });
    QAction* spaceAction = environmentMenu->addAction(tr("&Space"));
    connect(spaceAction, &QAction::triggered, this, [this]() { switchEnvironmentRequested(EnvironmentType::Space); });
    QAction* roverAction = environmentMenu->addAction(tr("&Rover"));
    connect(roverAction, &QAction::triggered, this, [this]() { switchEnvironmentRequested(EnvironmentType::Rover); });
    environmentMenu->addSeparator();
    QAction* envSettingsAction = environmentMenu->addAction(tr("&Environment Settings"));
    connect(envSettingsAction, &QAction::triggered, this, &MenuBar::openEnvironmentSettings);
}

void MenuBar::logMenu()
{
    QMenu* logMenu = addMenu(tr("&Log"));
    QAction* systemLogsAction = logMenu->addAction(tr("&System Logs"));
    connect(systemLogsAction, &QAction::triggered, this, &MenuBar::showSystemLogsRequested);
    QAction* aiDecisionsAction = logMenu->addAction(tr("&AI Decisions"));
    connect(aiDecisionsAction, &QAction::triggered, this, &MenuBar::showAIDecisionsRequested);
    QAction* anomalyLogsAction = logMenu->addAction(tr("&Anomaly Logs"));
    connect(anomalyLogsAction, &QAction::triggered, this, &MenuBar::showAnomalyLogsRequested);
    logMenu->addSeparator();
    QAction* exportLogsAction = logMenu->addAction(tr("&Export Logs"));
    connect(exportLogsAction, &QAction::triggered, this, &MenuBar::exportLogsRequested);
}

void MenuBar::helpMenu()
{
    QMenu* helpMenu = addMenu(tr("&Help"));
    QAction* documentationAction = helpMenu->addAction(tr("&Documentation"));
    connect(documentationAction, &QAction::triggered, this, &MenuBar::openDocumentationRequested);
    QAction* shortcutsAction = helpMenu->addAction(tr("&Shortcuts"));
    connect(shortcutsAction, &QAction::triggered, this, &MenuBar::showShortcutsRequested);
    helpMenu->addSeparator();
    QAction* aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, &MenuBar::showAboutRequested);
    QAction* diagnosticsAction = helpMenu->addAction(tr("&Diagnostics"));
    connect(diagnosticsAction, &QAction::triggered, this, &MenuBar::showDiagnosticsRequested);
}
