#ifndef EIGRPWIDGET_H
#define EIGRPWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include "dbmanager.h"

class EigrpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EigrpWidget(int id, QWidget *parent = 0);
    
signals:
    
public slots:
    void sl_delete();

private:
    int _id;
    DBManager _dm;
    QHBoxLayout* _layout;

    QLabel* _as_label;
    QSpinBox* _as;
    QLabel* _ip_label;
    QLineEdit* _ip;
    QLabel* _masque_label;
    QLineEdit* _masque;

    QPushButton* _supprimer;
    // TODO: Gérer la sauvegarde et le delete dans la bdd (mettre en place des id ?)
};

#endif // EIGRPWIDGET_H
