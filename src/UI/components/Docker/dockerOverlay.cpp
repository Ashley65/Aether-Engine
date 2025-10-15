//
// Created by DevAccount on 13/10/2025.
//

#include <../../../include/UI/components/Docker/dockerOverlay.h>

DockOverlay::DockOverlay(QWidget *parent)
    : QWidget(parent), m_currentZone(NoZone)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    hide();

    m_animation = new QPropertyAnimation(this, "windowOpacity", this);
    m_animation->setDuration(150);
}

void DockOverlay::showOverlay(const QRect &targetRect, DropZone zone) {
    m_currentZone = zone;
    setGeometry(targetRect);

    m_animation->stop();
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(0.7);
    m_animation->start();

    show();
    raise();
    update();
}

void DockOverlay::hideOverlay() {
    m_currentZone = NoZone;
    hide();
}

void DockOverlay::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_currentZone != NoZone) {
        QColor fillColor(0, 120, 212, 180);  // Blue with transparency
        QColor borderColor(0, 120, 212, 255);

        painter.fillRect(rect(), fillColor);
        painter.setPen(QPen(borderColor, 2));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));

        // Draw text
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPointSize(14);
        font.setBold(true);
        painter.setFont(font);

        QString text;
        switch (m_currentZone) {
        case LeftZone: text = "Dock Left"; break;
        case RightZone: text = "Dock Right"; break;
        case TopZone: text = "Dock Top"; break;
        case BottomZone: text = "Dock Bottom"; break;
        case CenterZone: text = "Dock Center"; break;
        default: break;
        }

        painter.drawText(rect(), Qt::AlignCenter, text);
    }
}