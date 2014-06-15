/*!
 * \file            dbsql_mysql.h
 * \brief           Interface to MySQL SQL statement class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBSQL_MYSQL_H
#define PG_GENERAL_LEDGER_DATABASE_DBSQL_MYSQL_H

#include "dbsqlstatements.h"

namespace genleg {

/*!
 * \brief           MySQL SQL statements class.
 * \ingroup         sql
 */
class DBSQLMySQL : public DBSQLStatements {
};              //  class DBSQLMySql

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBSQL_MYSQL_H

