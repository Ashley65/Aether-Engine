//
// Created by DevAccount on 13/10/2025.
//

#include <../../../include/UI/components/Docker/FloatingPanel.h>


FloatingPanel::FloatingPanel(DockPanel *panel, QWidget *parent)
    : QWidget(parent, Qt::Window), m_dockPanel(panel), m_dragging(false)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose, false);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(2, 2, 2, 2);

    if (panel) {
        m_layout->addWidget(panel);
        setWindowTitle(panel->title());
        resize(400, 300);
    }

    setStyleSheet("FloatingPanel { border: 2px solid #0078d4; background-color: white; }");
}

void FloatingPanel::setDockPanel(DockPanel *panel) {
    if (m_dockPanel) {
        m_layout->removeWidget(m_dockPanel);
    }
    m_dockPanel = panel;
    if (m_dockPanel) {
        m_layout->addWidget(m_dockPanel);
        setWindowTitle(m_dockPanel->title());
    }
}

void FloatingPanel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPos = event->globalPos() - frameGeometry().topLeft();
        m_dragging = true;
    }
    QWidget::mousePressEvent(event);
}

void FloatingPanel::mouseMoveEvent(QMouseEvent *event) {
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        QPoint newPos = event->globalPos() - m_dragStartPos;
        move(newPos);
        emit dockRequested(this, event->globalPos());
    }
    QWidget::mouseMoveEvent(event);
}

void FloatingPanel::mouseReleaseEvent(QMouseEvent *event) {
    m_dragging = false;
    QWidget::mouseReleaseEvent(event);
}

void FloatingPanel::closeEvent(QCloseEvent *event) {
    emit closed(this);
    event->accept();
}
