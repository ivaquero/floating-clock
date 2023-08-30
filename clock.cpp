#include "clock.h"

Clock::Clock(QWidget *parent) : QWidget{parent}, pressed(false) {
  // geometry of Main Window (x, y, width, height)
  setGeometry(1100, 800, 180, 60);

  // hide frame
  setWindowFlag(Qt::WindowStaysOnTopHint, true);
  setWindowFlag(Qt::FramelessWindowHint, true);
  setAttribute(Qt::WA_TranslucentBackground);

  // setFixedSize(this->width(), this->height());
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint &
                 ~Qt::WindowMinimizeButtonHint);

  // clock object
  QTimer *clock = new QTimer(this);
  connect(clock, &QTimer::timeout, this, &Clock::showTime);
  clock->start(1000); // update the clock per second
  show();

  settings = new QSettings(
      QString("%1/config.ini").arg(QCoreApplication::applicationDirPath()),
      QSettings::IniFormat);

  font = QFont();
  font.setFamily(settings->value("USER/FONT_FAMILY").toString());
  font.setPointSize(settings->value("USER/FONT_SIZE").toInt());

  // load settings
  settings = new QSettings(
      QString("%1/config.ini").arg(QCoreApplication::applicationDirPath()),
      QSettings::IniFormat);

  // font object
  font = QFont();
  font.setFamily(settings->value("DEFAULT/FONT_FAMILY").toString());
  font_size_step = settings->value("USER/FONT_SIZE_STEP").toInt();

  // label object
  label = new QLabel();
  label->setAlignment(Qt::AlignCenter);

  // layout
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(label);
  setLayout(layout);

  reloadUI();
}

void Clock::showTime() {
  QString current_time = QTime::currentTime().toString("hh:mm");
  label->setText(current_time);
}

void Clock::reloadUI() {
  font_size = settings->value("USER/FONT_SIZE").toInt();
  font.setPointSize(font_size);
  label->setFont(font);
  label->setStyleSheet(QString("color: %1; background-color: %2")
                           .arg(settings->value("USER/FONT_COLOR").toString(),
                                settings->value("USER/BG_COLOR").toString()));
}

void Clock::resetUI() {
  QString default_bg_color = settings->value("DEFAULT/BG_COLOR").toString();
  QString default_font_color = settings->value("DEFAULT/FONT_COLOR").toString();
  QString default_font_size = settings->value("DEFAULT/FONT_SIZE").toString();

  settings->setValue("USER/BG_COLOR", default_bg_color);
  settings->setValue("USER/FONT_COLOR", default_font_color);
  settings->setValue("USER/FONT_SIZE", default_font_size);

  reloadUI();
}

void Clock::increaseFontSize() {
  font_size += font_size_step;
  changeFontSize();
}

void Clock::decreaseFontSize() {
  font_size -= font_size_step;
  changeFontSize();
}

void Clock::changeFontSize() {
  font.setPointSize(font_size);
  label->setFont(font);
}

void Clock::setFontColor(const QString &color) {
  settings->setValue("USER/FONT_COLOR", color);
  reloadUI();
}

void Clock::setBackgroundColor(const QString &color) {
  settings->setValue("USER/BG_COLOR", color);
  reloadUI();
}

void Clock::mousePressEvent(QMouseEvent *event) {
  pressed = true;
  oldPos = event->pos();
  QWidget::mousePressEvent(event);
}

void Clock::mouseMoveEvent(QMouseEvent *event) {
  if (pressed) {
    move(pos() + (event->pos() - oldPos));
  }
  QWidget::mouseMoveEvent(event);
}

void Clock::mouseReleaseEvent(QMouseEvent *event) {
  pressed = false;
  oldPos = event->pos();
  QWidget::mouseReleaseEvent(event);
}

void Clock::contextMenuEvent(QContextMenuEvent *event) {
  QMenu *menu = new QMenu();

  // menu->setFixedWidth(100);

  // font size
  QMenu *font_size_menu = menu->addMenu("font size");
  QAction *larger_action = new QAction("larger", this);
  QAction *smaller_action = new QAction("smaller", this);

  connect(larger_action, &QAction::triggered, this, &Clock::increaseFontSize);
  connect(smaller_action, &QAction::triggered, this, &Clock::decreaseFontSize);

  font_size_menu->addAction(larger_action);
  font_size_menu->addAction(smaller_action);

  QStringList ft_colors = {"none", "blue",   "orange", "green",
                           "red",  "yellow", "white"};
  QStringList bg_colors = {"none", "blue",   "orange", "green",
                           "red",  "yellow", "white"};

  // font color
  QMenu *font_color_menu = menu->addMenu("font color");
  QList<QAction *> font_color_actions;
  for (const QString &color : ft_colors) {
    QAction *action = new QAction(color, this);
    connect(action, &QAction::triggered, [=]() { setFontColor(color); });
    font_color_actions.append(action);
  }
  font_color_menu->addActions(font_color_actions);

  // background color
  QMenu *bg_color_menu = menu->addMenu("bg color");
  QList<QAction *> bg_color_actions;
  for (const QString &color : bg_colors) {
    QAction *action = new QAction(color, this);
    connect(action, &QAction::triggered, [=]() { setBackgroundColor(color); });
    bg_color_actions.append(action);
  }
  bg_color_menu->addActions(bg_color_actions);

  // reset
  QAction *reset_action = new QAction("reset", this);
  connect(reset_action, &QAction::triggered, this, &Clock::resetUI);
  menu->addAction(reset_action);

  // quit
  QAction *quit_action = new QAction("quit", this);
  connect(quit_action, &QAction::triggered, this, &Clock::close);
  menu->addAction(quit_action);

  // menu.exec(mapToGlobal(pos));
  menu->exec(event->globalPos());
  delete menu;
}
