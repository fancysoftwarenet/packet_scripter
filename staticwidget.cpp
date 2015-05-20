#include "staticwidget.h"

StaticWidget::StaticWidget(QWidget *parent) :
    QWidget(parent), _dm(), _id(_dm.getStaticCount())
{
    _layout = new QHBoxLayout();

    _dst_ip_label = new QLabel("IP du réseau de destination: ");
    _dst_ip = new QLineEdit();
    _dst_ip->setInputMask("000.000.000.000");

    _dst_masque_label = new QLabel("Masque: ");
    _dst_masque = new QLineEdit();
    _dst_masque->setInputMask("000.000.000.000");

    _to_label = new QLabel("Router vers ");
    _to = new QLineEdit();
    _to->setInputMask("000.000.000.000");

    _supprimer = new QPushButton();
    _supprimer->setIcon(QIcon("trash.png"));

    _layout->addWidget(_dst_ip_label);
    _layout->addWidget(_dst_ip);
    _layout->addWidget(_dst_masque_label);
    _layout->addWidget(_dst_masque);
    _layout->addWidget(_to_label);
    _layout->addWidget(_to);
    _layout->addWidget(_supprimer);

    QObject::connect(_dst_ip, SIGNAL(textChanged(QString)), this, SLOT(sl_sauvegarder(QString)));
    QObject::connect(_dst_masque, SIGNAL(textChanged(QString)), this, SLOT(sl_sauvegarder(QString)));
    QObject::connect(_to, SIGNAL(textChanged(QString)), this, SLOT(sl_sauvegarder(QString)));
    QObject::connect(_supprimer, SIGNAL(clicked()), this, SLOT(sl_delete()));
    QObject::connect(this, SIGNAL(destroyed()), this, SLOT(sl_delete()));
    this->setLayout(_layout);

    sl_sauvegarder(NULL);
}


void StaticWidget::sl_delete()
{
    qDebug() << "Entree dans StaticWidget::sl_delete()\n";

    emit si_deleted();
    _dm.remove("static", _id);
    delete this;

    qDebug() << "Sortie de StaticWidget::sl_delete()\n";
}

void StaticWidget::sl_sauvegarder(QString s)
{
    if ( _dm.getStatic("ip", _id) == NULL )
        _dm.putStatic(_id, _dst_ip->text(), _dst_masque->text(), _to->text());
    else
        _dm.updateStatic(_id, _dst_ip->text(), _dst_masque->text(), _to->text());

    emit si_edited();
}

void StaticWidget::setId(int id)
{
    _id = id;
}

void StaticWidget::decrementId()
{
    qDebug() << "Entree dans StaticWidget::decrementId()\n\t_id = " << _id << "\n";
    _id--;
    _dm.updateStatic(_id, _dst_ip->text(), _dst_masque->text(), _to->text());
    qDebug() << "Sortie de StaticWidget::decrementId()\n\t_id = " << _id << "\n";
}

