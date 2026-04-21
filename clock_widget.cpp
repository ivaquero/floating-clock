#include "clock_widget.h"
#include "config_manager.h"
#include "window_helper.h"
#include <QVBoxLayout>
#include <QTime>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>
#include <QScreen>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent), m_dragging(false), m_resizing(false), m_resizeBorder(5)
{
    setupUI();
    createMenu();
    loadSettings();

    // Set window properties for cross-platform always-on-top
    Qt::WindowFlags flags = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool;

#ifdef Q_OS_MAC
    // On macOS, we need additional flags for proper always-on-top behavior in fullscreen
    flags |= Qt::WindowDoesNotAcceptFocus;
    setAttribute(Qt::WA_ShowWithoutActivating);
#endif

    setWindowFlags(flags);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true); // Enable mouse tracking for resize cursor

    // Set up platform-specific window properties after window creation
    WindowHelper::setupAlwaysOnTopForFullscreen(this);

    // Start timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ClockWidget::updateTime);
    m_timer->start(1000);

    updateTime();
}

ClockWidget::~ClockWidget()
{
    // Settings are now saved immediately after changes, no need to save here
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
        if (isInResizeArea(event->pos()))
        {
            m_resizing = true;
            m_resizeStartPos = event->globalPosition().toPoint();
            m_resizeStartSize = size();
            event->accept();
        }
        else
        {
            m_dragging = true;
            m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void ClockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_resizing && (event->buttons() & Qt::LeftButton))
    {
        QPoint delta = event->globalPosition().toPoint() - m_resizeStartPos;
        QSize newSize = m_resizeStartSize + QSize(delta.x(), delta.y());

        // Minimum size constraints
        newSize = newSize.expandedTo(QSize(100, 50));

        resize(newSize);
        event->accept();
    }
    else if (m_dragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
    else
    {
        // Update cursor shape when hovering over resize area
        if (isInResizeArea(event->pos()))
        {
            setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void ClockWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_resizing)
        {
            m_resizing = false;
            // Save the new size and position to config
            if (m_configManager)
            {
                m_configManager->setWindowPosition(pos());
                m_configManager->setWindowSize(size());
                m_configManager->saveSettings();
            }
            event->accept();
        }
        else if (m_dragging)
        {
            m_dragging = false;
            // Save the new position to config
            if (m_configManager)
            {
                m_configManager->setWindowPosition(pos());
                m_configManager->saveSettings();
            }
            event->accept();
        }
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

    // Re-apply platform-specific window properties after changing window flags
    if (m_alwaysOnTop)
    {
        WindowHelper::setupAlwaysOnTopForFullscreen(this);
    }
}

void ClockWidget::changeFontColor()
{
    QColor color = QColorDialog::getColor(m_fontColor, this, "Choose Font Color");
    if (color.isValid())
    {
        m_fontColor = color;
        m_configManager->setFontColor(m_fontColor);
        updateStyleSheet();
    }
}

void ClockWidget::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(m_backgroundColor, this, "Choose Background Color");
    if (color.isValid())
    {
        m_backgroundColor = color;
        m_configManager->setBackgroundColor(m_backgroundColor);
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
        m_configManager->setFontSize(m_fontSize);
        updateStyleSheet();
    }
}

void ClockWidget::resetSettings()
{
    int ret = QMessageBox::question(this, "Reset Settings", "Are you sure you want to reset all settings?");
    if (ret == QMessageBox::Yes)
    {
        m_configManager->resetToDefaults();
        loadSettings();
        updateStyleSheet();
        // Reset to default size
        resize(m_configManager->windowSize());
    }
}

void ClockWidget::quitApplication()
{
    qApp->quit();
}

bool ClockWidget::isInResizeArea(const QPoint &pos) const
{
    // Check if mouse is in the bottom-right corner resize area
    QRect resizeArea(rect().bottomRight() - QPoint(m_resizeBorder * 2, m_resizeBorder * 2),
                     QSize(m_resizeBorder * 2, m_resizeBorder * 2));
    return resizeArea.contains(pos);
}

void ClockWidget::positionAtBottomRight()
{
    // Get primary screen geometry
    QScreen *screen = QApplication::primaryScreen();
    if (!screen)
    {
        // Fallback to default position if no screen available
        move(100, 100);
        return;
    }

    QRect screenGeometry = screen->availableGeometry();
    QSize windowSize = m_configManager->windowSize();

    // Calculate position: bottom-right corner with some margin
    int margin = 20; // 20 pixels margin from screen edges
    int x = screenGeometry.right() - windowSize.width() - margin;
    int y = screenGeometry.bottom() - windowSize.height() - margin;

    move(x, y);
}

void ClockWidget::loadSettings()
{
    m_configManager = new ConfigManager(this);

    // Load from XML config file
    if (!m_configManager->loadSettings())
    {
        // If loading fails, config manager already has default values
        qDebug() << "Using default settings";
    }

    // Apply loaded settings
    m_fontColor = m_configManager->fontColor();
    m_backgroundColor = m_configManager->backgroundColor();
    m_fontSize = m_configManager->fontSize();
    m_alwaysOnTop = m_configManager->alwaysOnTop();

    // Restore window position and size
    QPoint windowPos = m_configManager->windowPosition();
    if (windowPos.x() == -1 && windowPos.y() == -1)
    {
        // First time: position at bottom-right corner
        positionAtBottomRight();
    }
    else
    {
        move(windowPos);
    }
    resize(m_configManager->windowSize());

    // Update always on top checkbox in menu
    QList<QAction *> actions = m_contextMenu->actions();
    for (QAction *action : actions)
    {
        if (action->text() == QString("Always on Top"))
        {
            action->setChecked(m_alwaysOnTop);
            break;
        }
    }

    updateStyleSheet();
}

void ClockWidget::saveSettings()
{
    if (!m_configManager)
        return;

    // Update config manager with current values
    m_configManager->setFontColor(m_fontColor);
    m_configManager->setBackgroundColor(m_backgroundColor);
    m_configManager->setFontSize(m_fontSize);
    m_configManager->setAlwaysOnTop(m_alwaysOnTop);
    m_configManager->setWindowPosition(pos());
    m_configManager->setWindowSize(size());

    // Save to XML file
    if (!m_configManager->saveSettings())
    {
        qDebug() << "Failed to save settings to config.xml";
    }
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
