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
            QObject::connect(bouton, SIGNAL(clicked(int)), this, SLOT(sl_if_param(int)));
            _v.push_back(bouton);
        }
    }

    else if (equipement == "Routeur")
    {
        _n = 4;
        QMessageBox::information(this, "Attention", "Veillez à bien insérer la carte HWIC-2T dans le slot en bas à droite ;)");

        for ( int i = 0 ; i < 2 ; i++ )
        {
            IfBouton* b = new IfBouton("Serial 0/0/" + QString::number(i), i);
            QObject::connect(b, SIGNAL(clicked(int)), this, SLOT(sl_if_param(int)));
        }

        for ( int i = 0 ; i < 2 ; i++ )
        {
            IfBouton* b = new IfBouton("Fast Ethernet 0/" + QString::number(i), i+2);
            QObject::connect(b, SIGNAL(clicked(int)), this, SLOT(sl_if_param(int)));
        }
    }

    for ( int i = 0 ; i < _v.size() ; i++ )
        _layout->addWidget(_v[i]);

    this->setLayout(_layout);
}

void If_List::sl_if_param(int id)
{
    std::cout << "id du bouton cliqué: " << id << std::endl;
}
