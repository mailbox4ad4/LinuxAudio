
/////////////////////
// Application.cpp //
/////////////////////

#include <QDebug>
#include "Application.h"


Application::Application(int & argc, char ** argv) : QApplication(argc, argv)
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

    mainWindow = new MainWindow(this);

    mainWindow->show();
}

Application::~Application()
{
    qDebug() << __PRETTY_FUNCTION__;

    delete mainWindow;

    delete audio;

    audioSource->close();

    delete audioSource;
}

void Application::audioOutputStateChangedSlot(QAudio::State state)
{
    QString stateString = QString("unknown (%1)").arg(state);

    switch (state)
    {
        case QAudio::ActiveState    : stateString = "active"; break;
        case QAudio::SuspendedState : stateString = "suspended"; break;
        case QAudio::StoppedState   : stateString = "stopped"; break;
        case QAudio::IdleState      : stateString = "idle"; break;
    }

    qDebug() << __PRETTY_FUNCTION__ << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << stateString;
}

void Application::startAudioSlot()
{
    qDebug() << __PRETTY_FUNCTION__ ;

    audio->start(audioSource);
}

void Application::stopAudioSlot()
{
    qDebug() << __PRETTY_FUNCTION__;
    audio->stop();
}

void Application::suspendAudioSlot()
{
    qDebug() << __PRETTY_FUNCTION__;
    audio->suspend();
}

void Application::resumeAudioSlot()
{
    qDebug() << __PRETTY_FUNCTION__;
    audio->resume();
}

void Application::resetAudioSlot()
{
    qDebug() << __PRETTY_FUNCTION__;
    audio->reset();
}
