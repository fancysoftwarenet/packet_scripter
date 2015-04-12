#ifndef IFCONFIG_H
#define IFCONFIG_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>
#include <QPushButton>
#include "enums.h"

class IfConfig : public QWidget
{
    Q_OBJECT
public:
    explicit IfConfig(enum if_type type, QWidget *parent = 0);
    
signals:
    void si_modif();

public slots:
    void sl_modif();
    
private:
    QFormLayout* _layout;

    QLineEdit* _ip;
    QLineEdit* _masque;

    //Si FA
    QLineEdit* _passerelle;
    QCheckBox* _debut;

    //Si SE
    //TODO : Bouton pour fen de conf du Routage ;)
    QPushButton* _routage;
    QPushButton* _dhcp;
    QPushButton* _nat;
};

#endif // IFCONFIG_H
