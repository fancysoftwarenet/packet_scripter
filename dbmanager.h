#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QMessageBox>
#include <QtSql>

class DBManager
{
public:
    // TODO: clearDB(); update();

    explicit DBManager();
    QString get(QString colonne, QString nom);
    bool put(QString nom, QString ip, QString masque, QString passerelle);
    bool put(int id, QString nom, QString ip, QString masque, QString passerelle);
    bool clearTable(QString table = "interfaces");
    ~DBManager();
private:
    QSqlDatabase _bdd;
};

#endif // DBMANAGER_H
