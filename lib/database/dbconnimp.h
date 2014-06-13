/*!
 * \file            dbconnimp.h
 * \brief           Interface to abstract database implementation base class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DBCONNIMP_H
#define PG_DATABASE_DBCONNIMP_H

#include <string>

#include "data_structures.h"

namespace gldb {

/*!
 * \brief       Abstract database implementation base class
 * \ingroup     database
 */
class DBConnImp {
    public:
        /*!  Constructor  */
        DBConnImp () {};

        /*!  Destructor  */
        virtual ~DBConnImp () {};

        /*!
         * \brief           Runs an SQL SELECT query.
         * \param query     The query.
         * \returns         A Table object containing the results.
         */
        virtual Table select(std::string query) = 0;

};              //  class DBConnImp

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONNIMP_H

