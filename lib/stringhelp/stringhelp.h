/*!
 * \file            stringhelp.h
 * \brief           Interface to string helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_STRINGHELP_STRINGHELP_H
#define PG_STRINGHELP_STRINGHELP_H

#include <string>
#include <vector>

namespace pgstring {

/*!
 * \brief               Trims leading whitespace from a string.
 * \ingroup             helpers
 * \param s             The string to trim.
 * \returns             The trimmed string.
 */
std::string& trim_front(std::string& s);

/*!
 * \brief               Trims trailing whitespace from a string.
 * \ingroup             helpers
 * \param s             The string to trim.
 * \returns             The trimmed string.
 */
std::string& trim_back(std::string& s);

/*!
 * \brief               Trims leading and trailing whitespace from a string.
 * \ingroup             helpers
 * \param s             The string to trim.
 * \returns             The trimmed string.
 */
std::string& trim(std::string& s);

/*!
 * \brief               Splits a delimited string into tokens.
 * \ingroup             helpers
 * \param s             The string to split.
 * \param delim         The delimiter character on which to split.
 * \returns             A vector of tokens.
 */
std::vector<std::string> split(const std::string& s, const char delim);

}           //  namespace pgstring

#endif      //  PG_STRINGHELP_STRINGHELP_H

