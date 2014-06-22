/*!
 * \file            currency.cpp
 * \brief           Implementation of currency amount class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <vector>
#include "currency.h"
#include "stringhelp.h"

using namespace pgutils;

bool pgutils::operator==(const Currency& lhs, const Currency& rhs)
{
    return lhs.m_int == rhs.m_int && lhs.m_frac == rhs.m_frac;
}

bool pgutils::operator!=(const Currency& lhs, const Currency& rhs)
{
    return !(lhs == rhs);
}

bool pgutils::operator<(const Currency& lhs, const Currency& rhs)
{
    return lhs.m_int < rhs.m_int ||
           (lhs.m_int == rhs.m_int &&
            lhs.m_frac < rhs.m_frac);
}

bool pgutils::operator>(const Currency& lhs, const Currency& rhs)
{
    return rhs < lhs;
}

bool pgutils::operator<=(const Currency& lhs, const Currency& rhs)
{
    return !(lhs > rhs);
}

bool pgutils::operator>=(const Currency& lhs, const Currency& rhs)
{
    return !(lhs < rhs);
}

Currency pgutils::operator+(Currency lhs, const Currency& rhs)
{
    return lhs += rhs;
}

Currency pgutils::operator-(Currency lhs, const Currency& rhs)
{
    return lhs -= rhs;
}

Currency& Currency::operator+=(const Currency& rhs)
{
    const int64_t sum_big = expand() + rhs.expand();
    m_int = sum_big / 100;
    m_frac = sum_big % 100;
    return *this;
}

Currency& Currency::operator-=(const Currency& rhs)
{
    return operator+=(-rhs);
}

Currency pgutils::currency_from_string(const std::string& s)
try
{

    std::vector<std::string> vec = split(s, '.');
    if ( vec.size() > 2 ) {
        throw CurrencyException("Invalid currency representation");
    }

    size_t i;

    const int64_t int_part = stoll(vec[0], &i);
    if ( vec[0][i] != '\0' ) {
        throw CurrencyException("Invalid integral part of currency");
    }

    const uint64_t frac_part = vec.size() > 1 ? stoull(vec[1], &i) : 0;
    if ( vec.size() > 1 && (vec[1][i] != '\0') ) {
        throw CurrencyException("Invalid fractional part of currency");
    }

    if ( frac_part > 99 ) {
        throw CurrencyException("Fractional part is too large");
    }

    return Currency{int_part, static_cast<uint8_t>(frac_part)};
}
catch ( const std::invalid_argument& e ) {
    throw CurrencyException("Invalid currency representation");
}

