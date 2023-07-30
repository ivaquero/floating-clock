#ifndef CLOCK_H
#define CLOCK_H

#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QMenu>
#include <QMouseEvent>
#include <QPoint>
#include <QSettings>
#include <QTime>
#include <QTimer>
#include <QTranslator>
#include <QVBoxLayout>
#include <QWidget>

class Clock : public QWidget {
  Q_OBJECT
public:
  explicit Clock(QWidget *parent = nullptr);
  void reloadUI();
  void resetUI();
  void increaseFontSize();
  void decreaseFontSize();
  void changeFontSize();
  void setFontColor(const class QString &color);
  void setBackgroundColor(const class QString &color);

protected:
  void mousePressEvent(QMouseEvent *event);
  // void mousePressEvent(QMouseEvent *event) ;
  void mouseMoveEvent(QMouseEvent *event);
  // void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  // void mouseReleaseEvent(QMouseEvent *event) ;
  void mouseRightMenu(const QPoint &pos);

signals:

public slots:
  void showTime();

private:
  bool pressed;
  QPoint oldPos;
  QSettings *settings;
  QFont font;
  int font_size_step;
  int font_size;
  QLabel *label;
};

#endif // CLOCK_H
