/*!
 * \file            database_imp.h
 * \brief           Interface to database implementation factory function.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_IMP_H
#define PG_GENERAL_LEDGER_DATABASE_IMP_H

#include <memory>

#include "database/database.h"

namespace gldb {

/*!
 * \brief           Creates and returns a pointer to a database implementation.
 * \details         The implementation of this function is provided by the
 * individual database implementations. One database implementation is compiled
 * into the program at any one time. Multiple database systems are, or will be,
 * supported, and not every system will possess the libraries and headers to
 * compile every implementation. Therefore, only only implementation is
 * compiled in at a time. The fact that each database implementation will
 * implement this function to return the correct derived class prevents any
 * attempt to compile unsupported library code. This would not be feasible
 * if we were to simply provide each implementation as a subclass.
 * \ingroup         database
 * \param database  The name of the database to which to connect.
 * \param hostname  The hostname of the computer running the database.
 * \param username  The username with which to log into the database.
 * \param password  The password with which to log into the database.
 * \returns         A pointer to the database implementation.
 */
DBConnImp * get_connection(const std::string& database,
                           const std::string& hostname,
                           const std::string& username,
                           const std::string& password);

/*!
 * \brief           Returns the name of the compiled-in database type.
 * \ingroup         database
 * \returns         The name of the compiled-in database type.
 */
std::string get_database_type();

}           //  namespace gldb

#endif      //  PG_GENERAL_LEDGER_DATABASE_IMP_H

