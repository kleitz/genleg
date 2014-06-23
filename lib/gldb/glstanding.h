/*!
 * \file            glstanding.h
 * \brief           Interface to general ledger standing data class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_STANDING_DATA_H
#define PG_GENERAL_LEDGER_STANDING_DATA_H

#include <string>

namespace genleg {

/*!
 * \brief               General ledger standing data class.
 * \ingroup             gldatabase
 */
class GLStandingData {
    public:

        /*!
         * \brief               Constructor.
         * \param organization  The overall organization.
         * \param period        The current accounting period.
         * \param year          The current accounting year.
         * \param num_periods   The number of accounting periods in a year.
         */
        GLStandingData (const std::string& organization,
                        const int period,
                        const int year,
                        const int num_periods) :
            m_org{organization},
            m_period{period},
            m_year{year},
            m_num_periods{num_periods}
        {}

        /*!
         * \brief           Returns the overall organization.
         * \returns         The overall organization
         */
        const std::string& organization() const { return m_org; }

        /*!
         * \brief           Returns the current accounting period.
         * \returns         The current accounting period.
         */
        int period() const { return m_period; }

        /*!
         * \brief           Returns the current accounting year.
         * \returns         The current accounting year.
         */
        int year() const { return m_year; }

        /*!
         * \brief           Returns the number of accounting periods in a year.
         * \returns         The number of accounting periods in a year.
         */
        int num_periods() const { return m_num_periods; }

    private:

        /*!  Overall organization  */
        std::string m_org;

        /*!  Current period  */
        int m_period;

        /*!  Current year  */
        int m_year;

        /*!  Number of periods per year  */
        int m_num_periods;

};              //  class GLStandingData

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_STANDING_DATA_H

