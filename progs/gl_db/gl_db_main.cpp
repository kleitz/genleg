/*!
 * \file            gl_db_main.cpp
 * \brief           Main functionality for gl_db program.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>
#include <memory>

#include "database/database.h"
#include "database_imp/database_imp.h"
#include "dbsql/dbsql.h"
#include "config/config.h"

using namespace genleg;

/*!
 * \brief           Static variable for program name.
 * \ingroup         gl_db
 */
static const char * progname = "gl_db";

/*!
 * \brief           Sets program configuration options.
 * \ingroup         gl_db
 * \param config    Reference to a Config object.
 * \param argc      \c argc passed to \c main().
 * \param argv      \c argv passed to \c main().
 */
static void set_configuration(Config& config, int argc, char *argv[]);

/*!
 * \brief           Prints a program usage message.
 * \ingroup         gl_db
 */
static void print_usage_message();

/*!
 * \brief           Prints a program version message.
 * \ingroup         gl_db
 */
static void print_version_message();

/*!
 * \brief           Prints a program help message.
 * \ingroup         gl_db
 */
static void print_help_message();

/*!
 * \brief           Gets a password from the terminal.
 * \ingroup         gl_db
 * \returns         The password.
 */
static std::string login(void);


/*!
 * \brief           Main function
 * \ingroup         gl_db
 * \param argc      Number of command line arguments.
 * \param argv      Command line arguments.
 * \returns         Exit status code.
 */
