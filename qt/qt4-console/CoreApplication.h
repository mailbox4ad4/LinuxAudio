
///////////////////////
// CoreApplication.h //
///////////////////////

#ifndef CoreApplication_h
#define CoreApplication_h

#include <QCoreApplication>
#include <QAudioOutput>

#include "AudioSource.h"

class CoreApplication : public QCoreApplication
{
    Q_OBJECT

    public:

        CoreApplication(int & argc, char ** argv);

        virtual ~CoreApplication();

    private slots:

        void audioOutputStateChangedSlot(QAudio::State state);

    private:

        AudioSource * audioSource;

        QAudioOutput * audio;
};

#endif // CoreApplication_h
