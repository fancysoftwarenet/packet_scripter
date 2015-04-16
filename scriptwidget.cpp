#include "scriptwidget.h"

ScriptWidget::ScriptWidget(QWidget *parent) :
    QWidget(parent), _dm()
{
    _layout = new QVBoxLayout();

    _texte = new QTextEdit();
    _texte->setReadOnly(true);

    _selectionner = new QPushButton("Sélectionner tout");
    QObject::connect(_selectionner, SIGNAL(clicked()), this, SLOT(sl_selectionner()));

    _layout->addWidget(_texte);
    _layout->addWidget(_selectionner);

    this->setLayout(_layout);
    this->sl_genere_script();
}

void ScriptWidget::sl_genere_script()
{
    //TODO
    QString script = "\nen\n"
            "conf t\n"
            "no ip domain-l\n"
            "enable secret class\n"
            "line con0\n"
            "password cisco\n"
            "login\n"
            "line vty 0-15\n"
            "password cisco\n"
            "login\n"
            "do wr\n"
            "end\n"
            "\n";



    _texte->setText(script);
}

void ScriptWidget::sl_selectionner()
{
    _texte->selectAll();
    _texte->setFocus();
}
