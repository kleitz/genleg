/*!
 * \file            tpwindowimp.cpp
 * \brief           Implementation of generic curses window impl class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>
#include <curses.h>
#include "tpwindowimp.h"
#include "tpexception.h"

using namespace pgcurses;

namespace {

/*!
 * \brief           Makes a new curses window.
 * \details         Throws exception on failure.
 * \param rect      The dimensions of the new window.
 * \throws          TPCursesException on failure.
 */
WINDOW * make_new_window(const Rectangle rect)
{
    std::cerr << "Entering make_new_window..." << std::endl;
    std::cerr << "Size: " << rect.size.width << ", " << rect.size.height
              << std::endl
              << "Origin: " << rect.origin.x << ", " << rect.origin.y
              << std::endl;
    WINDOW * win = newwin(rect.size.height, rect.size.width,
                          rect.origin.y, rect.origin.x);

    if ( !win ) {
        throw TPCursesException("newwin() failed initializing TPWindow");
    }
    std::cerr << "Leaving make_new_window..." << std::endl;
    keypad(win, true);
    return win;
}

}           //  namespace

TPWindowImp::TPWindowImp(const Point origin, const Size sz) :
    m_win{::make_new_window(Rectangle{sz, origin})},
    m_origin{origin},
    m_size{sz}
{}

TPWindowImp::TPWindowImp(const Rectangle rect) :
    m_win{::make_new_window(rect)},
    m_origin{rect.origin},
    m_size{rect.size}
{}

TPWindowImp::~TPWindowImp()
{
    delwin(m_win);
}

int TPWindowImp::get_char()
{
    return wgetch(m_win);
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

