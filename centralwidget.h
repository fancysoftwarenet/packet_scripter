#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QTextEdit>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QGroupBox* _param;
    QFormLayout* _param_layout;

    QComboBox* _equipement;

    QGroupBox* _script;
    QVBoxLayout* _script_layout;

    QTextEdit* _texte;

    QHBoxLayout* _main_layout;
};

#endif // CENTRALWIDGET_H
