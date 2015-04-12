#ifndef IF_LIST_H
#define IF_LIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <QMessageBox>
#include <iostream>
#include "ifbouton.h"

class If_List : public QWidget
{
    Q_OBJECT

public:
    If_List(QString equipement);

signals:
    void si_clicked(int, enum if_type);

public slots:
    void sl_if_param(int id);

private:
    int _n;

    QVBoxLayout* _layout;
    std::vector<IfBouton*> _v;
};

#endif // IF_LIST_H
