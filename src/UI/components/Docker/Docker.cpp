#include <../../../include/UI/components/Docker/Docker.h>
#include <QDebug>


DynamicDocker::DynamicDocker(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    m_resizeTimer = new QTimer(this);
    m_resizeTimer->setSingleShot(true);
    m_resizeTimer->setInterval(100);
    connect(m_resizeTimer, &QTimer::timeout, this, [this]() {
    autoResizePanels();});
}
void DynamicDocker::setupUI() {
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    m_mainSplitter->setHandleWidth(3);
    m_mainSplitter->setStyleSheet(
        "QSplitter::handle { background-color: #e0e0e0; }"
        "QSplitter::handle:hover { background-color: #0078d4; }"
    );
    connect(m_mainSplitter, &QSplitter::splitterMoved, m_resizeTimer, [this]() {
    m_resizeTimer->start();});

    m_centerSplitter = new QSplitter(Qt::Vertical, m_mainSplitter);
    m_centerSplitter->setHandleWidth(3);
    m_centerSplitter->setStyleSheet(
        "QSplitter::handle { background-color: #e0e0e0; }"
        "QSplitter::handle:hover { background-color: #0078d4; }"
    );
    connect(m_centerSplitter, &QSplitter::splitterMoved, m_resizeTimer, [this]() {
    m_resizeTimer->start(); });

    m_centerWidget = new QWidget(m_centerSplitter);
    m_centerWidget->setStyleSheet("QWidget { background-color: #f5f5f5; }");
    QVBoxLayout *centerLayout = new QVBoxLayout(m_centerWidget);
    QLabel *centerLabel = new QLabel("Main Content Area\n\nDrag panels here to dock", m_centerWidget);
    centerLabel->setAlignment(Qt::AlignCenter);
    centerLabel->setStyleSheet("QLabel { color: #999; font-size: 16px; }");
    centerLayout->addWidget(centerLabel);

    m_centerSplitter->addWidget(m_centerWidget);
    m_mainSplitter->addWidget(m_centerSplitter);

    m_mainLayout->addWidget(m_mainSplitter);

    m_overlay = new DockOverlay(nullptr);
}

QSplitter* DynamicDocker::getOrCreateSplitter(DockArea area) {
    switch (area) {
        case LeftArea:
        case RightArea:
            return m_mainSplitter;
        case TopArea:
        case BottomArea:
        case CenterArea:
            return m_centerSplitter;
        default:
            return nullptr;
    }
}

void DynamicDocker::addDockWidget(const QString &id, const QString &title,
                                   QWidget *widget, DockArea area) {
    if (m_dockPanels.contains(id)) {
        qWarning() << "Dock widget with id" << id << "already exists";
        return;
    }

    if (area == FloatingArea) {
        DockPanel *panel = new DockPanel(title, widget, nullptr);
        panel->setPanelId(id);
        panel->setFloating(true);
        m_dockPanels[id] = panel;
        m_dockAreas[id] = FloatingArea;

        connect(panel, &DockPanel::closeRequested, this, [this, id]() {
            removeDockWidget(id);
        });
        connect(panel, &DockPanel::floatRequested, this, [this, id]() {
            setDockFloating(id, !isDockFloating(id));
        });

        makeFloating(id);
        return;
    }

    DockPanel *panel = new DockPanel(title, widget, this);
    panel->setPanelId(id);
    panel->setMinimumSize(150, 100);

    connect(panel, &DockPanel::closeRequested, this, [this, id]() {
        removeDockWidget(id);
    });
    connect(panel, &DockPanel::floatRequested, this, [this, id]() {
        setDockFloating(id, !isDockFloating(id));
    });
    connect(panel, SIGNAL(dragStarted(DockPanel*)), this, SLOT(onPanelDragStarted(DockPanel*)));

    m_dockPanels[id] = panel;
    m_dockAreas[id] = area;

    QSplitter *splitter = getOrCreateSplitter(area);

    switch (area) {
        case LeftArea:
            splitter->insertWidget(0, panel);
            break;
        case RightArea:
            splitter->addWidget(panel);
            break;
        case TopArea:
            splitter->insertWidget(0, panel);
            break;
        case BottomArea:
            splitter->addWidget(panel);
            break;
        case CenterArea:
            m_centerWidget->hide();
            splitter->insertWidget(splitter->indexOf(m_centerWidget), panel);
            break;
        default:
            break;
    }

    QTimer::singleShot(50, this, &DynamicDocker::autoResizePanels);
}

