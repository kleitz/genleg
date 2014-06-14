/*!
 * \file            gl_user_main.cpp
 * \brief           Main functionality for gl_user program.
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
 * \ingroup         gl_user
 */
static const char * progname = "gl_user";

/*!
 * \brief           Sets program configuration options.
 * \ingroup         gl_user
 * \param config    Reference to a Config object.
 * \param argc      \c argc passed to \c main().
 * \param argv      \c argv passed to \c main().
 */
static void set_configuration(Config& config, int argc, char *argv[]);

/*!
 * \brief           Prints help or version messages if requested.
 * \ingroup         gl_user
 * \param config    Reference to a Config object.
 * \returns         `true` if the help or version message was requested,
 * `false` otherwise.
 */
static bool check_help_and_version(const Config& config);

/*!
 * \brief           Checks if database, hostname and username were provided.
 * \ingroup         gl_user
 * \param config    Reference to a Config object.
 * \returns         `true` if the information was provided, `false` otherwise.
 */
static bool check_db_parameters(const Config& config);

/*!
 * \brief           Outputs details for a user.
 * \ingroup         gl_user
 * \param user      Reference to user.
 */
static void show_user_details(const GLUser& user);

/*!
 * \brief           Enables or disables a user.
 * \ingroup         gl_user
 * \param user      Reference to user.
 * \param config    Reference to program configuration.
 * \param gdb       Reference to database object.
 */
static void enable_user(GLUser& user, Config& config,
                        GLDatabase& gdb);

/*!
 * \brief           Prints a program usage message.
 * \ingroup         gl_user
 */
static void print_usage_message();

/*!
 * \brief           Prints a program version message.
 * \ingroup         gl_user
 */
static void print_version_message();

/*!
 * \brief           Prints a program help message.
 * \ingroup         gl_user
 */
static void print_help_message();

/*!
 * \brief           Gets a password from the terminal.
 * \ingroup         gl_user
 * \returns         The password.
 */
static std::string login(void);


/*!
 * \brief           Main function
 * \ingroup         gl_user
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

    if ( config.is_set("show") ) {
        if ( config.is_set("id") ) {
            show_user_details(gdb.get_user_by_id(config["id"]));
        }
        else if ( config.is_set("name") ) {
            show_user_details(gdb.get_user_by_username(config["name"]));
        }
        else {
            std::cerr << progname << ": you must specify a user ID or name."
                      << std::endl;
        }
    }
    else if ( config.is_set("enable") ) {
        if ( config.is_set("id") ) {
            GLUser user = gdb.get_user_by_id(config["id"]);
            enable_user(user, config, gdb);
        }
        else if ( config.is_set("name") ) {
            GLUser user = gdb.get_user_by_username(config["name"]);
            enable_user(user, config, gdb);
        }
        else {
            std::cerr << progname << ": you must specify a user ID or name."
                      << std::endl;
        }
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
    config.add_cmdline_option("show", Argument::NO_ARG);
    config.add_cmdline_option("enable", Argument::REQ_ARG);
    config.add_cmdline_option("id", Argument::REQ_ARG);
    config.add_cmdline_option("name", Argument::REQ_ARG);
    config.populate_from_file("conf_files/gl_user_conf.conf");
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

static void show_user_details(const GLUser& user) {
    std::cout << "ID         : " << user.id() << std::endl;
    std::cout << "Username   : " << user.username() << std::endl;
    std::cout << "First Name : " << user.firstname() << std::endl;
    std::cout << "Last Name  : " << user.lastname() << std::endl;
    std::cout << "Enabled    : "
              << (user.enabled() ? "Yes" : "No") << std::endl;
}

static void enable_user(GLUser& user, Config& config,
                        GLDatabase& gdb) {
    if ( config["enable"] != "yes" && config["enable"] != "no" ) {
        throw ConfigBadOption("enable");
    }

    if ( !user.enabled() && config["enable"] == "yes" ) {
        std::cout << "Enabling user '" << user.username() << "'..."
                  << std::endl;
        user.set_enabled(true);
        gdb.update_user(user);
        std::cout << "...success." << std::endl;
    }
    else if ( user.enabled() && config["enable"] == "no" ) {
        std::cout << "Disabling user '" << user.username() << "'..."
                  << std::endl;
        user.set_enabled(false);
        gdb.update_user(user);
        std::cout << "...success." << std::endl;
    }
    else {
        std::cout << "No action needed for user '"
                  << user.username() << "'" << std::endl;
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
        << "  --show                Show details of a user\n"
        << "  --enable=<yes|no>     Enabled or disable a user\n"
        << "  --id=<id>             Specify a user by ID\n"
        << "  --name=<name>         Specify a user by username\n";
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

