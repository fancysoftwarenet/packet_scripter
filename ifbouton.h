#ifndef IFBOUTON_H
#define IFBOUTON_H

#include <QPushButton>
#include <QString>

class IfBouton : public QPushButton
{
    Q_OBJECT
public:
    explicit IfBouton(QString texte, int id, QWidget *parent = 0);
    
signals:
    void clicked(int);

public slots:
    void sl_clicked();

private:
    int _id;
};

#endif // IFBOUTON_H
