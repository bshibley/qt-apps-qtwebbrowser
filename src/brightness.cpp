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
    // Scale, clamp and round value to the proper brightness
    double ret = m_level = (unsigned)(max(min((double)m_maxLevel*(percent/100.0),m_maxLevel),0)+0.5);

    if(invert_brightness)
        m_level = m_maxLevel-m_level;

    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // error condition
        return -1;
    }

    m_file.write(QByteArray::number(m_level));

    m_file.close();

    return (ret/(double)m_maxLevel)*100.0;
}


unsigned Brightness::level()
{
    return m_level;
}
