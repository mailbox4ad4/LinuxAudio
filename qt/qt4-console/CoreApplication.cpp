
/////////////////////////
// CoreApplication.cpp //
/////////////////////////

#include <QDebug>
#include "CoreApplication.h"

CoreApplication::CoreApplication(int & argc, char ** argv) : QCoreApplication(argc, argv)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (true)
    {
        QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

        qDebug() << "Number of audio output devices found:" << devices.size();

        for (const QAudioDeviceInfo & deviceInfo : devices)
        {
            qDebug() << deviceInfo.deviceName();
        }
    }

    audioSource = new AudioSource;

    bool openOk = audioSource->open(QIODevice::ReadOnly);
    Q_ASSERT(openOk);

    QAudioFormat format;

    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleRate(48000);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);

    audio = new QAudioOutput(format);

    bool connectOk;

    connectOk = QObject::connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioOutputStateChangedSlot(QAudio::State)));
    Q_ASSERT(connectOk);

    audio->start(audioSource);
}

CoreApplication::~CoreApplication()
{
    qDebug() << __PRETTY_FUNCTION__;

    delete audio;

    audioSource->close();

    delete audioSource;
}

void CoreApplication::audioOutputStateChangedSlot(QAudio::State state)
{
    QString stateString = QString("unknown (%1)").arg(state);

    switch (state)
    {
        case QAudio::ActiveState    : stateString = "active"; break;
        case QAudio::SuspendedState : stateString = "suspended"; break;
        case QAudio::StoppedState   : stateString = "stopped"; break;
        case QAudio::IdleState      : stateString = "idle"; break;
    }

    qDebug() << __PRETTY_FUNCTION__ << "State changed to:" << stateString;
}
