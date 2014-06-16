/*!
 * \file            dbconn_mysql_imp.cpp
 * \brief           Implementation of MySQL database connection implementation
 * class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "dbconn_mysql_imp.h"

using namespace gldb;

DBConnMySQL::DBConnMySQL(const std::string& database,
                         const std::string& hostname,
                         const std::string& username,
                         const std::string& password) :
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

DBConnMySQL::~DBConnMySQL() {
    if ( m_conn ) {
        mysql_close(m_conn);
    }
    mysql_library_end();
}

void DBConnMySQL::query(const std::string& sql_query) {
    if ( mysql_query(m_conn, sql_query.c_str()) ) {
        std::string msg = mysql_error(m_conn);
        throw DBConnCouldNotQuery(msg);
    }
}

Table DBConnMySQL::select(const std::string& query) {
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

    Table table{std::move(field_names)};

    MYSQL_ROW row;
    while ( (row = mysql_fetch_row(result)) ) {
        TableRow record(num_fields);

        unsigned long * lengths = mysql_fetch_lengths(result);

        for ( size_t i = 0; i < num_fields; ++i ) {
            std::string new_field;
            if ( lengths[i] ) {
                new_field.resize(lengths[i]);
                for ( size_t j = 0; j < lengths[i]; ++j ) {
                    new_field[j] = row[i][j];
                }
            }
            record[i] = TableField(std::move(new_field));
        }

        table.append_record(std::move(record));
    }

    mysql_free_result(result);
    return table;
}

