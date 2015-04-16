#ifndef SCRIPTWIDGET_H
#define SCRIPTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include "dbmanager.h"

class ScriptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScriptWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void sl_selectionner();
    void sl_genere_script();

private:
    DBManager _dm;

    QVBoxLayout* _layout;
    QTextEdit* _texte;
    QPushButton* _selectionner;
};

#endif // SCRIPTWIDGET_H
