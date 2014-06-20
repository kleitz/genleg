/*
 *  test_stringhelp_trim.cpp
 *  ========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for string trim functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "pgutils/pgutils.h"

using namespace pgutils;

BOOST_AUTO_TEST_SUITE(stringhelp_trim_suite)

BOOST_AUTO_TEST_CASE(test_trim_front_alnum) {
    std::string test_string = "    wacka wacka  ";
    const std::string check_string = "wacka wacka  ";
    trim_front(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_front_all_spaces) {
    std::string test_string = "      ";
    const std::string check_string = "";
    trim_front(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_front_empty) {
    std::string test_string = "";
    const std::string check_string = "";
    trim_front(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_back_alnum) {
    std::string test_string = "    wacka wacka  ";
    const std::string check_string = "    wacka wacka";
    trim_back(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_back_all_spaces) {
    std::string test_string = "      ";
    const std::string check_string = "";
    trim_back(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_back_empty) {
    std::string test_string = "";
    const std::string check_string = "";
    trim_back(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_alnum) {
    std::string test_string = "    wacka wacka  ";
    const std::string check_string = "wacka wacka";
    trim(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_all_spaces) {
    std::string test_string = "      ";
    const std::string check_string = "";
    trim(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(test_trim_empty) {
    std::string test_string = "";
    const std::string check_string = "";
    trim(test_string);

    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_SUITE_END()

