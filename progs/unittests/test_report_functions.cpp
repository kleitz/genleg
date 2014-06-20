/*
 *  test_report_functions.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for reporting building functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "gldb/gldb.h"
#include "database/database.h"

using namespace gldb;
using namespace genleg;

BOOST_AUTO_TEST_SUITE(report_functions_suite)

BOOST_AUTO_TEST_CASE(test_plain_report) {
    TableRow headers{"h1", "h2", "h3"};
    Table table{headers};
    table.append_record(TableRow{"a", "ab", "abcd"});
    table.append_record(TableRow{"ef", "efgh", "e"});
    table.append_record(TableRow{"i", "ij", "ijklm"});

    const std::string test_report = plain_report_from_table(table);
    const std::string control_report{"h1 h2   h3    \n"
                                     "a  ab   abcd  \n"
                                     "ef efgh e     \n"
                                     "i  ij   ijklm \n"};

    BOOST_CHECK_EQUAL(test_report, control_report);
}

BOOST_AUTO_TEST_CASE(test_decorated_report) {
    TableRow headers{"h1", "h2", "h3"};
    Table table{headers};
    table.append_record(TableRow{"a", "ab", "abcd"});
    table.append_record(TableRow{"ef", "efgh", "e"});
    table.append_record(TableRow{"i", "ij", "ijklm"});

    const std::string test_report = decorated_report_from_table(table);
    const std::string control_report{"+----+------+-------+\n"
                                     "| h1 | h2   | h3    |\n"
                                     "+----+------+-------+\n"
                                     "| a  | ab   | abcd  |\n"
                                     "| ef | efgh | e     |\n"
                                     "| i  | ij   | ijklm |\n"
                                     "+----+------+-------+\n"};

    BOOST_CHECK_EQUAL(test_report, control_report);
}

BOOST_AUTO_TEST_SUITE_END()

