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

using namespace pgutils;

std::string& pgutils::trim_front(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string& pgutils::trim_back(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string& pgutils::trim(std::string& s)
{
    return trim_front(trim_back(s));
}

std::vector<std::string> pgutils::split(const std::string& s,
                                         const char delim)
{
    std::vector<std::string> vec;
    return split(vec, s, delim);
}

std::vector<std::string>& pgutils::split(std::vector<std::string>& vec,
        const std::string& s, const char delim)
{
    std::stringstream ss(s);
    std::string token;

    while ( std::getline(ss, token, delim) ) {
        vec.push_back(token);
    }

    return vec;
}

bool pgutils::next_content_line(std::istream& ifs,
        std::string& s)
{
    while ( std::getline(ifs, s) ) {
        trim(s);
        if ( s != "" && s[0] != '#' ) {
            return true;
        }
    }
    return false;
}

std::vector<std::string>&
pgutils::content_lines(std::vector<std::string>& vec,std::istream& ifs)
{
    std::string s;
    while ( next_content_line(ifs, s) ) {
        vec.push_back(s);
    }
    return vec;
}

std::vector<std::vector<std::string>>&
pgutils::split_lines(std::vector<std::vector<std::string>>& vec,
        std::istream& ifs, const char delim)
{
    std::string s;
    while ( next_content_line(ifs, s) ) {
        std::vector<std::string> tokens;
        vec.push_back(split(tokens, s, delim));
    }
    return vec;
}

std::string& pgutils::join(const std::vector<std::string>& vec,
        std::string& s, const char delim)
{
    std::ostringstream ss;
    for ( size_t i = 0; i < vec.size(); ++i ) {
        if ( i != 0 ) {
            ss << delim;
        }
        ss << vec[i];
    }
    s = ss.str();
    return s; 
}
 
bool pgutils::replace(std::string& str,
                       const std::string& from,
                       const std::string& to)
{
    const size_t start_pos = str.find(from);
    if ( start_pos == std::string::npos ) {
        return false;
    }
    str.replace(start_pos, from.length(), to);
    return true;
}

