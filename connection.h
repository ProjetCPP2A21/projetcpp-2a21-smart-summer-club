#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connection
{
public:
    static connection* instance();
    bool createconnect();
private:
    connection();
    ~connection();
    connection(const connection&) = delete;
    connection& operator=(const connection&);


    static connection* p_instance;

};

#endif // CONNECTION_H
