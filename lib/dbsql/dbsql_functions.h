/*!
 * \file            dbsql_functions.h
 * \brief           Interface to SQL module standalone functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H
#define PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H

#include <memory>

#include "dbsqlstatements.h"

namespace genleg {

/*!
 * \brief           Factory function for DBSQL objects
 * \returns         The DBSQLStatements corresponding to the compiled-in
 * database backend.
 */
std::shared_ptr<const DBSQLStatements> get_sql_object();

}           //  namespace genleg

#endif      //  PG_GENERAL_LEDGER_DATABASE_DBSQL_FUNCTIONS_H

