/*!
 * \file            gldatabase.cpp
 * \brief           Implementation of General Ledger database class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sstream>
#include "gldatabase.h"
#include "glexception.h"
#include "database_imp/database_imp.h"

using namespace genleg;

GLDatabase::GLDatabase(const std::string database,
                         const std::string hostname,
                         const std::string username,
                         const std::string password) try :
    m_dbc(gldb::get_connection(database, hostname, username, password)),
    m_sql(get_sql_object()),
    m_tables({"standing_data", "users", "perms", "user_perms", "entities",
              "jesrcs", "nomaccts", "jes", "jelines"}),
    m_views({"current_trial_balance", "check_total", "all_jes"})
{ }
catch ( const gldb::DBConnException& e ) {
    throw GLDBException(e.what());
}

GLDatabase::~GLDatabase() {
}

void GLDatabase::create_structure() try {
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

void GLDatabase::destroy_structure() try {
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

void GLDatabase::load_sample_data(const std::string& dir) try {
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

std::string GLDatabase::backend() {
    return gldb::get_database_type();
}

GLUser GLDatabase::create_user(gldb::Table& table) {
    bool enabled;
    if ( table.get_field("enabled", 0) == "1" ||
         table.get_field("enabled", 0) == "TRUE" ) {
        enabled = true;
    }
    else if ( table.get_field("enabled", 0) == "0" ||
              table.get_field("enabled", 0) == "FALSE" ) {
        enabled = false;
    }
    else {
        throw GLDBException("Bad value for user enabled");
    }

    GLUser new_user(table.get_field("id", 0),
                    table.get_field("user_name", 0),
                    table.get_field("first_name", 0),
                    table.get_field("last_name", 0),
                    table.get_field("pass_hash", 0),
                    table.get_field("pass_salt", 0),
                    enabled);

    std::string permquery = m_sql->get_perms(new_user);
    gldb::Table permtable = m_dbc.select(permquery);
    std::vector<std::string> p;
    for ( size_t i = 0; i < permtable.num_records(); ++i ) {
        p.push_back(permtable.get_field("Permission", i));
    }
    new_user.set_permissions(std::move(p));

    return new_user;
}

GLUser GLDatabase::get_user_by_id(const std::string& user_id) {
    std::string query = m_sql->user_by_id(user_id);
    gldb::Table table = m_dbc.select(query);
    return create_user(table);
}

GLUser GLDatabase::get_user_by_username(const std::string& user_name) {
    std::string query = m_sql->user_by_username(user_name);
    gldb::Table table = m_dbc.select(query);
    return create_user(table);
}

void GLDatabase::update_user(const GLUser& user) {
    std::string query = m_sql->update_user(user);
    m_dbc.query(query);
}

void GLDatabase::grant(const GLUser& user, const std::string& perm) {
    std::string query = m_sql->grant(user, perm);
    m_dbc.query(query);
}

void GLDatabase::revoke(const GLUser& user, const std::string& perm) {
    std::string query = m_sql->revoke(user, perm);
    m_dbc.query(query);
}

