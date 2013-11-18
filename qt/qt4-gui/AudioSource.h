
///////////////////
// AudioSource.h //
///////////////////

#ifndef AudioSource_h
#define AudioSource_h

#include <QIODevice>

class AudioSource : public QIODevice
{
    Q_OBJECT

    public:

        AudioSource();

        virtual ~AudioSource();

        virtual qint64 readData(char * data, qint64 maxSize);

        virtual qint64 writeData(const char * data, qint64 maxSize);

    private:

        quint64 frameNr;
};

#endif // AudioSource_h
