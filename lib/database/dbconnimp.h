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
         * \brief           Runs an SQL query.
         * \param sql_query The query.
         */
        virtual void query(const std::string& sql_query) = 0;

        /*!
         * \brief           Runs an SQL SELECT query.
         * \param query     The query.
         * \returns         A Table object containing the results.
         */
        virtual Table select(const std::string& query) = 0;

        /*!
         * \brief           Begins a transaction.
         */
        virtual void begin_transaction() = 0;

        /*!
         * \brief           Rolls back a transaction.
         */
        virtual void rollback_transaction() = 0;

        /*!
         * \brief           Commits a transaction.
         */
        virtual void commit_transaction() = 0;

        /*!
         * \brief           Returns the last auto incremented value.
         * \returns         The last auto incremented value.
         */
        virtual unsigned long long last_auto_increment() = 0;

};              //  class DBConnImp

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONNIMP_H

