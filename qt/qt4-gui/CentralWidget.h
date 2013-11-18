
/////////////////////
// CentralWidget.h //
/////////////////////

#ifndef CentralWidget_h
#define CentralWidget_h

#include <QWidget>

class Application;

class CentralWidget : public QWidget
{
    Q_OBJECT

    public:

        CentralWidget(Application * app);

        virtual ~CentralWidget();

    private:

};

#endif // CentralWidget_h
