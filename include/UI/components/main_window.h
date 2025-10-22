//
// Created by DevAccount on 09/10/2025.
//

#ifndef OPENWORLD_MAIN_WINDOW_H
#define OPENWORLD_MAIN_WINDOW_H

#include <QWidget>
#include <UI/components/menu_bar.h>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QApplication>
#include <QScreen>
#include <QDockWidget>
#include <QMap>


#include "Docker/Docker.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class main_window;
}

QT_END_NAMESPACE

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget* parent = nullptr);
    ~main_window() override;
    void animationStep(bool toFullscreen);
    void setupDockerPanels();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;


private:
    Ui::main_window* ui;
    MenuBar* menuBar;
    QMap<QString, QDockWidget*> m_dockWidgets;
    QWidget* m_centralEditor;
    void WindowsFlags();
    bool resizing = false;
    QRect originalGeometry;
    QPoint dragStartPos;
    enum ResizeRegion { None, Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight };
    ResizeRegion resizeRegion = None;
    int borderWidth = 8; // px
};


#endif //OPENWORLD_MAIN_WINDOW_H