#include "staticwidget.h"

StaticWidget::StaticWidget(QWidget *parent) :
    QWidget(parent)
{
    _layout = new QHBoxLayout();

    _dst_ip_label = new QLabel("IP du réseau de destination: ");
    _dst_ip = new QLineEdit();
    _dst_ip->setInputMask("000.000.000.000");

    _dst_masque_label = new QLabel("Masque: ");
    _dst_masque = new QLineEdit();
    _dst_masque->setInputMask("000.000.000.000");

    _to_label = new QLabel("Router vers ");
    _to = new QLineEdit();
    _to->setInputMask("000.000.000.000");

    _layout->addWidget(_dst_ip_label);
    _layout->addWidget(_dst_ip);
    _layout->addWidget(_dst_masque_label);
    _layout->addWidget(_dst_masque);
    _layout->addWidget(_to_label);
    _layout->addWidget(_to);

    this->setLayout(_layout);
}
