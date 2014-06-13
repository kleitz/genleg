/*!
 * \file            config.cpp
 * \brief           Implementation of program configurations class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <fstream>

#include "config.h"
#include "stringhelp/stringhelp.h"

using namespace genleg;
using namespace pgstring;
using ArgPair = std::pair<std::string, enum Argument>;

/*!
 * \brief           Constructor for Config class
 */
Config::Config() : m_opts_set(), m_opts_supp() {
}


/*!
 * \brief           Destructor for Config class
 */
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
        throw ConfigOptionNotSet();
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
            if ( line == "" || line[0] == '#' ) {
                continue;
            }

            std::vector<std::string> tokens = split(line, '=');
            if ( tokens.size() != 2 ) {
                throw ConfigBadConfigFile();
            }
            const std::string& key = trim_back(tokens[0]);
            const std::string& value = trim_front(tokens[1]);

            m_opts_set[key] = value;
        }
        ifs.close();
    }
    else {
        throw ConfigCouldNotOpenFile();
    }
}

