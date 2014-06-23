/*!
 * \file            termprogramimp.h
 * \brief           Interface to main terminal program implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_CURSES_TERM_PROGRAM_IMP_H
#define PG_CURSES_TERM_PROGRAM_IMP_H

#include <curses.h>
#include "tpgentypes.h"

namespace pgcurses {

/*!
 * \brief               Main terminal program implementation class
 * \ingroup             pgcurses
 */
class TermProgramImp {
    public:

        /*!  Constructor  */
        TermProgramImp ();

        /*!  Destructor  */
        ~TermProgramImp ();

        /*!  Deleted copy constructor  */
        TermProgramImp(const TermProgramImp& tp) = delete;

        /*!  Deleted move constructor  */
        TermProgramImp(TermProgramImp&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TermProgramImp& operator=(const TermProgramImp& tp) = delete;

        /*!  Deleted move assignment operator  */
        TermProgramImp& operator=(TermProgramImp&& tp) = delete;

        /*!
         * \brief               Sleep for a period of time.
         * \param secs          The number of seconds to sleep.
         */
        void sleep(const unsigned int secs) const;

        /*!
         * \brief               Returns the main terminal dimensions.
         * \returns             The main terminal dimensions.
         */
        Size terminal_size() const;

    private:

        /*!  Pointer to main window  */
        WINDOW * m_mainwin;

        /*!  Value of old cursor  */
        int m_old_cursor;

        /*!  Terminal size  */
        Size m_termsize;

};              //  class TermProgramImp

}               //  namespace pgcurses

#endif          //  PG_CURSES_TERM_PROGRAM_IMP_H

