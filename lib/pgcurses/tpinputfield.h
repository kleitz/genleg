/*!
 * \file            tpinputfield.h
 * \brief           Interface to input field class.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_PGCURSES_TPINPUTFIELD_H
#define PG_PGCURSES_TPINPUTFIELD_H

#include "tpgentypes.h"
#include "tpfunctions.h"
#include "tpcontrol.h"

namespace pgcurses {

/*!
 * \brief               Abstract control base class
 * \ingroup             pgcurses
 */
class TPInputField : public TPControl {
    public:
        
        /*!
         * \brief           Constructor.
         * \throws          TPException on failure.
         */
        TPInputField (Rectangle rect) :
            TPControl{rect} {};

        /*!  Destructor  */
        virtual ~TPInputField () {};

        /*!  Deleted copy constructor  */
        TPInputField(const TPInputField& tp) = delete;

        /*!  Deleted move constructor  */
        TPInputField(TPInputField&& tp) = delete;

        /*!  Deleted copy assignment operator  */
        TPInputField& operator=(const TPInputField& tp) = delete;

        /*!  Deleted move assignment operator  */
        TPInputField& operator=(TPInputField&& tp) = delete;

};              //  class TPInputField

}               //  namespace pgcurses

#endif          //  PG_PGCURSES_TPINPUTFIELD_H

