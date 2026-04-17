#ifndef CLOCK_WIDGET_H
#define CLOCK_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QColor>

class ConfigManager;

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);
    ~ClockWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void updateTime();
    void toggleAlwaysOnTop();
    void changeFontColor();
    void changeBackgroundColor();
    void changeFontSize();
    void resetSettings();
    void quitApplication();

private:
    void setupUI();
    void createMenu();
    void loadSettings();
    void saveSettings();
    void updateStyleSheet();

    QLabel *m_timeLabel;
    QTimer *m_timer;
    QMenu *m_contextMenu;

    // Drag related
    QPoint m_dragPosition;
    bool m_dragging;

    // Resize related
    bool m_resizing;
    QPoint m_resizeStartPos;
    QSize m_resizeStartSize;
    int m_resizeBorder;

    // Settings
    ConfigManager *m_configManager;
    QColor m_fontColor;
    QColor m_backgroundColor;
    int m_fontSize;
    bool m_alwaysOnTop;

    // Helper methods
    bool isInResizeArea(const QPoint &pos) const;

#ifdef Q_OS_MAC
    void setupMacOSWindowProperties();
#endif
};

#endif // CLOCK_WIDGET_H
