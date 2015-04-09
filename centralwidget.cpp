#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent)
{
    _main_layout = new QHBoxLayout();

    _param = new QGroupBox();
    _param->setTitle("Paramètres");

    _param_layout = new QFormLayout();

    _equipement = new QComboBox();
    _equipement->addItem("Switch");
    _equipement->addItem("Routeur");

    _param_layout->addWidget(_equipement);

    _param->setLayout(_param_layout);

    _script = new QGroupBox();
    _script->setTitle("Script de configuration");

    _script_layout = new QVBoxLayout();

    _texte = new QTextEdit();
    _script->setLayout(_script_layout);

    _script_layout->addWidget(_texte);
    _script->setLayout(_script_layout);

    _main_layout->addWidget(_param);
    _main_layout->addWidget(_script);

    this->setLayout(_main_layout);
}
