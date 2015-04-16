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
    bool put(int id, QString nom, QString ip, QString masque, QString passerelle);
    bool put(QString nom, QString ip, QString masque, QString passerelle);
    bool update(QString nom, QString ip, QString masque, QString passerelle);
    bool clearTable(QString table = "interfaces");
    QString get(QString colonne, QString valeur);
    ~DBManager();

private:
    QSqlDatabase _bdd;
};

#endif // DBMANAGER_H
