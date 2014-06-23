/*!
 * \file            tpwindow.h
 * \brief           Interface to generic curses window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_PGCURSES_TPWINDOW_H
#define PG_PGCURSES_TPWINDOW_H

#include <string>
#include <memory>
#include "tpgentypes.h"

namespace pgcurses {

class TPWindowImp;

/*!
 * \brief               Generic window class
 * \ingroup             pgcurses
 */
class TPWindow {
    public:
        
        /*!
         * \brief           Constructor.
         * \param origin    The new window's origin.
         * \param sz        The new window's size.
         * \throws          TPException on failure.
         */
        TPWindow (const Point origin, const Size sz);

        /*!
         * \brief           Constructor.
         * \param rect      The new window's rectangle.
         * \throws          TPException on failure.
         */
        TPWindow (const Rectangle rect);

        /*!  Destructor  */
        virtual ~TPWindow ();

        /*!  Deleted copy constructor  */
        TPWindow(const TPWindow& tp) = delete;

        /*!  Deleted move constructor  */
        TPWindow(TPWindow&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TPWindow& operator=(const TPWindow& tp) = delete;

        /*!  Deleted move assignment operator  */
        TPWindow& operator=(TPWindow&& tp) = delete;

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
        
        /*!  Pointer to implementation  */
        std::unique_ptr<TPWindowImp> m_imp;

};              //  class TPWindow

}               //  namespace pgcurses

#endif          //  PG_PGCURSES_TPWINDOW_H

