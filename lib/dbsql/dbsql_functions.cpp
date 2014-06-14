#include "database_imp/database_imp.h"
#include "dbsql_functions.h"

using namespace genleg;

std::shared_ptr<DBSQLStatements>
genleg::get_sql_object() {
    const std::string type = gldb::get_database_type();

    if ( type == "MySQL" ) {
        return std::shared_ptr<DBSQLStatements>(new DBSQLMySQL());
    }

    throw "Unrecognized type";
}

