
/////////////////////
// AudioSource.cpp //
/////////////////////

#include <QDebug>

#include "AudioSource.h"

AudioSource::AudioSource()
{
    qDebug() << __PRETTY_FUNCTION__;
    frameNr = 0;
}

AudioSource::~AudioSource()
{
    qDebug() << __PRETTY_FUNCTION__;
}

qint64 AudioSource::readData(char * data, qint64 maxSize)
{
    qDebug() << __PRETTY_FUNCTION__ << maxSize;

    qint64 size = 0;
    qint16 * frame = reinterpret_cast<qint16 *>(data);

    while (size + 4 <= maxSize)
    {
        double t = frameNr / 48000.0;

        frame[0] = round(10000.0 * sin(440.0 * t * 2.0 * M_PI)); // left
        frame[1] = round(10000.0 * sin(880.0 * t * 2.0 * M_PI)); // right

        frame += 2;
        ++frameNr;
        size += 4;
    }

    return maxSize;
}

qint64 AudioSource::writeData(const char * data, qint64 maxSize)
{
    qDebug() << __PRETTY_FUNCTION__ << maxSize;

    (void)data; // unused

    Q_ASSERT(false);

    return -1;
}
