#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QTextEdit>
#include "if_list.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void sl_change_equipement();

private:
    QGroupBox* _param;
    QFormLayout* _param_layout;
    QComboBox* _equipement;

    QGroupBox* _script;
    QVBoxLayout* _script_layout;
    QTextEdit* _texte;

    QGroupBox* _if;
    QVBoxLayout* _if_layout;
    If_List* _if_list;

    QHBoxLayout* _main_layout;
};

#endif // CENTRALWIDGET_H