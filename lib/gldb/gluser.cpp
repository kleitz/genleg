/*!
 * \file            gluser.cpp
 * \brief           Implementation of user class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gluser.h"

using namespace genleg;

GLUser::GLUser(const std::string& id,
               const std::string& username,
               const std::string& firstname,
               const std::string& lastname,
               const std::string& pass_hash,
               const std::string& pass_salt,
               std::vector<std::string>&& perms,
               const bool enabled) :
    m_id(id),
    m_username(username),
    m_firstname(firstname),
    m_lastname(lastname),
    m_pass_hash(pass_hash),
    m_pass_salt(pass_salt),
    m_perms(perms),
    m_enabled(enabled)
{
}

GLUser::~GLUser() {
}

const std::string& GLUser::id() const {
    return m_id;
}

const std::string& GLUser::username() const {
    return m_username;
}

const std::string& GLUser::firstname() const {
    return m_firstname;
}

const std::string& GLUser::lastname() const {
    return m_lastname;
}

const std::string& GLUser::pass_hash() const {
    return m_pass_hash;
}

const std::string& GLUser::pass_salt() const {
    return m_pass_salt;
}

const std::vector<std::string>& GLUser::permissions() const {
    return m_perms;
}

bool GLUser::enabled() const {
    return m_enabled;
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

