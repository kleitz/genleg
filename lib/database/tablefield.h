/*!
 * \file            tablefield.h
 * \brief           Interface to database table field class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DATASTRUCT_TABLEFIELD_H
#define PG_DATABASE_DATASTRUCT_TABLEFIELD_H

#include <iostream>
#include <string>

namespace gldb {

/*!
 * \brief       Database table field class
 * \ingroup     database
 */
class TableField {
    public:

        /*  Default constructor  */
        TableField ();

        /*!
         * \brief           Constructor accepting `const char *` data.
         * \param data      The initial contents of the field.
         */
        explicit TableField (const char * data);

        /*!
         * \brief           Constructor accepting `std:string` data.
         * \param data      The initial contents of the field.
         */
        TableField (const std::string& data);

        /*!
         * \brief           Constructor accepting `std:string` data with move
         * semantics.
         * \param data      The initial contents of the field.
         */
        TableField (std::string&& data);

        /*!
         * \brief           Copy constructor.
         * \param field     The field from which to copy.
         */
        TableField (const TableField& field);

        /*!
         * \brief           Move constructor.
         * \param field     The field from which to move.
         */
        TableField (TableField&& field);

        /*!  Destructor  */
        ~TableField ();

        /*!
         * \brief           Returns the length of the field.
         * \returns         The length of the field.
         */
        size_t length() const { return m_data.length(); }

        /*!
         * \brief           Overridden conversion operator.
         * \details         Returns the field contents as a string.
         */
        operator std::string () const { return m_data; }

        /*!
         * \brief           Overridden assignment operator for `const char *`.
         * \param data      The new contents of the field.
         * \returns         A reference to the same field.
         */
        TableField& operator=(const char * data);

        /*!
         * \brief           Overridden assignment operator for `std::string`.
         * \param data      The new contents of the field.
         * \returns         A reference to the same field.
         */
        TableField& operator=(const std::string& data);

        /*!
         * \brief           Overridden assignment operator for `std::string`
         * with move semantics.
         * \param data      The new contents of the field.
         * \returns         A reference to the same field.
         */
        TableField& operator=(std::string&& data);

        /*!
         * \brief           Overridden copy assignment operator.
         * \param field     The field to copy.
         * \returns         A reference to the same field.
         */
        TableField& operator=(const TableField& field);

        /*!
         * \brief           Overridden move assignment operator.
         * \param field     The field to move.
         * \returns         A reference to the same field.
         */
        TableField& operator=(TableField&& field);

        /*!
         * \brief           Overridden index operator.
         * \param idx       The desired index.
         * \returns         A reference to the character at the specified
         * index.
         */
        char& operator[](const size_t idx) { return m_data[idx]; }

        /*!
         * \brief           Overridden index operator.
         * \param idx       The desired index.
         * \returns         A const reference to the character at the specified
         * index.
         */
        const char& operator[](const size_t idx) const { return m_data[idx]; }

        /*!
         * \brief           Overridden compound assignment operator.
         * \param c         The character to append to the field.
         * \returns         A reference to the same field.
         */
        TableField& operator+=(const char c);

        /*!
         * \brief           Overridden compound assignment operator.
         * \param data      The string to append to the field.
         * \returns         A reference to the same field.
         */
        TableField& operator+=(const std::string& data);

        friend std::ostream& operator<< (std::ostream& out,
                const TableField& field);

    private:

        /*!  The field contents  */
        std::string m_data;

};              //  class TableField

/*!
 * \brief           Overridden << operator for printing a field.
 * \param out       The ostream to which to print.
 * \param field     A reference to the field.
 * \returns         A reference to `out`.
 */
std::ostream& operator<< (std::ostream& out, const TableField& field);

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLEFIELD_H

