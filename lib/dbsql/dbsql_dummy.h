/*!
 * \file            dbsql_dummy.h
 * \brief           Interface to dummy SQL statement class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBSQL_DUMMY_H
#define PG_GENERAL_LEDGER_DATABASE_DBSQL_DUMMY_H

#include "dbsqlstatements.h"

namespace genleg {

/*!
 * \brief           Dummy SQL statements class.
 * \ingroup         sql
 */
class DBSQLDummy : public DBSQLStatements {
};              //  class DBSQLDummy

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBSQL_DUMMY_H

