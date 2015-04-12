#include "ifconfig.h"

IfConfig::IfConfig(enum if_type type, QWidget *parent) :
    QWidget(parent)
{
    _layout = new QFormLayout();

    _ip = new QLineEdit();
    _ip->setInputMask("000.000.000.000;");
    _ip->setPlaceholderText("192.168.0.50");
    _layout->addRow("Adresse ip: ", _ip);
    connect(_ip, SIGNAL(editingFinished()), this, SLOT(sl_modif()));

    _masque = new QLineEdit();
    _masque->setInputMask("000.000.000.000;");
    _masque->setPlaceholderText("255.255.255.0");
    _layout->addRow("Masque: ", _masque);
    connect(_masque, SIGNAL(editingFinished()), this, SLOT(sl_modif()));

    if ( type == FA )
    {
        _passerelle = new QLineEdit();
        _passerelle->setInputMask("000.000.000.000;");
        _passerelle->setPlaceholderText("192.168.0.254");
        _layout->addRow("Passerelle par défaut: ", _passerelle);
        connect(_passerelle, SIGNAL(editingFinished()), this, SLOT(sl_modif()));

        _debut = new QCheckBox();
        connect(_debut, SIGNAL(clicked()), this, SLOT(sl_modif()));

        _layout->addRow("Passerelle en début de réseau", _debut);
    }
    else if ( type == SE )
    {
        _routage = new QPushButton("Routage...");
        _layout->addRow(_routage);

        _dhcp = new QPushButton("DHCP...");
        _layout->addRow(_dhcp);

        _nat = new QPushButton("NAT...");
        _layout->addRow(_nat);

        //TODO: Connecter le click à un show de la fen de conf. En EIGRP, penser à demander le numéro d'AS (spinbox would be nice)
    }

    this->setLayout(_layout);
}

void IfConfig::sl_modif()
{
    emit si_modif();
}
