/*!
 * \file            currency.cpp
 * \brief           Implementation of currency amount class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "currency.h"

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

