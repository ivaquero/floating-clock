#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QMenu>
#include <QFontDialog>
#include <QColorDialog>
#include <QSettings>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QPainter>
#include <QPainterPath>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDomDocument>
#include <QMessageBox>

class FloatingClock : public QWidget
{
  Q_OBJECT

public:
  FloatingClock(QWidget *parent = nullptr) : QWidget(parent)
  {
    // 先加载XML配置（在创建UI之前）
    loadXmlConfig();

    // 无边框、置顶、透明背景
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint |
                   Qt::Tool |
                   Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    // 创建时间标签
    timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignCenter);

    updateStyle();

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(timeLabel);
    layout->setContentsMargins(20, 20, 20, 20);
    setLayout(layout);

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(shadowBlurRadius);
    shadow->setColor(shadowColor);
    shadow->setOffset(shadowOffsetX, shadowOffsetY);
    timeLabel->setGraphicsEffect(shadow);

    // 定时器更新
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FloatingClock::updateTime);
    timer->start(1000);
    updateTime();

    // 加载用户设置（覆盖XML默认值）
    loadUserSettings();

    // 调整大小
    resize(windowWidth, windowHeight);

    // 如果位置未设置，居中显示
    if (windowPosX < 0 || windowPosY < 0)
    {
      moveToCenter();
    }
    else
    {
      move(windowPosX, windowPosY);
    }
  }

protected:
  void mousePressEvent(QMouseEvent *event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      dragging = true;
      dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
      event->accept();
    }
    else if (event->button() == Qt::RightButton)
    {
      showContextMenu(event->globalPosition().toPoint());
    }
  }

  void mouseMoveEvent(QMouseEvent *event) override
  {
    if (dragging && (event->buttons() & Qt::LeftButton))
    {
      move(event->globalPosition().toPoint() - dragPos);
      event->accept();
    }
  }

  void mouseReleaseEvent(QMouseEvent *event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      dragging = false;
      saveUserSettings();
    }
  }

  void paintEvent(QPaintEvent *) override
  {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制半透明背景
    if (bgColor.alpha() > 0)
    {
      QPainterPath path;
      path.addRoundedRect(rect(), borderRadius, borderRadius);
      painter.fillPath(path, bgColor);

      // 绘制边框
      if (borderWidth > 0)
      {
        QPen pen(borderColor);
        pen.setWidth(borderWidth);
        painter.setPen(pen);
        painter.drawPath(path);
      }
    }
  }

private slots:
  void updateTime()
  {
    QTime time = QTime::currentTime();
    QString text = time.toString(timeFormat);
    timeLabel->setText(text);
  }

  void changeFontSize()
  {
    bool ok;
    int size = QInputDialog::getInt(this, "字体大小", "请输入字体大小:",
                                    fontSize, 6, 300, 1, &ok);
    if (ok)
    {
      fontSize = size;
      updateStyle();
      saveUserSettings();
    }
  }

  void changeFontColor()
  {
    QColor color = QColorDialog::getColor(fontColor, this, "选择字体颜色",
                                          QColorDialog::ShowAlphaChannel);
    if (color.isValid())
    {
      fontColor = color;
      updateStyle();
      saveUserSettings();
    }
  }

  void changeBgColor()
  {
    QColor color = QColorDialog::getColor(bgColor, this, "选择背景颜色",
                                          QColorDialog::ShowAlphaChannel);
    if (color.isValid())
    {
      bgColor = color;
      update();
      saveUserSettings();
    }
  }

  void resetSettings()
  {
    // 重新加载XML默认配置
    loadXmlConfig();
    updateStyle();
    update();
    moveToCenter();
    saveUserSettings();
  }

  void quitApp()
  {
    qApp->quit();
  }