int main(int argc, char *argv[]) {
    Config config;
    try {
        set_configuration(config, argc, argv);
    }
    catch (...) {
        std::cerr << progname << ": bad command line options" << std::endl;
        return 1;
    }

    if ( config.is_set("help") ) {
        print_help_message();
        return 0;
    }
    else if ( config.is_set("version") ) {
        print_version_message();
        return 0;
    }
    else if ( !config.is_set("database") ) {
        print_usage_message();
        std::cerr << progname << ": database name not provided" << std::endl;
        return 1;
    }
    else if ( !config.is_set("hostname") ) {
        print_usage_message();
        std::cerr << progname << ": hostname not provided" << std::endl;
        return 1;
    }
    else if ( !config.is_set("username") ) {
        print_usage_message();
        std::cerr << progname << ": hostname not provided" << std::endl;
        return 1;
    }

    std::string passwd;
    if ( config.is_set("password") ) {
        passwd = config["password"];
    }
    else {
        try {
            passwd = login();
        }
        catch (...) {
            std::cerr << std::endl << progname
                      << ": error getting password." << std::endl;
            return 1;
        }
    }

    if ( config.is_set("create") ) {
        const std::shared_ptr<DBSQLStatements> stmt = get_sql_object();
        
        const std::vector<std::string> tables = {
            "standing_data",
            "users",
            "entities",
            "jesrcs",
            "nomaccts",
            "jes",
            "jelines",
        };

        const std::vector<std::string> views = {
            "current_trial_balance",
            "check_total",
            "all_jes"
        };

        try {
            gldb::DBConn dbc(gldb::get_connection(config["database"],
                        config["hostname"], config["username"], passwd));

            for ( const auto& table_name : tables ) {
                const std::string query = stmt->create_table(table_name);
                std::cout << "Creating table '" << table_name
                          << "'...";
                try {
                    dbc.query(query);
                    std::cout << "success." << std::endl;
                }
                catch ( gldb::DBConnException& e ) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
            }

            for ( const auto& view_name : views ) {
                const std::string query = stmt->create_view(view_name);
                std::cout << "Creating view '" << view_name
                          << "'...";
                try {
                    dbc.query(query);
                    std::cout << "success." << std::endl;
                }
                catch ( gldb::DBConnException& e ) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
            }
        }
        catch ( gldb::DBConnCouldNotConnect& e ) {
            std::cerr << progname << ": couldn't connect to database: "
                      << e.what() << std::endl;
            return 1;
        }
    }
    else if ( config.is_set("delete") ) {
        const std::shared_ptr<DBSQLStatements> stmt = get_sql_object();
        
        const std::vector<std::string> tables = {
            "jelines",
            "jes",
            "nomaccts",
            "jesrcs",
            "entities",
            "users",
            "standing_data",
        };

        const std::vector<std::string> views = {
            "all_jes",
            "check_total",
            "current_trial_balance",
        };

        try {
            gldb::DBConn dbc(gldb::get_connection(config["database"],
                        config["hostname"], config["username"], passwd));

            for ( const auto& view_name : views ) {
                const std::string query = stmt->drop_view(view_name);
                std::cout << "Dropping view '" << view_name
                          << "'...";
                try {
                    dbc.query(query);
                    std::cout << "success." << std::endl;
                }
                catch ( gldb::DBConnException& e ) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
            }

            for ( const auto& table_name : tables ) {
                const std::string query = stmt->drop_table(table_name);
                std::cout << "Dropping table '" << table_name
                          << "'...";
                try {
                    dbc.query(query);
                    std::cout << "success." << std::endl;
                }
                catch ( gldb::DBConnException& e ) {
                    std::cerr << "error: " << e.what() << std::endl;
                }
            }
        }
        catch ( gldb::DBConnCouldNotConnect& e ) {
            std::cerr << progname << ": couldn't connect to database: "
                      << e.what() << std::endl;
            return 1;
        }
    }
    else if ( config.is_set("loadsample") ) {
        const std::vector<std::string> tables = {
            "standing_data",
            "users",
            "entities",
            "jesrcs",
            "nomaccts",
            "jes",
            "jelines",
        };

        try {
            gldb::DBConn dbc(gldb::get_connection(config["database"],
                        config["hostname"], config["username"], passwd));
            for ( auto& data : tables ) {
                std::string filename = "sample_data/" + data;
                std::cout << "Attempting to open " << filename << "...\n";
                gldb::Table table = gldb::Table::create_from_file(filename,
                                                                  ':');
                for ( size_t i = 0; i < table.num_records(); ++i ) {
                    try {
                        std::cout << "Loading sample data into '"
                                  << data << "'...";
                        std::string query = table.insert_query(data, i);
                        dbc.query(query);
                        std::cout << "success." << std::endl;
                    }
                    catch (gldb::DBConnCouldNotQuery& e) {
                        std::cerr << "couldn't query database: "
                                  << e.what() << std::endl;
                    }
                }
            }

        }
        catch ( gldb::DBConnCouldNotConnect& e ) {
            std::cerr << progname << ": couldn't connect to database: "
                      << e.what() << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << progname << ": no options selected." << std::endl;
    }

    return 0;
}

static void set_configuration(Config& config, int argc, char *argv[]) {
    config.add_cmdline_option("help", Argument::NO_ARG);
    config.add_cmdline_option("version", Argument::NO_ARG);
    config.add_cmdline_option("database", Argument::REQ_ARG);
    config.add_cmdline_option("hostname", Argument::REQ_ARG);
    config.add_cmdline_option("username", Argument::REQ_ARG);
    config.add_cmdline_option("password", Argument::REQ_ARG);
    config.add_cmdline_option("create", Argument::NO_ARG);
    config.add_cmdline_option("delete", Argument::NO_ARG);
    config.add_cmdline_option("loadsample", Argument::NO_ARG);
    config.populate_from_cmdline(argc, argv);
    config.populate_from_file("conf_files/gl_db_conf.conf");
}

static void print_usage_message() {
    std::cout << "Usage: " << progname << " [options]\n";
}

static void print_help_message() {
    print_usage_message();
    std::cout << "General options:\n"
        << "  --help                Display this information\n"
        << "  --version             Display version information\n"
        << "\nDatabase options:\n"
        << "  --create              Create database structure\n"
        << "  --delete              Delete database structure\n"
        << "  --loadsample          Load database with sample data\n";
}

static void print_version_message() {
    std::cout << progname << " v0.1 (experimental)\n"
              << "Copyright (C) 2014 Paul Griffiths\n"
              << "Compiled with " << gldb::get_database_type()
              << " database support.\n"
              << "This is free software; see the source for copying"
              << " conditions. There is NO\n"
              << "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
              << "PARTICULAR PURPOSE.\n";
}

static std::string login(void) {
    std::cout << "Enter password (*WILL BE VISIBLE*): " << std::flush;
    std::string passwd;

    if ( !std::getline(std::cin, passwd) ) {
        throw "Couldn't get password";
    }

    return passwd;
}

