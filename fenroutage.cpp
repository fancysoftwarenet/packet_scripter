#include "fenroutage.h"

FenRoutage::FenRoutage(QWidget *parent) :
    QWidget(parent), _routes()
{
    _layout = new QVBoxLayout();

    _ajouter = new QPushButton("Ajouter une route");
    _routes.push_back(new RouteWidget());

    _layout->addWidget(_routes[0]);
    _layout->addWidget(_ajouter);

    this->setLayout(_layout);
}
