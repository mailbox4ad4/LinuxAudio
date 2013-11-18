
///////////////////
// Application.h //
///////////////////

#ifndef Application_h
#define Application_h

#include <QApplication>
#include <QAudioOutput>
#include <QDebug>
#include <QFile>

#include "MainWindow.h"
#include "AudioSource.h"

class Application : public QApplication
{
    Q_OBJECT

    public:

        Application(int & argc, char ** argv);

        virtual ~Application();

    public slots:

        void startAudioSlot();
        void stopAudioSlot();
        void suspendAudioSlot();
        void resumeAudioSlot();
        void resetAudioSlot();

    private slots:

        void audioOutputStateChangedSlot(QAudio::State state);

    private:

        AudioSource * audioSource;

        QAudioOutput * audio;

        MainWindow * mainWindow;
};

#endif // Application_h
