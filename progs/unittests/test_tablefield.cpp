/*
 *  test_tablefield.cpp
 *  ===================
 *  Copyright 2014 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for TableField class.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include "database/database.h"

using namespace gldb;

BOOST_AUTO_TEST_SUITE(tablefield_suite)

BOOST_AUTO_TEST_CASE(tablefield_construct_default) {
    TableField field;

    //  Check default construction yields zero length

    BOOST_CHECK_EQUAL(field.length(), 0);

    //  Check default construction yields empty string contents

    const std::string empty_string;
    const std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, empty_string);
}

BOOST_AUTO_TEST_CASE(tablefield_construct_char) {
    const char * data = "this is a value";
    TableField field{data};

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 15);

    //  Check correct contents are yielded

    const std::string test_string = field;
    const std::string control_string{"this is a value"};
    BOOST_CHECK_EQUAL(test_string, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_construct_string_copy) {
    std::string data{"some data"};
    TableField field{data};

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 9);

    //  Check correct contents are yielded

    const std::string control_string{"some data"};
    const std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, control_string);

    //  Check copied string is unaltered

    BOOST_CHECK_EQUAL(data.length(), 9);
    BOOST_CHECK_EQUAL(data, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_construct_string_move) {
    std::string data{"some data"};
    TableField field{std::move(data)};

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 9);

    //  Check correct contents are yielded

    const std::string control_string{"some data"};
    const std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, control_string);

    //  Check moved string is empty

    const std::string empty_string;
    BOOST_CHECK_EQUAL(data.length(), 0);
    BOOST_CHECK_EQUAL(data, empty_string);
}

BOOST_AUTO_TEST_CASE(tablefield_construct_field_copy) {
    TableField field1{"some data"};
    TableField field2{field1};

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field2.length(), 9);

    //  Check correct contents are yielded

    const std::string control_string{"some data"};
    const std::string test_string2 = field2;
    BOOST_CHECK_EQUAL(test_string2, control_string);

    //  Check original field remains unaltered

    const std::string test_string1 = field1;
    BOOST_CHECK_EQUAL(field1.length(), 9);
    BOOST_CHECK_EQUAL(test_string1, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_construct_field_move) {
    TableField field1{"some data"};
    TableField field2{std::move(field1)};

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field2.length(), 9);

    //  Check correct contents are yielded

    const std::string control_string{"some data"};
    const std::string test_string2 = field2;
    BOOST_CHECK_EQUAL(test_string2, control_string);

    //  Check original field is cleared

    const std::string empty_string;
    const std::string test_string1 = field1;
    BOOST_CHECK_EQUAL(field1.length(), 0);
    BOOST_CHECK_EQUAL(test_string1, empty_string);
}

BOOST_AUTO_TEST_CASE(tablefield_assign_char) {
    TableField field{"this will be overwritten soon"};
    const char * data = "something different";
    field = data;

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 19);

    //  Check correct contents are yielded

    const std::string control_string{"something different"};
    const std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_assign_string_copy) {
    std::string test1{"original data"};
    std::string test2{"replacement data"};
    TableField field{test1};
    field = test2;

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 16);

    //  Check correct contents are yielded

    const std::string test_string = field;
    const std::string control_string{"replacement data"};
    BOOST_CHECK_EQUAL(test_string, control_string);

    //  Check original string remains unaltered

    BOOST_CHECK_EQUAL(test2, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_assign_string_move) {
    std::string test1{"original data"};
    std::string test2{"replacement data"};
    TableField field{test1};
    field = std::move(test2);

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field.length(), 16);

    //  Check correct contents are yielded

    const std::string test_string = field;
    const std::string control_string{"replacement data"};
    BOOST_CHECK_EQUAL(test_string, control_string);

    //  Check original string is empty

    /*  g++ 4.7.2 will not pass these tests, disable  */

    //const std::string empty_string;
    //BOOST_CHECK_EQUAL(test2.length(), 0);
    //BOOST_CHECK_EQUAL(test2, empty_string);
}

BOOST_AUTO_TEST_CASE(tablefield_assign_field_copy) {
    TableField field1{"original data"};
    TableField field2{"replacement data"};
    field1 = field2;

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field1.length(), 16);

    //  Check correct contents are yielded

    const std::string control_string{"replacement data"};
    const std::string test_string1 = field1;
    BOOST_CHECK_EQUAL(test_string1, control_string);

    //  Check copied field remains unaltered

    BOOST_CHECK_EQUAL(field2.length(), 16);
    const std::string test_string2 = field2;
    BOOST_CHECK_EQUAL(test_string2, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_assign_field_move) {
    TableField field1{"original data"};
    TableField field2{"replacement data"};
    field1 = std::move(field2);

    //  Check correct length is yielded

    BOOST_CHECK_EQUAL(field1.length(), 16);

    //  Check correct contents are yielded

    const std::string control_string{"replacement data"};
    const std::string test_string1 = field1;
    BOOST_CHECK_EQUAL(test_string1, control_string);

    //  Check copied field is emptied.

    /*  g++ 4.7.2 will not pass these tests, disable  */

    //BOOST_CHECK_EQUAL(field2.length(), 0);
    //const std::string empty_string;
    //const std::string test_string2 = field2;
    //BOOST_CHECK_EQUAL(test_string2, empty_string);
}

BOOST_AUTO_TEST_CASE(tablefield_index_read) {
    TableField field{"fork"};
    BOOST_CHECK_EQUAL(field[0], 'f');
    BOOST_CHECK_EQUAL(field[1], 'o');
    BOOST_CHECK_EQUAL(field[2], 'r');
    BOOST_CHECK_EQUAL(field[3], 'k');
}

BOOST_AUTO_TEST_CASE(tablefield_index_write) {
    TableField field{"Clock struck one."};
    field[13] = 't';
    field[14] = 'w';
    field[15] = 'o';

    const std::string control_string{"Clock struck two."};
    const std::string test_string = field;
    BOOST_CHECK_EQUAL(test_string, control_string);
}

BOOST_AUTO_TEST_CASE(tablefield_string_append_char) {
    TableField field("start");
    field += '1';
    field += '2';
    std::string check_string("start12");
    std::string test_string = field;
    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(tablefield_string_append_string) {
    TableField field("start");
    std::string app_string(" and end");
    field += app_string;
    std::string check_string("start and end");
    std::string test_string = field;
    BOOST_CHECK_EQUAL(check_string, test_string);
}

BOOST_AUTO_TEST_CASE(tablefield_length) {
    TableField field("some data");
    BOOST_CHECK_EQUAL(field.length(), 9U);
    BOOST_CHECK(field.length() != 8U);
    BOOST_CHECK(field.length() != 10U);
}

BOOST_AUTO_TEST_SUITE_END()

