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

    qDebug() << "Taille de _routes : " << _routes.size();
}

void FenRoutage::sl_ajouter()
{
    int id = getNbRoutes();

    _routes.push_back(new RouteWidget(id));
    QObject::connect(_routes[id], SIGNAL(si_widget_deleted(int, ROUTE_TYPE)), this, SLOT(sl_route_deleted(int, ROUTE_TYPE)));

    _layout->removeWidget(_ajouter);
    _layout->addWidget(_routes[_routes.size()-1]);
    _layout->addWidget(_ajouter);
}

int FenRoutage::getNbRoutes()
{
    return _routes.size();
}

void FenRoutage::sl_route_deleted(int id, ROUTE_TYPE rt)
{
    for ( unsigned int i = id+1 ; i < _routes.size() ; i++ )
    {
        _routes[i]->decrementId(rt);
    }
}
