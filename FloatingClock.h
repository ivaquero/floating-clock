#ifndef FLOATINGCLOCK_H
#define FLOATINGCLOCK_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QMap>
#include <QTimer>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QContextMenuEvent>
#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QAction>

class FloatingClock : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingClock(QWidget *parent = nullptr);
    ~FloatingClock();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private slots:
    void updateTime();
    void changeFontSize();
    void changeFontColor();
    void changeBgColor();
    void resetSettings();
    void quitApp();

private:
    void showContextMenu(const QPoint &pos);
    void updateStyle();
    void moveToCenter();
    void loadXmlConfig();
    void createDefaultXml(const QString &path);
    void setDefaultValues();
    void applyXmlValues(const QMap<QString, QString> &values);
    bool parseBool(const QString &str);
    void loadUserSettings();
    void saveUserSettings();
    QColor parseColor(const QString &str);

    QLabel *timeLabel;

    int windowWidth, windowHeight;
    int windowPosX, windowPosY;
    int borderRadius;
    int borderWidth;
    QColor borderColor;

    int fontSize;
    QString fontFamily;
    bool fontWeight;
    bool fontItalic;
    QColor fontColor;

    QColor bgColor;
    QString timeFormat;

    int shadowBlurRadius;
    int shadowOffsetX, shadowOffsetY;
    QColor shadowColor;

    bool dragging = false;
    QPoint dragPos;
};

#endif
