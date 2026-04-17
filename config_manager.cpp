#include "config_manager.h"
#include <QFile>
#include <QDebug>

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
{
    setDefaultValues();
}

bool ConfigManager::loadSettings(const QString &filename)
{
    QFile file(filename);
    if (!file.exists())
    {
        qDebug() << "Config file does not exist, using defaults";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open config file for reading:" << file.errorString();
        return false;
    }

    QXmlStreamReader reader(&file);

    // Check if it's a valid XML file
    if (!reader.readNextStartElement() || reader.name() != QString("QFlockConfig"))
    {
        qDebug() << "Invalid config file format";
        file.close();
        return false;
    }

    // Read configuration values
    while (reader.readNextStartElement())
    {
        QString name = reader.name().toString();
        QString text = reader.readElementText();

        if (name == "FontColor")
        {
            m_fontColor = QColor(text);
        }
        else if (name == "BackgroundColor")
        {
            m_backgroundColor = QColor(text);
        }
        else if (name == "FontSize")
        {
            m_fontSize = text.toInt();
        }
        else if (name == "AlwaysOnTop")
        {
            m_alwaysOnTop = (text.toLower() == QString("true"));
        }
        else if (name == "WindowPosition")
        {
            // Parse position format: "x,y"
            QStringList coords = text.split(',');
            if (coords.size() == 2)
            {
                int x = coords[0].toInt();
                int y = coords[1].toInt();
                m_windowPosition = QPoint(x, y);
            }
        }
        else if (name == "WindowSize")
        {
            // Parse size format: "width,height"
            QStringList dims = text.split(',');
            if (dims.size() == 2)
            {
                int width = dims[0].toInt();
                int height = dims[1].toInt();
                m_windowSize = QSize(width, height);
            }
        }
        else
        {
            reader.skipCurrentElement();
        }
    }

    file.close();

    if (reader.hasError())
    {
        qDebug() << "Error reading config file:" << reader.errorString();
        return false;
    }

    return true;
}

bool ConfigManager::saveSettings(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open config file for writing:" << file.errorString();
        return false;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    // Root element
    writer.writeStartElement("QFlockConfig");

    // Font color
    writer.writeTextElement("FontColor", m_fontColor.name(QColor::HexArgb));

    // Background color
    writer.writeTextElement("BackgroundColor", m_backgroundColor.name(QColor::HexArgb));

    // Font size
    writer.writeTextElement("FontSize", QString::number(m_fontSize));

    // Always on top
    writer.writeTextElement("AlwaysOnTop", m_alwaysOnTop ? "true" : "false");

    // Window position
    QString positionStr = QString("%1,%2")
                              .arg(m_windowPosition.x())
                              .arg(m_windowPosition.y());
    writer.writeTextElement("WindowPosition", positionStr);

    // Window size
    QString sizeStr = QString("%1,%2")
                          .arg(m_windowSize.width())
                          .arg(m_windowSize.height());
    writer.writeTextElement("WindowSize", sizeStr);

    // Close root element
    writer.writeEndElement();

    writer.writeEndDocument();
    file.close();

    return true;
}

void ConfigManager::resetToDefaults()
{
    setDefaultValues();
}

bool ConfigManager::configExists(const QString &filename) const
{
    return QFile::exists(filename);
}

void ConfigManager::setDefaultValues()
{
    m_fontColor = QColor(255, 255, 255);      // White
    m_backgroundColor = QColor(0, 0, 0, 150); // Semi-transparent black
    m_fontSize = 24;
    m_alwaysOnTop = true;
    m_windowPosition = QPoint(100, 100);
    m_windowSize = QSize(200, 80); // Default clock size
}
