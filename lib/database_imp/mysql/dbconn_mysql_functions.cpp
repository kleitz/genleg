

#include "../database_imp.h"
#include "dbconn_mysql_imp.h"

using namespace gldb;

DBConnImp * gldb::get_connection(const std::string database,
        const std::string hostname, const std::string username,
        const std::string password) {
    return new DBConnMySQL(database, hostname, username, password);
}

std::string gldb::get_database_type() {
    return "MySQL";
}

