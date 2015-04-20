#include "ifconfig.h"

IfConfig::IfConfig(QString nom, int id, enum if_type type, QWidget *parent) :
    QWidget(parent), _dm(), _type(type), _id(id)
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
        QObject::connect(_routage, SIGNAL(clicked()), this, SLOT(sl_routage()));

        _dhcp = new QPushButton("DHCP...");
        _layout->addRow(_dhcp);

        _nat = new QPushButton("NAT...");
        _layout->addRow(_nat);

        //TODO: Connecter le click à un show de la fen de conf. FenDhcp & FenNat restants
    }

    _on = new QCheckBox();
    QObject::connect(_on, SIGNAL(clicked()), this, SLOT(sl_modif()));
    _layout->addRow("Allumer l'interface ", _on);

    _sauvegarder = new QPushButton("Enregistrer");
    QObject::connect(_sauvegarder, SIGNAL(clicked()), this, SLOT(sl_save_conf()));
    QObject::connect(_sauvegarder, SIGNAL(clicked()), this, SLOT(sl_modif()));
    _layout->addRow(_sauvegarder);

    if ( _dm.getInterface("nom", getNom()) != NULL )
    {
        _ip->setText( _dm.getInterface("ip", getNom()));
        _masque->setText( _dm.getInterface("masque", getNom()));

        if ( type == FA )
            _passerelle->setText(_dm.getInterface("passerelle", getNom()));
    }
    this->setLayout(_layout);
}

void IfConfig::sl_modif()
{
    emit si_modif();
}

#include <iostream>

void IfConfig::sl_save_conf()
{
    if ( _dm.getInterface("nom", getNom()) != NULL )
    {
        if ( _type == FA )
            _dm.update(getNom(), _ip->text(), _masque->text(), _passerelle->text());
        else
            _dm.update(getNom(), _ip->text(), _masque->text(), "...");
    }
    else
    {
        if ( _type == FA )
            _dm.putInterface(_id, getNom(), _ip->text(), _masque->text(), _passerelle->text());
        else
            _dm.putInterface(_id, getNom(), _ip->text(), _masque->text(), "...");
    }

    emit si_modif();
}

void IfConfig::sl_routage()
{
    _fen_routage = new FenRoutage();
    _fen_routage->show();
}

QString IfConfig::getNom()
{
    return _nom->text().right(_nom->text().length() - 30).left(_nom->text().length() - 41);
}
