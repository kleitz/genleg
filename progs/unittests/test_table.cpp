/*
 *  test_table.cpp
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for Table class.
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

BOOST_AUTO_TEST_SUITE(table_suite)

BOOST_AUTO_TEST_CASE(table_get_field) {
    std::vector<std::string> h({"h1", "h2", "h3", "h4"});
    std::vector<std::string> r1({"d1", "d2", "d3", "d4"});
    std::vector<std::string> r2({"d5", "d6", "d7", "d8"});
    std::vector<std::string> r3({"d9", "d10", "d11", "d12"});
    std::vector<bool> q({true, false, true, false});

    TableRow headers(h);
    TableRow record1(r1);
    TableRow record2(r2);
    TableRow record3(r3);

    Table table(headers);
    table.append_record(record1);
    table.append_record(record2);
    table.append_record(record3);
    table.set_quoted(q);

    BOOST_CHECK_EQUAL(table.num_records(), 3);
    BOOST_CHECK_EQUAL(table.num_fields(), 4);

    std::string test_string = table.get_field("h1", 0);
    BOOST_CHECK_EQUAL(test_string, "d1");

    test_string = table.get_field("h2", 1);
    BOOST_CHECK_EQUAL(test_string, "d6");

    test_string = table.get_field("h3", 2);
    BOOST_CHECK_EQUAL(test_string, "d11");

    test_string = table.get_field("h4", 1);
    BOOST_CHECK_EQUAL(test_string, "d8");

    BOOST_CHECK_THROW(table.get_field("h5", 0), TableNoSuchField);
    BOOST_CHECK_THROW(table.get_field("h3", 3), TableNoSuchRecord);

    std::string ins = table.insert_query("test", 1);
    test_string = "INSERT INTO test (h1,h2,h3,h4) VALUES ('d5',d6,'d7',d8)";
    BOOST_CHECK_EQUAL(ins, test_string);
}

BOOST_AUTO_TEST_SUITE_END()

