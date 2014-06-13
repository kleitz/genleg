/*
 *  test_config.cpp
 *  ===============
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

#include <iostream>
#include <string>
#include <memory>
#include "config/config.h"

BOOST_AUTO_TEST_SUITE(config_suite)

BOOST_AUTO_TEST_CASE(config_test_cmdline_is_set) {
    char arg1[] = "ut";
    char arg2[] = "--opt1";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt1", genleg::Argument::NO_ARG);
    config.add_cmdline_option("opt2", genleg::Argument::NO_ARG);
    config.populate_from_cmdline(2, argv);

    BOOST_CHECK(config.is_set("opt1"));
    BOOST_CHECK(config.is_set("opt2") == false);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_value_no_arg) {
    char arg1[] = "ut";
    char arg2[] = "--opt3";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt3", genleg::Argument::NO_ARG);
    config.populate_from_cmdline(2, argv);

    std::string empty_string;
    BOOST_CHECK_EQUAL(config["opt3"], empty_string);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_value_opt_arg) {
    char arg1[] = "ut";
    char arg2[] = "--opt4=turnip";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt4", genleg::Argument::OPT_ARG);
    config.populate_from_cmdline(2, argv);

    std::string test_string("turnip");
    BOOST_CHECK_EQUAL(config["opt4"], test_string);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_value_req_arg) {
    char arg1[] = "ut";
    char arg2[] = "--opt5=parsnip";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt5", genleg::Argument::REQ_ARG);
    config.populate_from_cmdline(2, argv);

    std::string test_string("parsnip");
    BOOST_CHECK_EQUAL(config["opt5"], test_string);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_empty_arg_noexcept) {
    char arg1[] = "ut";
    char arg2[] = "--opt6=";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt6", genleg::Argument::REQ_ARG);
    BOOST_CHECK_NO_THROW(config.populate_from_cmdline(2, argv));
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_missing_arg_except) {
    char arg1[] = "ut";
    char arg2[] = "--opt7";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt7", genleg::Argument::REQ_ARG);
    BOOST_CHECK_THROW(config.populate_from_cmdline(2, argv),
            genleg::ConfigBadOption);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_unexpected_arg_except) {
    char arg1[] = "ut";
    char arg2[] = "--opt8=marrow";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt8", genleg::Argument::NO_ARG);
    BOOST_CHECK_THROW(config.populate_from_cmdline(2, argv),
            genleg::ConfigBadOption);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_value_missing_except) {
    char arg1[] = "ut";
    char arg2[] = "--opt9";
    char * const argv[] = {arg1, arg2, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt9", genleg::Argument::NO_ARG);
    config.add_cmdline_option("opt10", genleg::Argument::NO_ARG);
    config.populate_from_cmdline(2, argv);

    BOOST_CHECK_THROW(config["opt10"], genleg::ConfigOptionNotSet);
}

BOOST_AUTO_TEST_CASE(config_test_cmdline_multiple_options) {
    char arg1[] = "ut";
    char arg2[] = "--opt11";
    char arg3[] = "--opt12=cucumber";
    char arg4[] = "--opt13";
    char arg5[] = "--opt14=carrot";
    char arg6[] = "--opt15";
    char * const argv[] = {arg1, arg2, arg3, arg4, arg5, arg6, nullptr};

    genleg::Config config;
    config.add_cmdline_option("opt11", genleg::Argument::NO_ARG);
    config.add_cmdline_option("opt12", genleg::Argument::OPT_ARG);
    config.add_cmdline_option("opt13", genleg::Argument::OPT_ARG);
    config.add_cmdline_option("opt14", genleg::Argument::REQ_ARG);
    config.add_cmdline_option("opt15", genleg::Argument::NO_ARG);
    config.populate_from_cmdline(6, argv);

    std::string empty_string("");
    std::string test_string_1("cucumber");
    std::string test_string_2("carrot");
    BOOST_CHECK_EQUAL(config["opt11"], empty_string);
    BOOST_CHECK_EQUAL(config["opt12"], test_string_1);
    BOOST_CHECK_EQUAL(config["opt13"], empty_string);
    BOOST_CHECK_EQUAL(config["opt14"], test_string_2);
    BOOST_CHECK_EQUAL(config["opt15"], empty_string);
}

BOOST_AUTO_TEST_SUITE_END()

