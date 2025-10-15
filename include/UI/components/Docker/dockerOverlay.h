//
// Created by DevAccount on 13/10/2025.
//

#ifndef OPENWORLD_DOCKEROVERLAY_H
#define OPENWORLD_DOCKEROVERLAY_H

#pragma once
#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>


class DockOverlay : public QWidget {
    Q_OBJECT
public:
    enum DropZone {
        NoZone,
        LeftZone,
        RightZone,
        TopZone,
        BottomZone,
        CenterZone
    };

    explicit DockOverlay(QWidget *parent = nullptr);
    void showOverlay(const QRect &targetRect, DropZone zone);
    void hideOverlay();
    DropZone currentZone() const { return m_currentZone; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    DropZone m_currentZone;
    QPropertyAnimation *m_animation;
};

#endif //OPENWORLD_DOCKEROVERLAY_H