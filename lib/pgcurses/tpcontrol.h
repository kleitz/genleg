/*!
 * \file            tpcontrol.h
 * \brief           Interface to abstract control base class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_PGCURSES_TPCONTROL_H
#define PG_PGCURSES_TPCONTROL_H

#include "tpgentypes.h"
#include "tpfunctions.h"
#include "tpwindow.h"

namespace pgcurses {

/*!
 * \brief               Abstract control base class
 * \ingroup             pgcurses
 */
class TPControl : public TPWindow {
    public:
        
        /*!
         * \brief           Constructor.
         * \throws          TPException on failure.
         */
        TPControl (Rectangle rect) :
            TPWindow{rect} {};

        /*!  Destructor  */
        virtual ~TPControl () {};

        /*!  Deleted copy constructor  */
        TPControl(const TPControl& tp) = delete;

        /*!  Deleted move constructor  */
        TPControl(TPControl&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TPControl& operator=(const TPControl& tp) = delete;

        /*!  Deleted move assignment operator  */
        TPControl& operator=(TPControl&& tp) = delete;

};              //  class TPControl

}               //  namespace pgcurses

#endif          //  PG_PGCURSES_TPCONTROL_H

