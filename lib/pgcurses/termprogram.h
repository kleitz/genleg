/*!
 * \file            termprogram.h
 * \brief           Interface to main terminal program class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_CURSES_TERM_PROGRAM_H
#define PG_CURSES_TERM_PROGRAM_H

#include <memory>
#include "tpgentypes.h"

namespace pgcurses {

class TermProgramImp;

/*!
 * \brief               Main terminal program class
 * \ingroup             pgcurses
 */
class TermProgram {
    public:

        /*!  Constructor  */
        TermProgram ();

        /*!  Destructor  */
        ~TermProgram ();

        /*!  Deleted copy constructor  */
        TermProgram(const TermProgram& tp) = delete;

        /*!  Deleted move constructor  */
        TermProgram(TermProgram&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TermProgram& operator=(const TermProgram& tp) = delete;

        /*!  Deleted move assignment operator  */
        TermProgram& operator=(TermProgram&& tp) = delete;

        /*!
         * \brief               Sleeps for a period of time.
         * \param secs          The number of seconds to sleep.
         */
        void sleep(const unsigned int secs) const;

        /*!
         * \brief               Returns the main terminal dimensions.
         * \returns             The main terminal dimensions.
         */
        Size terminal_size() const;

    private:

        /*!  Pointer to implementation  */
        std::unique_ptr<TermProgramImp> m_imp;

};              //  class TermProgram

}               //  namespace pgcurses

#endif          //  PG_CURSES_TERM_PROGRAM_H

