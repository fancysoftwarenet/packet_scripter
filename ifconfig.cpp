#include "ifconfig.h"

IfConfig::IfConfig(QString nom, enum if_type type, QWidget *parent) :
    QWidget(parent), _dm()
{
    _layout = new QFormLayout();
    _nom = new QLabel("<b><span style=\"color: green\">" + nom + "</span></b>");
    _nom->setAlignment(Qt::AlignCenter);

    _layout->addRow(_nom);

    _espace = new QSpacerItem(1, 25);
    _layout->addItem(_espace);

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
        _layout->addRow("Passerelle par d�faut: ", _passerelle);
        connect(_passerelle, SIGNAL(editingFinished()), this, SLOT(sl_modif()));

        _debut = new QCheckBox();
        connect(_debut, SIGNAL(clicked()), this, SLOT(sl_modif()));

        _layout->addRow("Passerelle en d�but de r�seau", _debut);
    }
    else if ( type == SE )
    {
        _routage = new QPushButton("Routage...");
        _layout->addRow(_routage);

        _dhcp = new QPushButton("DHCP...");
        _layout->addRow(_dhcp);

        _nat = new QPushButton("NAT...");
        _layout->addRow(_nat);

        //TODO: Connecter le click � un show de la fen de conf. En EIGRP, penser � demander le num�ro d'AS (spinbox would be nice)
    }

    _on = new QCheckBox();
    QObject::connect(_on, SIGNAL(clicked()), this, SLOT(sl_modif()));
    _layout->addRow("Allumer l'interface ", _on);

    _sauvegarder = new QPushButton("Enregistrer");
    QObject::connect(_sauvegarder, SIGNAL(clicked()), this, SLOT(sl_save_conf()));
    _layout->addRow(_sauvegarder);

    this->setLayout(_layout);
}

void IfConfig::sl_modif()
{
    emit si_modif();
}

void IfConfig::sl_save_conf()
{
    if ( _dm.get("nom", _nom->text()) != NULL )
    {

    }

    _dm.put(_nom->text(), _ip->text(), _masque->text(), _passerelle->text());
}
