/*!
 * \file            dbsqlstatements.h
 * \brief           Interface to SQL statement class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_SQL_STATEMENTS_H
#define PG_GENERAL_LEDGER_DATABASE_SQL_STATEMENTS_H

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
        virtual std::string create_table(const std::string table_name) const;

        /*!
         * \brief               Returns a SQL statement for dropping a table.
         * \param table_name    The table to drop.
         * \returns             The SQL statement to drop the table.
         */
        virtual std::string drop_table(const std::string table_name) const;

        /*!
         * \brief               Returns a SQL statement for creating a view.
         * \param view_name     The view to create.
         * \returns             The SQL statement to create the view.
         */
        virtual std::string create_view(const std::string view_name) const;

        /*!
         * \brief               Returns a SQL statement for dropping a view.
         * \param view_name     The view to drop.
         * \returns             The SQL statement to drop the view.
         */
        virtual std::string drop_view(const std::string view_name) const;
        
        /*!
         * \brief               Returns a SQL statement to select a user by ID.
         * \param user_id       The user_id
         * \returns             The SQL statement.
         */
        virtual std::string user_by_id(const std::string user_id) const;
        
        /*!
         * \brief               Returns a SQL statement to select a user by
         * username.
         * \param user_name     The username.
         * \returns             The SQL statement.
         */
        virtual std::string user_by_username(const std::string user_name) const;

        /*!
         * \brief               Returns a SQL UPDATE statement to update a
         * user.
         * \param user          A user object.
         * \returns             The SQL statement.
         */
        virtual std::string update_user(const GLUser& user) const;

        /*!
         * \brief               Returns a SQL statement to grant a user a
         * permission.
         * \attention           This function always sets the user granting
         * the permission to user 1. This will need to be updated to support
         * the recording of which user has granted the permission, when
         * support for others to be able to do so is implemented.
         * \param user          The user for which to grant the permission.
         * \param perm          A string containing the name of the permission.
         * \returns             The SQL statement.
         */
        virtual std::string grant(const GLUser& user, const std::string perm);

        /*!
         * \brief               Returns a SQL UPDATE statement to revoke a
         * permission from a user.
         * \param user          The user from which to revoke.
         * \param perm          The permission to revoke.
         * \returns             The SQL statement.
         */
        virtual std::string revoke(const GLUser& user, const std::string perm);

        /*!
         * \brief               Returns a SQL UPDATE statement to list a
         * user's permissions.
         * \param user          The user for which to list.
         * \returns             The SQL statement.
         */
        virtual std::string get_perms(const GLUser& user);

};              //  class DBSQLStatements

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_DATABASE_SQL_STATEMENTS_H

