#ifndef STATICWIDGET_H
#define STATICWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class StaticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StaticWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
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
