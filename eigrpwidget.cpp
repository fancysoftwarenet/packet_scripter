#include "eigrpwidget.h"

EigrpWidget::EigrpWidget(QWidget *parent) :
    QWidget(parent), _id(DBManager::getInstance()->getEigrpCount())
{
    _dm = DBManager::getInstance();

    _layout = new QHBoxLayout();

    _as_label = new QLabel("AS: ");
    _as = new QSpinBox();

    _ip_label = new QLabel("Adresse de réseau: ");
    _ip = new QLineEdit();
    _ip->setInputMask("000.000.000.000");

    _masque_label = new QLabel("Masque inversé: ");
    _masque = new QLineEdit();
    _masque->setInputMask("000.000.000.000");

    _supprimer = new QPushButton();
    _supprimer->setIcon(QIcon("trash.png"));

    _layout->addWidget(_as_label);
    _layout->addWidget(_as);
    _layout->addWidget(_ip_label);
    _layout->addWidget(_ip);
    _layout->addWidget(_masque_label);
    _layout->addWidget(_masque);
    _layout->addWidget(_supprimer);

    this->setLayout(_layout);

    QObject::connect(_as, SIGNAL(valueChanged(QString)), this, SLOT(sl_sauvegarder(QString)));
    QObject::connect(_ip, SIGNAL(textChanged(QString)), this, SLOT(sl_sauvegarder(QString)));
    QObject::connect(_masque, SIGNAL(textChanged(QString)), this, SLOT(sl_sauvegarder(QString)));

    QObject::connect(_supprimer, SIGNAL(clicked()), this, SLOT(sl_delete()));

    sl_sauvegarder(NULL);

    //Debug
    l = new QLabel(QString::number(_id));
    _layout->addWidget(l);
}

void EigrpWidget::sl_delete()
{
    emit si_deleted();
    qDebug() << "EigrpWidget[" << _id << "] deleted";

    _dm->remove("eigrp", _id);
    delete this;

}

void EigrpWidget::sl_sauvegarder(QString s)
{
    if ( _dm->getEigrpInfo("ip", _id) == NULL )
        _dm->putEigrp(_id, _as->value(), _ip->text(), _masque->text());
    else
        _dm->updateEigrp(_id, _id, _as->value(), _ip->text(), _masque->text());

    emit si_edited();
}

void EigrpWidget::setId(int id)
{
    _id = id;
    l->setText(QString::number(_id));
}

void EigrpWidget::decrementId()
{
    qDebug() << "Entree dans EigrpWidget[" << _id << "]::decrementId()";
    this->setId(_id - 1);
    _dm->updateEigrp((_id+1), _id, _as->value(), _ip->text(), _masque->text());
}

