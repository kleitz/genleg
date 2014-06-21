/*
 *  test_currency.cpp
 *  =================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for Currency class.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include "pgutils/pgutils.h"

using namespace pgutils;

BOOST_AUTO_TEST_SUITE(currency_suite)

BOOST_AUTO_TEST_CASE(currency_construct) {
    Currency c1;
    BOOST_CHECK_EQUAL(c1.int_part(), 0);
    BOOST_CHECK_EQUAL(c1.frac_part(), 0);

    Currency c2{10};
    BOOST_CHECK_EQUAL(c2.int_part(), 10);
    BOOST_CHECK_EQUAL(c2.frac_part(), 0);

    Currency c3{10,99};
    BOOST_CHECK_EQUAL(c3.int_part(), 10);
    BOOST_CHECK_EQUAL(c3.frac_part(), 99);

    Currency c4{-10,99};
    BOOST_CHECK_EQUAL(c4.int_part(), -10);
    BOOST_CHECK_EQUAL(c4.frac_part(), 99);

}

BOOST_AUTO_TEST_CASE(currency_equality) {
    Currency c1{5, 12};
    Currency c2{5, 12};
    Currency c3{5, 13};
    Currency c4{6, 12};
    Currency c5{-5, 12};

    BOOST_CHECK(c1 == c2);
    BOOST_CHECK(!(c1 == c3));
    BOOST_CHECK(!(c1 == c4));
    BOOST_CHECK(!(c1 == c5));
}

BOOST_AUTO_TEST_CASE(currency_inequality) {
    Currency c1{5, 12};
    Currency c2{5, 12};
    Currency c3{5, 13};
    Currency c4{6, 12};
    Currency c5{-5, 12};

    BOOST_CHECK(!(c1 != c2));
    BOOST_CHECK(c1 != c3);
    BOOST_CHECK(c1 != c4);
    BOOST_CHECK(c1 != c5);
}

BOOST_AUTO_TEST_CASE(currency_lessthan_pospos) {
    Currency c1{5, 12};
    Currency c2{5, 11};
    Currency c3{5, 13};
    Currency c4{4, 12};
    Currency c5{4, 11};
    Currency c6{4, 13};
    Currency c7{6, 12};
    Currency c8{6, 11};
    Currency c9{6, 13};

    BOOST_CHECK(c2 < c1);
    BOOST_CHECK(!(c3 < c1));
    BOOST_CHECK(c4 < c1);
    BOOST_CHECK(c5 < c1);
    BOOST_CHECK(c6 < c1);
    BOOST_CHECK(!(c7 < c1));
    BOOST_CHECK(!(c8 < c1));
    BOOST_CHECK(!(c9 < c1));
}

BOOST_AUTO_TEST_CASE(currency_lessthan_negneg) {
    Currency c1{-5, 12};
    Currency c2{-5, 11};
    Currency c3{-5, 13};
    Currency c4{-4, 12};
    Currency c5{-4, 11};
    Currency c6{-4, 13};
    Currency c7{-6, 12};
    Currency c8{-6, 11};
    Currency c9{-6, 13};

    BOOST_CHECK(c1 < c2);
    BOOST_CHECK(!(c1 < c3));
    BOOST_CHECK(c1 < c4);
    BOOST_CHECK(c1 < c5);
    BOOST_CHECK(c1 < c6);
    BOOST_CHECK(!(c1 < c7));
    BOOST_CHECK(!(c1 < c8));
    BOOST_CHECK(!(c1 < c9));
}

BOOST_AUTO_TEST_CASE(currency_greaterthan_pospos) {
    Currency c1{5, 12};
    Currency c2{5, 11};
    Currency c3{5, 13};
    Currency c4{4, 12};
    Currency c5{4, 11};
    Currency c6{4, 13};
    Currency c7{6, 12};
    Currency c8{6, 11};
    Currency c9{6, 13};

    BOOST_CHECK(c1 > c2);
    BOOST_CHECK(!(c1 > c3));
    BOOST_CHECK(c1 > c4);
    BOOST_CHECK(c1 > c5);
    BOOST_CHECK(c1 > c6);
    BOOST_CHECK(!(c1 > c7));
    BOOST_CHECK(!(c1 > c8));
    BOOST_CHECK(!(c1 > c9));
}

BOOST_AUTO_TEST_CASE(currency_greaterthan_negneg) {
    Currency c1{-5, 12};
    Currency c2{-5, 11};
    Currency c3{-5, 13};
    Currency c4{-4, 12};
    Currency c5{-4, 11};
    Currency c6{-4, 13};
    Currency c7{-6, 12};
    Currency c8{-6, 11};
    Currency c9{-6, 13};

    BOOST_CHECK(c2 > c1);
    BOOST_CHECK(!(c3 > c1));
    BOOST_CHECK(c4 > c1);
    BOOST_CHECK(c5 > c1);
    BOOST_CHECK(c6 > c1);
    BOOST_CHECK(!(c7 > c1));
    BOOST_CHECK(!(c8 > c1));
    BOOST_CHECK(!(c9 > c1));
}

BOOST_AUTO_TEST_CASE(currency_greaterequalthan_pospos) {
    Currency c1{5, 11};
    Currency c2{5, 12};
    Currency c3{5, 12};
    Currency c4{5, 13};

    BOOST_CHECK(!(c1 >= c2));
    BOOST_CHECK(c3 >= c2);
    BOOST_CHECK(c4 >= c2);
}

BOOST_AUTO_TEST_CASE(currency_greaterequalthan_negneg) {
    Currency c1{-5, 11};
    Currency c2{-5, 12};
    Currency c3{-5, 12};
    Currency c4{-5, 13};

    BOOST_CHECK(!(c2 >= c1));
    BOOST_CHECK(c2 >= c3);
    BOOST_CHECK(c2 >= c4);
}

BOOST_AUTO_TEST_CASE(currency_lessequalthan_pospos) {
    Currency c1{5, 11};
    Currency c2{5, 12};
    Currency c3{5, 12};
    Currency c4{5, 13};

    BOOST_CHECK(c1 <= c2);
    BOOST_CHECK(c3 <= c2);
    BOOST_CHECK(!(c4 <= c2));
}

BOOST_AUTO_TEST_CASE(currency_lessequalthan_negneg) {
    Currency c1{-5, 11};
    Currency c2{-5, 12};
    Currency c3{-5, 12};
    Currency c4{-5, 13};

    BOOST_CHECK(!(c1 <= c2));
    BOOST_CHECK(c3 <= c2);
    BOOST_CHECK(c4 <= c2);
}

BOOST_AUTO_TEST_CASE(currency_addition_pospos_nocarry) {
    Currency c1{5, 12};
    Currency c2{9, 33};
    Currency c3{14, 45};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_pospos_carry) {
    Currency c1{5, 72};
    Currency c2{9, 53};
    Currency c3{15, 25};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_posneg_nocarry) {
    Currency c1{17, 72};
    Currency c2{-9, 53};
    Currency c3{8, 19};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_posneg_carry) {
    Currency c1{17, 72};
    Currency c2{-9, 83};
    Currency c3{7, 89};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_negpos_nocarry) {
    Currency c1{-9, 30};
    Currency c2{5, 10};
    Currency c3{-4, 20};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_negpos_carry) {
    Currency c1{-9, 30};
    Currency c2{5, 50};
    Currency c3{-3, 80};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_negneg_nocarry) {
    Currency c1{-9, 30};
    Currency c2{-5, 50};
    Currency c3{-14, 80};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_addition_negneg_carry) {
    Currency c1{-9, 70};
    Currency c2{-5, 80};
    Currency c3{-15, 50};
    Currency c4 = c1 + c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_pospos_nocarry) {
    Currency c1{9, 55};
    Currency c2{4, 33};
    Currency c3{5, 22};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_pospos_carry) {
    Currency c1{9, 55};
    Currency c2{4, 77};
    Currency c3{4, 78};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_posneg_nocarry) {
    Currency c1{9, 55};
    Currency c2{-4, 33};
    Currency c3{13, 88};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_posneg_carry) {
    Currency c1{9, 55};
    Currency c2{-4, 66};
    Currency c3{14, 21};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_negpos_nocarry) {
    Currency c1{-9, 55};
    Currency c2{4, 33};
    Currency c3{-13, 88};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_negpos_carry) {
    Currency c1{-9, 55};
    Currency c2{4, 88};
    Currency c3{-14, 43};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_negneg_nocarry) {
    Currency c1{-9, 55};
    Currency c2{-4, 33};
    Currency c3{-5, 22};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_CASE(currency_subtraction_negneg_carry) {
    Currency c1{-9, 55};
    Currency c2{-4, 77};
    Currency c3{-4, 78};
    Currency c4 = c1 - c2;

    BOOST_CHECK(c3 == c4);
}

BOOST_AUTO_TEST_SUITE_END()

