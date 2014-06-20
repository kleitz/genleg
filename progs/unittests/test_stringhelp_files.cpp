/*
 *  test_stringhelp_files.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for string file stream functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "pgutils/pgutils.h"

using namespace pgutils;

BOOST_AUTO_TEST_SUITE(stringhelp_stream_suite)

BOOST_AUTO_TEST_CASE(test_next_content_line) {
    std::stringstream ss;
    ss << "This is the first line\n"
       << "This is the second line\n"
       << "This is the last line\n";

    std::string test_string;
    BOOST_CHECK(next_content_line(ss, test_string));
    BOOST_CHECK_EQUAL(test_string, "This is the first line");
    BOOST_CHECK(next_content_line(ss, test_string));
    BOOST_CHECK_EQUAL(test_string, "This is the second line");
    BOOST_CHECK(next_content_line(ss, test_string));
    BOOST_CHECK_EQUAL(test_string, "This is the last line");
    BOOST_CHECK(!next_content_line(ss, test_string));
}

BOOST_AUTO_TEST_CASE(test_next_content_line_no_data) {
    std::stringstream ss;
    std::string test_string;
    BOOST_CHECK(!next_content_line(ss, test_string));
    BOOST_CHECK_EQUAL(test_string, "");
}

BOOST_AUTO_TEST_CASE(test_content_lines) {
    std::stringstream ss;
    ss << "This is the first line\n"
       << "This is the second line\n"
       << "This is the last line\n";

    std::vector<std::string> vec;
    content_lines(vec, ss);

    BOOST_CHECK_EQUAL(vec.size(), 3);
    BOOST_CHECK_EQUAL(vec[0], "This is the first line");
    BOOST_CHECK_EQUAL(vec[1], "This is the second line");
    BOOST_CHECK_EQUAL(vec[2], "This is the last line");
}

BOOST_AUTO_TEST_CASE(test_content_lines_no_data) {
    std::stringstream ss;
    std::vector<std::string> vec;
    content_lines(vec, ss);
    BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_split_lines) {
    std::stringstream ss;
    ss << "one:two:three\n"
       << "four:five\n"
       << "six:seven:eight:nine\n";
    std::vector<std::vector<std::string>> vec;
    split_lines(vec, ss, ':');

    BOOST_CHECK_EQUAL(vec.size(), 3);

    std::vector<std::string> v1 = vec[0];
    BOOST_CHECK_EQUAL(v1.size(), 3);
    BOOST_CHECK_EQUAL(v1[0], "one");
    BOOST_CHECK_EQUAL(v1[1], "two");
    BOOST_CHECK_EQUAL(v1[2], "three");

    std::vector<std::string> v2 = vec[1];
    BOOST_CHECK_EQUAL(v2.size(), 2);
    BOOST_CHECK_EQUAL(v2[0], "four");
    BOOST_CHECK_EQUAL(v2[1], "five");

    std::vector<std::string> v3 = vec[2];
    BOOST_CHECK_EQUAL(v3.size(), 4);
    BOOST_CHECK_EQUAL(v3[0], "six");
    BOOST_CHECK_EQUAL(v3[1], "seven");
    BOOST_CHECK_EQUAL(v3[2], "eight");
    BOOST_CHECK_EQUAL(v3[3], "nine");
}

BOOST_AUTO_TEST_CASE(test_split_lines_no_data) {
    std::stringstream ss;
    std::vector<std::vector<std::string>> vec;
    split_lines(vec, ss, ':');
    BOOST_CHECK_EQUAL(vec.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

