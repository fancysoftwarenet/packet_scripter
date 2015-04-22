#include "eigrpwidget.h"

EigrpWidget::EigrpWidget(int id, QWidget *parent) :
    QWidget(parent), _dm(), _id(id)
{
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

    QObject::connect(_supprimer, SIGNAL(clicked()), this, SLOT(sl_delete()));
}

void EigrpWidget::sl_delete()
{
    delete this;
}
