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
#include "glreport.h"
#include "gljournal.h"

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
        GLDatabase(const std::string& database,
                   const std::string& hostname,
                   const std::string& username,
                   const std::string& password);
        
        /*!  Destructor  */
        ~GLDatabase();

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

        /*!
         * \brief           Updates a user's details.
         * \param user      The user object.
         */
        void update_user(const GLUser& user);

        /*!
         * \brief           Grants a user a permission.
         * \param user      The user for which to grant.
         * \param perm      A string containing the permission to grant.
         */
        void grant(const GLUser& user, const std::string& perm);

        /*!
         * \brief           Revokes a permission from a user.
         * \param user      The user for which to revoke.
         * \param perm      A string containing the permission to revoke.
         */
        void revoke(const GLUser& user, const std::string& perm);
        
        /*!
         * \brief           Posts a journal entry.
         * \param journal   The journal entry to post.
         */
        void post_journal(const GLJournal& journal);

        /*!
         * \brief               Runs a report
         * \param report_name   The name of the report.
         * \param arg           An optional argument.
         * \returns             A report object.
         */
        GLReport report(const std::string& report_name,
                        const std::string& arg = "");

    private:
        /*!  Database connection  */
        gldb::DBConn m_dbc;

        /*!  SQL statements object  */
        const std::shared_ptr<const DBSQLStatements> m_sql;

        /*!  Vector containing database table names  */
        const std::vector<std::string> m_tables;

        /*!  Vector containing database view names  */
        const std::vector<std::string> m_views;
        
        /*!
         * \brief           Creates a user from a query table.
         * \details         Provided because the public functions can
         * get a user either from an ID or a name, this function contains
         * the common functionality.
         * \param table     A table from the appropriate query.
         * \returns         The new user.
         */
        GLUser create_user(gldb::Table& table);

        /*!
         * \brief           Returns a current trial balance report.
         * \param entity    The entity for which to run the report, or
         * an empty string for all entities.
         * \returns         A GLReport object with the report.
         */
        GLReport current_trial_balance_report(const std::string& entity);

        /*!
         * \brief           Returns a list users report.
         * \returns         A GLReport object with the report.
         */
        GLReport list_users_report();

};              //  class GLDatabase

/*!
 * \brief           Database transaction RAII class
 * \ingroup         gldatabase
 */
class GLDBTransaction {
    public:

        GLDBTransaction(gldb::DBConn& dbc) :
            m_dbc(dbc), m_commit(false)
        {
            m_dbc.begin_transaction();
        }

        ~GLDBTransaction() {
            if ( m_commit ) {
                m_dbc.commit_transaction();
            }
            else {
                m_dbc.rollback_transaction();
            }
        }

        void commit() {
            m_commit = true;
        }

    private:
        gldb::DBConn& m_dbc;
        bool m_commit;

};

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GL_DATABASE_H

