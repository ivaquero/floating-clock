#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class ConfigManager : public QObject
{
    Q_OBJECT

public:
    explicit ConfigManager(QObject *parent = nullptr);

    // Load settings from XML file
    bool loadSettings(const QString &filename = "config.xml");

    // Save settings to XML file
    bool saveSettings(const QString &filename = "config.xml");

    // Getters
    QColor fontColor() const { return m_fontColor; }
    QColor backgroundColor() const { return m_backgroundColor; }
    int fontSize() const { return m_fontSize; }
    bool alwaysOnTop() const { return m_alwaysOnTop; }
    QPoint windowPosition() const { return m_windowPosition; }
    QSize windowSize() const { return m_windowSize; }

    // Setters
    void setFontColor(const QColor &color) { m_fontColor = color; }
    void setBackgroundColor(const QColor &color) { m_backgroundColor = color; }
    void setFontSize(int size) { m_fontSize = size; }
    void setAlwaysOnTop(bool onTop) { m_alwaysOnTop = onTop; }
    void setWindowPosition(const QPoint &pos) { m_windowPosition = pos; }
    void setWindowSize(const QSize &size) { m_windowSize = size; }

    // Reset to default values
    void resetToDefaults();

    // Check if config file exists
    bool configExists(const QString &filename = "config.xml") const;

private:
    // Default values
    void setDefaultValues();

    // Settings data
    QColor m_fontColor;
    QColor m_backgroundColor;
    int m_fontSize;
    bool m_alwaysOnTop;
    QPoint m_windowPosition;
    QSize m_windowSize;
};

#endif // CONFIG_MANAGER_H
