/*!
 * \file            gltermmainwin.cpp
 * \brief           Implementation of gl_term main window class
 * \details         Implementation of gl_term main window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sstream>
#include <unistd.h>
#include "gltermmainwin.h"

using namespace pgcurses;

void GLTermMainWin::show() {
    write_str("Sample Terminal Program", Point{28, 5});
    write_str("=======================", Point{28, 6});
    write_str("Press 'Q' to quit", Point{30, 8});
    draw();
    Key key;
    do {
        key = get_key();
        write_str("You pressed: ", Point{28, 10});
        switch ( key.value ) {
            case Key::KeyValue::Enter:
                write_str("<ENTER>    ", Point{41,10});
                break;

            case Key::KeyValue::Tab:
                write_str("<TAB>      ", Point{41,10});
                break;

            case Key::KeyValue::Backspace:
                write_str("<BACKSPACE>", Point{41,10});
                break;

            case Key::KeyValue::Up:
                write_str("<UP>       ", Point{41,10});
                break;

            case Key::KeyValue::Left:
                write_str("<LEFT>     ", Point{41,10});
                break;

            case Key::KeyValue::Down:
                write_str("<DOWN>     ", Point{41,10});
                break;

            case Key::KeyValue::Right:
                write_str("<RIGHT>    ", Point{41,10});
                break;

            case Key::KeyValue::Value:
                std::ostringstream ss;
                ss << "'" << static_cast<char>(key.char_value) << "'        ";
                write_str(ss.str(), Point{41,10});
                break;

        }
    } while ( key.char_value != 'Q' && key.char_value != 'q' );
}

