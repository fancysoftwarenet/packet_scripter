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
    explicit EigrpWidget(QWidget *parent = 0);
    void setId(int id);
    void decrementId();

signals:
    void si_edited();
    void si_deleted();

public slots:
    void sl_delete();
    void sl_sauvegarder(QString s);

private:
    DBManager* _dm;
    int _id;
    QHBoxLayout* _layout;

    QLabel* _as_label;
    QSpinBox* _as;
    QLabel* _ip_label;
    QLineEdit* _ip;
    QLabel* _masque_label;
    QLineEdit* _masque;

    QPushButton* _supprimer;

    //Debug
    QLabel* l;
};

#endif // EIGRPWIDGET_H
