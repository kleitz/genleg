/*!
 * \file            gl_report_main.cpp
 * \brief           Main functionality for gl_report program.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>

#include "database/database.h"
#include "database_imp/database_imp.h"
#include "config/config.h"

/*!
 * \brief           Static variable for program name.
 * \ingroup         gl_report
 */
static const char * progname = "gl_report";

/*!
 * \brief           Sets program configuration options.
 * \ingroup         gl_report
 * \param config    Reference to a Config object.
 * \param argc      \c argc passed to \c main().
 * \param argv      \c argv passed to \c main().
 */
static void set_configuration(genleg::Config& config, int argc, char *argv[]);

/*!
 * \brief           Prints a program usage message.
 * \ingroup         gl_report
 */
static void print_usage_message();

/*!
 * \brief           Prints a program version message.
 * \ingroup         gl_report
 */
static void print_version_message();

/*!
 * \brief           Prints a program help message.
 * \ingroup         gl_report
 */
static void print_help_message();

/*!
 * \brief           Gets a password from the terminal.
 * \ingroup         gl_report
 * \returns         The password.
 */
static std::string login(void);


/*!
 * \brief           Main function
 * \ingroup         gl_report
 * \param argc      Number of command line arguments.
 * \param argv      Command line arguments.
 * \returns         Exit status code.
 */
int main(int argc, char *argv[]) {
    genleg::Config config;
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

    if ( config.is_set("currenttb") ) {
        std::string query = "SELECT * FROM current_trial_balance";
        if ( config.is_set("entity") ) {
            const std::string entity = config["entity"];
            if ( !entity.empty() ) {
                query += " WHERE Entity = ";
                query += entity;
            }
        }

        try {
            gldb::DBConn dbc(gldb::get_connection(config["database"],
                        config["hostname"], config["username"], passwd));

            const gldb::Table table = dbc.select(query);

            table.get_headers().print(std::cout);
            for ( size_t i = 0; i < table.num_records(); ++i ) {
                table[i].print(std::cout);
            }
            std::cout << "Number of records: [" << table.num_records()
                      << "]" << std::endl;
        }
        catch ( gldb::DBConnCouldNotConnect& e ) {
            std::cerr << progname << ": couldn't connect to database: "
                      << e.what() << std::endl;
            return 1;
        }
        catch ( gldb::DBConnCouldNotQuery& e ) {
            std::cerr << progname << ": couldn't query database: "
                      << e.what() << std::endl;
            return 1;
        }
        catch ( ... ) {
            std::cerr << progname << ": unknown exception." << std::endl;
            return 1;
        }

    }
    else {
        std::cerr << progname << ": no options selected." << std::endl;
    }

    return 0;
}

static void set_configuration(genleg::Config& config, int argc, char *argv[]) {
    config.add_cmdline_option("help", genleg::Argument::NO_ARG);
    config.add_cmdline_option("version", genleg::Argument::NO_ARG);
    config.add_cmdline_option("database", genleg::Argument::REQ_ARG);
    config.add_cmdline_option("hostname", genleg::Argument::REQ_ARG);
    config.add_cmdline_option("username", genleg::Argument::REQ_ARG);
    config.add_cmdline_option("password", genleg::Argument::REQ_ARG);
    config.add_cmdline_option("currenttb", genleg::Argument::NO_ARG);
    config.add_cmdline_option("entity", genleg::Argument::OPT_ARG);
    config.populate_from_cmdline(argc, argv);
    config.populate_from_file("conf_files/gl_report_conf.conf");
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
        << "  --database=<database> Specify database name\n"
        << "  --hostname=<hostname> Specify database hostname\n"
        << "  --username=<username> Specify username for database\n"
        << "  --password=<password> Specify password for database\n"
        << "\nReporting options:\n"
        << "  --entity=<entity>     Specifies an entity\n"
        << "  --listusers           Show a list of users\n"
        << "  --listentities        Show a list of entities\n"
        << "  --listnomaccts        Show a list of nominal accounts\n"
        << "  --listjes             Show a list of simple journal entries\n"
        << "  --listjelines         Show a list of journal entry lines\n"
        << "  --listjesrcs          Show a list of journal entry sources\n"
        << "  --standingdata        Show the standing data\n"
        << "  --currenttb           Show a current trial balance\n"
        << "                               (optionally for <entity>)\n"
        << "  --checktotal          Show double entry check totals\n"
        << "                               (optionally for <entity>)\n"
        << "  --entries[=<je_num>]  Show detailed journal entries\n"
        << "                               (optionally for <je_num> only)\n";
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

