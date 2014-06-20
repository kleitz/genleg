/*!
 * \file            glreport.h
 * \brief           Interface to report class
 * \details         Interface to report class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_GENERAL_LEDGER_GLREPORT_H
#define PG_GENERAL_LEDGER_GLREPORT_H

#include <string>
#include <database/database.h>

namespace genleg {

/*!
 * \brief           General ledger report class
 * \ingroup         gldatabase
 */
class GLReport {
    public:

        /*!  Constructor  */
        GLReport () {}

        /*!  Destructor  */
        ~GLReport () {}

    private:

};              //  class GLReport

/*!
 * \brief           Creates a plain report from a table.
 * \details         A "plain report" separates each column with a space.
 * \ingroup         gldatabase
 * \param table     The table from which to create the report.
 * \returns         A string containing the report.
 */
std::string plain_report_from_table(const gldb::Table& table);

/*!
 * \brief           Creates a decorated report from a table.
 * \details         A "decorated report" presents the table surrounding with
 * ASCII-art style lines consisting of \c '+' , \c '-' and \c '|' characters.
 * \ingroup         gldatabase
 * \param table     The table from which to create the report.
 * \returns         A string containing the report.
 */
std::string decorated_report_from_table(const gldb::Table& table);

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GLREPORT_H

