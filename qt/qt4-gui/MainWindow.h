
//////////////////
// MainWindow.h //
//////////////////

#ifndef MainWindow_h
#define MainWindow_h

#include <QMainWindow>
#include "CentralWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        MainWindow(Application * app);

        virtual ~MainWindow();

    private:

        CentralWidget * centralWidget;
};

#endif // MainWindow_h
