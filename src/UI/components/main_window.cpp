//
// Created by DevAccount on 09/10/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <QMouseEvent>
#include <UI/components/main_window.h>
#include "../../../resources/ui/ui_main_window.h"
#include <UI/components/menu_bar.h>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "UI/components/Setting/settingwindow.h"


main_window::main_window(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::main_window)
{

    ui->setupUi(this);
    WindowsFlags();
    menuBar = new MenuBar(this);
    setMenuBar(menuBar);

    setupDockerPanels();


    setupDockerPanels();
    connect(menuBar, &MenuBar::openSettings, this, [this]() {
        SettingWindow* settingsWin = new SettingWindow(this);
        settingsWin->setWindowTitle("Settings");
        settingsWin->setWindowModality(Qt::ApplicationModal); // Block main window while open
        settingsWin->resize(900, 600);
        settingsWin->show();
    });

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(
        "main_window {"
        "  background-color: white;"
        "  border-radius: 16px;"
        "}"
        "QLineEdit { border-width: 1px; border-style: solid; border-radius: 4px; }"
    );
}

main_window::~main_window()
{
    delete ui;
}

void main_window::setupDockerPanels()
{
    // Left Panel - File Explorer
    QTreeWidget* fileTree = new QTreeWidget();
    fileTree->setHeaderLabel("Project Files");
    QTreeWidgetItem* srcItem = new QTreeWidgetItem(fileTree, QStringList("src"));
    srcItem->addChild(new QTreeWidgetItem(QStringList("main.cpp")));
    srcItem->addChild(new QTreeWidgetItem(QStringList("main_window.cpp")));
    srcItem->addChild(new QTreeWidgetItem(QStringList("main_window.h")));
    QTreeWidgetItem* uiItem = new QTreeWidgetItem(fileTree, QStringList("UI"));
    uiItem->addChild(new QTreeWidgetItem(QStringList("docker.cpp")));
    uiItem->addChild(new QTreeWidgetItem(QStringList("docker.h")));
    fileTree->expandAll();
    fileTree->setStyleSheet(
        "QTreeWidget { background-color: black; border: none; padding: 5px; }"
        "QTreeWidget::item { padding: 4px; }"
        "QTreeWidget::item:selected { background-color: #0078d4; color: black; }"
        "QTreeWidget::item:hover { background-color: #e5f3ff; }"
    );

    QDockWidget* filesDock = new QDockWidget("Project Explorer", this);
    filesDock->setWidget(fileTree);
    filesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, filesDock);
    m_dockWidgets["files"] = filesDock;

    // Right Panel - Properties
    QTableWidget* properties = new QTableWidget(10, 2);
    properties->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");
    properties->setItem(0, 0, new QTableWidgetItem("Name"));
    properties->setItem(0, 1, new QTableWidgetItem("main_window"));
    properties->setItem(1, 0, new QTableWidgetItem("Type"));
    properties->setItem(1, 1, new QTableWidgetItem("QWidget"));
    properties->setItem(2, 0, new QTableWidgetItem("Width"));
    properties->setItem(2, 1, new QTableWidgetItem("1200"));
    properties->setItem(3, 0, new QTableWidgetItem("Height"));
    properties->setItem(3, 1, new QTableWidgetItem("800"));
    properties->horizontalHeader()->setStretchLastSection(true);
    properties->setStyleSheet(
        "QTableWidget { background-color: white; border: none; gridline-color: #e0e0e0; }"
        "QHeaderView::section { background-color: #f0f0f0; padding: 6px; border: none; font-weight: bold; }"
    );

    QDockWidget* propDock = new QDockWidget("Properties", this);
    propDock->setWidget(properties);
    propDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, propDock);
    m_dockWidgets["properties"] = propDock;

    // Bottom Panel - Console
    QTextEdit* console = new QTextEdit();
    console->setPlainText(
        "=== Build Output ===\n"
        "Compiling main.cpp...\n"
        "Build successful! (0 errors, 0 warnings)\n"
    );
    console->setReadOnly(true);
    console->setStyleSheet(
        "QTextEdit { background-color: #1e1e1e; color: #d4d4d4; border: none; "
        "font-family: 'Consolas', monospace; font-size: 11px; padding: 5px; }"
    );

    QDockWidget* consoleDock = new QDockWidget("Console Output", this);
    consoleDock->setWidget(console);
    consoleDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, consoleDock);
    m_dockWidgets["console"] = consoleDock;

    // Top Panel - Toolbar (as dock widget)
    QWidget* toolbarWidget = new QWidget();
    QHBoxLayout* toolbarLayout = new QHBoxLayout(toolbarWidget);
    toolbarLayout->setContentsMargins(10, 8, 10, 8);

    QPushButton* newBtn = new QPushButton("📄 New");
    QPushButton* openBtn = new QPushButton("📁 Open");
    QPushButton* saveBtn = new QPushButton("💾 Save");
    QPushButton* buildBtn = new QPushButton("🔨 Build");
    QPushButton* runBtn = new QPushButton("▶ Run");

    QString btnStyle = "QPushButton { background-color: #0078d4; color: white; "
                       "border: none; padding: 8px 16px; border-radius: 4px; }";
    newBtn->setStyleSheet(btnStyle);
    openBtn->setStyleSheet(btnStyle);
    saveBtn->setStyleSheet(btnStyle);
    buildBtn->setStyleSheet(btnStyle);
    runBtn->setStyleSheet(btnStyle);

    toolbarLayout->addWidget(newBtn);
    toolbarLayout->addWidget(openBtn);
    toolbarLayout->addWidget(saveBtn);
    toolbarLayout->addSpacing(20);
    toolbarLayout->addWidget(buildBtn);
    toolbarLayout->addWidget(runBtn);
    toolbarLayout->addStretch();

    QDockWidget* toolbarDock = new QDockWidget("Quick Actions", this);
    toolbarDock->setWidget(toolbarWidget);
    toolbarDock->setAllowedAreas(Qt::TopDockWidgetArea);
    toolbarDock->setFeatures(QDockWidget::DockWidgetMovable);  // Can't close/float
    addDockWidget(Qt::TopDockWidgetArea, toolbarDock);
    m_dockWidgets["toolbar"] = toolbarDock;

    // Center Widget - Editor (NOT a dock widget, use setCentralWidget)
    QTextEdit* editor = new QTextEdit();
    editor->setPlainText("// main_window.cpp - QDockWidget Integration\n"
                         "#include \"main_window.h\"\n"
                         "...");
    editor->setStyleSheet(
        "QTextEdit { background-color: white; border: none; "
        "font-family: 'Consolas', monospace; font-size: 12px; padding: 10px; }"
    );
    setCentralWidget(editor);  // The center is NOT a dock widget
    m_centralEditor = editor;
}



