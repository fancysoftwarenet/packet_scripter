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

#include <iostream>

void ScriptWidget::sl_genere_script()
{
    //TODO
    QString script = "\nen\n"
            "conf t\n"
            "no ip domain-l\n"
            "enable secret class\n"
            "line con 0\n"
            "password cisco\n"
            "login\n"
            "line vty 0-15\n"
            "password cisco\n"
            "login\n"
            "do wr\n";

    for ( int i = 0 ; i < _dm.getCount("interfaces") ; i++ )
    {
        QString if_name = "";

        if_name = _dm.get("nom", i).left(2).toLower();
        if ( if_name == "fa" )
            if_name += " " + _dm.get("nom", i).right(3);
        else if ( if_name == "se" )
            if_name += " " + _dm.get("nom", i).right(5);

        script += "in " + if_name + "\n";
        script += "ip ad " + _dm.get("ip", i) + " " + _dm.get("masque", i) + "\n";
        script += "no sh\n";
    }

    script += "end\n\n";



    _texte->setText(script);
}

void ScriptWidget::sl_selectionner()
{
    _texte->selectAll();
    _texte->setFocus();
}
