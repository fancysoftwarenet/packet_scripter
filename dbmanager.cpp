#include "dbmanager.h"

/* Structure de la bdd
  PK AI
   id       nom     ip      masque      passerelle
   int     String  String   String        String
*/

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
    }

    QSqlQuery req(_bdd);

    if ( !req.exec("CREATE TABLE IF NOT EXISTS interfaces ( id INTEGER PRIMARY KEY AUTOINCREMENT, nom STRING NOT NULL, ip VARCHAR2 NOT NULL, masque VARCHAR2 NOT NULL, passerelle VARCHAR2)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de créer la table pour la base de données, le programme peut ne pas fonctionner correctement");
}

QString DBManager::get(QString colonne, QString nom)
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT " + colonne + " FROM equipement WHERE nom=" + nom) && req.first() )
    {
        return req.value(0).toString();
    }

    return NULL;
}

bool DBManager::put(QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    return ( req.exec("INSERT INTO interface (nom, ip, masque, passerelle) VALUES (" + nom + ", " + ip + ", " + masque + ", " + passerelle + ") ")) ? true : false;
}

bool DBManager::put(int id, QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    return ( req.exec("INSERT INTO interface (id, nom, ip, masque, passerelle) VALUES (" + QString::number(id) + ", " + nom + ", " + ip + ", " + masque + ", " + passerelle + ") ")) ? true : false;
}

bool DBManager::clearTable(QString table)
{
    QSqlQuery req(_bdd);

    return req.exec("DELETE FROM " + table);
}

DBManager::~DBManager()
{
    _bdd.close();
}
