#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QFile>
#include <QTextStream>
#include <QDebug>

#define COLIBRI_IMX6_BACKLIGHT_PATH "/sys/class/backlight/backlight.15/"
#define APALIS_IMX6_BACKLIGHT_PATH "/sys/class/backlight/backlight.17/"
#define INVERT_BRIGHTNESS 1

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

class Brightness : public QObject
{
    Q_OBJECT
    //Q_PROPERTY (unsigned level READ level WRITE setLevel)

public:
    Brightness(QObject *parent = 0);
    Q_INVOKABLE double setLevel(double percent);
    Q_INVOKABLE unsigned level();
private:
    QFile m_file;
    unsigned m_level;
    unsigned m_maxLevel;
    const QString c_backlightSysPath = COLIBRI_IMX6_BACKLIGHT_PATH;
    const bool invert_brightness = INVERT_BRIGHTNESS;
};

#endif // BRIGHTNESS_H
