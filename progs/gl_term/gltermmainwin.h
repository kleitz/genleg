/*!
 * \file            gltermmainwin.h
 * \brief           Interface to gl_term main window class
 * \details         Interface to gl_term main window class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_GENERAL_LEDGER_GLTERMMAINWIN_H
#define PG_GENERAL_LEDGER_GLTERMMAINWIN_H

#include "pgcurses/pgcurses.h"
 
/*!
 * \brief           gl_term main window class.
 * \ingroup         gl_term
 */
class GLTermMainWin : public pgcurses::TPMainWindow {
    public:
        virtual void show();

};              //  class GLTermMainWin

#endif          //  PG_GENERAL_LEDGER_GLTERMMAINWIN_H
