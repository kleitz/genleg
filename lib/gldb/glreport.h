/*!
 * \file            glreport.h
 * \brief           Interface to report class
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
        GLReport (const std::string& report) :
            m_report_text(report) {}

        /*!  Destructor  */
        ~GLReport () {}

        friend std::ostream& operator<< (std::ostream& out,
                const GLReport& report);

    private:

        /*!  The main report text  */
        const std::string m_report_text;

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

/*!
 * \brief           Overridden << operator for printing a report.
 * \param out       The ostream to which to print.
 * \param report    A reference to the report.
 * \returns         A reference to `out`.
 */
std::ostream& operator<< (std::ostream& out, const GLReport& report);

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GLREPORT_H

