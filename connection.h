#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlDatabase>


class Connection
{

public:
    static Connection * instance();
    bool createconnect();

private:
    Connection();
    ~Connection();
    Connection(const Connection&) = delete; // delete the assignment operator
    Connection& operator=(const Connection&) = delete; //delete the assignment operator

    static Connection* p_instance; // pointeur to the unique instance

//signals:
};

#endif // CONNECTION_H
