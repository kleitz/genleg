/*!
 * \file            tpwindowimp.h
 * \brief           Interface to generic curses window impl class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_PGCURSES_TPWINDOWIMP_H
#define PG_PGCURSES_TPWINDOWIMP_H

#include <string>
#include <curses.h>
#include "tpgentypes.h"

namespace pgcurses {

/*!
 * \brief               Terminal program window implementation class.
 * \ingroup             pgcurses
 */
class TPWindowImp {
    public:

        /*!
         * \brief           Constructor.
         * \param origin    The new window's origin.
         * \param sz        The new window's size.
         * \throws          TPException on failure.
         */
        TPWindowImp (const Point origin, const Size sz);

        /*!
         * \brief           Constructor.
         * \param rect      The new window's rectangle.
         * \throws          TPException on failure.
         */
        TPWindowImp (const Rectangle rect);

        /*!  Destructor  */
        ~TPWindowImp ();

        /*!  Deleted copy constructor  */
        TPWindowImp(const TPWindowImp& tp) = delete;
        
        /*!  Deleted move constructor  */
        TPWindowImp(TPWindowImp&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TPWindowImp& operator=(const TPWindowImp& tp) = delete;

        /*!  Deleted move assignment operator  */
        TPWindowImp& operator=(TPWindowImp&& tp) = delete;

        /*!
         * \brief           Gets a character.
         * \returns         The character.
         */
        int get_char();

        /*!
         * \brief           Writes a character to the current position.
         * \param ch        The character to write.
         */
        void write_char(const char ch);

        /*!
         * \brief           Writes a character to a specified position.
         * \param ch        The character to write.
         * \param pt        The point at which to write.
         */
        void write_char(const char ch, const Point pt);

        /*!
         * \brief           Writes a string to the current position.
         * \param s         The string to write.
         */
        void write_str(const std::string& s);

        /*!
         * \brief           Writes a string to a specified position.
         * \param s         The string to write.
         * \param pt        The point at which to write.
         */
        void write_str(const std::string& s, const Point pt);

        /*!
         * \brief           Draws the window.
         */
        void draw();

        /*!
         * \brief           Forces a redraw of the window.
         */
        void redraw();

    private:

        /*!  Pointer to curses WINDOW  */
        WINDOW * m_win;

        /*!  The window's origin  */
        Point m_origin;

        /*!  The window's size  */
        Size m_size;

};              //  class TPWindowImp

}               //  namespace pgcurses

#endif          //  PG_PGCURSES_TPWINDOWIMP_H

