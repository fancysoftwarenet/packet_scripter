#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent)
{
    DBManager dm;
    dm.clearTable("interfaces");

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
    QObject::connect(_if_list, SIGNAL(si_clicked(QString, int, enum if_type)), this, SLOT(sl_if_conf_change(QString, int, enum if_type)));


/** La GroupBox dans laquelle on configure l'interface **/
    _if = new QGroupBox();
    _if->setTitle("Interface");

    _if_layout = new QVBoxLayout();
    _if_config = NULL;

    _if->setLayout(_if_layout);


/** La GroupBox dans laquelle on affiche le script **/
    _script = new QGroupBox();
    _script->setTitle("Script de configuration");

    _script_layout = new QVBoxLayout();
    _sw = new ScriptWidget();

    _script_layout->addWidget(_sw);

    _script->setLayout(_script_layout);

/** Le layout principal dans lequel on met nos trois GroupBox **/
    _main_layout->addWidget(_param);
    _main_layout->addWidget(_if);
    _main_layout->addWidget(_script);

    this->setLayout(_main_layout);
}

void CentralWidget::sl_change_equipement(QString s)
{
    DBManager dm;
    dm.clearTable("interfaces");

    _param_layout->removeWidget(_if_list);
    delete _if_list;
    if ( _if_config != NULL )
    {
        _if_layout->removeWidget(_if_config);
        delete _if_config;
    }

    _if_list = new If_List(s);
    QObject::connect(_if_list, SIGNAL(si_clicked(QString, int, enum if_type)), this, SLOT(sl_if_conf_change(QString, int, enum if_type)));
    _param_layout->addWidget(_if_list);
}

void CentralWidget::sl_if_conf_change(QString nom, int id, enum if_type type)
{
    if (_if_config != NULL)
    {
        _if_layout->removeWidget(_if_config);
    }

    _if_config = new IfConfig(nom, id, type);
    _if_layout->addWidget(_if_config);

    QObject::connect(_if_config, SIGNAL(si_modif()), _sw, SLOT(sl_genere_script()));
}
