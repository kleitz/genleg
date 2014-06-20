/*
 *  test_stringhelp_join.cpp
 *  ========================
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

#include "pgutils/pgutils.h"

using namespace pgutils;

BOOST_AUTO_TEST_SUITE(stringhelp_join_suite)

BOOST_AUTO_TEST_CASE(test_join_1) {
    std::vector<std::string> tokens = {"one", "two", "three"};

    std::string s;
    join(tokens, s, ':');
    BOOST_CHECK_EQUAL(s, "one:two:three");
}

BOOST_AUTO_TEST_CASE(test_join_2) {
    std::vector<std::string> tokens = {"two", "big", "scary", "clowns"};

    std::string s;
    join(tokens, s, ',');
    BOOST_CHECK_EQUAL(s, "two,big,scary,clowns");
}

BOOST_AUTO_TEST_CASE(test_join_no_data) {
    std::vector<std::string> tokens;

    std::string s;
    join(tokens, s, ',');
    BOOST_CHECK_EQUAL(s, "");
}

BOOST_AUTO_TEST_SUITE_END()

