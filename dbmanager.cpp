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

QString DBManager::get(QString colonne, QString valeur)
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT " + colonne + " FROM interfaces WHERE nom='" + valeur + "'") && req.first() )
    {
        return req.value(0).toString();
    }

    return NULL;
}

bool DBManager::put(QString nom, QString ip, QString masque, QString passerelle)
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

bool DBManager::put(int id, QString nom, QString ip, QString masque, QString passerelle)
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

DBManager::~DBManager()
{
    _bdd.close();
}