void DynamicDocker::removeDockWidget(const QString &id) {
    if (!m_dockPanels.contains(id)) {
        return;
    }

    if (m_floatingPanels.contains(id)) {
        FloatingPanel *floating = m_floatingPanels[id];
        floating->blockSignals(true);
        floating->close();
        floating->deleteLater();
        m_floatingPanels.remove(id);
    }

    DockPanel *panel = m_dockPanels[id];
    panel->deleteLater();

    m_dockPanels.remove(id);
    m_dockAreas.remove(id);

    QTimer::singleShot(50, this, &DynamicDocker::autoResizePanels);
}

QWidget* DynamicDocker::getDockWidget(const QString &id) {
    if (!m_dockPanels.contains(id)) {
        return nullptr;
    }
    return m_dockPanels[id]->content();
}

void DynamicDocker::setDockVisible(const QString &id, bool visible) {
    if (!m_dockPanels.contains(id)) {
        return;
    }

    if (m_floatingPanels.contains(id)) {
        m_floatingPanels[id]->setVisible(visible);
    } else {
        m_dockPanels[id]->setVisible(visible);
        if (visible) {
            QTimer::singleShot(50, this, &DynamicDocker::autoResizePanels);
        }
    }
}

bool DynamicDocker::isDockVisible(const QString &id) const {
    if (!m_dockPanels.contains(id)) {
        return false;
    }

    if (m_floatingPanels.contains(id)) {
        return m_floatingPanels[id]->isVisible();
    }
    return m_dockPanels[id]->isVisible();
}

void DynamicDocker::setDockFloating(const QString &id, bool floating) {
    if (!m_dockPanels.contains(id)) {
        return;
    }

    if (floating && !m_floatingPanels.contains(id)) {
        makeFloating(id);
    } else if (!floating && m_floatingPanels.contains(id)) {
        dockFloating(id, RightArea);
    }
}

bool DynamicDocker::isDockFloating(const QString &id) const {
    return m_floatingPanels.contains(id);
}

void DynamicDocker::makeFloating(const QString &id) {
    if (!m_dockPanels.contains(id) || m_floatingPanels.contains(id)) {
        return;
    }

    DockPanel *panel = m_dockPanels[id];
    panel->setParent(nullptr);
    panel->setFloating(true);

    FloatingPanel *floating = new FloatingPanel(panel, this);
    m_floatingPanels[id] = floating;
    m_dockAreas[id] = FloatingArea;

    connect(floating, &FloatingPanel::dockRequested,
            this, &DynamicDocker::onFloatingPanelDockRequested);
    connect(floating, &FloatingPanel::closed,
            this, &DynamicDocker::onFloatingPanelClosed);

    QPoint globalPos = QCursor::pos();
    floating->move(globalPos - QPoint(200, 20));
    floating->show();

    QTimer::singleShot(50, this, &DynamicDocker::autoResizePanels);
}

void DynamicDocker::dockFloating(const QString &id, DockArea area) {
    if (!m_floatingPanels.contains(id)) {
        return;
    }

    FloatingPanel *floating = m_floatingPanels[id];
    DockPanel *panel = floating->dockPanel();

    panel->setParent(this);
    panel->setFloating(false);
    panel->show();

    m_floatingPanels.remove(id);
    m_dockAreas[id] = area;

    QSplitter *splitter = getOrCreateSplitter(area);

    switch (area) {
        case LeftArea:
            splitter->insertWidget(0, panel);
            break;
        case RightArea:
            splitter->addWidget(panel);
            break;
        case TopArea:
            splitter->insertWidget(0, panel);
            break;
        case BottomArea:
            splitter->addWidget(panel);
            break;
        case CenterArea:
            m_centerWidget->hide();
            splitter->insertWidget(splitter->indexOf(m_centerWidget), panel);
            break;
        default:
            break;
    }

    floating->blockSignals(true);
    floating->close();
    floating->deleteLater();

    QTimer::singleShot(50, this, &DynamicDocker::autoResizePanels);
}

DynamicDocker::DockArea DynamicDocker::dropZoneToArea(DockOverlay::DropZone zone) {
    switch (zone) {
        case DockOverlay::LeftZone: return LeftArea;
        case DockOverlay::RightZone: return RightArea;
        case DockOverlay::TopZone: return TopArea;
        case DockOverlay::BottomZone: return BottomArea;
        case DockOverlay::CenterZone: return CenterArea;
        default: return CenterArea;
    }
}

void DynamicDocker::onPanelDragStarted(DockPanel *panel) {
    QString id = panel->panelId();
    if (id.isEmpty()) {
        for (auto it = m_dockPanels.begin(); it != m_dockPanels.end(); ++it) {
            if (it.value() == panel) {
                id = it.key();
                break;
            }
        }
    }

    if (!id.isEmpty()) {
        m_draggedPanelId = id;
        makeFloating(id);
    }
}

