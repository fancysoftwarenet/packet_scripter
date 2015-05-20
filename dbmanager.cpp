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

DBManager* DBManager::_instance = 0;
QSqlDatabase* DBManager::_bdd;

DBManager::DBManager()
{
    _bdd = new QSqlDatabase();
    *_bdd = QSqlDatabase::addDatabase("QSQLITE");

    _bdd->setHostName("localhost");
    _bdd->setDatabaseName("packet_scripter");
    _bdd->setUserName("root");
    _bdd->setPassword("");

    if ( ! _bdd->open() )
    {
        QMessageBox::critical(NULL, "Attention", "Il y a eu une erreur à l'ouverture de la base de données.\n\n" + _bdd->lastError().text());
        exit(-1);
    }

    QSqlQuery req(*_bdd);

    if ( !req.exec("CREATE TABLE IF NOT EXISTS interfaces ( id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING NOT NULL, ip VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL, passerelle VARCHAR2)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
    if ( !req.exec("CREATE TABLE IF NOT EXISTS eigrp ( id INTEGER PRIMARY KEY AUTOINCREMENT, as_num INTEGER NOT NULL, ip VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
    if ( !req.exec("CREATE TABLE IF NOT EXISTS static ( id INTEGER PRIMARY KEY AUTOINCREMENT, dst VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL, vers VARCHAR2 NOT NULL)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement\nErreur: <b>" + req.lastError().text() + "</b>.");
}

DBManager* DBManager::getInstance()
{
    if ( !_instance)
    {
        DBManager* tmp = new DBManager();
        _instance = tmp;
    }

    return _instance;
}

QString DBManager::getInterface(QString colonne, QString nom_interface)
{
    QSqlQuery req(*_bdd);

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
    else
    {
        QMessageBox::critical(NULL, "Erreur", "Problème lors de la lecture de la base de données.\n<b>" + req.lastError().text() + ".</b>");
    }

     return NULL;
}

bool DBManager::putInterface(QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(*_bdd);

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
    QSqlQuery req(*_bdd);

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
    QSqlQuery req(*_bdd);

    if ( ! req.exec("UPDATE interfaces SET ip='" + ip + "', masque='" + masque + "', passerelle='" + passerelle + "' WHERE nom='" + nom + "'") )
    {
        QMessageBox::critical(NULL, "Erreur durant l'update", "La requête <b>" + req.lastQuery() + "</b> ne s'est pas exécutée correctement.\nErreur: " + req.lastError().text());
        return false;
    }
    else
        return true;
}

bool DBManager::remove(QString table, int id)
{
    QSqlQuery req(*_bdd);

    if ( !req.exec("DELETE FROM " + table + " WHERE id=" + QString::number(id)))
    {
        qDebug() << "ERROR: DBManager::remove(QString, int) returned false.\n\tREQUEST: " << req.lastQuery() << "\n\tREASON: " << req.lastError().text();
        return false;
    }

    for ( int i = id+1 ; i < getCount(table) ; i++)
    {
        if ( !req.exec("UPDATE " + table + " SET id=" + QString::number(i-1) + " WHERE id=" + QString::number(i)))
        {
            qDebug() << "ERROR: DBManager::remove(QString, int) returned false.\n\tREQUEST: " << req.lastQuery() << "\n\tREASON: " << req.lastError().text();
            return false;
        }
    }

    return true;

}

bool DBManager::clearTable(QString table)
{
    QSqlQuery req(*_bdd);

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
    QSqlQuery req(*_bdd);

    if ( req.exec("SELECT COUNT(id) FROM eigrp") && req.first() )
         return req.value(0).toInt();

    qDebug() << "DBManager::getEigrpCount() returned -1";
    return -1;
}

int DBManager::getStaticCount()
{
    QSqlQuery req(*_bdd);

    if ( req.exec("SELECT COUNT(id) FROM static") && req.first() )
         return req.value(0).toInt();

    qDebug() << "DBManager::getStaticCount() returned -1";
     return -1;
}

int DBManager::getEigrpAS(int id)
{
    QSqlQuery req(*_bdd);

    if ( !(req.exec("SELECT as_num FROM eigrp WHERE id=" + QString::number(id)) && req.first()) )
    {
        qDebug() << "DBManager::getEigrpAs(int line) returned -1";
        return -1;
    }

    return req.value(0).toInt();
}

QString DBManager::getEigrpInfo(QString colonne, int id)
{
    QSqlQuery req(*_bdd);

    if ( !(req.exec("SELECT " + colonne + " FROM eigrp WHERE id=" + QString::number(id)) && req.first()) )
    {
        qDebug() << "DBManager::getEigrpInfo returned NULL\n\tcolonne: " << colonne << "\n\tid: " << id << "\n";

         return NULL;
    }

    return req.value(0).toString();
}

vector<int> DBManager::getAllEigrpAS()
{
    vector<int> v(0);
    QSqlQuery req(*_bdd);

    if ( !(req.exec("SELECT DISTINCT as_num FROM eigrp") && req.first()) )
    {
        qDebug() << "DBManager::getAllEigrpAs() returned an EMPTY ARRAY\n";
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
    QSqlQuery req(*_bdd);

    if ( !(req.exec("SELECT " + colonne + "FROM static") && req.first()) )
    {
        cout << "DBManager::getStatic(QString colonne, int id) ed return NULL with:\n"
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
    QSqlQuery req(*_bdd);

    if ( !req.exec("INSERT INTO static (id, dst, masque, vers) VALUES (" + QString::number(id) + ", '" + dst + "', '" + masque + "', '" + vers + "')" ))
    {
        cout << "DBManager::putStatic(int id, QString dst, QString masque, QString vers) returned false\n";
        return false;
    }
    return true;
}

bool DBManager::updateStatic(int id, QString dst, QString masque, QString vers)
{
    QSqlQuery req(*_bdd);

    if ( !req.exec("UPDATE static SET id=" + QString::number(id) + ", dst='" + dst + "', masque='" + masque + "', vers='" + vers + "' WHERE id=" + QString::number(id)) )
    {
        cout << "DBManager::updateStatic(int id, QString dst, QString masque, QString vers) returnreturned false";
        cout << "\n\tREQUEST: " << req.lastQuery().toStdString() << "\n\tREASON: " << req.lastError().text().toStdString() << endl;
        return false;
    }
    return true;
}

bool DBManager::putEigrp(int id, int as_num, QString ip, QString masque)
{
    QSqlQuery req(*_bdd);
    if ( !req.exec("INSERT INTO eigrp (id, as_num, ip, masque) VALUES (" + QString::number(id) + ", " + QString::number(as_num) + ", '" + ip + "', '" + masque + "')") )
    {
        cout << "ERROR: DBManager::putEigrp(int id, int as_num, QString ip, QString masque) returnreturned false\nREASON: " << req.lastError().text().toStdString();
        return false;
    }
    return true;
}

bool DBManager::updateEigrp(int id_in_db, int new_id, int as_num, QString ip, QString masque)
{
    qDebug() << "Entree dans DBManager::updateEigrp(int id, int as_num, QString ip, QString masque)\n\tid_in_db = " << id_in_db;
    qDebug() << "\tnew_id = " << new_id << "\n\tas_num = " << as_num << "\n\tip = " << ip << "\n\tmasque = " << masque;

    QSqlQuery req(*_bdd);

    if ( !req.exec("UPDATE eigrp SET id=" + QString::number(new_id) + ", as_num=" + QString::number(as_num) + ", ip='" + ip + "', masque='" + masque + "' WHERE id=" + QString::number(id_in_db)) )
    {
        qDebug() << "ERREUR: DBManager::updateEigrp(int id, int as_num, QString ip, QString masque) returnreturned false\n\tREQUEST: " << req.lastQuery() << "\n\tREASON: " << req.lastError().text();
        return false;
    }
    return true;
}

DBManager::~DBManager()
{
}
