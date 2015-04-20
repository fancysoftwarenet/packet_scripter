#include "fenroutage.h"

FenRoutage::FenRoutage(QWidget *parent) :
    QWidget(parent), _routes()
{
    _layout = new QVBoxLayout();

    _ajouter = new QPushButton("Ajouter une route");
    QObject::connect(_ajouter, SIGNAL(clicked()), this, SLOT(sl_ajouter()));

    _routes.push_back(new RouteWidget(getNbRoutes()));

    _layout->addWidget(_routes[0]);
    _layout->addWidget(_ajouter);

    this->setLayout(_layout);
}

void FenRoutage::sl_ajouter()
{
    _routes.push_back(new RouteWidget());
    _layout->removeWidget(_ajouter);
    _layout->addWidget(_routes[_routes.size()-1]);
    _layout->addWidget(_ajouter);
}

int FenRoutage::getNbRoutes()
{
    return _routes.size();
}
