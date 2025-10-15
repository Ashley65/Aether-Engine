//
// Created by DevAccount on 12/10/2025.
//

#ifndef OPENWORLD_DOCKERPANEL_H
#define OPENWORLD_DOCKERPANEL_H
#pragma once

#include <QFrame>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QApplication>


class DockPanel : public QFrame {
    Q_OBJECT
public:
    explicit DockPanel(const QString &title, QWidget *content, QWidget *parent = nullptr);

    void setContent(QWidget *content);
    QWidget* content() const { return m_content; }
    QString title() const { return m_title; }
    void setFloating(bool floating);
    bool isFloating() const { return m_isFloating; }
    QString panelId() const { return m_panelId; }
    void setPanelId(const QString &id) { m_panelId = id; }

    signals:
        void closeRequested();
    void floatRequested();
    void dragStarted(DockPanel *panel);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QString m_title;
    QString m_panelId;
    QWidget *m_content;
    QLabel *m_titleLabel;
    QPushButton *m_closeBtn;
    QPushButton *m_floatBtn;
    QVBoxLayout *m_layout;
    QWidget *m_titleBar;

    bool m_isFloating;
    bool m_dragging;
    QPoint m_dragStartPos;
};

#endif //OPENWORLD_DOCKERPANEL_H