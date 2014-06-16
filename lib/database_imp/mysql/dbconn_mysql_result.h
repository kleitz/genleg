/*!
 * \file            dbconn_mysql_result.h
 * \brief           Interface to MySQL result structure resource handle class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_MYSQL_MYSQLRESULT_H
#define PG_DATABASE_MYSQL_MYSQLRESULT_H

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

namespace gldb {

/*!
 * \brief           MySQL result structure class
 * \ingroup         database
 */
class MySQLResult {
    public:

        /*!
         * \brief           Constructor
         * \param conn      MySQL connection
         * \throws          DBConnCouldNotQuery on failure
         */
        explicit MySQLResult(MYSQL * conn);

        /*!  Destructor  */
        ~MySQLResult();

        /*!  Deleted copy constructor  */
        MySQLResult(const MySQLResult& result) = delete;

        /*!  Deleted move constructor  */
        MySQLResult(MySQLResult&& result) = delete;

        /*!  Deleted copy assignment operator  */
        MySQLResult& operator=(const MySQLResult& result) = delete;

        /*!  Deleted move assignment operator  */
        MySQLResult& operator=(MySQLResult&& result) = delete;
        
        /*!
         * \brief           Returns the MYSQL_RES pointer.
         * \returns         The MYSQL_RES pointer.
         */
        MYSQL_RES * result() { return m_result; }

        /*! 
         * \brief           Returns the number of fields in the result set.
         * \returns         The number of fields in the result set.
         */
        unsigned int num_fields() const { return m_num_fields; }

    private:

        /*!  The MYSQL_RES pointer  */
        MYSQL_RES * m_result;

        /*!  The number of fields in the result set  */
        unsigned int m_num_fields;

};              //  class MySQLResult

}               //  namespace gldb

#endif          //  PG_DATABASE_MYSQL_MYSQLRESULT_H

