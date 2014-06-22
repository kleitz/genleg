/*!
 * \file            glaccount.h
 * \brief           Interface to nominal account class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_NOMINAL_ACCOUNT_H
#define PG_GENERAL_LEDGER_NOMINAL_ACCOUNT_H

#include <string>

namespace genleg {

/*!
 * \brief           Nominal account class.
 * \ingroup         gldatabase
 */
class GLAccount {
    public:

        /*!
         * \brief               Constructor.
         * \param number        The account number.
         * \param description   The account description.
         * \param enabled       The enabled flag.
         */
        GLAccount (const std::string number,
                   const std::string description,
                   const bool enabled) :
            m_number{number},
            m_description{description},
            m_enabled{enabled}
        {}

        /*!
         * \brief           Returns the account number.
         * \returns         The account number.
         */
        const std::string& number() const { return m_number; }

        /*!
         * \brief           Returns the account description.
         * \returns         The account description.
         */
        const std::string& description() const { return m_description; }

        /*!
         * \brief           Returns the enabled flag.
         * \returns         The enabled flag.
         */
        bool enabled() const { return m_enabled; }

    private:

        /*!  Account number  */
        std::string m_number;

        /*!  Account description  */
        std::string m_description;

        /*!  Enabled flag  */
        bool m_enabled;

};              //  class GLAccount

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_NOMINAL_ACCOUNT_H

