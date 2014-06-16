/*!
 * \file            dbconn_mysql_functions.cpp
 * \brief           Implementation of MySQL implementation factory function.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "../database_imp.h"
#include "dbconn_mysql_imp.h"

using namespace gldb;

DBConnImp * gldb::get_connection(const std::string& database,
                                 const std::string& hostname,
                                 const std::string& username,
                                 const std::string& password) {
    return new DBConnMySQL(database, hostname, username, password);
}

std::string gldb::get_database_type() {
    return "MySQL";
}

