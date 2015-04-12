#include "ifconfig.h"

IfConfig::IfConfig(enum if_type type, QWidget *parent) :
    QWidget(parent)
{
    _layout = new QFormLayout();

    _ip = new QLineEdit();
    _ip->setPlaceholderText("192.168.0.x");
    _ip->setInputMask("000.000.000.000;");

    _masque = new QLineEdit();
    _masque->setPlaceholderText("255.255.255.0");
    _masque->setInputMask("000.000.000.000;");

    _passerelle = new QLineEdit();
    _passerelle->setPlaceholderText("192.168.0.254");
    _passerelle->setInputMask("000.000.000.000;");

    _debut = new QCheckBox();

    _layout->addRow("Adresse ip: ", _ip);
    _layout->addRow("Masque: ", _masque);
    _layout->addRow("Passerelle par défaut: ", _passerelle);
    _layout->addRow("Passerelle en début de réseau", _debut);

    this->setLayout(_layout);
}

void IfConfig::sl_modif()
{
    emit si_modif();
}
