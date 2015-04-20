#include "routewidget.h"

RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    _layout = new QHBoxLayout();

    _protocole = new QComboBox();
    _protocole->addItem("EIGRP");
    _protocole->addItem("Statique");
    QObject::connect(_protocole, SIGNAL(currentIndexChanged(int)), this, SLOT(sl_prot_change(int)));
    _eigrp = new EigrpWidget();

    _layout->addWidget(_protocole);
    _layout->addWidget(_eigrp);

    this->setLayout(_layout);
}

void RouteWidget::sl_prot_change(int a)
{

    switch(a)
    {
    case 0:
        if ( _layout->itemAt(1) != NULL )
        {
            delete _layout->itemAt(_layout->count()-1)->widget();
        }//*
        _eigrp = new EigrpWidget();
        _layout->addWidget(_eigrp);//*/
        break;

    case 1:
        if ( _layout->itemAt(1) != NULL )
        {
            delete _layout->itemAt(_layout->count()-1)->widget();
        }//*
        _static = new StaticWidget();
        _layout->addWidget(_static);//*/
        break;

    default:
        break;
    }
}
