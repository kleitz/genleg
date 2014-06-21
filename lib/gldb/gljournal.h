/*!
 * \file            gljournal.h
 * \brief           Interface to journal entry classes
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_JOURNAL_ENTRY_H
#define PG_GENERAL_LEDGER_JOURNAL_ENTRY_H

#include <vector>
#include <string>
#include "pgutils/pgutils.h"

namespace genleg {

/*!
 * \brief           Journal entry line class.
 * \ingroup         gldatabase
 */
class GLJELine {
    public:

        /*!
         * \brief           Constructor
         */
        GLJELine (const std::string account,
                  const pgutils::Currency& amount) :
            m_acct{account}, m_amount{amount} {};

    private:

        /*!  Account number/name  */
        std::string m_acct;

        /*!  Amount  */
        pgutils::Currency m_amount;

};              //  class GLJELine

/*!
 * \brief           Journal entry class.
 * \ingroup         gldatabase
 */
class GLJournal {
    public:

        /*!
         * \brief           Constructor
         * \param entity    The entity number.
         * \param period    The accounting period.
         * \param year      The accounting year.
         * \param source    The journal entry source.
         * \param memo      A memo for the journal entry.
         */
        GLJournal (const unsigned int entity,
                   const int period,
                   const int year,
                   const std::string& source,
                   const std::string& memo) :
            m_entity{entity},
            m_period{period},
            m_year{year},
            m_source{source},
            m_memo{memo},
            m_lines{}
        {}

        /*!
         * \brief           Returns the entity number.
         * \returns         The entity number.
         */
        unsigned int entity() const { return m_entity; }

        /*!
         * \brief           Returns the accounting period.
         * \returns         The accounting period.
         */
        int period() const { return m_period; }

        /*!
         * \brief           Returns the accounting year.
         * \returns         The accounting year.
         */
        int year() const { return m_year; }

        /*!
         * \brief           Returns the journal entry source.
         * \returns         The journal entry source.
         */
        const std::string& source() const { return m_source; }

        /*!
         * \brief           Returns the memo for the journal entry.
         * \returns         The memo for the journal entry.
         */
        const std::string& memo() const { return m_memo; }

        /*!
         * \brief           Index operator.
         * \param i         The index.
         * \returns         The journal entry line at index \c i.
         */
        const GLJELine& operator[](const size_t i) const { return m_lines[i]; }

        /*!
         * \brief           Adds a journal entry line.
         * \param account   The account number or name.
         * \param amount    The currency amount.
         */
        void add_line(const std::string& account,
                      const pgutils::Currency& amount) {
            m_lines.push_back(GLJELine{account, amount});
        }

    private:

        /*!  The entity number for the journal entry.  */
        unsigned int m_entity;

        /*!  The accounting period.  */
        int m_period;

        /*!  The accounting year.  */
        int m_year;

        /*!  The journal entry source.  */
        std::string m_source;

        /*!  The memo for the journal entry.  */
        std::string m_memo;

        /*!  A vector of journal entry lines.  */
        std::vector<GLJELine> m_lines;

};              //  class GLJournal

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_JOURNAL_ENTRY_H

