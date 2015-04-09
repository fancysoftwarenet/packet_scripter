#include <QApplication>
#include "mainwindow.h"

int main ( int argc, char** argv )
{
    QApplication app(argc, argv);
    app.setStyle("cleanlooks");

    MainWindow mw;
    mw.show();


    return app.exec();
}
