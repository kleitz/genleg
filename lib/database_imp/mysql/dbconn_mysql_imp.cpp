/*!
 * \file            dbconn_mysql_imp.cpp
 * \brief           Implementation of MySQL database connection implementation class
 * \details         Implementation of MySQL database connection implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include "dbconn_mysql_imp.h"

using namespace gldb;


/*!
 * \brief           Constructor for DBConnMySQL_imp class
 */

DBConnMySQL::DBConnMySQL(const std::string database,
        const std::string hostname, const std::string username,
        const std::string password) :
    m_conn(nullptr) {
    m_conn = mysql_init(nullptr);
    if ( !m_conn ) {
        std::string msg = "Could not initialize connection";
        throw DBConnCouldNotConnect(msg);
    }

    if ( !mysql_real_connect(m_conn, hostname.c_str(),
            username.c_str(), password.c_str(),
            database.c_str(), 0, nullptr, 0) ) {
        std::string msg = mysql_error(m_conn);
        mysql_close(m_conn);
        mysql_library_end();
        throw DBConnCouldNotConnect(msg);
    }
}


/*!
 * \brief           Destructor for DBConnMySQL_imp class
 */

DBConnMySQL::~DBConnMySQL() {
    if ( m_conn ) {
        mysql_close(m_conn);
    }
    mysql_library_end();
}

Table DBConnMySQL::select(std::string query) {
    if ( mysql_query(m_conn, query.c_str()) ) {
        std::string msg = mysql_error(m_conn);
        throw DBConnCouldNotQuery(msg);
    }

    MYSQL_RES * result = mysql_store_result(m_conn);
    if ( !result ) {
        std::string msg = mysql_error(m_conn);
        throw DBConnCouldNotQuery(msg);
    }

    const unsigned int num_fields = mysql_num_fields(result);
    const MYSQL_FIELD * fields = mysql_fetch_fields(result);

    TableRow field_names(num_fields);
    for ( size_t i = 0; i < num_fields; ++i ) {
        field_names[i] = fields[i].name;
    }

    Table table(field_names);

    MYSQL_ROW row;
    while ( (row = mysql_fetch_row(result)) ) {
        TableRow record(num_fields);

        unsigned long * lengths = mysql_fetch_lengths(result);

        for ( size_t i = 0; i < num_fields; ++i ) {
            TableField new_field;
            if ( lengths[i] ) {
                for ( size_t j = 0; j < lengths[i]; ++j ) {
                    new_field += row[i][j];
                }
            }
            record[i] = new_field;
        }

        table.append_record(record);
    }

    mysql_free_result(result);
    return table;
}


