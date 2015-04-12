#include <QApplication>
#include "mainwindow.h"
#include <QMacStyle>

int main ( int argc, char** argv )
{
    QApplication::setStyle("cleanlooks");

    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();


    return app.exec();
}
