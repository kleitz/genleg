/*!
 * \file            config.h
 * \brief           Interface to program configurations class
 * \details         Interface to program configurations class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_GENERAL_LEDGER_CONFIGURATION_H
#define PG_GENERAL_LEDGER_CONFIGURATION_H

#include <map>
#include <list>
#include <string>

namespace genleg {

enum class Argument {NO_ARG, OPT_ARG, REQ_ARG};

class ConfigOptionNotSet : public std::exception {};
class ConfigBadOption : public std::exception {};
class ConfigCouldNotOpenFile : public std::exception {};
class ConfigBadConfigFile : public std::exception {};

class Config {
    public:
        Config ();
        ~Config ();
        void add_cmdline_option(const std::string option,
                                const enum Argument arg);
        void populate_from_cmdline(const int argc, char * const * argv);
        void populate_from_file(const std::string filename);
        bool is_set(const std::string option) const;
        const std::string& operator[](const std::string& option) const;

    private:
        std::map<std::string, std::string> m_opts_set;
        std::list<std::pair<std::string, enum Argument> > m_opts_supp;

};              //  class Config

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_CONFIGURATION_H

