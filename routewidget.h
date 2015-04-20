#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include "eigrpwidget.h"
#include "staticwidget.h"

class RouteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RouteWidget(QWidget *parent = 0);

signals:
    
public slots:
    void sl_prot_change(int a);

private:
    QHBoxLayout* _layout;

    QComboBox* _protocole;
    EigrpWidget* _eigrp;
    StaticWidget* _static;
};

#endif // ROUTEWIDGET_H
