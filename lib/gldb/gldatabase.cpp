/*!
 * \file            gldatabase.cpp
 * \brief           Implementation of General Ledger database class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "gldatabase.h"
#include "glexception.h"
#include "database_imp/database_imp.h"
#include "pgutils/pgutils.h"

using namespace genleg;
using namespace gldb;
using namespace boost::filesystem;
using pgutils::Currency;
using pgutils::currency_from_string;

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

    /*  Load tables directly  */

    for ( const auto& tname : m_tables ) {
        if ( tname == "jes" || tname == "jelines" ) {

            /*  Ignore journal entry tables  */

            continue;
        }

        std::string filename = dir + "/" + tname;
        Table table{Table::create_from_file(filename, ':')};
        for ( size_t i = 0; i < table.num_records(); ++i ) {
            m_dbc.query(table.insert_query(tname, i));
        }
    }

    /*  Get journal entry files  */

    const std::string jedir = dir + "/je";
    if ( !is_directory(jedir) ) {
        throw GLDBException("Sample JE directory not present");
    }

    std::vector<path> v;
    std::copy(directory_iterator(jedir), directory_iterator(),
            back_inserter(v));
    std::sort(v.begin(), v.end());

    /*  Load journal entries from files  */

    for ( const auto& p : v ) {
        std::ifstream ifs(p.string());
        if ( !ifs.is_open() ) {
            throw GLDBException("Couldn't open file");
        }
        post_journal(journal_from_stream(ifs));
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

GLEntity GLDatabase::create_entity(Table& table) {
    const bool enabled = boolstring_to_bool(table.get_field("enabled", 0));
    const bool aggregate = boolstring_to_bool(table.get_field("aggregate", 0));
    GLEntity new_entity(std::stoul(table.get_field("id", 0)),
                        table.get_field("name", 0),
                        table.get_field("shortname", 0),
                        std::stoul(table.get_field("parent", 0)),
                        aggregate,
                        enabled);

    return new_entity;
}

GLEntity GLDatabase::get_entity_by_id(const std::string& entity_id)
{
    Table table{m_dbc.select(m_sql->entity_by_id(entity_id))};
    return create_entity(table);
}

GLEntity GLDatabase::get_entity_by_name(const std::string& entity_name)
{
    Table table{m_dbc.select(m_sql->entity_by_name(entity_name))};
    return create_entity(table);
}

GLAccount GLDatabase::get_account_by_name(const std::string& acc_name)
{
    Table table{m_dbc.select(m_sql->account_by_name(acc_name))};
    const bool enabled = boolstring_to_bool(table.get_field("enabled", 0));
    GLAccount acct{table.get_field("num", 0),
                   table.get_field("description", 0),
                   enabled};
    return acct;
}

GLJournal GLDatabase::get_je_by_id(const std::string& je_id) {
    Table table{m_dbc.select(m_sql->je_by_id(je_id))};
    GLJournal j{std::stoul(table.get_field("entity", 0)),
                std::stoi(table.get_field("period", 0)),
                std::stoi(table.get_field("year", 0)),
                table.get_field("source", 0),
                table.get_field("memo", 0),
                std::stoul(table.get_field("id", 0)),
                std::stoul(table.get_field("user", 0))};

    Table lines{m_dbc.select(m_sql->jelines_by_id(je_id))};
    for ( const auto& line : lines ) {
        j.add_line(line[0], currency_from_string(line[1]));
    }
    if ( !j.balances() ) {
        throw GLDBException("Journal entry doesn't balance after retrieval");
    }
    return j;
}

void GLDatabase::post_journal(const GLJournal& journal)
{
    if ( !journal.balances() ) {
        throw GLDBException("Journal entry doesn't balance");
    }
    std::string query = m_sql->post_je(
            1,
            journal.entity(),
            journal.period(),
            journal.year(),
            journal.source(),
            journal.memo());

    GLDBTransaction txn(m_dbc);

    m_dbc.query(query);

    const int n = m_dbc.last_auto_increment();
    for ( const auto& line : journal ) {
        std::string query = m_sql->post_je_line(n, line.account(),
                line.amount().string());
        m_dbc.query(query);
    }

    txn.commit();
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
    else if ( report_name == "je" ) {
        return je_report(arg);
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

    GLReport report{"Current Trial Balance Report",
                    decorated_report_from_table(m_dbc.select(query))};
    if ( !entity.empty() ) {
        GLEntity e = get_entity_by_id(entity);
        std::ostringstream ss;
        ss << e.name() << " [" << e.id() << "]";
        report.add_header("Entity", ss.str());
    }
    return report;
}

GLReport GLDatabase::list_users_report()
{
    const std::string query = m_sql->listusers();
    return GLReport{"Users List Report",
                    decorated_report_from_table(m_dbc.select(query))};
}

GLReport GLDatabase::je_report(const std::string& je_id)
{
    GLJournal j = get_je_by_id(je_id);

    TableRow headers{"Account", "Description", "Amount"};
    Table lines{headers};

    for ( const auto& line : j ) {
        GLAccount acct = get_account_by_name(line.account());
        TableRow row{line.account(),
                     acct.description(),
                     line.amount().string()};
        lines.append_record(row);
    }

    GLReport report{"Single JE report",
                    decorated_report_from_table(lines)};

    GLEntity e = get_entity_by_id(std::to_string(j.entity()));
    std::ostringstream es;
    es << e.name() << " [" << e.id() << "]";
    report.add_header("Entity", es.str());

    report.add_header("Period", std::to_string(j.period()));
    report.add_header("Year", std::to_string(j.year()));
    report.add_header("Source", j.source());
    report.add_header("Memo", j.memo());

    GLUser u = get_user_by_id(std::to_string(j.user()));
    std::ostringstream us;
    us << u.username() << " [" << u.id() << "]";
    report.add_header("Posted by", us.str());

    return report;
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

