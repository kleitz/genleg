/*!
 * \file            currency.h
 * \brief           Interface to currency amount class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_UTILS_CURRENCY_H
#define PG_UTILS_CURRENCY_H

#include <cstdint>

namespace pgutils {

/*!
 * \brief           Currency amount class.
 * \ingroup         utils
 */
class Currency {
    public:

        /*!
         * \brief           Constructor.
         * \param i         The integer part.
         * \param f         The fractional part.
         */
        explicit Currency (const int64_t i = 0,
                           const uint8_t f = 0) :
            m_int{i},
            m_frac{i >= 0 ? f : -f}
            {}

        /*!
         * \brief           Returns the integer part of the currency amount.
         * \returns         The integer part of the currency amount.
         */
        int64_t int_part() const { return m_int; }

        /*!
         * \brief           Returns the fractional part of the currency amount.
         * \returns         The fractional part of the currency amount.
         */
        uint8_t frac_part() const { return m_frac > 0 ? m_frac : -m_frac; }

        /*!
         * \brief           Unary negation opertor.
         * \returns         The negated currency amount.
         */
        Currency operator-() const { return Currency{-m_int, frac_part()}; }

        /*!
         * \brief           Addition assignment operator.
         * \param rhs       Right hand side currency amount.
         * \returns         A reference to the original currency amount.
         */
        Currency& operator+=(const Currency& rhs);

        /*!
         * \brief           Subtraction assignment operator.
         * \param rhs       Right hand side currency amount.
         * \returns         A reference to the original currency amount.
         */
        Currency& operator-=(const Currency& rhs);

        /*!  Friend equality operator function  */
        friend bool operator==(const Currency& lhs, const Currency& rhs);

        /*!  Friend less than comparison operator function  */
        friend bool operator<(const Currency& lhs, const Currency& rhs);

        /*!  Friend addition operator function  */
        friend Currency operator+(Currency lhs, const Currency& rhs);

    private:

        /*!  Integer part  */
        int64_t m_int;

        /*!  Fractional part  */
        int m_frac;

        /*!
         * \brief           Returns a Currency amount as a whole integer.
         * \returns         The Currency amount expanded to a whole integer,
         * equivalent to multiplying it by 100.
         */
        int64_t expand() const { return m_int * 100 + m_frac; }

};              //  class Currency

/*!
 * \brief           Currency addition operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \returns         The sum of the two sides.
 */
Currency operator+(Currency lhs, const Currency& rhs);

/*!
 * \brief           Currency subtraction operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \returns         The difference between the two sides.
 */
Currency operator-(Currency lhs, const Currency& rhs);

/*!
 * \brief           Currency equality comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the two sides are equal.
 * \retval false    If the two sides are not equal.
 */
bool operator==(const Currency& lhs, const Currency& rhs);

/*!
 * \brief           Currency inequality comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the two sides are not equal.
 * \retval false    If the two sides are equal.
 */
bool operator!=(const Currency& lhs, const Currency& rhs);

/*!
 * \brief           Currency less than comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the lhs is less than the rhs.
 * \retval false    If the lhs is not less than the rhs.
 */
bool operator<(const Currency& lhs, const Currency& rhs);

/*!
 * \brief           Currency greater than comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the lhs is greater than the rhs.
 * \retval false    If the lhs is not greater than the rhs.
 */
bool operator>(const Currency& lhs, const Currency& rhs);

/*!
 * \brief           Currency less than or equal to comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the lhs is less than or equal to the rhs.
 * \retval false    If the lhs is not less than or equal to the rhs.
 */
bool operator<=(const Currency& lhs, const Currency& rhs);

/*!
 * \brief           Currency greater than or equal to comparison operator
 * \ingroup         utils
 * \param lhs       Left hand side.
 * \param rhs       Right hand side.
 * \retval true     If the lhs is greater than or equal to the rhs.
 * \retval false    If the lhs is not greater than or equal to the rhs.
 */
bool operator>=(const Currency& lhs, const Currency& rhs);

}               //  namespace pgutils

#endif          //  PG_UTILS_CURRENCY_H

