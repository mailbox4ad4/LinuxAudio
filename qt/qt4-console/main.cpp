
//////////////
// main.cpp //
//////////////

#include "CoreApplication.h"
#include <QTimer>

int main(int argc, char ** argv)
{
    CoreApplication * app = new CoreApplication(argc, argv);

    QTimer::singleShot(2000, app, SLOT(quit()));
    int exitcode = QCoreApplication::exec();

    delete app;

    return exitcode;
}
