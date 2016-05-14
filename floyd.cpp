#include "connector/include/mysql_connection.h"
#include "connector/include/cppconn/driver.h"
#include "connector/include/cppconn/exception.h"
#include "connector/include/cppconn/resultset.h"
#include "connector/include/cppconn/statement.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << endl;
    cout << "Running 'SELECT 'Hello World!' » AS _message'..." << endl;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://192.168.1.33:3306", "root", "");
        /* Connect to the MySQL test database */
        con->setSchema("Users");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Users");
        while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("user") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column fata by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
        }
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;
    return 0;
}
