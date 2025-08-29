#include "KennyTracker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KennyTracker window;
    window.show();
    return app.exec();
}
