#include "routewidget.h"

RouteWidget::RouteWidget(int id, QWidget *parent) :
    QWidget(parent), _id(id), _eigrp(), _static()
{
    this->_id = id;
    _layout = new QHBoxLayout();

    _protocole = new QComboBox();
    _protocole->addItem("EIGRP");
    _protocole->addItem("Statique");
    QObject::connect(_protocole, SIGNAL(currentIndexChanged(int)), this, SLOT(sl_prot_change(int)));

    _eigrp = new EigrpWidget();
    QObject::connect(_eigrp, SIGNAL(destroyed()), this, SLOT(sl_widget_deleted()));
    _route_type = EIGRP;

    _layout->addWidget(_protocole);
    _layout->addWidget(_eigrp);

    this->setLayout(_layout);

    qDebug() << "Bouton créé avec l'id " << _id;
}

void RouteWidget::sl_prot_change(int a)
{
    switch(a)
    {
    case 0:

        _eigrp = new EigrpWidget();
        QObject::connect(_eigrp, SIGNAL(destroyed()), this, SLOT(sl_widget_deleted()));

        _route_type = EIGRP;
        _layout->addWidget(_eigrp);//*/
        break;

    case 1:
        _static = new StaticWidget();
        QObject::connect(_static, SIGNAL(destroyed()), this, SLOT(sl_widget_deleted()));
        _route_type = STATIC;
        _layout->addWidget(_static);//*/
        break;
    }
}

void RouteWidget::decrementId(ROUTE_TYPE rt)
{
    qDebug() << "Entree dans RouteWidget::decrementId(" + QString((rt != EIGRP) ? ((rt == STATIC) ? "STATIC" : "NONE") : "EIGRP") + ") ET id = " << _id;

    if ( rt == _route_type )
    {
        if ( rt == EIGRP )
            _eigrp->decrementId();
        else if ( rt == STATIC )
            _static->decrementId();
    }

}

void RouteWidget::setId(int id)
{
    _id = id;
}

void RouteWidget::sl_widget_deleted() //Quand on switche de protocole
{
    emit si_widget_deleted(_id, _route_type);
    _route_type = NONE;

    if ( _eigrp != NULL )
        _eigrp = NULL;
    else if ( _static != NULL )
        _static = NULL;
}
