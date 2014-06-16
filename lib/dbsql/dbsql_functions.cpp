/*!
 * \file            dbsqlstatements.h
 * \brief           Implementation of SQL module standalone functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdexcept>

#include "dbsql_functions.h"
#include "dbsql_implementations.h"
#include "database_imp/database_imp.h"

using namespace genleg;

std::shared_ptr<const DBSQLStatements>
genleg::get_sql_object() {
    const std::string type = gldb::get_database_type();
    if ( type == "MySQL" ) {
        return std::shared_ptr<const DBSQLStatements>(new const DBSQLMySQL());
    }
    else if ( type == "DUMMY" ) {
        return std::shared_ptr<const DBSQLStatements>(new const DBSQLDummy());
    }
    else {
        throw std::runtime_error("Unrecognized database implementation type");
    }
}

