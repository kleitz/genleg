/*!
 * \file            gltermmainwin.cpp
 * \brief           Implementation of gl_term main window class
 * \details         Implementation of gl_term main window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <unistd.h>
#include "gltermmainwin.h"

using namespace pgcurses;

void GLTermMainWin::show() {
    write_str("Sample Terminal Program", Point{28, 5});
    write_str("=======================", Point{28, 6});
    write_str("Press 'Q' to quit", Point{30, 8});
    draw();
    int ch;
    do {
        ch = get_char();
    } while ( ch != 'Q' && ch != 'q' );
}

