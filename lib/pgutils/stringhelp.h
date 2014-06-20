/*!
 * \file            stringhelp.h
 * \brief           Interface to string helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_UTILS_STRINGHELP_STRINGHELP_H
#define PG_UTILS_STRINGHELP_STRINGHELP_H

#include <string>
#include <vector>

namespace pgutils {

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

/*!
 * \brief               Splits a delimited string into tokens.
 * \ingroup             helpers
 * \param vec           The vector into which to add the tokens.
 * \param s             The string to split.
 * \param delim         The delimiter character on which to split.
 * \returns             A reference to \c vec.
 */
std::vector<std::string>& split(std::vector<std::string>& vec,
        const std::string& s, const char delim);

/*!
 * \brief               Gets the next content line from a stream.
 * \details             A "content line" is defined as a line which,
 * after being trimmed of trailing and leading whitespace, is not empty,
 * and does not start with a '#' character (indicating a comment line).
 * \param ifs           The input stream.
 * \param s             The string in which to store the line.
 * \returns             `true` if there is a next content line, `false`
 * otherwise.
 */
bool next_content_line(std::istream& ifs, std::string& s);

/*!
 * \brief               Populates a vector of content lines from a stream.
 * \param vec           The vector to populate.
 * \param ifs           The input stream.
 * \returns             A reference to \c vec.
 */
std::vector<std::string>&
content_lines(std::vector<std::string>& vec, std::istream& ifs);

/*!
 * \brief               Populates a vector of vectors of fields from a stream.
 * \param vec           The vector to populate.
 * \param ifs           The input stream.
 * \param delim         The delimiter character to split each content line.
 * \returns             A reference to \c vec.
 */
std::vector<std::vector<std::string>>&
split_lines(std::vector<std::vector<std::string>>& vec,
        std::istream& ifs, const char delim);

/*!
 * \brief               Joins a vector of strings into a delimited line.
 * \details             The function is the opposite of \c split.
 * \param vec           The vector containing the strings.
 * \param s             The string in which to store the line.
 * \param delim         The delimiter character to be used to delimit the
 * fields.
 * \returns             A reference to \c s.
 */
std::string& join(const std::vector<std::string>& vec,
        std::string& s, const char delim);

/*!
 * \brief               Replaces a substring with another string.
 * \param str           The string containing the substring to replace.
 * \param from          The substring to replace.
 * \param to            The string with which to replace the substring.
 * \returns             `true` if a replacement was made, `false` otherwise.
 */
bool replace(std::string& str, const std::string& from, const std::string& to);

}           //  namespace pgstring

#endif      //  PG_UTILS_STRINGHELP_STRINGHELP_H

