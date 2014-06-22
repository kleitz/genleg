/*
 *  test_journal.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for journal entry class.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <string>
#include "gldb/gldb.h"

using namespace genleg;
using pgutils::Currency;

BOOST_AUTO_TEST_SUITE(journal_entry_suite)

BOOST_AUTO_TEST_CASE(je_create_basic) {
    GLJournal j{1, 6, 2014, "MANUAL", "Test journal entry"};
    BOOST_CHECK_EQUAL(j.entity(), 1);
    BOOST_CHECK_EQUAL(j.period(), 6);
    BOOST_CHECK_EQUAL(j.year(), 2014);
    BOOST_CHECK_EQUAL(j.source(), std::string{"MANUAL"});
    BOOST_CHECK_EQUAL(j.memo(), std::string{"Test journal entry"});
    BOOST_CHECK_EQUAL(j.num_lines(), 0);
    BOOST_CHECK(j.balances());
}

BOOST_AUTO_TEST_CASE(je_create_lines_balance) {
    GLJournal j{1, 6, 2014, "MANUAL", "Test journal entry"};
    j.add_line("1000", Currency{1000, 15});
    j.add_line("2000", Currency{1500, 35});
    j.add_line("3000", Currency{-2500, 50});
    BOOST_CHECK_EQUAL(j.num_lines(), 3);
    BOOST_CHECK(j.balances());
}

BOOST_AUTO_TEST_CASE(je_create_lines_nobalance) {
    GLJournal j{1, 6, 2014, "MANUAL", "Test journal entry"};
    j.add_line("1000", Currency{1000, 15});
    j.add_line("2000", Currency{1500, 35});
    j.add_line("3000", Currency{-2500, 49});
    BOOST_CHECK_EQUAL(j.num_lines(), 3);
    BOOST_CHECK(!j.balances());
}

BOOST_AUTO_TEST_CASE(je_create_from_file) {
    std::ifstream ifs;
    ifs.open("progs/unittests/example.je");
    BOOST_CHECK(ifs.is_open());
    GLJournal j = journal_from_stream(ifs);

    BOOST_CHECK_EQUAL(j.entity(), 1);
    BOOST_CHECK_EQUAL(j.period(), 4);
    BOOST_CHECK_EQUAL(j.year(), 2014);
    BOOST_CHECK_EQUAL(j.source(), std::string{"SAMPLE"});
    BOOST_CHECK_EQUAL(j.memo(), std::string{"Test journal entry"});

    BOOST_CHECK_EQUAL(j.num_lines(), 3);
    BOOST_CHECK(j.balances());

    BOOST_CHECK_EQUAL(j[0].account(), std::string{"1000"});
    BOOST_CHECK_EQUAL(j[1].account(), std::string{"2000"});
    BOOST_CHECK_EQUAL(j[2].account(), std::string{"3000"});

    Currency c1{1000, 15};
    Currency c2{1500, 35};
    Currency c3{-2500, 50};
    BOOST_CHECK(j[0].amount() == c1);
    BOOST_CHECK(j[1].amount() == c2);
    BOOST_CHECK(j[2].amount() == c3);
}

BOOST_AUTO_TEST_SUITE_END()

