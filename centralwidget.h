#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QTextEdit>
#include "if_list.h"
#include "ifconfig.h"
#include "scriptwidget.h"
#include "dbmanager.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void sl_change_equipement(QString s);
    void sl_if_conf_change(QString, int, enum if_type);

private:
    QGroupBox* _param;
    QFormLayout* _param_layout;
    QComboBox* _equipement;
    If_List* _if_list;

    QGroupBox* _if;
    QVBoxLayout* _if_layout;
    IfConfig* _if_config;

    QGroupBox* _script;
    QVBoxLayout* _script_layout;
    ScriptWidget* _sw;

    QHBoxLayout* _main_layout;
};

#endif // CENTRALWIDGET_H
