/*!
 * \file            glexception.h
 * \brief           Interface to General Ledger base exception class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_EXCEPTION_H
#define PG_GENERAL_LEDGER_GL_EXCEPTION_H

#include <string>
#include <stdexcept>

namespace genleg {

/*!
 * \brief       Base general ledger database exceptionc class.
 * \ingroup     gldatabase
 */
class GLDBException : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit GLDBException(const std::string& msg) :
            std::runtime_error(msg) {};
};

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_GL_EXCEPTION_H

