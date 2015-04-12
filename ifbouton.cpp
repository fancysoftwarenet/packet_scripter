#include "ifbouton.h"

IfBouton::IfBouton(QString texte, int id, QWidget *parent) :
    QPushButton(parent), _id(id)
{
    this->setText(texte);
    connect(this, SIGNAL(clicked()), this, SLOT(sl_clicked()));
}

void IfBouton::sl_clicked()
{
    emit clicked(_id);
}
