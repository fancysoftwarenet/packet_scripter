#ifndef EIGRPWIDGET_H
#define EIGRPWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

class EigrpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EigrpWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void sl_delete();

private:
    QHBoxLayout* _layout;

    QLabel* _as_label;
    QSpinBox* _as;
    QLabel* _ip_label;
    QLineEdit* _ip;
    QLabel* _masque_label;
    QLineEdit* _masque;

    QPushButton* _supprimer;
};

#endif // EIGRPWIDGET_H
