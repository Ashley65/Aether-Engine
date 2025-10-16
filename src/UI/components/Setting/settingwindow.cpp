//
// Created by DevAccount on 14/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWindow.h" resolved

#include <QMouseEvent>
#include <QPushButton>
#include <UI/components/Setting/settingwindow.h>
#include "../resources/ui/ui_SettingWindow.h"


SettingWindow::SettingWindow(QWidget* parent) :
    QWidget(parent), ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    setMinimumSize(800, 600);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setMouseTracking(true);

    connect(ui->SettingExit, &QPushButton::clicked, this, &SettingWindow::close);


    // Main frame styling
    ui->frame->setStyleSheet(
        "QFrame#frame {"
        "   background-color: #131720;"  /* bg-secondary */
        "   border: 1px solid #374151;"  /* border-default */
        "   border-radius: 8px;"
        "}"
    );

    // Close button styling
    ui->SettingExit->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: #9ca3af;"              /* text-secondary */
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   border: none;"
        "   border-radius: 4px;"
        "   padding: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #ef4444;"   /* danger-500 */
        "   color: #ffffff;"               /* text-inverse */
        "}"
    );

    // Tab widget styling

    ui->tabWidget->setStyleSheet(
        "QTabWidget::pane {"
        "   background-color: #1a1f2e;"   /* bg-tertiary */
        "   border: 1px solid #2d3748;"   /* border-subtle */
        "   border-radius: 4px;"
        "}"
        "QTabWidget::pane:focus {"
        "   outline: none;"                /* Remove focus border */
        "}"
        "QTabBar::tab {"
        "   background-color: #131720;"   /* bg-secondary */
        "   color: #9ca3af;"               /* text-secondary */
        "   padding: 8px 12px;"
        "   border: 1px solid #2d3748;"
        "   border-right: none;"
        "   outline: none;"                /* Remove focus outline */
        "}"
        "QTabBar::tab:selected {"
        "   background-color: #1a1f2e;"   /* bg-tertiary */
        "   color: #e5e7eb;"               /* text-primary */
        "   border-left: 2px solid #3b82f6;" /* info-500 */
        "   outline: none;"
        "}"
        "QTabBar::tab:hover:!selected {"
        "   background-color: #242938;"   /* bg-elevated */
        "   color: #e5e7eb;"
        "}"
        "QTabBar::tab:focus {"
        "   outline: none;"                /* Remove focus outline */
        "}"
    );


    // Bottom buttons container styling
    ui->horizontalLayoutWidget->setStyleSheet(
        "QWidget {"
        "   background-color: transparent;"
        "}"
    );

    // Reset All button styling
    ui->RestAll->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: #9ca3af;"               /* text-secondary */
        "   border: 1px solid #4b5563;"   /* border-strong */
        "   border-radius: 4px;"
        "   padding: 8px 16px;"
        "   font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "   background-color: #ef4444;"   /* danger-500 */
        "   color: #ffffff;"
        "   border-color: #dc2626;"        /* danger-600 */
        "}"
    );

    // Save button styling (primary action)
    ui->pushButton_2->setStyleSheet(
        "QPushButton {"
        "   background-color: #3b82f6;"   /* info-500 - primary button */
        "   color: #ffffff;"               /* text-inverse */
        "   border: 1px solid #2563eb;"   /* info-600 */
        "   border-radius: 4px;"
        "   padding: 8px 16px;"
        "   font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2563eb;"   /* info-600 */
        "   border-color: #1d4ed8;"        /* info-700 */
        "}"
        "QPushButton:pressed {"
        "   background-color: #1d4ed8;"   /* info-700 */
        "}"
    );

    // Set main window background
    setStyleSheet("QWidget#SettingWindow { background-color: #0a0e17; }"); /* bg-primary */


    while (ui -> tabWidget ->count() > 0)
        ui -> tabWidget ->removeTab(0);

    QList<TabInfo> tabs = {
        { "simulation", "Simulation", ":/icons/Lucide/icons/gauge.svg" },
        { "physics", "Physics Engine", ":/icons/Lucide/icons/cpu.svg" },
        { "drone", "Drone Settings", ":/icons/Lucide/icons/rocket.svg" },
        { "ai", "AI Agent", ":/icons/Lucide/icons/zap.svg" },
        { "hardware", "Hardware/HIL", ":/icons/Lucide/icons/harddrive.svg" },
        { "communication", "Communication", ":/icons/Lucide/icons/radio.svg" },
        { "environment", "Environment", ":/icons/Lucide/icons/globe.svg" },
        { "visualization", "Visualization", ":/icons/Lucide/icons/eye.svg" },
        { "advanced", "Advanced", ":/icons/Lucide/icons/settings.svg" }
    };

    for (const auto& tab : tabs) {
        QWidget* page = new QWidget();
        ui->tabWidget->addTab(page, QIcon(tab.iconPath), tab.label);
    }

}

