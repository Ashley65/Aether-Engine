//
// Created by DevAccount on 12/10/2025.
//

#ifndef OPENWORLD_DOCKER_H
#define OPENWORLD_DOCKER_H
#pragma once
#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QFrame>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QPropertyAnimation>
#include "dockerPanel.h"

#include "dockerOverlay.h"
#include "FloatingPanel.h"

class DynamicDocker : public QWidget {
    Q_OBJECT
public:
    enum DockArea {
        LeftArea,
        RightArea,
        TopArea,
        BottomArea,
        CenterArea,
        FloatingArea
    };

    explicit DynamicDocker(QWidget *parent = nullptr);

    void addDockWidget(const QString &id, const QString &title,
                       QWidget *widget, DockArea area);
    void removeDockWidget(const QString &id);
    QWidget* getDockWidget(const QString &id);
    void setDockVisible(const QString &id, bool visible);
    bool isDockVisible(const QString &id) const;

    // Floating panels
    void setDockFloating(const QString &id, bool floating);
    bool isDockFloating(const QString &id) const;

    // Configure splitter sizes
    void setSplitterSizes(Qt::Orientation orientation, const QList<int> &sizes);
    QList<int> getSplitterSizes(Qt::Orientation orientation) const;

    // Auto-resize
    void autoResizePanels();

private slots:
    void onPanelDragStarted(DockPanel *panel);
    void onFloatingPanelDockRequested(FloatingPanel *floating, const QPoint &globalPos);
    void onFloatingPanelClosed(FloatingPanel *floating);

private:
    void setupUI();
    QSplitter* getOrCreateSplitter(DockArea area);
    void autoResizeSplitter(QSplitter *splitter);
    DockOverlay::DropZone getDropZone(const QPoint &pos);
    void makeFloating(const QString &id);
    void dockFloating(const QString &id, DockArea area);
    DockArea dropZoneToArea(DockOverlay::DropZone zone);

    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;      // Horizontal: Left | Center | Right
    QSplitter *m_centerSplitter;    // Vertical: Top | Center | Bottom
    QWidget *m_centerWidget;
    DockOverlay *m_overlay;

    QMap<QString, DockPanel*> m_dockPanels;
    QMap<QString, DockArea> m_dockAreas;
    QMap<QString, FloatingPanel*> m_floatingPanels;

    QString m_draggedPanelId;
    QTimer *m_resizeTimer;
};

#endif //OPENWORLD_DOCKER_H