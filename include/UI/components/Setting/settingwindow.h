//
// Created by DevAccount on 14/10/2025.
//

#ifndef OPENWORLD_SETTINGWINDOW_H
#define OPENWORLD_SETTINGWINDOW_H

#include <QWidget>


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

private:
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

    bool m_isDragging = false;
    bool m_isResizing = false;
    QPoint m_dragPosition;
    ResizeEdge m_resizeEdge = ResizeEdge::None;
    QRect m_resizeStartGeometry;
    QPoint m_resizeStartPos;
    static constexpr int RESIZE_MARGIN = 8;
};


#endif //OPENWORLD_SETTINGWINDOW_H