/*
 *  test_stringhelp_replace.cpp
 *  ===========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for string replace functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "pgutils/pgutils.h"

using namespace pgutils;

BOOST_AUTO_TEST_SUITE(stringhelp_replace_suite)

BOOST_AUTO_TEST_CASE(test_replace_do_start) {
    std::string start = "hello good buddy";
    const std::string test_string = "goodbye good buddy";
    bool status = replace(start, "hello", "goodbye");

    BOOST_CHECK_EQUAL(status, true);
    BOOST_CHECK_EQUAL(start, test_string);
}

BOOST_AUTO_TEST_CASE(test_replace_do_end) {
    std::string start = "hello good buddy";
    const std::string test_string = "hello good frenemy";
    bool status = replace(start, "buddy", "frenemy");

    BOOST_CHECK_EQUAL(status, true);
    BOOST_CHECK_EQUAL(start, test_string);
}

BOOST_AUTO_TEST_CASE(test_replace_do_mid) {
    std::string start = "hello good buddy";
    const std::string test_string = "hello bad buddy";
    bool status = replace(start, "good", "bad");

    BOOST_CHECK_EQUAL(status, true);
    BOOST_CHECK_EQUAL(start, test_string);
}

BOOST_AUTO_TEST_CASE(test_replace_dont) {
    std::string start = "hello good buddy";
    const std::string test_string = "hello good buddy";
    bool status = replace(start, "friznit", "bad");

    BOOST_CHECK_EQUAL(status, false);
    BOOST_CHECK_EQUAL(start, test_string);
}

BOOST_AUTO_TEST_SUITE_END()

