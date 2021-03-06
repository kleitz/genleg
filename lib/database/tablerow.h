/*!
 * \file            tablerow.h
 * \brief           Interface to database table row data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DATASTRUCT_TABLEROW_H
#define PG_DATABASE_DATASTRUCT_TABLEROW_H

#include <iostream>
#include <vector>
#include <string>

#include "tablefield.h"

namespace gldb {

/*!
 * \brief       Database table row class
 * \ingroup     database
 */
class TableRow {
    public:

        /*!  Default constructor  */
        TableRow ();

        /*!
         * \brief           Constructor with initial number of fields.
         * \param size      The initial number of fields.
         */
        explicit TableRow (const size_t size);

        /*!
         * \brief           Constructor with string vector.
         * \param vec       The vector.
         */
        explicit TableRow (const std::vector<std::string>& vec);

        /*!
         * \brief           Constructor with string vector and move semantics.
         * \param vec       The vector.
         */
        explicit TableRow (std::vector<std::string>&& vec);

        /*!
         * \brief           Constructor with std::string initializer list.
         * \param i         The initializer list.
         */
        explicit TableRow (std::initializer_list<std::string> i);

        /*!
         * \brief           Copy constructor.
         * \param row       The row to copy.
         */
        TableRow (const TableRow& row);

        /*!
         * \brief           Move constructor.
         * \param row       The row to move.
         */
        TableRow (TableRow&& row);

        /*!
         * \brief           Copy assignment operator.
         * \param row       The row to copy.
         * \returns         A reference to the assigned-to row.
         */
        TableRow& operator=(const TableRow& row);

        /*!
         * \brief           Move assignment operator.
         * \param row       The row to move.
         * \returns         A reference to the assigned-to row.
         */
        TableRow& operator=(TableRow&& row);

        /*!  Destructor  */
        ~TableRow ();

        /*!
         * \brief           Returns the number of fields.
         * \returns         The number of fields.
         */
        size_t size() const { return m_fields.size(); }

        /*!  Type definition for iterator  */
        using iterator = std::vector<TableField>::iterator;

        /*!
         * \brief           Returns iterator for beginning.
         * \returns         Iterator for beginning.
         */
        iterator begin() { return m_fields.begin(); }

        /*!
         * \brief           Returns iterator for end plus one.
         * \returns         Iterator for end plus one.
         */
        iterator end() { return m_fields.end(); }

        /*!  Type definition for const iterator  */
        using const_iterator = std::vector<TableField>::const_iterator;

        /*!
         * \brief           Returns const iterator for beginning.
         * \returns         Const iterator for beginning.
         */
        const_iterator begin() const { return m_fields.begin(); }

        /*!
         * \brief           Returns const iterator for end plus one.
         * \returns         Const iterator for end plus one.
         */
        const_iterator end() const { return m_fields.end(); }

        /*!
         * \brief           Overridden index operator.
         * \param idx       The zero-based index of the field.
         * \returns         A reference to the field at the specified index.
         */
        TableField& operator[](const size_t idx) { return m_fields[idx]; }

        /*!
         * \brief           Overridden index operator.
         * \param idx       The zero-based index of the field.
         * \returns         A const reference to the field at the
         * specified index.
         */
        const TableField& operator[](const size_t idx) const
                                                { return m_fields[idx];}

        /*!
         * \brief           Appends a field to the row.
         * \param new_field The contents of the new field.
         */
        void append_field(const char * new_field);

        /*!
         * \brief           Appends a field to the row.
         * \param new_field The contents of the new field.
         */
        void append_field(const std::string& new_field);

        /*!
         * \brief           Appends a field to the row with move semantics.
         * \param new_field The contents of the new field.
         */
        void append_field(std::string&& new_field);

        /*!
         * \brief           Appends a field to the row.
         * \param new_field A field from which to copy.
         */
        void append_field(const TableField& new_field);

        /*!
         * \brief           Appends a field to the row with move semantics.
         * \param new_field A field from which to copy.
         */
        void append_field(TableField&& new_field);

        /*!
         * \brief           Prints a row.
         * \param stream    The ostream to which to print.
         */
        void print(std::ostream& stream) const;

        /*!
         * \brief           Creates a comma separated string of fields.
         * \param quoted    A vector of \c bool, for each field `true` means
         * that field will be enclosed in single quotes in the comma separated
         * string, `false` means it will not be.
         * \returns         The comma separated string.
         */
        std::string record_string(const std::vector<bool>& quoted) const;

        /*!
         * \brief           Creates an unquoted comma separated string of
         * fields.
         * \returns         The unquoted comma separated string.
         */
        std::string record_string() const;

    private:

        /*!  A vector of fields  */
        std::vector<TableField> m_fields;

};              //  class TableRow

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLEROW_H

