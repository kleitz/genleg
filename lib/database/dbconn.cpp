/*!
 * \file            dbconn.cpp
 * \brief           Implementation of database connection abstract base class
 * \details         Implementation of database connection abstract base class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "dbconn.h"

using namespace gldb;

DBConn::DBConn(DBConnImp * imp) : m_imp(imp) {
}

DBConn::~DBConn() {
    delete m_imp;
}

Table DBConn::select(std::string query) {
    return m_imp->select(query);
}

