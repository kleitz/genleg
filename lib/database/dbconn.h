/*!
 * \file            dbconn.h
 * \brief           Interface to database connection base class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DBCONN_H
#define PG_DATABASE_DBCONN_H

#include <string>
#include <memory>
#include <stdexcept>

#include "data_structures.h"
#include "dbconnimp.h"

namespace gldb {

/*!  Could not connect to database exception class  */
class DBConnCouldNotConnect : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit DBConnCouldNotConnect(const std::string& msg) :
            std::runtime_error(msg) {};
};

/*!  Could not execute database query exception class  */
class DBConnCouldNotQuery : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit DBConnCouldNotQuery(const std::string& msg) :
            std::runtime_error(msg) {};
};

/*!  Database connection class  */
class DBConn {
    public:
        /*!
         * \brief           Constructor.
         * \param imp       Pointer to database implementation object.
         */
        explicit DBConn (DBConnImp * imp);

        /*!
         * \brief           Destructor..
         */
        ~DBConn ();

        /*!
         * \brief           Runs an SQL SELECT query.
         * \param query     The query.
         * \returns         A Table object containing the results.
         */
        Table select(std::string query);

        /*!  Deleted copy constructor  */
        DBConn (const DBConn&) = delete;

        /*!  Deleted assignment operator  */
        DBConn& operator= (const DBConn&) = delete;

    private:
        /*!  Pointer to database implementation object.  */
        DBConnImp * m_imp;

};              //  class DBConn

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONN_H

