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
using namespace gldb;

/*!
 * \brief           Converts a string representation of a bool to a bool.
 * \param bs        The bool string.
 * \returns         `true` if `bs` contains "1" or "TRUE", `false` if `bs`
 * contains "0" or "FALSE".
 * \throws          GLDBException if `bs` contains any other value.
 */
static bool boolstring_to_bool(const std::string& bs);

GLDatabase::GLDatabase(const std::string& database,
                       const std::string& hostname,
                       const std::string& username,
                       const std::string& password) try :
    m_dbc(get_connection(database, hostname, username, password)),
    m_sql(get_sql_object()),
    m_tables({"standing_data", "users", "perms", "user_perms", "entities",
              "jesrcs", "nomaccts", "jes", "jelines"}),
    m_views({"current_trial_balance", "check_total", "all_jes"})
{ }
catch ( const DBConnException& e ) {
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
catch ( const DBConnException& e ) {
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
catch ( const DBConnException& e ) {
    throw GLDBException(e.what());
}

void GLDatabase::load_sample_data(const std::string& dir) try {
    for ( const auto& tname : m_tables ) {
        std::string filename = dir + "/" + tname;
        Table table{Table::create_from_file(filename, ':')};
        for ( size_t i = 0; i < table.num_records(); ++i ) {
            m_dbc.query(table.insert_query(tname, i));
        }
    }
}
catch ( const DBConnException& e ) {
    throw GLDBException(e.what());
}
catch ( const TableCouldNotOpenInputFile& e ) {
    std::ostringstream ss;
    ss << "Couldn't open input file '" << e.what() << "'.";
    throw GLDBException(ss.str());
}
catch ( const TableBadInputFile& e ) {
    std::ostringstream ss;
    ss << "Malformed input file '" << e.what() << "'.";
    throw GLDBException(ss.str());
}

std::string GLDatabase::backend() {
    return get_database_type();
}

GLUser GLDatabase::create_user(Table& table) {
    const std::string permquery = m_sql->get_perms(table.get_field("id", 0));
    Table permtable{m_dbc.select(permquery)};
    std::vector<std::string> perms;
    for ( size_t i = 0; i < permtable.num_records(); ++i ) {
        perms.push_back(permtable[i][0]);
    }

    const bool enabled = boolstring_to_bool(table.get_field("enabled", 0));
    GLUser new_user(table.get_field("id", 0),
                    table.get_field("user_name", 0),
                    table.get_field("first_name", 0),
                    table.get_field("last_name", 0),
                    table.get_field("pass_hash", 0),
                    table.get_field("pass_salt", 0),
                    std::move(perms),
                    enabled);

    return new_user;
}

GLUser GLDatabase::get_user_by_id(const std::string& user_id) {
    Table table{m_dbc.select(m_sql->user_by_id(user_id))};
    return create_user(table);
}

GLUser GLDatabase::get_user_by_username(const std::string& user_name) {
    Table table{m_dbc.select(m_sql->user_by_username(user_name))};
    return create_user(table);
}

void GLDatabase::update_user(const GLUser& user) {
    m_dbc.query(m_sql->update_user(user));
}

void GLDatabase::grant(const GLUser& user, const std::string& perm) {
    m_dbc.query(m_sql->grant(user.id(), perm));
}

void GLDatabase::revoke(const GLUser& user, const std::string& perm) {
    m_dbc.query(m_sql->revoke(user.id(), perm));
}

GLReport GLDatabase::report(const std::string& report_name,
                            const std::string& arg)
{
    if ( report_name == "currenttb" ) {
        return current_trial_balance_report(arg);
    }
    else if ( report_name == "listusers" ) {
        return list_users_report();
    }
    else {
        throw GLDBException{"Unrecognized report"};
    }
}

GLReport GLDatabase::current_trial_balance_report(const std::string& entity)
{
    std::string query;
    if ( !entity.empty() ) {
        query = m_sql->currenttb_by_entity(entity);
    }
    else {
        query = m_sql->currenttb();
    }

    return GLReport{decorated_report_from_table(m_dbc.select(query))};
}

GLReport GLDatabase::list_users_report()
{
    const std::string query = m_sql->listusers();
    return GLReport{decorated_report_from_table(m_dbc.select(query))};
}
static bool boolstring_to_bool(const std::string& bs) {
    if ( bs == "1" || bs == "TRUE" ) {
        return true;
    }
    else if ( bs == "0" || bs == "FALSE" ) {
        return false;
    }
    else {
        throw GLDBException("Bad value for bool string");
    }
}