void DynamicDocker::onFloatingPanelDockRequested(FloatingPanel *floating, const QPoint &globalPos) {
    QRect dockerRect = QRect(mapToGlobal(rect().topLeft()),
                             mapToGlobal(rect().bottomRight()));

    if (!dockerRect.adjusted(-50, -50, 50, 50).contains(globalPos)) {
        m_overlay->hideOverlay();
        return;
    }

    QPoint localPos = mapFromGlobal(globalPos);
    DockOverlay::DropZone zone = getDropZone(localPos);

    if (zone != DockOverlay::NoZone) {
        QRect overlayRect;
        QRect dockerLocalRect = rect();

        switch (zone) {
            case DockOverlay::LeftZone:
                overlayRect = QRect(0, 0, dockerLocalRect.width() / 3, dockerLocalRect.height());
                break;
            case DockOverlay::RightZone:
                overlayRect = QRect(dockerLocalRect.width() * 2 / 3, 0,
                                   dockerLocalRect.width() / 3, dockerLocalRect.height());
                break;
            case DockOverlay::TopZone:
                overlayRect = QRect(0, 0, dockerLocalRect.width(), dockerLocalRect.height() / 3);
                break;
            case DockOverlay::BottomZone:
                overlayRect = QRect(0, dockerLocalRect.height() * 2 / 3,
                                   dockerLocalRect.width(), dockerLocalRect.height() / 3);
                break;
            case DockOverlay::CenterZone:
                overlayRect = dockerLocalRect.adjusted(80, 80, -80, -80);
                break;
            default:
                break;
        }

        QRect globalRect(mapToGlobal(overlayRect.topLeft()),
                        overlayRect.size());
        m_overlay->showOverlay(globalRect, zone);
    } else {
        m_overlay->hideOverlay();
    }
}

void DynamicDocker::onFloatingPanelClosed(FloatingPanel *floating) {
    m_overlay->hideOverlay();

    QString id;
    for (auto it = m_floatingPanels.begin(); it != m_floatingPanels.end(); ++it) {
        if (it.value() == floating) {
            id = it.key();
            break;
        }
    }

    if (!id.isEmpty()) {
        DockOverlay::DropZone currentZone = m_overlay->currentZone();
        if (currentZone != DockOverlay::NoZone) {
            DockArea area = dropZoneToArea(currentZone);
            dockFloating(id, area);
        }
    }
}

DockOverlay::DropZone DynamicDocker::getDropZone(const QPoint &pos) {
    QRect dockerRect = rect();
    int edgeThreshold = 80;

    if (pos.x() < edgeThreshold) {
        return DockOverlay::LeftZone;
    } else if (pos.x() > dockerRect.width() - edgeThreshold) {
        return DockOverlay::RightZone;
    } else if (pos.y() < edgeThreshold) {
        return DockOverlay::TopZone;
    } else if (pos.y() > dockerRect.height() - edgeThreshold) {
        return DockOverlay::BottomZone;
    } else if (dockerRect.adjusted(edgeThreshold, edgeThreshold,
                                   -edgeThreshold, -edgeThreshold).contains(pos)) {
        return DockOverlay::CenterZone;
    }

    return DockOverlay::NoZone;
}

void DynamicDocker::autoResizePanels() {
    autoResizeSplitter(m_mainSplitter);
    autoResizeSplitter(m_centerSplitter);
}

void DynamicDocker::autoResizeSplitter(QSplitter *splitter) {
    if (!splitter) return;

    QList<int> sizes;
    int totalSize = (splitter->orientation() == Qt::Horizontal) ?
                    splitter->width() : splitter->height();
    int visibleCount = 0;

    for (int i = 0; i < splitter->count(); ++i) {
        if (splitter->widget(i)->isVisible()) {
            visibleCount++;
        }
    }

    if (visibleCount == 0) return;

    int sizePerWidget = totalSize / visibleCount;

    for (int i = 0; i < splitter->count(); ++i) {
        if (splitter->widget(i)->isVisible()) {
            sizes.append(sizePerWidget);
        } else {
            sizes.append(0);
        }
    }

    splitter->setSizes(sizes);
}

void DynamicDocker::setSplitterSizes(Qt::Orientation orientation, const QList<int> &sizes) {
    if (orientation == Qt::Horizontal) {
        m_mainSplitter->setSizes(sizes);
    } else {
        m_centerSplitter->setSizes(sizes);
    }
}

QList<int> DynamicDocker::getSplitterSizes(Qt::Orientation orientation) const {
    if (orientation == Qt::Horizontal) {
        return m_mainSplitter->sizes();
    } else {
        return m_centerSplitter->sizes();
    }
}