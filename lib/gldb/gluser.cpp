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
               const bool enabled) :
    m_id(id),
    m_username(username),
    m_firstname(firstname),
    m_lastname(lastname),
    m_enabled(enabled)
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

