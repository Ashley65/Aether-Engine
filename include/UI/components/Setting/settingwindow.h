//
// Created by DevAccount on 14/10/2025.
//

#ifndef OPENWORLD_SETTINGWINDOW_H
#define OPENWORLD_SETTINGWINDOW_H

#include <QWidget>
#include "utils/settingManager.h"
#include "Tabs/simulationtab.h"
#include "Tabs/physicsenginetab.h"
#include "Tabs/aiagenttab.h"
#include "Tabs/hardwaretab.h"
#include "Tabs/communicationtab.h"
#include "Tabs/envtab.h"
#include "Tabs/visualisationtab.h"
#include "Tabs/advancedtab.h"
#include "Tabs/dronetab.h"


QT_BEGIN_NAMESPACE


namespace Ui
{
    class SettingWindow;
}

QT_END_NAMESPACE

struct TabInfo
{
    QString id;
    QString label;
    QString iconPath;
};

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget* parent = nullptr);
    ~SettingWindow() override;


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onSaveButtonClicked();
    void onResetButtonClicked();
    void onCancelButtonClicked();
    void updateButtonStates();



private:
    Ui::SettingWindow *ui;

    enum class ResizeEdge {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    ResizeEdge getResizeEdge(const QPoint& pos);
    void updateCursor(const QPoint& pos);
    void loadSettings(const QVariantMap& params, bool force);
    bool m_isDragging = false;
    bool m_isResizing = false;
    QPoint m_dragPosition;
    ResizeEdge m_resizeEdge = ResizeEdge::None;
    QRect m_resizeStartGeometry;
    QPoint m_resizeStartPos;
    static constexpr int RESIZE_MARGIN = 8;
    void loadSettingsFromManager();
};


#endif //OPENWORLD_SETTINGWINDOW_H