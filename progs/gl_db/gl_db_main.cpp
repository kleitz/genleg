/*!
 * \file            gl_db_main.cpp
 * \brief           Main functionality for gl_db program.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>

#include "gldb/gldb.h"
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
 * \brief           Prints help or version messages if requested.
 * \ingroup         gl_db
 * \param config    Reference to a Config object.
 * \returns         `true` if the help or version message was requested,
 * `false` otherwise.
 */
static bool check_help_and_version(const Config& config);

/*!
 * \brief           Checks if database, hostname and username were provided.
 * \ingroup         gl_db
 * \param config    Reference to a Config object.
 * \returns         `true` if the information was provided, `false` otherwise.
 */
static bool check_db_parameters(const Config& config);

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
int main(int argc, char *argv[]) try {
    Config config;
    set_configuration(config, argc, argv);

    if ( check_help_and_version(config) ) {
        return 0;
    }

    if ( !check_db_parameters(config) ) {
        return 1;
    }

    std::string passwd;
    if ( config.is_set("password") ) {
        passwd = config["password"];
    }
    passwd = login();

    GLDatabase gdb(config["database"], config["hostname"],
                    config["username"], passwd);

    if ( config.is_set("create") ) {
        std::cout << "Creating database structure..." << std::endl;
        gdb.create_structure();
        std::cout << "...success." << std::endl;
    }
    else if ( config.is_set("delete") ) {
        std::cout << "Destroying database structure..." << std::endl;
        gdb.destroy_structure();
        std::cout << "...success." << std::endl;
    }
    else if ( config.is_set("loadsample") ) {
        std::cout << "Loading sample data..." << std::endl;
        gdb.load_sample_data(config["loadsample"]);
        std::cout << "...success." << std::endl;
    }
    else if ( config.is_set("reinit") ) {
        std::cout << "Destroying database structure..." << std::endl;
        gdb.destroy_structure();
        std::cout << "...success." << std::endl;

        std::cout << "Creating database structure..." << std::endl;
        gdb.create_structure();
        std::cout << "...success." << std::endl;

        std::cout << "Loading sample data..." << std::endl;
        gdb.load_sample_data(config["reinit"]);
        std::cout << "...success." << std::endl;
    }
    else {
        std::cerr << progname << ": no options selected." << std::endl;
    }

    return 0;
}
catch ( const ConfigBadOption& e ) {
    std::cerr << progname << ": Invalid command line options" << std::endl;
}
catch ( const ConfigOptionNotSet& e ) {
    std::cerr << progname << ": Request for value of missing option '"
              << e.what() << "'" << std::endl;
}
catch ( const ConfigCouldNotOpenFile& e ) {
    std::cerr << progname << ": could not open configuration file '"
              << e.what() << "'" << std::endl;
}
catch ( const ConfigBadConfigFile& e ) {
    std::cerr << progname << ": configuration file '" << e.what()
              << "' is badly formed." << std::endl;
}
catch (const GLDBException& e) {
    std::cerr << progname << ": database error - " << e.what() << std::endl;
}
catch (const std::runtime_error& e) {
    std::cerr << progname << ": error - " << e.what() << std::endl;
}
catch (...) {
    std::cerr << progname << ": unknown error" << std::endl;
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
    config.add_cmdline_option("loadsample", Argument::REQ_ARG);
    config.add_cmdline_option("reinit", Argument::REQ_ARG);
    config.populate_from_file("conf_files/gl_db_conf.conf");
    config.populate_from_cmdline(argc, argv);
}

static bool check_help_and_version(const Config& config) {
    if ( config.is_set("help") ) {
        print_help_message();
        return true;
    }
    else if ( config.is_set("version") ) {
        print_version_message();
        return true;
    }
    return false;
}

static bool check_db_parameters(const Config& config) {
    if ( !config.is_set("database") ) {
        print_usage_message();
        std::cerr << progname << ": database name not provided" << std::endl;
        return false;
    }
    else if ( !config.is_set("hostname") ) {
        print_usage_message();
        std::cerr << progname << ": hostname not provided" << std::endl;
        return false;
    }
    else if ( !config.is_set("username") ) {
        print_usage_message();
        std::cerr << progname << ": username not provided" << std::endl;
        return false;
    }
    else {
        return true;
    }
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
        << "  --loadsample=<dir>    Load database with sample data\n"
        << "                                     from directory <dir>\n"
        << "  --reinit=<dir>        Delete and create database structure\n"
        << "                                     and load sample data\n"
        << "                                     from directory <dir>\n";
}

static void print_version_message() {
    std::cout << progname << " v0.1 (experimental)\n"
              << "Copyright (C) 2014 Paul Griffiths\n"
              << "Compiled with " << GLDatabase::backend()
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
        std::cout << std::endl;
        throw std::runtime_error("Couldn't get password");
    }

    return passwd;
}