// C++ (in main_window.cpp)
void main_window::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPos = event->globalPos();
        originalGeometry = geometry();

        // Detect region
        int x = event->pos().x();
        int y = event->pos().y();
        int w = width();
        int h = height();

        if (x < borderWidth && y < borderWidth)
            resizeRegion = TopLeft;
        else if (x > w - borderWidth && y < borderWidth)
            resizeRegion = TopRight;
        else if (x < borderWidth && y > h - borderWidth)
            resizeRegion = BottomLeft;
        else if (x > w - borderWidth && y > h - borderWidth)
            resizeRegion = BottomRight;
        else if (x < borderWidth)
            resizeRegion = Left;
        else if (x > w - borderWidth)
            resizeRegion = Right;
        else if (y < borderWidth)
            resizeRegion = Top;
        else if (y > h - borderWidth)
            resizeRegion = Bottom;
        else
            resizeRegion = None;

        if (resizeRegion != None)
            resizing = true;
    }
    QWidget::mousePressEvent(event);
}

void main_window::mouseMoveEvent(QMouseEvent* event)
{
    if (resizing) {
        QPoint delta = event->globalPos() - dragStartPos;
        QRect newGeom = originalGeometry;

        switch (resizeRegion) {
            case Left:      newGeom.setLeft(newGeom.left() + delta.x()); break;
            case Right:     newGeom.setRight(newGeom.right() + delta.x()); break;
            case Top:       newGeom.setTop(newGeom.top() + delta.y()); break;
            case Bottom:    newGeom.setBottom(newGeom.bottom() + delta.y()); break;
            case TopLeft:
                newGeom.setTop(newGeom.top() + delta.y());
                newGeom.setLeft(newGeom.left() + delta.x());
                break;
            case TopRight:
                newGeom.setTop(newGeom.top() + delta.y());
                newGeom.setRight(newGeom.right() + delta.x());
                break;
            case BottomLeft:
                newGeom.setBottom(newGeom.bottom() + delta.y());
                newGeom.setLeft(newGeom.left() + delta.x());
                break;
            case BottomRight:
                newGeom.setBottom(newGeom.bottom() + delta.y());
                newGeom.setRight(newGeom.right() + delta.x());
                break;
            default: break;
        }
        setGeometry(newGeom);
    } else {
        // Change cursor shape
        int x = event->pos().x();
        int y = event->pos().y();
        int w = width();
        int h = height();
        if (x < borderWidth && y < borderWidth)
            setCursor(Qt::SizeFDiagCursor);
        else if (x > w - borderWidth && y < borderWidth)
            setCursor(Qt::SizeBDiagCursor);
        else if (x < borderWidth && y > h - borderWidth)
            setCursor(Qt::SizeBDiagCursor);
        else if (x > w - borderWidth && y > h - borderWidth)
            setCursor(Qt::SizeFDiagCursor);
        else if (x < borderWidth || x > w - borderWidth)
            setCursor(Qt::SizeHorCursor);
        else if (y < borderWidth || y > h - borderWidth)
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::ArrowCursor);
    }
    QWidget::mouseMoveEvent(event);
}

void main_window::mouseReleaseEvent(QMouseEvent* event)
{
    resizing = false;
    resizeRegion = None;
    QWidget::mouseReleaseEvent(event);
}

// C++
void main_window::animationStep(bool toFullscreen)
{
    QRect startGeom = geometry();
    QRect endGeom;

    if (toFullscreen) {
        endGeom = QApplication::primaryScreen()->geometry();
    } else {
        // Use originalGeometry or a default size/position
        endGeom = originalGeometry.isValid() ? originalGeometry : QRect(100, 100, 1200, 800);
    }

    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(300); // ms
    anim->setStartValue(startGeom);
    anim->setEndValue(endGeom);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void main_window::WindowsFlags()
{
    // Get the current window flags
    Qt::WindowFlags flags = this->windowFlags();
    // Set the window to be frameless
    this->setWindowFlags(flags | Qt::FramelessWindowHint);
    // Apply the changes
    this->show();
}
