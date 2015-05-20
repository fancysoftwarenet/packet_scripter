#ifndef IFCONFIG_H
#define IFCONFIG_H

#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QCheckBox>
#include <QFormLayout>
#include <QPushButton>
#include "enums.h"
#include "dbmanager.h"
#include "fenroutage.h"

class IfConfig : public QWidget
{
    Q_OBJECT

public:
    explicit IfConfig(QString nom, int id, if_type type, QWidget *parent = 0);
    QString getNom();
signals:
    void si_modif();

public slots:
    void sl_modif();
    void sl_save_conf();
    void sl_routage();

private:
    int _id;
    if_type _type;

    QFormLayout* _layout;

    QLabel* _nom;
    QSpacerItem* _espace;
    QLineEdit* _ip;
    QLineEdit* _masque;
    QCheckBox* _on;

    //Si FA
    QLineEdit* _passerelle;
    QCheckBox* _debut;

    //Si SE
    QPushButton* _routage;
    QPushButton* _dhcp;
    QPushButton* _nat;
    FenRoutage* _fen_routage;

    QPushButton* _sauvegarder;
};

#endif // IFCONFIG_H
