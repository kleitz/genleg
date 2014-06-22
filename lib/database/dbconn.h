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

/*!
 * \brief       Base database connection exception class
 * \ingroup     database
 */
class DBConnException : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit DBConnException(const std::string& msg) :
            std::runtime_error(msg) {};
};

/*!
 * \brief       Could not connect to database exception class.
 * \ingroup     database
 */
class DBConnCouldNotConnect : public DBConnException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit DBConnCouldNotConnect(const std::string& msg) :
            DBConnException(msg) {};
};

/*!
 * \brief       Could not execute database query exception class
 * \ingroup     database
 */
class DBConnCouldNotQuery : public DBConnException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit DBConnCouldNotQuery(const std::string& msg) :
            DBConnException(msg) {};
};

/*! 
 * \brief       Database connection class
 * \ingroup     database
 */
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
         * \brief           Runs an SQL query.
         * \param sql_query The query.
         * \returns         A Table object containing the results.
         */
        void query(const std::string& sql_query);

        /*!
         * \brief           Runs an SQL SELECT query.
         * \param query     The query.
         * \returns         A Table object containing the results.
         */
        Table select(const std::string& query);

        /*!
         * \brief           Returns the last auto incremented value.
         * \returns         The last auto incremented value.
         */
        unsigned long long last_auto_increment();

        /*!  Deleted copy constructor  */
        DBConn (const DBConn&) = delete;

        /*!  Deleted move constructor  */
        DBConn (const DBConn&&) = delete;

        /*!  Deleted copy assignment operator  */
        DBConn& operator= (const DBConn&) = delete;

        /*!  Deleted move assignment operator  */
        DBConn& operator= (const DBConn&&) = delete;

    private:

        /*!  Pointer to database implementation object.  */
        DBConnImp * m_imp;

};              //  class DBConn

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONN_H

