/*!
 * \file            dbconnimp.h
 * \brief           Interface to abstract database implementation base class
 * \details         Interface to abstract database implementation base class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DBCONNIMP_H
#define PG_DATABASE_DBCONNIMP_H

#include <string>

#include "data_structures.h"

namespace gldb {

class DBConnImp {
    public:
        DBConnImp () {};
        virtual ~DBConnImp () {};
        virtual Table select(std::string query) = 0;

};              //  class DBConnImp

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONNIMP_H

