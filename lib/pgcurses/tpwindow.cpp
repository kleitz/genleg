/*!
 * \file            tpwindow.cpp
 * \brief           Implementation of generic curses window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "tpwindow.h"
#include "tpwindowimp.h"

using namespace pgcurses;

TPWindow::TPWindow(const Point origin, const Size sz) :
    m_imp{std::unique_ptr<TPWindowImp>(new TPWindowImp{origin, sz})}
{
}

TPWindow::TPWindow(const Rectangle rect) :
    m_imp{std::unique_ptr<TPWindowImp>(new TPWindowImp{rect})}
{
}

TPWindow::~TPWindow() {
}

void TPWindow::write_char(const char ch)
{
    m_imp->write_char(ch);
}

void TPWindow::write_char(const char ch, const Point pt)
{
    m_imp->write_char(ch, pt);
}

void TPWindow::write_str(const std::string& s)
{
    m_imp->write_str(s);
}

void TPWindow::write_str(const std::string& s, const Point pt)
{
    m_imp->write_str(s, pt);
}

void TPWindow::draw()
{
    m_imp->draw();
}

void TPWindow::redraw()
{
    m_imp->redraw();
}

