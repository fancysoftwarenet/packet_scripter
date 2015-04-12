#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent)
{
    _main_layout = new QHBoxLayout();

/** La GroupBox paramètres **/
    _param = new QGroupBox();
    _param->setTitle("Paramètres");

    _param_layout = new QFormLayout();

    _equipement = new QComboBox();
    _equipement->addItem("Switch");
    _equipement->addItem("Routeur");

    _param_layout->addWidget(_equipement);

    _if_list = new If_List(_equipement->currentText());
    _param_layout->addWidget(_if_list);

    _param->setLayout(_param_layout);

    QObject::connect(_equipement, SIGNAL(currentIndexChanged(QString)), this, SLOT(sl_change_equipement(QString)));

/** La GroupBox dans laquelle on configure l'interface **/
    _if = new QGroupBox();
    _if->setTitle("Interface");

    _if_layout = new QVBoxLayout();
    _if_config = new IfConfig(SE);

    _if_layout->addWidget(_if_config);
    _if->setLayout(_if_layout);


/** La GroupBox dans laquelle on affiche le script **/
    _script = new QGroupBox();
    _script->setTitle("Script de configuration");

    _script_layout = new QVBoxLayout();

    _texte = new QTextEdit();
    _script->setLayout(_script_layout);

    _script_layout->addWidget(_texte);
    _script->setLayout(_script_layout);




/** Le layout principal dans lequel on met nos trois GroupBox **/
    _main_layout->addWidget(_param);
    _main_layout->addWidget(_if);
    _main_layout->addWidget(_script);

    this->setLayout(_main_layout);
}

void CentralWidget::sl_change_equipement(QString s)
{

    _param_layout->removeWidget(_if_list);
    delete _if_list;

    _if_list = new If_List(s);
    _param_layout->addWidget(_if_list);
}
