#include "dbmanager.h"

/* Structure de la table interfaces
  PK AI
   id       nom     ip      masque      passerelle
   int     String  String   String        String

TABLE eigrp
    id      as_num      ip      masque
    INT     INT   String    String

TABLE static
    id      dst     masque      vers
    INT     String  String      String
*/

#include <iostream>

using namespace std;

DBManager::DBManager()
{
    _bdd = QSqlDatabase::addDatabase("QSQLITE");

    _bdd.setHostName("localhost");
    _bdd.setDatabaseName("packet_scripter");
    _bdd.setUserName("root");
    _bdd.setPassword("");

    if ( ! _bdd.open() )
    {
        QMessageBox::critical(NULL, "Attention", "Il y a eu une erreur à l'ouverture de la base de données.\n\n" + _bdd.lastError().text());
        exit(-1);
    }

    QSqlQuery req(_bdd);

    if ( !req.exec("CREATE TABLE IF NOT EXISTS interfaces ( id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING NOT NULL, ip VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL, passerelle VARCHAR2)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
    if ( !req.exec("CREATE TABLE IF NOT EXISTS eigrp ( id INTEGER PRIMARY KEY AUTOINCREMENT, as_num INTEGER NOT NULL, ip VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
    if ( !req.exec("CREATE TABLE IF NOT EXISTS static ( id INTEGER PRIMARY KEY AUTOINCREMENT, dst VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL, vers VARCHAR2 NOT NULL)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
}

QString DBManager::getInterface(QString colonne, QString nom_interface)
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT " + colonne + " FROM interfaces WHERE nom='" + nom_interface + "'") && req.first() )
    {
        return req.value(0).toString();
    }

    return NULL;
}

QString DBManager::getInterface(QString colonne, int line)
{
    QSqlQuery req;

    if ( req.exec("SELECT " + colonne + " FROM interfaces") && req.first() )
    {
        for ( int i = 0 ; i < line ; i++ )
            req.next();

        return req.value(0).toString();
    }

    return NULL;
}

bool DBManager::putInterface(QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    if ( !req.exec("INSERT INTO interfaces (nom, ip, masque, passerelle) VALUES ('" + nom + "', '" + ip + "', '" + masque + "', '" + passerelle + "') "))
    {
        QMessageBox::critical(NULL, "Echec de l'insertion", "La requete <b>" + req.lastQuery() + "</b> n'a pu être effectuée.\nErreur: " + req.lastError().text());
        return false;
    }
    else
        return true;
}

bool DBManager::putInterface(int id, QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    if ( !req.exec("INSERT INTO interfaces (id, nom, ip, masque, passerelle) VALUES (" + QString::number(id) + ", '" + nom + "', '" + ip + "', '" + masque + "', '" + passerelle + "') "))
    {
        QMessageBox::critical(NULL, "Echec de l'insertion", "La requete <b>" + req.lastQuery() + "</b> n'a pu être effectuée.\nErreur: " + req.lastError().text());
        return false;
    }
    else
        return true;
}

bool DBManager::update(QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    if ( ! req.exec("UPDATE interfaces SET ip='" + ip + "', masque='" + masque + "', passerelle='" + passerelle + "' WHERE nom='" + nom + "'") )
    {
        QMessageBox::critical(NULL, "Erreur durant l'update", "La requête <b>" + req.lastQuery() + "</b> ne s'est pas exécutée correctement.\nErreur: " + req.lastError().text());
        return false;
    }
    else
        return true;
}

bool DBManager::clearTable(QString table)
{
    QSqlQuery req(_bdd);

    return req.exec("DELETE FROM " + table);
}

int DBManager::getCount(QString table)
{
    QSqlQuery req;
    if ( req.exec("SELECT COUNT(id) FROM " + table) && req.first() )
        return req.value(0).toInt();
    else
        return -1;
}

int DBManager::getEigrpCount()
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT COUNT(id) FROM eigrp") && req.first() )
        return req.value(0).toInt();

    std::cout << "DBManager::getEigrpCount() returned -1" << std::endl;
    return -1;
}

int DBManager::getStaticCount()
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT COUNT(id) FROM static") && req.first() )
        return req.value(0).toInt();

    cout << "DBManager::getStaticCount() returned -1" << endl;
    return -1;
}

int DBManager::getEigrpAS(int line)
{
    QSqlQuery req(_bdd);

    if ( !(req.exec("SELECT as_num FROM eigrp") && req.first()) )
    {
        cout << "DBManager::getEigrpAs(int line) returned -1";
        return -1;
    }

    for ( int i = 0 ; i < line ; i++ )
        req.next();

    return req.value(0).toInt();
}

QString DBManager::getEigrpInfo(QString colonne, int AS, int line)
{
    QSqlQuery req(_bdd);

    if ( !(req.exec("SELECT " + colonne + " FROM eigrp WHERE as_num=" + QString::number(AS)) && req.first()) )
    {
        cout << "DBManager::EigrpInfo returned NULL\n"
                "\tcolonne: " << colonne.toStdString() << "\n"
                "\tAS: " << AS << "\n"
                "\tline: " << line << "\n";

        return NULL;
    }

    for ( int i = 0 ; i < line ; i++ )
        req.next();
    return req.value(0).toString();
}

vector<int> DBManager::getAllEigrpAS()
{
    vector<int> v(0);
    QSqlQuery req(_bdd);

    if ( !(req.exec("SELECT DISTINCT as_num FROM eigrp") && req.first()) )
    {
        cout << "DBManager::getAllEigrpAs() returned an EMPTY ARRAY\n";
        return v;
    }

    for ( int i = 0 ; i < req.size() ; i++)
    {
        v.push_back(req.value(0).toInt());
        req.next();
    }

    return v;
}

QString DBManager::getStatic(QString colonne, int line)
{
    QSqlQuery req(_bdd);

    if ( !(req.exec("SELECT " + colonne + "FROM static") && req.first()) )
    {
        cout << "DBManager::getStatic(QString colonne, int id) returned NULL with:\n"
                "\tcolonne = " << colonne.toStdString() << "\n"
                "\tline = " << line << "\n";
        return NULL;
    }
    for ( int i = 0 ; i < line ; i++ )
        req.next();

    return req.value(0).toString();
}

bool DBManager::putStatic(int id, QString dst, QString masque, QString vers)
{
    QSqlQuery req(_bdd);

    if ( !req.exec("INSERT INTO static (id, dst, masque, vers) VALUES " + QString::number(id) + ", '" + dst + "', '" + masque + "', '" + vers + "')" ))
    {
        cout << "DBManager::putStatic(int id, QString dst, QString masque, QString vers) returned FALSE\n";
        return false;
    }
    return true;
}

bool DBManager::updateStatic(int id, QString dst, QString masque, QString vers)
{
    QSqlQuery req(_bdd);

    if ( !req.exec("UPDATE static SET dst='" + dst + "', masque='" + masque + "', vers='" + vers + "' WHERE id=" + QString::number(id)) )
    {
        cout << "DBManager::updateStatic(int id, QString dst, QString masque, QString vers) returned FALSE\n";
        return false;
    }
    return true;
}

bool DBManager::putEigrp(int id, int as_num, QString ip, QString masque)
{
    QSqlQuery req(_bdd);
    if ( !req.exec("INSERT INTO eigrp (id, as_num, ip, masque) VALUES (" + QString::number(id) + ", " + QString::number(as_num) + "', '" + ip + "', '" + masque) )
    {
        cout << "ERROR: DBManager::putEigrp(int id, int as_num, QString ip, QString masque) returned false\n";
        return false;
    }
    return true;
}

bool DBManager::updateEigrp(int id, int as_num, QString ip, QString masque)
{
    QSqlQuery req(_bdd);

    if ( !req.exec("UPDATE eigrp SET as_num=" + QString::number(as_num) + ", ip='" + ip + "', masque='" + masque + "' WHERE id=" + QString::number(id)) )
    {
        cout << "ERREUR: DBManager::updateEigrp(int id, int as_num, QString ip, QString masque) returned false\n";
        return false;
    }
    return true;
}

DBManager::~DBManager()
{
    _bdd.close();
}
