
//////////////
// main.cpp //
//////////////

#include "Application.h"

int main(int argc, char ** argv)
{
    Application * app = new Application(argc, argv);

    int exitcode = QApplication::exec();

    delete app;

    return exitcode;
}
