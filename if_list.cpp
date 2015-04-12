#include "if_list.h"

using namespace std;

If_List::If_List(QString equipement)
    : _n(0), _v(0)
{

    _layout = new QVBoxLayout();

    if (equipement == "Switch")
    {
        _n = 24;

        for ( int i = 0 ; i < _n ; i++ )
        {
            IfBouton* bouton = new IfBouton("Fast Ethernet 0/" + QString::number(i+1), i);
            _v.push_back(bouton);
        }
    }

    else if (equipement == "Routeur")
    {
        _n = 4;
        QMessageBox::information(this, "Attention", "Veillez à bien insérer la carte HWIC-2T dans le slot en bas à droite ;)");

        for ( int i = 0 ; i < _n ; i++ )
        {
            IfBouton* b = NULL;

            if ( i < 2 )
                b = new IfBouton("Serial 0/0/" + QString::number(i), i);
            else
                b = new IfBouton("Fast Ethernet 0/" + QString::number(i-2), i);

            _v.push_back(b);
        }
    }

    for ( int i = 0 ; i < _v.size() ; i++ )
    {
        QObject::connect(_v[i], SIGNAL(clicked(int)), this, SLOT(sl_if_param(int)));
        _layout->addWidget(_v[i]);
    }

    this->setLayout(_layout);
}

void If_List::sl_if_param(int id)
{
    if ( _v[id]->text().left(2) == "Se")
    {
        emit si_clicked(_v[id]->text(), id, SE);
    }
    else
        emit si_clicked(_v[id]->text(), id, FA);
}