SettingWindow::~SettingWindow()
{
    delete ui;
}

SettingWindow::ResizeEdge SettingWindow::getResizeEdge(const QPoint& pos)
{
    bool left = pos.x() <= RESIZE_MARGIN;
    bool right = pos.x() >= width() - RESIZE_MARGIN;
    bool top = pos.y() <= RESIZE_MARGIN;
    bool bottom = pos.y() >= height() - RESIZE_MARGIN;

    if (top && left) return ResizeEdge::TopLeft;
    if (top && right) return ResizeEdge::TopRight;
    if (bottom && left) return ResizeEdge::BottomLeft;
    if (bottom && right) return ResizeEdge::BottomRight;
    if (left) return ResizeEdge::Left;
    if (right) return ResizeEdge::Right;
    if (top) return ResizeEdge::Top;
    if (bottom) return ResizeEdge::Bottom;

    return ResizeEdge::None;
}

void SettingWindow::updateCursor(const QPoint& pos)
{
    ResizeEdge edge = getResizeEdge(pos);

    switch (edge) {
        case ResizeEdge::Left:
        case ResizeEdge::Right:
            setCursor(Qt::SizeHorCursor);
            break;
        case ResizeEdge::Top:
        case ResizeEdge::Bottom:
            setCursor(Qt::SizeVerCursor);
            break;
        case ResizeEdge::TopLeft:
        case ResizeEdge::BottomRight:
            setCursor(Qt::SizeFDiagCursor);
            break;
        case ResizeEdge::TopRight:
        case ResizeEdge::BottomLeft:
            setCursor(Qt::SizeBDiagCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
    }
}

void SettingWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_resizeEdge = getResizeEdge(event->pos());

        if (m_resizeEdge != ResizeEdge::None) {
            m_isResizing = true;
            m_resizeStartGeometry = geometry();
            m_resizeStartPos = event->globalPosition().toPoint();
        } else {
            m_isDragging = true;
            m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        }
        event->accept();
    }
}

void SettingWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isResizing) {
        QPoint delta = event->globalPosition().toPoint() - m_resizeStartPos;
        QRect newGeometry = m_resizeStartGeometry;

        switch (m_resizeEdge) {
            case ResizeEdge::Left:
                newGeometry.setLeft(m_resizeStartGeometry.left() + delta.x());
                break;
            case ResizeEdge::Right:
                newGeometry.setRight(m_resizeStartGeometry.right() + delta.x());
                break;
            case ResizeEdge::Top:
                newGeometry.setTop(m_resizeStartGeometry.top() + delta.y());
                break;
            case ResizeEdge::Bottom:
                newGeometry.setBottom(m_resizeStartGeometry.bottom() + delta.y());
                break;
            case ResizeEdge::TopLeft:
                newGeometry.setTopLeft(m_resizeStartGeometry.topLeft() + delta);
                break;
            case ResizeEdge::TopRight:
                newGeometry.setTopRight(m_resizeStartGeometry.topRight() + QPoint(delta.x(), delta.y()));
                break;
            case ResizeEdge::BottomLeft:
                newGeometry.setBottomLeft(m_resizeStartGeometry.bottomLeft() + QPoint(delta.x(), delta.y()));
                break;
            case ResizeEdge::BottomRight:
                newGeometry.setBottomRight(m_resizeStartGeometry.bottomRight() + delta);
                break;
            default:
                break;
        }

        // Enforce minimum size
        if (newGeometry.width() >= minimumWidth() && newGeometry.height() >= minimumHeight()) {
            setGeometry(newGeometry);
        }
        event->accept();
    } else if (m_isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    } else {
        updateCursor(event->pos());
    }
}

void SettingWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
        m_isResizing = false;
        m_resizeEdge = ResizeEdge::None;
        setCursor(Qt::ArrowCursor);
        event->accept();
    }
}

void SettingWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // Resize frame
    int frameWidth = width() - 20;
    int frameHeight = height() - 20;
    ui->frame->setGeometry(10, 10, frameWidth, frameHeight);

    // Reposition close button to top-right of frame
    ui->SettingExit->move(frameWidth - 41, 10);

    // Resize and reposition tab widget
    ui->tabWidget->setGeometry(10, 40, frameWidth - 20, frameHeight - 90);

    // Reposition bottom buttons container
    ui->horizontalLayoutWidget->move(frameWidth - 176, frameHeight - 51);
}
