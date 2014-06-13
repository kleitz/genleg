/*!
 * \file            dbconn.h
 * \brief           Interface to database connection abstract base class
 * \details         Interface to database connection abstract base class
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

class DBConnCouldNotConnect : public std::runtime_error {
    public:
        DBConnCouldNotConnect(const std::string& msg) :
            std::runtime_error(msg) {};
};

class DBConnCouldNotQuery : public std::runtime_error {
    public:
        DBConnCouldNotQuery(const std::string& msg) :
            std::runtime_error(msg) {};
};

class DBConn {
    public:
        DBConn (DBConnImp * imp);
        ~DBConn ();
        Table select(std::string query);
        DBConn (const DBConn&) = delete;
        DBConn& operator= (const DBConn&) = delete;

    private:
        DBConnImp * m_imp;

};              //  class DBConn

}               //  namespace gldb

#endif          //  PG_DATABASE_DBCONN_H

