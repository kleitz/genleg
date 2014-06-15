#ifndef PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H
#define PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H

#include <string>
#include <memory>

#include "dbsql_implementations.h"

namespace genleg {

std::shared_ptr<const DBSQLStatements> get_sql_object();

}           //  namespace genleg

#endif      //  PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H

