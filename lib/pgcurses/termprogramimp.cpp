/*!
 * \file            termprogramimp.cpp
 * \brief           Implementation of main terminal program implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <unistd.h>
#include <curses.h>
#include "termprogramimp.h"
#include "tpexception.h"
#include "tpfunctions.h"

using namespace pgcurses;

namespace {

/*!
 * \brief           Interface to initscr() call.
 * \details         Throws exception on failure, for use in constructor.
 * \returns         A pointer to a valid WINDOW struct.
 * \throws          TPException on failure.
 */
WINDOW * curses_init()
{
    WINDOW * win = initscr();
    if ( !win ) {
        throw TPCursesException("initscr() failed initializing curses");
    }
    return win;
}

}           //  namespace

TermProgramImp::TermProgramImp() :
    m_termsize{::terminal_size()},
    m_mainwin{::curses_init()},
    m_old_cursor{curs_set(0)},
    m_win{nullptr}
{
    noecho();
    keypad(m_mainwin, true);
    refresh();
}

TermProgramImp::~TermProgramImp()
{
    delwin(m_mainwin);
    m_mainwin = nullptr;
    curs_set(m_old_cursor);
    endwin();
    refresh();
}

void TermProgramImp::set_main_window(std::unique_ptr<TPMainWindow> mainwin)
{
    m_win = std::move(mainwin);
}

void TermProgramImp::run() {
    if ( !m_win ) {
        throw TPException("run() failed - Main window not set");
    }
    m_win->show();
}

void TermProgramImp::sleep(const unsigned int secs) const
{
    ::sleep(secs);
}

