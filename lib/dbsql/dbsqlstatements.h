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

};              //  class DBSQLStatements

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_DATABASE_SQL_STATEMENTS_H

