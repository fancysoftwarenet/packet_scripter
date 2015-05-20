#ifndef STATICWIDGET_H
#define STATICWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include "dbmanager.h"

class StaticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StaticWidget(QWidget *parent = 0);
    void setId(int id);
    void decrementId();

signals:
    void si_edited();
    void si_deleted();

public slots:
    void sl_delete();
    void sl_sauvegarder(QString s);

private:
    DBManager _dm;
    int _id;

    QHBoxLayout* _layout;
    QLabel* _dst_ip_label;
    QLineEdit* _dst_ip;
    QLabel* _dst_masque_label;
    QLineEdit* _dst_masque;
    QLabel* _to_label;
    QLineEdit* _to;

    QPushButton* _supprimer;
    // TODO: Gérer la sauvegarde et le delete dans la bdd (mettre en place des id ?)
};

#endif // STATICWIDGET_H
