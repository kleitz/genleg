

#include "../database_imp.h"
#include "dbconn_dummy_imp.h"

using namespace gldb;

DBConnImp * gldb::get_connection(const std::string database,
        const std::string hostname, const std::string username,
        const std::string password) {
    return new DBConnDummy(database, hostname, username, password);
}

std::string gldb::get_database_type() {
    return "DUMMY";
}

