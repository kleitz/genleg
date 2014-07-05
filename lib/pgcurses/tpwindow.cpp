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

TPWindow::~TPWindow()
{
}

Key TPWindow::get_key()
{
    const int kv = m_imp->get_char();
    switch ( kv ) {
        case '\n':
        case KEY_ENTER:
            return Key(Key::KeyValue::Enter);

        case KEY_BACKSPACE:
        case KEY_DC:
        case 127:
            return Key(Key::KeyValue::Backspace);

        case '\t':
            return Key(Key::KeyValue::Tab);

        case KEY_UP:
            return Key(Key::KeyValue::Up);

        case KEY_LEFT:
            return Key(Key::KeyValue::Left);

        case KEY_DOWN:
            return Key(Key::KeyValue::Down);

        case KEY_RIGHT:
            return Key(Key::KeyValue::Right);

        default:
            return Key(Key::KeyValue::Value, kv);
    }
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

