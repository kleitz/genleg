/*!
 * \file            gluser.cpp
 * \brief           Implementation of user class
 * \details         Implementation of user class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gluser.h"

using namespace genleg;

GLUser::GLUser(const std::string id,
               const std::string username,
               const std::string firstname,
               const std::string lastname,
               const std::string pass_hash,
               const std::string pass_salt,
               const bool enabled) :
    m_id(id),
    m_username(username),
    m_firstname(firstname),
    m_lastname(lastname),
    m_enabled(enabled),
    m_pass_hash(pass_hash),
    m_pass_salt(pass_salt)
{
}

GLUser::~GLUser() {
}

std::string GLUser::id() const {
    return m_id;
}

std::string GLUser::username() const {
    return m_username;
}

std::string GLUser::firstname() const {
    return m_firstname;
}

std::string GLUser::lastname() const {
    return m_lastname;
}

bool GLUser::enabled() const {
    return m_enabled;
}

std::string GLUser::pass_hash() const {
    return m_pass_hash;
}

std::string GLUser::pass_salt() const {
    return m_pass_salt;
}

void GLUser::set_username(const std::string& new_username) {
    m_username = new_username;
}

void GLUser::set_firstname(const std::string& new_firstname) {
    m_firstname = new_firstname;
}

void GLUser::set_lastname(const std::string& new_lastname) {
    m_lastname = new_lastname;
}

void GLUser::set_enabled(const bool new_enabled) {
    m_enabled = new_enabled;
}

