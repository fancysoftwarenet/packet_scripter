#ifndef IFCONFIG_H
#define IFCONFIG_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>

enum if_type
{
    FA, SE
};

class IfConfig : public QWidget
{
    Q_OBJECT
public:
    explicit IfConfig(enum if_type type, QWidget *parent = 0);
    
signals:
    void si_modif();

public slots:
    void sl_modif();
    
private:
    QFormLayout* _layout;
    QLineEdit* _ip;
    QLineEdit* _masque;
    QLineEdit* _passerelle;
    QCheckBox* _debut;
};

#endif // IFCONFIG_H
