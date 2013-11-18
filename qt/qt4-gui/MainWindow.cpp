
////////////////////
// MainWindow.cpp //
////////////////////

#include <QDebug>
#include "MainWindow.h"

MainWindow::MainWindow(Application * app)
{
    qDebug() << __PRETTY_FUNCTION__;

    centralWidget = new CentralWidget(app);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    qDebug() << __PRETTY_FUNCTION__;
}
