#include "Utils.h"
#include <QPainter>
#include <windows.h>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QProcess>
#include <QPalette>

#undef min  // Undefine min macro to avoid conflicts with std::min
#undef max  // Undefine max macro to avoid conflicts with std::max

QString getTheme()
{
    // Determine the theme based on registry value
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        QSettings::NativeFormat);
    int value = settings.value("AppsUseLightTheme", 1).toInt();

    return (value == 0) ? "light" : "dark";
}

QIcon Utils::getIcon(int type, int volume, bool muted)
{
    QString theme = getTheme();
    QString variant;
    if (type == 1) {
        QString volumeSymbol;
        if (volume > 66) {
            volumeSymbol = "100";
        } else if (volume > 33) {
            volumeSymbol = "66";
        } else if (volume > 0) {
            volumeSymbol = "33";
        } else {
            volumeSymbol = "0";
        }
        return QIcon(":/icons/tray_" + theme + "_" + volumeSymbol + ".png");
    } else if (type == 2) {
        if (muted) {
            return QIcon(":/icons/headset_" + theme + "_muted.png");
        } else {
            return QIcon(":/icons/headset_" + theme + ".png");
        }
    } else {
        if (muted) {
            return QIcon(":/icons/mic_" + theme + "_muted.png");
        } else {
            return QIcon(":/icons/mic_" + theme + ".png");
        }
    }
}

int getBuildNumber()
{
    QSettings registry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", QSettings::NativeFormat);
    QVariant buildVariant = registry.value("CurrentBuild");

    if (!buildVariant.isValid()) {
        buildVariant = registry.value("CurrentBuildNumber");
    }

    if (buildVariant.isValid() && buildVariant.canConvert<QString>()) {
        bool ok;
        int buildNumber = buildVariant.toString().toInt(&ok);
        if (ok) {
            return buildNumber;
        }
    }

    qDebug() << "Failed to retrieve build number from the registry.";
    return -1;
}

bool Utils::isWindows10()
{
    int buildNumber = getBuildNumber();
    return (buildNumber >= 10240 && buildNumber < 22000);
}

QColor Utils::adjustColor(const QColor &color, double factor) {
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    int a = color.alpha();

    r = std::min(std::max(static_cast<int>(r * factor), 0), 255);
    g = std::min(std::max(static_cast<int>(g * factor), 0), 255);
    b = std::min(std::max(static_cast<int>(b * factor), 0), 255);

    return QColor(r, g, b, a);
}

bool Utils::isDarkMode(const QColor &color) {
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    double brightness = (r + g + b) / 3.0;
    return brightness < 127;
}

void Utils::setFrameColorBasedOnWindow(QWidget *window, QFrame *frame) {
    QColor main_bg_color = window->palette().color(QPalette::Window);
    QColor frame_bg_color;

    if (isDarkMode(main_bg_color)) {
        frame_bg_color = adjustColor(main_bg_color, 1.75);  // Brighten color
    } else {
        frame_bg_color = adjustColor(main_bg_color, 0.95);  // Darken color
    }

    QPalette palette = frame->palette();
    palette.setBrush(QPalette::Window, QBrush(frame_bg_color));
    frame->setAutoFillBackground(true);
    frame->setPalette(palette);
}

QIcon Utils::generateMutedIcon(QPixmap originalPixmap) {
    // Load the muted layer and scale it to match the original pixmap size
    QPixmap mutedLayer(":/icons/muted_layer.png");
    mutedLayer = mutedLayer.scaled(originalPixmap.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a painter to combine the original icon with the muted layer
    QPainter painter(&originalPixmap);  // Pass originalPixmap as writable
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);  // Ensure the layer is drawn on top
    painter.drawPixmap(0, 0, mutedLayer);  // Draw muted layer on top of the original icon
    painter.end();  // End the painting process

    return QIcon(originalPixmap);  // Return the modified icon with the muted layer
}

