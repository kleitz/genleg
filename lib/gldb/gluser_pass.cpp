/*!
 * \file            gluser_pass.cpp
 * \brief           Implementation of password functions for user class
 * \todo            Implement a better form of password encryption. In
 * particular, these functions are not re-entrant, and only use the first
 * 8 characters of the password.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro  */
#define _XOPEN_SOURCE 600

#include <random>
#include <functional>
#include <stdexcept>
#include <unistd.h>
#include "gluser.h"

using namespace genleg;

/*!
 * \brief           Generates a random two-character salt for crypt()
 * \returns         The two-character salt.
 */
static std::string generate_salt();

void GLUser::set_password(const std::string& new_pass) {
    m_pass_salt = generate_salt();
    if ( new_pass.length() < 8 ) {
        throw std::runtime_error("Password too short");
    }
    m_pass_hash = crypt(new_pass.c_str(), m_pass_salt.c_str());
}

bool GLUser::check_password(const std::string& check_pass) {
    if ( check_pass.length() < 8 ) {
        throw std::runtime_error("Password too short");
    }
    const std::string check_hash = crypt(check_pass.c_str(),
                                         m_pass_salt.c_str());
    return check_hash == m_pass_hash;
}

static std::string generate_salt() {
    static const char c[] = "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                            "0123456789./";

    std::default_random_engine re(std::random_device{}());
    std::uniform_int_distribution<int> ud{0, sizeof c - 2};
    static_assert((sizeof c - 2) == 63, "Range upper bound incorrect");
    auto gen = std::bind(ud, re);
                    
    std::string salt;
    salt += c[gen()];
    salt += c[gen()];
    return salt;
}

