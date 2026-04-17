#include "clockwidget.h"
#include <QVBoxLayout>
#include <QTime>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent), m_dragging(false)
{
    setupUI();
    createMenu();
    loadSettings();

    // Set window properties
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(200, 80);

    // Start timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ClockWidget::updateTime);
    m_timer->start(1000);

    updateTime();
}

ClockWidget::~ClockWidget()
{
    saveSettings();
}

void ClockWidget::setupUI()
{
    m_timeLabel = new QLabel(this);
    m_timeLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_timeLabel);
    layout->setContentsMargins(10, 10, 10, 10);
}

void ClockWidget::createMenu()
{
    m_contextMenu = new QMenu(this);

    QAction *alwaysOnTopAction = new QAction("Always on Top", this);
    alwaysOnTopAction->setCheckable(true);
    alwaysOnTopAction->setChecked(true);
    connect(alwaysOnTopAction, &QAction::triggered, this, &ClockWidget::toggleAlwaysOnTop);

    QAction *fontColorAction = new QAction("Set Font Color", this);
    connect(fontColorAction, &QAction::triggered, this, &ClockWidget::changeFontColor);

    QAction *bgColorAction = new QAction("Set Background Color", this);
    connect(bgColorAction, &QAction::triggered, this, &ClockWidget::changeBackgroundColor);

    QAction *fontSizeAction = new QAction("Set Font Size", this);
    connect(fontSizeAction, &QAction::triggered, this, &ClockWidget::changeFontSize);

    QAction *resetAction = new QAction("Reset Settings", this);
    connect(resetAction, &QAction::triggered, this, &ClockWidget::resetSettings);

    QAction *quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, this, &ClockWidget::quitApplication);

    m_contextMenu->addAction(alwaysOnTopAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(fontColorAction);
    m_contextMenu->addAction(bgColorAction);
    m_contextMenu->addAction(fontSizeAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(resetAction);
    m_contextMenu->addAction(quitAction);
}

void ClockWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void ClockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void ClockWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void ClockWidget::updateTime()
{
    QString currentTime = QTime::currentTime().toString("HH:mm:ss");
    m_timeLabel->setText(currentTime);
}

void ClockWidget::toggleAlwaysOnTop()
{
    m_alwaysOnTop = !m_alwaysOnTop;

    Qt::WindowFlags flags = windowFlags();
    if (m_alwaysOnTop)
    {
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags &= ~Qt::WindowStaysOnTopHint;
    }
    setWindowFlags(flags);
    show();
}

void ClockWidget::changeFontColor()
{
    QColor color = QColorDialog::getColor(m_fontColor, this, "Choose Font Color");
    if (color.isValid())
    {
        m_fontColor = color;
        updateStyleSheet();
    }
}

void ClockWidget::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(m_backgroundColor, this, "Choose Background Color");
    if (color.isValid())
    {
        m_backgroundColor = color;
        updateStyleSheet();
    }
}

void ClockWidget::changeFontSize()
{
    bool ok;
    int size = QInputDialog::getInt(this, "Set Font Size", "Font Size:", m_fontSize, 8, 72, 1, &ok);
    if (ok)
    {
        m_fontSize = size;
        updateStyleSheet();
    }
}

void ClockWidget::resetSettings()
{
    int ret = QMessageBox::question(this, "Reset Settings", "Are you sure you want to reset all settings?");
    if (ret == QMessageBox::Yes)
    {
        m_settings->clear();
        loadSettings();
        updateStyleSheet();
    }
}

void ClockWidget::quitApplication()
{
    qApp->quit();
}

void ClockWidget::loadSettings()
{
    m_settings = new QSettings("QFlock", "Clock", this);

    m_fontColor = m_settings->value("fontColor", QColor(255, 255, 255)).value<QColor>();
    m_backgroundColor = m_settings->value("backgroundColor", QColor(0, 0, 0, 150)).value<QColor>();
    m_fontSize = m_settings->value("fontSize", 24).toInt();
    m_alwaysOnTop = m_settings->value("alwaysOnTop", true).toBool();

    // Restore window position
    QPoint pos = m_settings->value("position", QPoint(100, 100)).toPoint();
    move(pos);

    updateStyleSheet();
}

void ClockWidget::saveSettings()
{
    m_settings->setValue("fontColor", m_fontColor);
    m_settings->setValue("backgroundColor", m_backgroundColor);
    m_settings->setValue("fontSize", m_fontSize);
    m_settings->setValue("alwaysOnTop", m_alwaysOnTop);
    m_settings->setValue("position", pos());
}

void ClockWidget::updateStyleSheet()
{
    QString styleSheet = QString(
                             "QLabel { "
                             "color: %1; "
                             "font-size: %2pt; "
                             "font-weight: bold; "
                             "background-color: %3; "
                             "border-radius: 10px; "
                             "padding: 5px; "
                             "}")
                             .arg(m_fontColor.name(),
                                  QString::number(m_fontSize),
                                  m_backgroundColor.name(QColor::HexArgb));

    m_timeLabel->setStyleSheet(styleSheet);
    setStyleSheet(QString("background-color: transparent;"));
}
