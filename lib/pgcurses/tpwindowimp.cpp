/*!
 * \file            tpwindowimp.cpp
 * \brief           Implementation of generic curses window impl class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "tpwindowimp.h"
#include "tpexception.h"

using namespace pgcurses;

TPWindowImp::TPWindowImp(const Point origin, const Size sz) :
    m_win{nullptr},
    m_origin{origin},
    m_size{sz}
{
    m_win = newwin(m_size.height, m_size.width, m_origin.y, m_origin.x);
    if ( !m_win ) {
        throw TPException("Couldn't initialize window");
    }
}

TPWindowImp::TPWindowImp(const Rectangle rect) :
    m_win{nullptr},
    m_origin{rect.origin},
    m_size{rect.size}
{
    m_win = newwin(m_size.height, m_size.width, m_origin.y, m_origin.x);
    if ( !m_win ) {
        throw TPException("Couldn't initialize window");
    }
}

TPWindowImp::~TPWindowImp() {
    delwin(m_win);
}

void TPWindowImp::write_char(const char ch)
{
    waddch(m_win, ch);
}

void TPWindowImp::write_char(const char ch, const Point pt)
{
    mvwaddch(m_win, pt.y, pt.x, ch);
}

void TPWindowImp::write_str(const std::string& s)
{
    waddstr(m_win, s.c_str());
}

void TPWindowImp::write_str(const std::string& s, const Point pt)
{
    mvwaddstr(m_win, pt.y, pt.x, s.c_str());
}

void TPWindowImp::draw()
{
    wrefresh(m_win);
}

void TPWindowImp::redraw()
{
    touchwin(m_win);
    wrefresh(m_win);
}

