/*
 *  test_tablefield.cpp
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for Config class.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include "database/database.h"

BOOST_AUTO_TEST_SUITE(field_suite)

BOOST_AUTO_TEST_CASE(field_create_empty) {
    gldb::TableField field;
    std::string empty_string;
    std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, empty_string);
}

BOOST_AUTO_TEST_CASE(field_create_non_empty) {
    gldb::TableField field("this is a value");
    std::string test_string = field;
    std::string check_string("this is a value");
    BOOST_CHECK_EQUAL(test_string, check_string);
}

BOOST_AUTO_TEST_CASE(field_string_assign_field) {
    gldb::TableField field("this is a value");
    gldb::TableField field2("something different");
    field = field2;
    std::string test_string_1 = field;
    std::string test_string_2 = field2;
    BOOST_CHECK_EQUAL(test_string_1, test_string_2);
}

BOOST_AUTO_TEST_CASE(field_string_assign_string) {
    gldb::TableField field("this is a value");
    std::string data("something different");
    field = data;
    std::string check_string = field;
    BOOST_CHECK_EQUAL(check_string, data);
}

BOOST_AUTO_TEST_CASE(field_string_assign_cstring) {
    gldb::TableField field("this is a value");
    const char * data = "something different";
    field = data;
    std::string check_string = field;
    std::string test_string(data);
    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(field_string_append_char) {
    gldb::TableField field("start");
    field += '1';
    field += '2';
    std::string check_string("start12");
    std::string test_string = field;
    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(field_string_append_string) {
    gldb::TableField field("start");
    std::string app_string(" and end");
    field += app_string;
    std::string check_string("start and end");
    std::string test_string = field;
    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(field_length) {
    gldb::TableField field("some data");
    BOOST_CHECK_EQUAL(field.length(), 9U);
    BOOST_CHECK(field.length() != 8U);
    BOOST_CHECK(field.length() != 10U);
}

BOOST_AUTO_TEST_SUITE_END()

