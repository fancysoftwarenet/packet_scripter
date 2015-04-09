#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _cw = new CentralWidget();

    this->setCentralWidget(_cw);
    this->setGeometry(100, 100, 768, 550);
}
