#ifndef PG_GENERAL_LEDGER_DATABASE_IMP_H
#define PG_GENERAL_LEDGER_DATABASE_IMP_H

#include <memory>

#include "database/database.h"

namespace gldb {

DBConnImp * get_connection(const std::string database,
        const std::string hostname, const std::string username,
        const std::string password);
}

#endif      //  PG_GENERAL_LEDGER_DATABASE_IMP_H

