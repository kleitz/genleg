/*!
 * \file            tpexception.h
 * \brief           Interface to terminal program exception class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_CURSES_TPEXCEPTION_H
#define PG_CURSES_TPEXCEPTION_H

#include <stdexcept>

namespace pgcurses {

/*!
 * \brief           Base terminal program exception class.
 * \ingroup         pgcurses
 */
class TPException : public std::runtime_error {
    public:

        /*!
         * \brief           Constructor
         * \param msg       Error message
         */
        TPException (const std::string& msg) :
            std::runtime_error(msg) {};

};              //  class TPException

/*!
 * \brief           Terminal program curses exception class.
 * \ingroup         pgcurses
 */
class TPCursesException : public TPException {
    public:

        /*!
         * \brief           Constructor
         * \param msg       Error message
         */
        TPCursesException (const std::string& msg) :
            TPException(msg) {};

};              //  class TPCursesException

/*!
 * \brief           Terminal program system exception class.
 * \ingroup         pgcurses
 */
class TPSystemException : public TPException {
    public:

        /*!
         * \brief           Constructor
         * \param msg       Error message
         */
        TPSystemException (const std::string& msg) :
            TPException(msg) {};

};              //  class TPSystemException

}               //  namespace pgcurses

#endif          //  PG_CURSES_TPEXCEPTION_H

