/*
 *  test_stringhelp_split.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for string split functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "stringhelp/stringhelp.h"

using namespace pgstring;

BOOST_AUTO_TEST_SUITE(stringhelp_split_suite)

BOOST_AUTO_TEST_CASE(test_split) {
    std::string test_string = "one=two=three=four";
    std::vector<std::string> tokens = split(test_string, '=');

    BOOST_CHECK_EQUAL(tokens.size(), 4);
    BOOST_CHECK_EQUAL(tokens[0], "one");
    BOOST_CHECK_EQUAL(tokens[1], "two");
    BOOST_CHECK_EQUAL(tokens[2], "three");
    BOOST_CHECK_EQUAL(tokens[3], "four");
}

BOOST_AUTO_TEST_SUITE_END()

