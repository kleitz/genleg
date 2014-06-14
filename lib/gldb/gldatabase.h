/*!
 * \file            gldatabase.h
 * \brief           Interface to General Ledger database class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_DATABASE_H
#define PG_GENERAL_LEDGER_GL_DATABASE_H

#include <vector>
#include <string>
#include "database/database.h"
#include "dbsql/dbsql.h"
#include "gluser.h"

namespace genleg {

/*!
 * \brief       General ledger database class
 * \ingroup     gldatabase
 */
class GLDatabase {
    public:
        /*!
         * \brief           Constructor.
         * \param database  Database name.
         * \param hostname  Hostname of database machine.
         * \param username  Username to log into database.
         * \param password  Password to log into database.
         * \throws          GLDBException on error.
         */
        GLDatabase (const std::string database,
                     const std::string hostname,
                     const std::string username,
                     const std::string password);
        
        /*!  Destructor  */
        ~GLDatabase ();

        /*!
         * \brief           Creates the database structure.
         * \throws          GLDBException on error.
         */
        void create_structure();

        /*!
         * \brief           Destroys the database structure.
         * \throws          GLDBException on error.
         */
        void destroy_structure();

        /*!
         * \brief           Loads sample data into the database.
         * \param dir       The directory containing the sample data.
         * Individual files in that directory should be named after the
         * table they are intended to poplate.
         * \throws          GLDBException on error.
         */
        void load_sample_data(const std::string& dir);

        /*!
         * \brief           Returns the backend database implementation.
         * \details         This may be called to discover which database
         * platform support has been compiled into the application.
         * \returns         A string containing the database platform name.
         */
        static std::string backend();

        /*!
         * \brief           Returns a user from an ID.
         * \param user_id   The user ID.
         * \returns         The user.
         * \throws          GLDBException if the user cannot be found.
         */
        GLUser get_user_by_id(const std::string& user_id);

        /*!
         * \brief           Returns a user from a user name.
         * \param user_name The user name.
         * \returns         The user.
         * \throws          GLDBException if the user cannot be found.
         */
        GLUser get_user_by_username(const std::string& user_name);

    private:
        /*!  Database connection  */
        gldb::DBConn m_dbc;

        /*!  SQL statements object  */
        std::shared_ptr<DBSQLStatements> m_sql;

        /*!  Vector containing database table names  */
        const std::vector<std::string> m_tables;

        /*!  Vector containing database view names  */
        const std::vector<std::string> m_views;
        
};              //  class GLDatabase

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GL_DATABASE_H

