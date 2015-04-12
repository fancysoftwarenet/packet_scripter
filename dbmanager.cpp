#include "dbmanager.h"

/* Structure de la bdd
  PK AI
   id       nom     ip      masque      passerelle
   int     String  String   String        String
*/

DBManager::DBManager(QString hote, QString db, QString user, QString pwd)
    : _hote(hote), _db(db), _user(user), _pwd(pwd)
{
    _bdd = QSqlDatabase::addDatabase("QSQLITE");
    _bdd.setHostName("localhost");
    _bdd.setDatabaseName("packet_scripter");
    _bdd.setUserName("root");
    _bdd.setPassword("");

    if ( ! _bdd.open() )
    {
        QMessageBox::warning(NULL, "Attention", "Il y a eu une erreur � l'ouverture de la base de donn�es.\n\n" + _bdd.lastError().text());
    }

    QSqlQuery req(_bdd);

    if ( !req.exec("CREATE TABLE IF NOT EXISTS interface ( id INT PRIMARY KEY AUTOINCREMENT, nom STRING NOT NULL, ip STRING NOT NULL, masque STRING NOT NULL, passerelle)"))
        QMessageBox::critical(NULL, "Erreur critique", "Impossible de cr�er la table pour la base de donn�es, le programme peut ne pas fonctionner correctement");
}

QString DBManager::get(QString colonne, int id)
{
    QSqlQuery req(_bdd);

    if ( req.exec("SELECT " + colonne + " FROM equipement WHERE id=" + QString::number(id)) && req.first() )
    {
        return req.value(0).toString();
    }

    return NULL;
}

bool DBManager::put(int id, QString nom, QString ip, QString masque, QString passerelle)
{
    QSqlQuery req(_bdd);

    return ( req.exec("INSERT INTO interface (id, nom, ip, masque, passerelle) VALUES (" + QString::number(id) + ", " + nom + ", " + ip + ", " + masque + ", " + passerelle + ") ")) ? true : false;
}