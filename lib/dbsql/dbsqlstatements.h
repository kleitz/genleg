/*!
 * \file            dbsqlstatements.h
 * \brief           Interface to SQL statements class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DBSQL_STATEMENTS_H
#define PG_GENERAL_LEDGER_DATABASE_DBSQL_STATEMENTS_H

#include <string>
#include "gldb/gluser.h"

namespace genleg {

/*!
 * \brief           SQL statements class.
 * \ingroup         sql
 */
class DBSQLStatements {
    public:

        /*!  Constructor  */
        DBSQLStatements ();

        /*!  Destructor  */
        virtual ~DBSQLStatements ();

        /*!
         * \brief               Returns a SQL statement for creating a table.
         * \param table_name    The table to create.
         * \returns             The SQL statement to create the table.
         */
        virtual std::string create_table(const std::string& table_name) const;

        /*!
         * \brief               Returns a SQL statement for dropping a table.
         * \param table_name    The table to drop.
         * \returns             The SQL statement to drop the table.
         */
        virtual std::string drop_table(const std::string& table_name) const;

        /*!
         * \brief               Returns a SQL statement for creating a view.
         * \param view_name     The view to create.
         * \returns             The SQL statement to create the view.
         */
        virtual std::string create_view(const std::string& view_name) const;

        /*!
         * \brief               Returns a SQL statement for dropping a view.
         * \param view_name     The view to drop.
         * \returns             The SQL statement to drop the view.
         */
        virtual std::string drop_view(const std::string& view_name) const;
        
        /*!
         * \brief               Returns a SQL statement to select a user by ID.
         * \param user_id       The user_id
         * \returns             The SQL statement.
         */
        virtual std::string user_by_id(const std::string& user_id) const;
        
        /*!
         * \brief               Returns a SQL statement to select a user by
         * username.
         * \param user_name     The username.
         * \returns             The SQL statement.
         */
        virtual std::string
            user_by_username(const std::string& user_name) const;

        /*!
         * \brief               Returns a SQL UPDATE statement to update a
         * user.
         * \param user          A user object.
         * \returns             The SQL statement.
         */
        virtual std::string update_user(const GLUser& user) const;

        /*!
         * \brief               Returns a SQL statement to select an entity
         * by ID.
         * \param entity_id     The entity ID.
         * \returns             The SQL statement.
         */
        virtual std::string entity_by_id(const std::string& entity_id) const;

        /*!
         * \brief               Returns a SQL statement to select an entity
         * by short name.
         * \param entity_name   The entity short name.
         * \returns             The SQL statement.
         */
        virtual std::string
        entity_by_name(const std::string& entity_name) const;

        /*!
         * \brief               Returns a SQL statement to select a nominal
         * account by name/number.
         * \param acc_name      The account name/number.
         * \returns             The SQL statement.
         */
        virtual std::string
        account_by_name(const std::string& acc_name) const;

        /*!
         * \brief               Returns a SQL statement to select a journal
         * entry by ID.
         * \param je_id         The journal entry ID.
         * \returns             The SQL statement.
         */
        virtual std::string je_by_id(const std::string& je_id) const;

        /*!
         * \brief               Returns a SQL statement to select journal
         * entry lines by ID.
         * \param je_id         The journal entry ID.
         * \returns             The SQL statement.
         */
        virtual std::string jelines_by_id(const std::string& je_id) const;

        /*!
         * \brief               Returns a SQL INSERT statement to post a
         * journal entry.
         * \param user          The ID of the posting user.
         * \param entity        The entity ID.
         * \param period        The accounting period.
         * \param year          The accounting year.
         * \param source        The journal entry source.
         * \param memo          The memo for the journal entry.
         * \returns             A string containing the query.
         */
        virtual std::string post_je(const unsigned int user,
                const unsigned int entity,
                const int period,
                const int year,
                const std::string& source,
                const std::string& memo) const;

        /*!
         * \brief               Returns a SQL INSERT query to post a journal
         * entry line.
         * \param je            The journal entry ID.
         * \param account       The account to which to post.
         * \param amount        The amount to post.
         * \returns             A string containing the SQL statement.
         */
        virtual std::string post_je_line(const unsigned long long je,
                const std::string account,
                const std::string amount) const;

        /*!
         * \brief               Returns a SQL statement to grant a user a
         * permission.
         * \attention           This function always sets the user granting
         * the permission to user 1. This will need to be updated to support
         * the recording of which user has granted the permission, when
         * support for others to be able to do so is implemented.
         * \param user_id       The user ID for which to grant the permission.
         * \param perm          A string containing the name of the permission.
         * \returns             The SQL statement.
         */
        virtual std::string grant(const std::string& user_id,
                                  const std::string& perm) const;

        /*!
         * \brief               Returns a SQL UPDATE statement to revoke a
         * permission from a user.
         * \param user_id       The user ID from which to revoke.
         * \param perm          The permission to revoke.
         * \returns             The SQL statement.
         */
        virtual std::string revoke(const std::string& user_id,
                                   const std::string& perm) const;

        /*!
         * \brief               Returns a SQL UPDATE statement to list a
         * user's permissions.
         * \param user_id       The user ID for which to list.
         * \returns             The SQL statement.
         */
        virtual std::string get_perms(const std::string& user_id) const;

        /*!
         * \brief               Returns a SQL statement to run the current
         * trial balance report.
         * \returns             The SQL statement.
         */
        virtual std::string currenttb() const;

        /*!
         * \brief               Returns a SQL statement to run the current
         * trial balance report by entity.
         * \param entity        The entity number for which to run the report.
         * \returns             The SQL statement.
         */
        virtual std::string currenttb_by_entity(
                const std::string& entity) const;

        /*!
         * \brief               Returns a SQL statement to run the list users
         * report.
         * \returns             The SQL statement.
         */
        std::string listusers() const;

};              //  class DBSQLStatements

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_DATABASE_DBSQL_STATEMENTS_H