private:
  void showContextMenu(const QPoint &pos)
  {
    QMenu menu(this);
    menu.setStyleSheet(R"(
            QMenu {
                background-color: #f0f0f0;
                border: 1px solid #cccccc;
                border-radius: 8px;
                padding: 5px;
            }
            QMenu::item {
                padding: 8px 25px;
                border-radius: 4px;
            }
            QMenu::item:selected {
                background-color: #e0e0e0;
            }
            QMenu::item::right-arrow {
                image: none;
                width: 10px;
                height: 10px;
                border-left: 6px solid #333;
                border-top: 5px solid transparent;
                border-bottom: 5px solid transparent;
                margin-right: 5px;
            }
        )");

    QMenu *fontMenu = menu.addMenu("▶ 字体大小");
    for (int size : {36, 48, 64, 72, 96, 120})
    {
      QAction *action = fontMenu->addAction(QString::number(size));
      connect(action, &QAction::triggered, this, [this, size]()
              {
                fontSize = size;
                updateStyle();
                saveUserSettings(); });
    }
    fontMenu->addSeparator();
    QAction *customSize = fontMenu->addAction("自定义...");
    connect(customSize, &QAction::triggered, this, &FloatingClock::changeFontSize);

    QMenu *colorMenu = menu.addMenu("▶ 字体颜色");
    QList<QPair<QString, QColor>> colors = {
        {"蓝色", QColor(0, 0, 255)},
        {"红色", QColor(255, 0, 0)},
        {"绿色", QColor(0, 128, 0)},
        {"黑色", QColor(0, 0, 0)},
        {"白色", QColor(255, 255, 255)},
        {"橙色", QColor(255, 165, 0)},
        {"紫色", QColor(128, 0, 128)}};
    for (auto &c : colors)
    {
      QPixmap pixmap(16, 16);
      pixmap.fill(c.second);
      QAction *action = colorMenu->addAction(QIcon(pixmap), c.first);
      connect(action, &QAction::triggered, this, [this, color = c.second]() mutable
              {
                fontColor = color;
                updateStyle();
                saveUserSettings(); });
    }
    colorMenu->addSeparator();
    QAction *customColor = colorMenu->addAction("自定义...");
    connect(customColor, &QAction::triggered, this, &FloatingClock::changeFontColor);

    QMenu *bgMenu = menu.addMenu("▶ 背景颜色");
    QList<QPair<QString, QColor>> bgColors = {
        {"透明", QColor(255, 255, 255, 0)},
        {"白色半透明", QColor(255, 255, 255, 180)},
        {"黑色半透明", QColor(0, 0, 0, 180)},
        {"灰色半透明", QColor(128, 128, 128, 180)},
        {"蓝色半透明", QColor(0, 100, 200, 180)},
        {"自定义...", QColor()}};
    for (auto &c : bgColors)
    {
      if (c.first == "自定义...")
      {
        QAction *action = bgMenu->addAction(c.first);
        connect(action, &QAction::triggered, this, &FloatingClock::changeBgColor);
      }
      else
      {
        QPixmap pixmap(16, 16);
        pixmap.fill(c.second);
        QAction *action = bgMenu->addAction(QIcon(pixmap), c.first);
        connect(action, &QAction::triggered, this, [this, color = c.second]() mutable
                {
                    bgColor = color;
                    update();
                    saveUserSettings(); });
      }
    }

    menu.addSeparator();
    QAction *resetAction = menu.addAction("重置");
    connect(resetAction, &QAction::triggered, this, &FloatingClock::resetSettings);

    menu.addSeparator();
    QAction *quitAction = menu.addAction("退出");
    connect(quitAction, &QAction::triggered, this, &FloatingClock::quitApp);

    menu.exec(pos);
  }

  void updateStyle()
  {
    QFont font(fontFamily, fontSize, fontWeight ? QFont::Bold : QFont::Normal);
    if (fontItalic)
      font.setItalic(true);
    timeLabel->setFont(font);

    QString style = QString("color: %1;").arg(fontColor.name());
    timeLabel->setStyleSheet(style);
  }

  void moveToCenter()
  {
    QScreen *screen = QApplication::primaryScreen();
    QRect geo = screen->geometry();
    move((geo.width() - width()) / 2, (geo.height() - height()) / 2);
  }

  // 加载XML配置文件
  void loadXmlConfig()
  {
    QString xmlPath = QApplication::applicationDirPath() + "/clock.xml";

    // 如果XML不存在，创建默认配置
    if (!QFile::exists(xmlPath))
    {
      createDefaultXml(xmlPath);
    }

    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      setDefaultValues();
      return;
    }

    QDomDocument doc;
    QString errorMsg;
    int errorLine, errorColumn;

    if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn))
    {
      qWarning() << "XML解析错误:" << errorMsg << "行:" << errorLine << "列:" << errorColumn;
      setDefaultValues();
      file.close();
      return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "ClockConfig")
    {
      qWarning() << "XML根节点错误";
      setDefaultValues();
      return;
    }

    // 解析Window节点
    QDomElement window = root.firstChildElement("Window");
    if (!window.isNull())
    {
      windowWidth = getXmlInt(window, "Width", 300);
      windowHeight = getXmlInt(window, "Height", 150);
      windowPosX = getXmlInt(window, "PosX", -1);
      windowPosY = getXmlInt(window, "PosY", -1);
      borderRadius = getXmlInt(window, "BorderRadius", 15);
      borderWidth = getXmlInt(window, "BorderWidth", 0);
      borderColor = parseColor(getXmlString(window, "BorderColor", "#cccccc"));
    }

    // 解析Font节点
    QDomElement font = root.firstChildElement("Font");
    if (!font.isNull())
    {
      fontSize = getXmlInt(font, "Size", 72);
      fontFamily = getXmlString(font, "Family", "Microsoft YaHei");
      fontWeight = getXmlBool(font, "Bold", true);
      fontItalic = getXmlBool(font, "Italic", false);
      fontColor = parseColor(getXmlString(font, "Color", "#0000ff"));
    }

    // 解析Background节点
    QDomElement background = root.firstChildElement("Background");
    if (!background.isNull())
    {
      bgColor = parseColor(getXmlString(background, "Color", "#00ffffff"));
    }

    // 解析Time节点
    QDomElement time = root.firstChildElement("Time");
    if (!time.isNull())
    {
      timeFormat = getXmlString(time, "Format", "HH:mm");
    }

    // 解析Shadow节点
    QDomElement shadow = root.firstChildElement("Shadow");
    if (!shadow.isNull())
    {
      shadowBlurRadius = getXmlInt(shadow, "BlurRadius", 20);
      shadowOffsetX = getXmlInt(shadow, "OffsetX", 2);
      shadowOffsetY = getXmlInt(shadow, "OffsetY", 2);
      shadowColor = parseColor(getXmlString(shadow, "Color", "#64000000"));
    }
  }

  // 创建默认XML文件
  void createDefaultXml(const QString &path)
  {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      setDefaultValues();
      return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);

    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
           << "<!-- 浮动时钟配置文件 -->\n"
           << "<ClockConfig>\n"
           << "    <!-- 窗口设置 -->\n"
           << "    <Window>\n"
           << "        <Width>300</Width>\n"
           << "        <Height>150</Height>\n"
           << "        <PosX>-1</PosX>  <!-- -1表示屏幕居中 -->\n"
           << "        <PosY>-1</PosY>\n"
           << "        <BorderRadius>15</BorderRadius>\n"
           << "        <BorderWidth>0</BorderWidth>  <!-- 0表示无边框 -->\n"
           << "        <BorderColor>#cccccc</BorderColor>\n"
           << "    </Window>\n"
           << "\n"
           << "    <!-- 字体设置 -->\n"
           << "    <Font>\n"
           << "        <Size>72</Size>\n"
           << "        <Family>Microsoft YaHei</Family>\n"
           << "        <Bold>true</Bold>\n"
           << "        <Italic>false</Italic>\n"
           << "        <Color>#0000ff</Color>  <!-- 蓝色 -->\n"
           << "    </Font>\n"
           << "\n"
           << "    <!-- 背景设置 -->\n"
           << "    <Background>\n"
           << "        <Color>#00ffffff</Color>  <!-- ARGB格式，00表示完全透明 -->\n"
           << "    </Background>\n"
           << "\n"
           << "    <!-- 时间格式 -->\n"
           << "    <Time>\n"
           << "        <Format>HH:mm</Format>  <!-- 可选: HH:mm:ss, h:mm AP 等 -->\n"
           << "    </Time>\n"
           << "\n"
           << "    <!-- 阴影效果 -->\n"
           << "    <Shadow>\n"
           << "        <BlurRadius>20</BlurRadius>\n"
           << "        <OffsetX>2</OffsetX>\n"
           << "        <OffsetY>2</OffsetY>\n"
           << "        <Color>#64000000</Color>  <!-- 半透明黑色阴影 -->\n"
           << "    </Shadow>\n"
           << "</ClockConfig>\n";

    file.close();
  }

  // 设置默认值
  void setDefaultValues()
  {
    windowWidth = 300;
    windowHeight = 150;
    windowPosX = -1;
    windowPosY = -1;
    borderRadius = 15;
    borderWidth = 0;
    borderColor = QColor("#cccccc");

    fontSize = 72;
    fontFamily = "Microsoft YaHei";
    fontWeight = true;
    fontItalic = false;
    fontColor = QColor("#0000ff");

    bgColor = QColor("#00ffffff");
    timeFormat = "HH:mm";

    shadowBlurRadius = 20;
    shadowOffsetX = 2;
    shadowOffsetY = 2;
    shadowColor = QColor("#64000000");
  }

  // XML辅助函数
  int getXmlInt(const QDomElement &parent, const QString &tagName, int defaultValue)
  {
    QDomElement elem = parent.firstChildElement(tagName);
    if (elem.isNull())
      return defaultValue;
    return elem.text().toInt();
  }

  bool getXmlBool(const QDomElement &parent, const QString &tagName, bool defaultValue)
  {
    QDomElement elem = parent.firstChildElement(tagName);
    if (elem.isNull())
      return defaultValue;
    QString text = elem.text().toLower();
    return text == "true" || text == "1" || text == "yes";
  }

  QString getXmlString(const QDomElement &parent, const QString &tagName, const QString &defaultValue)
  {
    QDomElement elem = parent.firstChildElement(tagName);
    if (elem.isNull())
      return defaultValue;
    return elem.text();
  }

  // 加载用户设置（覆盖XML默认值）
  void loadUserSettings()
  {
    QSettings settings("FloatingClock", "Settings");
    if (settings.contains("fontSize"))
    {
      fontSize = settings.value("fontSize").toInt();
    }
    if (settings.contains("fontColor"))
    {
      fontColor = settings.value("fontColor").value<QColor>();
    }
    if (settings.contains("bgColor"))
    {
      bgColor = settings.value("bgColor").value<QColor>();
    }
    if (settings.contains("pos"))
    {
      QPoint pos = settings.value("pos").toPoint();
      if (!pos.isNull())
        move(pos);
    }
  }

  // 保存用户设置
  void saveUserSettings()
  {
    QSettings settings("FloatingClock", "Settings");
    settings.setValue("fontSize", fontSize);
    settings.setValue("fontColor", fontColor);
    settings.setValue("bgColor", bgColor);
    settings.setValue("pos", pos());
  }

  // 解析颜色字符串 (#RGB, #RRGGBB, #ARGB, #AARRGGBB)
  QColor parseColor(const QString &str)
  {
    QString s = str.trimmed();
    if (s.startsWith("#"))
      s = s.mid(1);

    bool ok;
    uint val = s.toUInt(&ok, 16);
    if (!ok)
      return QColor();

    switch (s.length())
    {
    case 3: // #RGB
      return QColor(
          ((val >> 8) & 0xF) * 17,
          ((val >> 4) & 0xF) * 17,
          (val & 0xF) * 17);
    case 6: // #RRGGBB
      return QColor((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF);
    case 8: // #AARRGGBB
      return QColor(
          (val >> 16) & 0xFF,
          (val >> 8) & 0xFF,
          val & 0xFF,
          (val >> 24) & 0xFF);
    default:
      return QColor();
    }
  }

  QLabel *timeLabel;

  // XML配置项
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

#include "main.moc"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // 高分屏适配
  app.setAttribute(Qt::AA_EnableHighDpiScaling, true);
  app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

  FloatingClock clock;
  clock.show();

  return app.exec();
}
