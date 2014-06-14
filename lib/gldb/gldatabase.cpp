/*!
 * \file            gldatabase.cpp
 * \brief           Implementation of General Ledger database class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sstream>
#include "gldatabase.h"
#include "database_imp/database_imp.h"

using namespace genleg;

gl_database::gl_database(const std::string database,
                         const std::string hostname,
                         const std::string username,
                         const std::string password) try :
    m_dbc(gldb::get_connection(database, hostname, username, password)),
    m_sql(get_sql_object()),
    m_tables({"standing_data", "users", "entities", "jesrcs",
              "nomaccts", "jes", "jelines"}),
    m_views({"current_trial_balance", "check_total", "all_jes"})
{ }
catch ( const gldb::DBConnException& e ) {
    throw GLDBException(e.what());
}

gl_database::~gl_database() {
}

void gl_database::create_structure() try {
    for ( const auto& table_name : m_tables ) {
        m_dbc.query(m_sql->create_table(table_name));
    }

    for ( const auto& view_name : m_views ) {
        m_dbc.query(m_sql->create_view(view_name));
    }
}
catch ( const gldb::DBConnException& e ) {
    throw GLDBException(e.what());
}

void gl_database::destroy_structure() try {
    for ( auto itr = m_views.rbegin(); itr != m_views.rend(); ++itr ) {
        m_dbc.query(m_sql->drop_view(*itr));
    }

    for ( auto itr = m_tables.rbegin(); itr != m_tables.rend(); ++itr ) {
        m_dbc.query(m_sql->drop_table(*itr));
    }
}
catch ( const gldb::DBConnException& e ) {
    throw GLDBException(e.what());
}

void gl_database::load_sample_data(const std::string& dir) try {
    for ( const auto& tname : m_tables ) {
        std::string filename = dir + "/" + tname;
        gldb::Table table = gldb::Table::create_from_file(filename, ':');
        for ( size_t i = 0; i < table.num_records(); ++i ) {
            m_dbc.query(table.insert_query(tname, i));
        }
    }
}
catch ( const gldb::DBConnException& e ) {
    throw GLDBException(e.what());
}
catch ( const gldb::TableCouldNotOpenInputFile& e ) {
    std::ostringstream ss;
    ss << "Couldn't open input file '" << e.what() << "'.";
    throw GLDBException(ss.str());
}
catch ( const gldb::TableBadInputFile& e ) {
    std::ostringstream ss;
    ss << "Malformed input file '" << e.what() << "'.";
    throw GLDBException(ss.str());
}

std::string gl_database::backend() {
    return gldb::get_database_type();
}

