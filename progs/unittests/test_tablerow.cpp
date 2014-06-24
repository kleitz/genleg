/*
 *  test_tablerow.cpp
 *  =================
 *  Copyright 2014 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for TableRow class.
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

BOOST_AUTO_TEST_SUITE(tablerow_suite)

BOOST_AUTO_TEST_CASE(tablerow_for_range) {
    std::vector<std::string> data{"data", "some more", "a bit of data"};
    TableRow row{data};
   
    //  Just check that the for range construct works

    size_t i = 0;
    for ( auto& field : row ) {
        BOOST_CHECK_EQUAL(field.length(), data[i].length());
        const std::string content = field;
        BOOST_CHECK_EQUAL(data[i++], content);
    }
}

BOOST_AUTO_TEST_CASE(tablerow_for_range_const) {
    std::vector<std::string> data{"data", "some more", "a bit of data"};
    const TableRow row{data};
   
    //  Just check that the for range construct works

    size_t i = 0;
    for ( const auto& field : row ) {
        BOOST_CHECK_EQUAL(field.length(), data[i].length());
        const std::string content = field;
        BOOST_CHECK_EQUAL(data[i++], content);
    }
}

BOOST_AUTO_TEST_CASE(tablerow_construct_size) {
    TableRow row{5};

    //  Check size is as requested

    BOOST_CHECK_EQUAL(row.size(), 5);

    //  Check all fields are empty

    const std::string empty_string;
    for ( auto& field : row ) {
        BOOST_CHECK_EQUAL(field.length(), 0);
        const std::string content = field;
        BOOST_CHECK_EQUAL(content, empty_string);
    }
}

BOOST_AUTO_TEST_CASE(tablerow_construct_string_vector_copy) {
    const std::vector<std::string> control{"a", "bc", "def", "ghij"};
    std::vector<std::string> vec{"a", "bc", "def", "ghij"};
    TableRow row{vec};

    //  Check population of row

    BOOST_CHECK_EQUAL(row.size(), 4);
    size_t i = 0;
    for ( auto& field: row ) {
        const std::string test_string = field;
        BOOST_CHECK_EQUAL(test_string, control[i++]);
    }

    //  Check original vector still intact

    BOOST_CHECK_EQUAL(vec.size(), 4);
    i = 0;
    for ( auto& s: vec ) {
        BOOST_CHECK_EQUAL(s, control[i++]);
    }
}

BOOST_AUTO_TEST_CASE(tablerow_construct_string_vector_move) {
    const std::vector<std::string> control{"a", "bc", "def", "ghij"};
    std::vector<std::string> vec{"a", "bc", "def", "ghij"};
    TableRow row{std::move(vec)};

    //  Check population of row

    BOOST_CHECK_EQUAL(row.size(), 4);
    size_t i = 0;
    for ( auto& field: row ) {
        const std::string test_string = field;
        BOOST_CHECK_EQUAL(test_string, control[i++]);
    }

    //  Check original vector strings have been cleared

    BOOST_CHECK_EQUAL(vec.size(), 4);
    const std::string empty_string;
    for ( auto& s: vec ) {
        BOOST_CHECK_EQUAL(s, empty_string);
    }
}

BOOST_AUTO_TEST_CASE(tablerow_construct_initlist_copy) {
    TableRow row{"these", "are", "bits", "of", "data"};

    //  Check size and sample of contents

    BOOST_CHECK_EQUAL(row.size(), 5);
    BOOST_CHECK_EQUAL(static_cast<std::string>(row[0]), "these");
    BOOST_CHECK_EQUAL(static_cast<std::string>(row[2]), "bits");
    BOOST_CHECK_EQUAL(static_cast<std::string>(row[4]), "data");
}

BOOST_AUTO_TEST_CASE(tablerow_construct_row_copy) {
    TableRow row1{"some", "stuff"};
    TableRow row2{row1};

    //  Check row2 constructed as expected

    BOOST_CHECK_EQUAL(row2.size(), 2);
    const std::string control2_1 = row2[0];
    const std::string control2_2 = row2[1];
    BOOST_CHECK_EQUAL(control2_1, "some");
    BOOST_CHECK_EQUAL(control2_2, "stuff");

    //  Check row1 unaffected

    BOOST_CHECK_EQUAL(row1.size(), 2);
    const std::string control1_1 = row1[0];
    const std::string control1_2 = row1[1];
    BOOST_CHECK_EQUAL(control1_1, "some");
    BOOST_CHECK_EQUAL(control1_2, "stuff");
}

BOOST_AUTO_TEST_CASE(tablerow_construct_row_move) {
    TableRow row1{"some", "stuff"};
    TableRow row2{std::move(row1)};

    //  Check row2 constructed as expected

    BOOST_CHECK_EQUAL(row2.size(), 2);
    const std::string control2_1 = row2[0];
    const std::string control2_2 = row2[1];
    BOOST_CHECK_EQUAL(control2_1, "some");
    BOOST_CHECK_EQUAL(control2_2, "stuff");

    //  Check row1 emptied

    BOOST_CHECK_EQUAL(row1.size(), 0);
}

BOOST_AUTO_TEST_CASE(tablerow_assign_row_copy) {
    TableRow row1{"these", "are", "bits", "of", "data"};
    TableRow row2{"different", "stuff"};
    row1 = row2;

    //  Check row1 updated

    BOOST_CHECK_EQUAL(row1.size(), 2);
    const std::string control1_1 = row1[0];
    const std::string control1_2 = row1[1];
    BOOST_CHECK_EQUAL(control1_1, "different");
    BOOST_CHECK_EQUAL(control1_2, "stuff");

    //  Check row2 unaffected

    BOOST_CHECK_EQUAL(row2.size(), 2);
    const std::string control2_1 = row2[0];
    const std::string control2_2 = row2[1];
    BOOST_CHECK_EQUAL(control2_1, "different");
    BOOST_CHECK_EQUAL(control2_2, "stuff");
}

BOOST_AUTO_TEST_CASE(tablerow_assign_row_move) {
    TableRow row1{"these", "are", "bits", "of", "data"};
    TableRow row2{"different", "stuff"};
    row1 = std::move(row2);

    //  Check row1 updated

    BOOST_CHECK_EQUAL(row1.size(), 2);
    const std::string control1_1 = row1[0];
    const std::string control1_2 = row1[1];
    BOOST_CHECK_EQUAL(control1_1, "different");
    BOOST_CHECK_EQUAL(control1_2, "stuff");

    //  Check row2 emptied

    BOOST_CHECK_EQUAL(row2.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

