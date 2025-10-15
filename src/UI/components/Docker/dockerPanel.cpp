//
// Created by DevAccount on 12/10/2025.
//
#include <../../../include/UI/components/Docker/dockerPanel.h>

DockPanel::DockPanel(const QString &title, QWidget *content, QWidget *parent)
    : QFrame(parent), m_title(title), m_content(nullptr),
      m_isFloating(false), m_dragging(false)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    setLineWidth(1);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    // Title bar
    m_titleBar = new QWidget(this);
    m_titleBar->setStyleSheet("QWidget { background-color: #2d2d2d; }");
    m_titleBar->setFixedHeight(28);
    m_titleBar->setCursor(Qt::SizeAllCursor);
    QHBoxLayout *titleLayout = new QHBoxLayout(m_titleBar);
    titleLayout->setContentsMargins(8, 2, 5, 2);

    m_titleLabel = new QLabel(title, m_titleBar);
    m_titleLabel->setStyleSheet("QLabel { color: white; font-weight: bold; font-size: 12px; }");
    m_titleLabel->setCursor(Qt::SizeAllCursor);

    m_floatBtn = new QPushButton("⬜", m_titleBar);
    m_floatBtn->setFixedSize(20, 20);
    m_floatBtn->setToolTip("Float Panel");
    m_floatBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: white; "
        "border: none; font-size: 14px; }"
        "QPushButton:hover { background-color: #404040; border-radius: 3px; }"
    );

    m_closeBtn = new QPushButton("×", m_titleBar);
    m_closeBtn->setFixedSize(20, 20);
    m_closeBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: white; "
        "border: none; font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #c42b1c; border-radius: 3px; }"
    );

    connect(m_closeBtn, &QPushButton::clicked, this, &DockPanel::closeRequested);
    connect(m_floatBtn, &QPushButton::clicked, this, &DockPanel::floatRequested);

    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(m_floatBtn);
    titleLayout->addWidget(m_closeBtn);

    m_layout->addWidget(m_titleBar);

    setContent(content);
}

void DockPanel::setContent(QWidget *content) {
    if (m_content) {
        m_layout->removeWidget(m_content);
    }

    m_content = content;
    if (m_content) {
        m_layout->addWidget(m_content);
    }
}

void DockPanel::setFloating(bool floating) {
    m_isFloating = floating;
    if (floating) {
        m_floatBtn->setText("⬛");
        m_floatBtn->setToolTip("Dock Panel");
    } else {
        m_floatBtn->setText("⬜");
        m_floatBtn->setToolTip("Float Panel");
    }
}

void DockPanel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QWidget *widget = childAt(event->pos());
        if (widget == m_titleBar || widget == m_titleLabel) {
            m_dragStartPos = event->globalPos();
            m_dragging = true;
        }
    }
    QFrame::mousePressEvent(event);
}

void DockPanel::mouseMoveEvent(QMouseEvent *event) {
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        int distance = (event->globalPos() - m_dragStartPos).manhattanLength();
        if (distance > QApplication::startDragDistance()) {
            emit dragStarted(this);
            m_dragging = false;
        }
    }
    QFrame::mouseMoveEvent(event);
}

void DockPanel::mouseReleaseEvent(QMouseEvent *event) {
    m_dragging = false;
    QFrame::mouseReleaseEvent(event);
}

void DockPanel::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget *widget = childAt(event->pos());
    if (widget == m_titleBar || widget == m_titleLabel) {
        emit floatRequested();
    }
    QFrame::mouseDoubleClickEvent(event);
}