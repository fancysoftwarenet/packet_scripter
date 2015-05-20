#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include "eigrpwidget.h"
#include "staticwidget.h"

enum ROUTE_TYPE
{
    EIGRP, STATIC, NONE
};

class RouteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RouteWidget(int id, QWidget *parent = 0);
    void decrementId(ROUTE_TYPE rt);
    void setId(int id);

signals:
    void si_widget_deleted(int, ROUTE_TYPE);

public slots:
    void sl_prot_change(int a);
    void sl_widget_deleted();

private:
    ROUTE_TYPE _route_type;
    int _id;

    QHBoxLayout* _layout;

    QComboBox* _protocole;
    EigrpWidget* _eigrp;
    StaticWidget* _static;
};

#endif // ROUTEWIDGET_H
