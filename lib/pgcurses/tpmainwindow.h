/*!
 * \file            tpmainwindow.h
 * \brief           Interface to generic curses main window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_PGCURSES_TPMAINWINDOW_H
#define PG_PGCURSES_TPMAINWINDOW_H

#include "tpgentypes.h"
#include "tpfunctions.h"
#include "tpwindow.h"

namespace pgcurses {

/*!
 * \brief               Generic main window class
 * \ingroup             pgcurses
 */
class TPMainWindow : public TPWindow {
    public:
        
        /*!
         * \brief           Constructor.
         * \throws          TPException on failure.
         */
        TPMainWindow () :
            TPWindow{Rectangle{terminal_size()}} {};

        /*!  Destructor  */
        virtual ~TPMainWindow () {};

        /*!  Show function  */
        virtual void show() { draw(); }

        /*!  Deleted copy constructor  */
        TPMainWindow(const TPMainWindow& tp) = delete;

        /*!  Deleted move constructor  */
        TPMainWindow(TPMainWindow&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TPMainWindow& operator=(const TPMainWindow& tp) = delete;

        /*!  Deleted move assignment operator  */
        TPMainWindow& operator=(TPMainWindow&& tp) = delete;

};              //  class TPMainWindow

}               //  namespace pgcurses

#endif          //  PG_PGCURSES_TPMAINWINDOW_H

