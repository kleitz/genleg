/*!
 * \file            dbconn_mysql_imp.cpp
 * \brief           Implementation of MySQL database connection implementation
 * class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "dbconn_mysql_imp.h"
#include "dbconn_mysql_result.h"

using namespace gldb;

/*!
 * \brief               Gets field names from a MySQL result structure.
 * \ingroup database
 * \param result        The MySQL result structure.
 * \returns             A TableRow containing the field names.
 */
static TableRow
get_field_names(MySQLResult& result);

/*!
 * \brief               Creates a TableRow from a MySQL result row.
 * \ingroup database
 * \param result        The MySQL result structure.
 * \param row           The MySQL row structure.
 * \returns             A TableRow containing the row data.
 */
static TableRow
get_row(MySQLResult& result, MYSQL_ROW row);

DBConnMySQL::DBConnMySQL(const std::string& database,
                         const std::string& hostname,
                         const std::string& username,
                         const std::string& password) :
    m_conn{nullptr}
{
    std::unique_lock<std::mutex> lock{m_mtx};

    m_conn = mysql_init(nullptr);
    if ( !m_conn ) {
        throw DBConnCouldNotConnect("Could not initialize connection");
    }

    lock.unlock();

    if ( !mysql_real_connect(m_conn, hostname.c_str(),
            username.c_str(), password.c_str(),
            database.c_str(), 0, nullptr, 0) ) {
        const std::string msg = mysql_error(m_conn);
        mysql_close(m_conn);
        mysql_library_end();
        throw DBConnCouldNotConnect(msg);
    }
}

DBConnMySQL::~DBConnMySQL()
{
    if ( m_conn ) {
        mysql_close(m_conn);
    }
    mysql_library_end();
}

void DBConnMySQL::query(const std::string& sql_query)
{
    if ( mysql_query(m_conn, sql_query.c_str()) ) {
        throw DBConnCouldNotQuery(mysql_error(m_conn));
    }
}

Table DBConnMySQL::select(const std::string& sql_query)
{
    query(sql_query);
    MySQLResult result(m_conn);
    Table table{get_field_names(result)};

    for ( MYSQL_ROW row; (row = mysql_fetch_row(result.result())); ) {
        table.append_record(get_row(result, row));
    }

    return table;
}

static TableRow
get_field_names(MySQLResult& result)
{
    MYSQL_FIELD * fields = mysql_fetch_fields(result.result());
    TableRow field_names{result.num_fields()};

    for ( size_t i = 0; i < result.num_fields(); ++i ) {
        field_names[i] = fields[i].name;
    }

    return field_names;
}

static TableRow
get_row(MySQLResult& result, MYSQL_ROW row)
{
    TableRow record{result.num_fields()};
    unsigned long * lengths = mysql_fetch_lengths(result.result());

    for ( size_t f = 0; f < result.num_fields(); ++f ) {
        record[f] = std::string{row[f], lengths[f]};
    }

    return record;
}

