/*!
 * \file            stringhelp.cpp
 * \brief           Implementation of string helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>

#include "stringhelp.h"

using namespace pgstring;

std::string& pgstring::trim_front(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string& pgstring::trim_back(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string& pgstring::trim(std::string& s) {
    return trim_front(trim_back(s));
}

std::vector<std::string> pgstring::split(const std::string& s,
                                         const char delim) {
    std::stringstream ss(s);
    std::string token;
    std::vector<std::string> tokens;

    while ( std::getline(ss, token, delim) ) {
        tokens.push_back(token);
    }

    return tokens;
}

