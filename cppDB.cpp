#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

// global variables
const char *hostname = "localhost";
const char *username = "root";
const char *password = "No";
const char *database = "information_schema";
unsigned int port = 3306;
const char *unixsocket = NULL;
unsigned long clientflag = 0;

void connectdatabase()
{
    MYSQL *conn;
    conn = mysql_init(0); // initialize MySQL
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);

    if (conn)
    {
        cout << "Connected to database" << endl;
    }
    else
    {
        cout << "Failed to conect to database" << endl;
    }
}

int main()
{
    connectdatabase();
}