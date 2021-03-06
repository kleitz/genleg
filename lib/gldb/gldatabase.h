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
#include "glentity.h"
#include "glaccount.h"
#include "glstanding.h"

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
         * \brief           Gets the standing data.
         * \returns         The standing data.
         */
        GLStandingData get_standing_data();

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
         * \brief           Returns an entity from an ID.
         * \param entity_id The entity ID.
         * \returns         The entity.
         * \throws          GLDBException if the entity cannot be found.
         */
        GLEntity get_entity_by_id(const std::string& entity_id);

        /*!
         * \brief               Returns an entity from an entity short name.
         * \param entity_name   The entity short name.
         * \returns             The entity.
         * \throws              GLDBException if the user cannot be found.
         */
        GLEntity get_entity_by_name(const std::string& entity_name);

        /*!
         * \brief               Returns a nominal account from an account
         * number/name.
         * \param acc_name      The account number/name.
         * \returns             The account.
         * \throws              GLDBException if the user cannot be found.
         */
        GLAccount get_account_by_name(const std::string& acc_name);

        /*!
         * \brief               Returns a journal entry from an ID.
         * \param je_id         The journal entry ID.
         * \returns             The entity.
         */
        GLJournal get_je_by_id(const std::string& je_id);

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
         * \brief           Creates an entity from a query table.
         * \details         Provided because the public functions can
         * get a entity either from an ID or a name, this function contains
         * the common functionality.
         * \param table     A table from the appropriate query.
         * \returns         The new entity.
         */
        GLEntity create_entity(gldb::Table& table);

        /*!
         * \brief           Returns a standing data report.
         * \returns         A GLReport object with the report.
         */
        GLReport standing_data_report();

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

        /*!
         * \brief           Returns a single journal entry report.
         * \returns         A GLReport object with the report.
         */
        GLReport je_report(const std::string& je_id);

};              //  class GLDatabase

/*!
 * \brief           Database transaction RAII class
 * \ingroup         gldatabase
 */
class GLDBTransaction {
    public:

        /*!
         * \brief           Constructor.
         * \param dbc       Database connection.
         */
        GLDBTransaction(gldb::DBConn& dbc) :
            m_dbc(dbc), m_commit(false)
        {
            m_dbc.begin_transaction();
        }

        /*!  Destructor  */
        ~GLDBTransaction() {
            if ( m_commit ) {
                m_dbc.commit_transaction();
            }
            else {
                m_dbc.rollback_transaction();
            }
        }

        /*!
         * \brief           Set commit flag.
         */
        void commit() {
            m_commit = true;
        }

    private:

        /*!  Database connection  */
        gldb::DBConn& m_dbc;

        /*!  Commit flag  */
        bool m_commit;

};

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GL_DATABASE_H

