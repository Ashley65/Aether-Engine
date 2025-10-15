//
// Created by DevAccount on 13/10/2025.
//

#ifndef OPENWORLD_FLOATINGPANEL_H
#define OPENWORLD_FLOATINGPANEL_H
#pragma once


#include "dockerPanel.h"


class FloatingPanel : public QWidget {
    Q_OBJECT
public:
    explicit FloatingPanel(DockPanel *panel, QWidget *parent = nullptr);

    DockPanel* dockPanel() const { return m_dockPanel; }
    void setDockPanel(DockPanel *panel);

    signals:
        void dockRequested(FloatingPanel *floating, const QPoint &globalPos);
        void closed(FloatingPanel *floating);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    DockPanel *m_dockPanel;
    QVBoxLayout *m_layout;
    bool m_dragging;
    QPoint m_dragStartPos;
};
#endif //OPENWORLD_FLOATINGPANEL_H