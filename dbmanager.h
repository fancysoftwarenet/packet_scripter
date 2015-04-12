#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QMessageBox>
#include <QtSql>

class DBManager
{
public:
    DBManager(QString hote, QString db, QString user, QString pwd);
    QString get(QString colonne, int id);
    bool put(int id, QString nom, QString ip, QString masque, QString passerelle);

private:
    QSqlDatabase _bdd;
    QString _hote, _db, _user, _pwd, _equipement;
};

#endif // DBMANAGER_H
