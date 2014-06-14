/*!
 * \file            config.h
 * \brief           Interface to program configurations class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_CONFIGURATION_H
#define PG_GENERAL_LEDGER_CONFIGURATION_H

#include <map>
#include <list>
#include <string>
#include <stdexcept>

namespace genleg {

/*!
 * \brief       Enumeration class for option argument specifications
 * \ingroup     config
 */
enum class Argument {
    NO_ARG,         /*!<  No argument accepted              */
    OPT_ARG,        /*!<  Argument optionally accepted      */
    REQ_ARG         /*!<  Argument required                 */
};

/*!
 * \brief       Configuration module exception base class
 * \ingroup     config
 */
class ConfigException : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit ConfigException(const std::string& msg) :
            std::runtime_error(msg) {};
};

/*!
 * \brief       Exception class for option not set
 * \ingroup     config
 */
class ConfigOptionNotSet : public ConfigException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit ConfigOptionNotSet(const std::string& msg) :
            ConfigException(msg) {};
};

/*!
 * \brief       Exception class for bad provided option
 * \ingroup     config
 */
class ConfigBadOption : public ConfigException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit ConfigBadOption(const std::string& msg) :
            ConfigException(msg) {};
};

/*!
 * \brief       Exception class for when conf file cannot be opened
 * \ingroup     config
 */
class ConfigCouldNotOpenFile : public ConfigException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit ConfigCouldNotOpenFile(const std::string& msg) :
            ConfigException(msg) {};
};

/*!
 * \brief       Exception class for badly formed configuration file
 * \ingroup     config
 */
class ConfigBadConfigFile : public ConfigException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit ConfigBadConfigFile(const std::string& msg) :
            ConfigException(msg) {};
};

/*!
 * \brief       Configuration options class
 * \ingroup     config
 */
class Config {
    public:
        /*!  Constructor  */
        Config ();

        /*!  Destructor  */
        ~Config ();

        /*!
         * \brief           Adds a supported command line option.
         * \param option    The name of the option.
         * \param arg       The argument specification for the option.
         */
        void add_cmdline_option(const std::string option,
                                const enum Argument arg);

        /*!
         * \brief           Populates options from the command line.
         * \param argc      `argc` supplied to `main()`.
         * \param argv      `argv` supplied to `main()`.
         * \throws          ConfigBadOption If an unsupported option is
         * specified, or if a required argument is missing, or if an
         * unexpected argument is found.
         */
        void populate_from_cmdline(const int argc, char * const * argv);

        /*!
         * \brief           Populates options from a configuration file.
         * \param filename  The name of the configuration file.
         * \throws          ConfigCouldNotOpenFile If the configuration
         * file cannot be opened.
         * \throws          ConfigBadConfigFile If the
         * configuration file is badly formed.
         */
        void populate_from_file(const std::string filename);

        /*!
         * \brief           Checks is an option is set.
         * \param option    The name of the option to check.
         * \returns         `true` if the option has been set, `false`
         * if it has not.
         */
        bool is_set(const std::string option) const;

        /*!
         * \brief           operator[] overload.
         * \details         Retrieves the value of a set option.
         * \param option    The name of the option.
         * \returns         The value of the option.
         * \throws          ConfigOptionNotSet If the named option has
         * not been set.
         */
        const std::string& operator[](const std::string& option) const;

    private:
        /*!  Map of options which have been set  */
        std::map<std::string, std::string> m_opts_set;

        /*!  List of options which are supported  */
        std::list<std::pair<std::string, enum Argument> > m_opts_supp;

};              //  class Config

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_CONFIGURATION_H

