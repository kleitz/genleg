/*!
 * \file            gljournal.h
 * \brief           Interface to journal entry classes
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_JOURNAL_ENTRY_H
#define PG_GENERAL_LEDGER_JOURNAL_ENTRY_H

#include <iostream>
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

        /*!
         * \brief           Returns the account name/number.
         * \returns         The account name/number.
         */
        std::string account() const { return m_acct; }

        /*!
         * \brief           Returns the currency amount.
         * \returns         The currency amount.
         */
        pgutils::Currency amount() const { return m_amount; }

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
         * \brief           Returns the number of lines in the entry.
         * \returns         The number of lines in the entry.
         */
        size_t num_lines() const { return m_lines.size(); }

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

        /*!
         * \brief           Checks if the journal entry lines balance.
         * \retval true     If the journal entry lines balance.
         * \retval false    If the journal entry lines do not balance.
         */
        bool balances() const;

        /*!  Alias for iterator  */
        using iterator = std::vector<GLJELine>::iterator;

        /*!
         * \brief           Returns an iterator to the first line.
         * \returns         An iterator to the first line.
         */
        iterator begin() { return m_lines.begin(); }

        /*!
         * \brief           Returns an iterator to one past the last line.
         * \returns         An iterator to one past the last line.
         */
        iterator end() { return m_lines.end(); }

        /*!  Alias for const iterator  */
        using const_iterator = std::vector<GLJELine>::const_iterator;

        /*!
         * \brief           Returns a const iterator to the first line.
         * \returns         A const iterator to the first line.
         */
        const_iterator begin() const { return m_lines.begin(); }

        /*!
         * \brief           Returns a const iterator to one past the last line.
         * \returns         A const iterator to one past the last line.
         */
        const_iterator end() const { return m_lines.end(); }

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

/*!
 * \brief           Returns a journal entry from a stream in a standard format.
 * \param ifs       The input stream.
 * \returns         The journal entry.
 * \throws          GLDBException on failure.
 */
GLJournal journal_from_stream(std::istream& ifs);

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_JOURNAL_ENTRY_H

