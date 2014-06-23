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

}               //  namespace pgcurses

#endif          //  PG_CURSES_TPEXCEPTION_H
