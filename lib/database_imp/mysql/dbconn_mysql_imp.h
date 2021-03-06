/*!
 * \file            dbconn_mysql_imp.h
 * \brief           Interface to MySQL database connection implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBCONNMYSQLIMP_H
#define PG_GENERAL_LEDGER_DATABASE_DBCONNMYSQLIMP_H

#include <string>
#include <mutex>

#include "database/database.h"

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

namespace gldb {

/*!
 * \brief       MySQL database implementation class
 * \ingroup     database
 */
class DBConnMySQL : public DBConnImp {
    public:

        /*!
         * \brief           Constructor.
         * \param database  The name of the MySQL database.
         * \param hostname  The hostname of the server.
         * \param username  The username to log into the database.
         * \param password  The password to log into the database.
         * \throws          DBConnCouldNotConnect If could not connect
         * to database.
         */
        DBConnMySQL (const std::string& database,
                     const std::string& hostname,
                     const std::string& username,
                     const std::string& password);

        /*!  Deleted copy constructor  */
        DBConnMySQL (const DBConnMySQL&) = delete;

        /*!  Delete move constructor  */
        DBConnMySQL (const DBConnMySQL&&) = delete;

        /*!  Destructor  */
        virtual ~DBConnMySQL ();

        /*!  Deleted assignment operator  */
        DBConnMySQL& operator= (const DBConnMySQL&) = delete;

        /*!  Deleted move assignment operator  */
        DBConnMySQL& operator= (const DBConnMySQL&&) = delete;

        /*!
         * \brief           Runs an SQL query.
         * \param sql_query The SQL query.
         * \throws          DBConnCouldNotQuery If could not successfully
         * execute query.
         */
        virtual void query(const std::string& sql_query);

        /*!
         * \brief           Runs an SQL SELECT query.
         * \param sql_query The SQL query.
         * \returns         A Table object containing the results.
         * \throws          DBConnCouldNotQuery If could not successfully
         * execute query.
         */
        virtual Table select(const std::string& sql_query);

        /*!
         * \brief           Begins a transaction.
         */
        virtual void begin_transaction();

        /*!
         * \brief           Rolls back a transaction.
         */
        virtual void rollback_transaction();

        /*!
         * \brief           Commits a transaction.
         */
        virtual void commit_transaction();

        /*!
         * \brief           Returns the last auto incremented value.
         * \returns         The last auto incremented value.
         */
        virtual unsigned long long last_auto_increment();

    private:

        /*!  The initialized MySQL handle.  */
        MYSQL * m_conn;

        /*!  Database connection mutex  */
        static std::mutex mtx;

};              //  class DBConnMySQL

}               //  namespace gldb

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBCONNMYSQLIMP_H

