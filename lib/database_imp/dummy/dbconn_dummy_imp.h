/*!
 * \file            dbconn_dummy_imp.h
 * \brief           Interface to dummy database connection implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBCONNDUMMYIMP_H
#define PG_GENERAL_LEDGER_DATABASE_DBCONNDUMMYIMP_H

#include <string>

#include "database/database.h"

namespace gldb {

/*!
 * \brief       Dummy database implementation class
 * \ingroup     database
 */
class DBConnDummy : public DBConnImp {
    public:
        /*!
         * \brief           Constructor.
         * \param database  The name of the Dummy database.
         * \param hostname  The hostname of the server.
         * \param username  The username to log into the database.
         * \param password  The password to log into the database.
         */
        DBConnDummy (const std::string database,
                const std::string hostname, const std::string username,
                const std::string password);

        /*!  Deleted copy constructor  */
        DBConnDummy (const DBConnDummy&) = delete;

        /*!  Destructor  */
        virtual ~DBConnDummy ();

        /*!  Deleted assignment operator  */
        DBConnDummy& operator= (const DBConnDummy&) = delete;

        /*!
         * \brief           Fakes running of an SQL SELECT query.
         * \param query     Any query.
         * \returns         A Table object containing dummy results.
         */
        Table select(std::string query);

};              //  class DBConnDummy

}               //  namespace gldb

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBCONNDUMMYIMP_H

