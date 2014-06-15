/*
 *  test_user_password.cpp
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for user password functions.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <boost/test/unit_test.hpp>

#include "gldb/gldb.h"

using namespace genleg;

BOOST_AUTO_TEST_SUITE(user_password_suite)

BOOST_AUTO_TEST_CASE(user_password_check_good) {
    std::vector<std::string> v;
    GLUser user("", "", "", "", "", "", std::move(v), true);
    std::string passwd("filigree");
    user.set_password(passwd);
    BOOST_CHECK(user.check_password(passwd));
}

BOOST_AUTO_TEST_CASE(user_password_check_bad) {
    std::vector<std::string> v;
    GLUser user("", "", "", "", "", "", std::move(v), true);
    std::string passwd("filigree");
    user.set_password(passwd);
    std::string badpass("enormity");
    BOOST_CHECK(!user.check_password(badpass));
}

BOOST_AUTO_TEST_SUITE_END()

