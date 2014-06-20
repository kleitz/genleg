/*!
 * \file            glreport.cpp
 * \brief           Implementation of report class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "glreport.h"

using namespace genleg;
using namespace gldb;

/*!
 * \brief           Calculates the maximum required column widths for a table.
 * \ingroup         gldatabase
 * \param table     The table.
 * \returns         A vector of \c size_t containing the maximum required
 * width for each column, without padding.
 */
static std::vector<size_t> max_column_widths(const gldb::Table& table);

/*!
 * \brief           Increments a vector of required column widths.
 * \details         Each element of the vector is increased to fit the
 * width of each file in the row, if the existing width is not large enough
 * to contain it.
 * \ingroup         gldatabase
 * \param widths    An existing vector of widths.
 * \param row       The row against which to check and potentially increase
 * the vector.
 */
static void grow_widths(std::vector<size_t>& widths, const TableRow& row);

/*!
 * \brief           Returns a decorated separator row for a table.
 * \details         The "separator row" is of the format "+---+---+---+"
 * where each column is separated by a \c '+' character, and consists
 * of enough \c '-' characters to fit the respective width in the vector
 * plus two additional characters for spacing.
 * \ingroup         gldatabase
 * \param widths    A vector of required widths.
 * \returns         A string containing the separator row.
 */
static std::string separator_row(const std::vector<size_t>& widths);

/*!
 * \brief           Returns a row for a plain report.
 * \ingroup         gldatabase
 * \param row       The row for which to create the report row.
 * \param widths    A vector of required widths.
 * \returns         A string containing the plain row.
 */
static std::string plain_row(const TableRow& row,
                             const std::vector<size_t>& widths);

/*!
 * \brief           Returns a row for a decorated report.
 * \ingroup         gldatabase
 * \param row       The row for which to create the report row.
 * \param widths    A vector of required widths.
 * \returns         A string containing the decorated row.
 */
static std::string decorated_row(const TableRow& row,
                                 const std::vector<size_t>& widths);

std::ostream& genleg::operator<< (std::ostream& out, const GLReport& report) {
    out << report.m_report_text;
    return out;
}

std::string genleg::plain_report_from_table(const gldb::Table& table)
{
    std::ostringstream ss;

    const std::vector<size_t> widths = max_column_widths(table);
    ss << plain_row(table.get_headers(), widths);
    for ( const auto& record : table ) {
        ss << plain_row(record, widths);
    }

    return ss.str();
}

std::string genleg::decorated_report_from_table(const gldb::Table& table)
{
    std::ostringstream ss;

    const std::vector<size_t> widths = max_column_widths(table);
    ss << separator_row(widths);
    ss << decorated_row(table.get_headers(), widths);
    ss << separator_row(widths);
    for ( const auto& record : table ) {
        ss << decorated_row(record, widths);
    }
    ss << separator_row(widths);

    return ss.str();
}

static std::vector<size_t> max_column_widths(const gldb::Table& table)
{
    std::vector<size_t> widths(table.num_fields());

    grow_widths(widths, table.get_headers());
    for ( const auto& record : table ) {
        grow_widths(widths, record);
    }

    return widths;
}

static void grow_widths(std::vector<size_t>& widths, const TableRow& row)
{
    auto w_itr = widths.begin();
    for ( const auto& field : row ) {
        if ( field.length() > *w_itr ) {
            *w_itr = field.length();
        }
        ++w_itr;
    }
}

static std::string plain_row(const TableRow& row,
                             const std::vector<size_t>& widths)
{
    std::ostringstream ss;
    ss.setf(std::ios_base::left);

    auto w_itr = widths.begin();
    for ( const auto& field : row ) {
        ss << std::setw(*w_itr++ + 1) << field;
    }

    ss << std::endl;
    return ss.str();
}

static std::string decorated_row(const TableRow& row,
                                 const std::vector<size_t>& widths)
{
    std::ostringstream ss;
    ss.setf(std::ios_base::left);

    auto w_itr = widths.begin();
    for ( const auto& field : row ) {
        ss << "| " << std::setw(*w_itr++) << field << " ";
    }

    ss << "|" << std::endl;
    return ss.str();
}

static std::string separator_row(const std::vector<size_t>& widths)
{
    std::ostringstream ss;

    for ( const auto& w : widths ) {
        ss << "+-" << std::string(w, '-') << "-";
    }

    ss << "+" << std::endl;
    return ss.str();
}

