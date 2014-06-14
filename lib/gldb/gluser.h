/*!
 * \file            gluser.h
 * \brief           Interface to user class
 * \details         Interface to user class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_GENERAL_LEDGER_GL_USER_H
#define PG_GENERAL_LEDGER_GL_USER_H

#include <string>

namespace genleg {

/*!
 * \brief           General ledger user class
 * \ingroup         gldatabase
 */
class GLUser {
    public:
        /*!
         * \brief           Constructor.
         * \param id        User ID
         * \param username  Username
         * \param firstname First name
         * \param lastname  Last name
         * \param enabled   `true` if user is enabled, `false` otherwise.
         */
        GLUser (const std::string id,
                const std::string username,
                const std::string firstname,
                const std::string lastname,
                const bool enabled);

        /*!  Destructor  */
        ~GLUser ();

        /*!
         * \brief           Returns the user ID.
         * \returns         The user ID.
         */
        std::string id() const;

        /*!
         * \brief           Returns the username.
         * \returns         The username.
         */
        std::string username() const;

        /*!
         * \brief           Returns the user's first name.
         * \returns         The user's first name.
         */
        std::string firstname() const;

        /*!
         * \brief           Returns the user's last name.
         * \returns         The user's last name.
         */
        std::string lastname() const;

        /*!
         * \brief           Returns the user's enabled status.
         * \returns         The user's enabled status.
         */
        bool enabled() const;

        /*!
         * \brief               Sets a user's username.
         * \param new_username  The user's new username.
         */
        void set_username(const std::string& new_username);

        /*!
         * \brief               Sets a user's first name.
         * \param new_firstname The user's new first name.
         */
        void set_firstname(const std::string& new_firstname);

        /*!
         * \brief               Sets a user's last name.
         * \param new_lastname  The user's new last name.
         */
        void set_lastname(const std::string& new_lastname);

        /*!
         * \brief               Sets a user's enabled status.
         * \param new_enabled   The user's new enabled status.
         */
        void set_enabled(const bool new_enabled);

    private:
        /*!  User ID  */
        std::string m_id;

        /*!  Username  */
        std::string m_username;

        /*!  User's first name  */
        std::string m_firstname;

        /*!  User's last name  */
        std::string m_lastname;

        /*!  User's enabled status  */
        bool m_enabled;

};              //  class GLUser

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GL_USER_H
