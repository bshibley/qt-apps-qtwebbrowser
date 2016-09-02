#include "brightness.h"

Brightness::Brightness(QObject *parent)
    : QObject(parent)
{
    m_file.setFileName(c_backlightSysPath+"max_brightness");
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // error condition
        return;
    }

    m_maxLevel = m_file.readAll().trimmed().toUInt();

    qInfo() << "m_maxLevel: " << m_maxLevel;

    if(m_maxLevel <= 0)
        m_maxLevel = 1;

    m_file.close();

    m_file.setFileName(c_backlightSysPath+"brightness");

    setLevel(100.0);

    return;
}


double Brightness::setLevel(double percent)
{
    // Reducing slider value spectrum to only non-zero levels
    unsigned maxSliderValue = m_maxLevel - 1;

    // If slider has only one possible value, simply return 100% (and avoid divide by 0 below)
    if(maxSliderValue == 0)
        return 100.0;

    // Scale, clamp and round value to the proper brightness
    double ret = m_level = (unsigned)(max(min((double)maxSliderValue*(percent/100.0),maxSliderValue),0)+0.5);

    // Invert level if screen has inverted brightness
    if(invert_brightness)
        m_level = maxSliderValue-m_level;
    else // Ensure only non-zero value -ie. no zero brightness
        m_level++;

    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // error condition
        return -1;
    }

    // Write level to brightness PWM
    m_file.write(QByteArray::number(m_level+1));

    m_file.close();

    return (ret/(double)maxSliderValue)*100.0;
}


unsigned Brightness::level()
{
    return m_level;
}
