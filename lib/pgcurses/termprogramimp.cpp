/*!
 * \file            termprogramimp.cpp
 * \brief           Implementation of main terminal program implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <unistd.h>
#include <sys/ioctl.h>
#include <curses.h>
#include "termprogramimp.h"
#include "tpexception.h"

using namespace pgcurses;

TermProgramImp::TermProgramImp() :
    m_mainwin{nullptr},
    m_old_cursor{0},
    m_termsize{0, 0}
{
    struct winsize ws;
    if ( ioctl(0, TIOCGWINSZ, &ws) == -1 ) {
        throw TPException("Couldn't get terminal size");
    }
    m_termsize.width = ws.ws_col;
    m_termsize.height = ws.ws_row;

    m_mainwin = initscr();
    if ( !m_mainwin ) {
        throw TPException("Couldn't initialize main curses window");
    }
    
    noecho();
    keypad(m_mainwin, true);
    m_old_cursor = curs_set(0);
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

Size TermProgramImp::terminal_size() const
{
    return m_termsize;
}

void TermProgramImp::sleep(const unsigned int secs) const
{
    ::sleep(secs);
}

