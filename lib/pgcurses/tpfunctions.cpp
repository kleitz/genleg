/*!
 * \file            tpfunctions.cpp
 * \brief           Implementation of terminal functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sys/ioctl.h>
#include "tpexception.h"
#include "tpfunctions.h"

using namespace pgcurses;

/*!
 * \brief               Returns the terminal size.
 * \returns             The terminal size.
 * \throws              TPSystemException on failure.
 */
Size pgcurses::terminal_size() {
    struct winsize ws;
    if ( ioctl(0, TIOCGWINSZ, &ws) == -1 ) {
        throw TPSystemException("ioctl() failed getting terminal size");
    }
    return Size{ws.ws_col, ws.ws_row};
}

