#ifndef FENROUTAGE_H
#define FENROUTAGE_H

#include <QWidget>
#include <vector>

#include "routewidget.h"

class FenRoutage : public QWidget
{
    Q_OBJECT
public:
    explicit FenRoutage(QWidget *parent = 0);
    int getNbRoutes();

signals:
    
public slots:
    void sl_ajouter();

private:
    QVBoxLayout* _layout;
    std::vector<RouteWidget*> _routes;
    QPushButton* _ajouter;
};

#endif // FENROUTAGE_H
