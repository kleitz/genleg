/*!
 * \file            config.cpp
 * \brief           Implementation of program configurations class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <fstream>

#include "config.h"
#include "pgutils/pgutils.h"

using namespace genleg;
using namespace pgutils;
using ArgPair = std::pair<std::string, enum Argument>;

Config::Config() : m_opts_set(), m_opts_supp() {
}

Config::~Config() {
}

void Config::add_cmdline_option(const std::string option,
                                const enum Argument arg) {
    m_opts_supp.push_back(ArgPair(option, arg));
}

bool Config::is_set(const std::string option) const {
    return m_opts_set.count(option) ? true : false;
}

const std::string& Config::operator[](const std::string& option) const {
    if ( !is_set(option) ) {
        throw ConfigOptionNotSet(option);
    }
    return (m_opts_set.find(option))->second;
}

void Config::populate_from_file(const std::string filename) {
    std::ifstream ifs;
    ifs.open(filename);

    if ( ifs.is_open() ) {
        std::string line;

        while ( std::getline(ifs, line) ) {
            trim(line);

            /*  Ignore blank lines and comment lines  */

            if ( line == "" || line[0] == '#' ) {
                continue;
            }

            /*  Split line and populate vector  */

            std::vector<std::string> tokens = split(line, '=');
            if ( tokens.size() != 2 ) {

                /*  Badly formed line if not
                 *  exactly one delimiter character  */

                throw ConfigBadConfigFile(filename);
            }

            /*  Store key and value  */

            const std::string& key = trim_back(tokens[0]);
            const std::string& value = trim_front(tokens[1]);
            m_opts_set[key] = value;
        }

        ifs.close();
    }
    else {
        throw ConfigCouldNotOpenFile(filename);
    }
}

