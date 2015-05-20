#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QMessageBox>
#include <QtSql>

class DBManager
{
public:

    static DBManager *getInstance();

    bool clearTable(QString table = "interfaces");
    int getCount(QString table = "interfaces");
    QString getInterface(QString colonne, QString nom_interface);
    QString getInterface(QString colonne, int line);
    bool putInterface(QString nom, QString ip, QString masque, QString passerelle);
    bool putInterface(int id, QString nom, QString ip, QString masque, QString passerelle);
    bool update(QString nom, QString ip, QString masque, QString passerelle);
    bool remove(QString table, int id);

    int getStaticCount();
    QString getStatic(QString colonne, int line);
    bool putStatic(int id, QString dst, QString masque, QString vers);
    bool updateStatic(int id, QString dst, QString masque, QString vers);

    int getEigrpCount();
    QString getEigrpInfo(QString colonne, int id);
    int getEigrpAS(int id);
    bool putEigrp(int id, int as_num, QString ip, QString masque);
    bool updateEigrp(int id_in_db, int new_id, int as_num, QString ip, QString masque);
    std::vector<int> getAllEigrpAS();


private:
    DBManager();

    static DBManager* _instance;
    static QSqlDatabase* _bdd;

    ~DBManager();
};

#endif // DBMANAGER_H
