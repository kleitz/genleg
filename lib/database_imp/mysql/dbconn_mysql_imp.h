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

#include "database/database.h"

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

namespace gldb {

/*!  MySQL database implementation class  */
class DBConnMySQL : public DBConnImp {
    public:
        /*!
         * \brief           Constructor.
         * \param database  The name of the MySQL database.
         * \param hostname  The hostname of the server.
         * \param username  The username to log into the database.
         * \param password  The password to log into the database.
         */
        DBConnMySQL (const std::string database,
                const std::string hostname, const std::string username,
                const std::string password);
        DBConnMySQL (const DBConnMySQL&) = delete;
        virtual ~DBConnMySQL ();

        DBConnMySQL& operator= (const DBConnMySQL&) = delete;

        Table select(std::string query);

    private:
        MYSQL * m_conn;

};              //  class DBConnMySQL

}               //  namespace gldb

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBCONNMYSQLIMP_H
