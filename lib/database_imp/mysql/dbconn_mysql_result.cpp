/*!
 * \file            dbconn_mysql_result.cpp
 * \brief           Implementation of MySQL result structure resource
 * handle class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <string>
#include "database/database.h"
#include "dbconn_mysql_result.h"

using namespace gldb;

MySQLResult::MySQLResult(MYSQL * conn) :
    m_result{mysql_store_result(conn)},
    m_num_fields{0}
{
    if ( !m_result ) {
        throw DBConnCouldNotQuery(mysql_error(conn));
    }
    m_num_fields = mysql_num_fields(m_result);
}

MySQLResult::~MySQLResult()
{
    mysql_free_result(m_result);
}

