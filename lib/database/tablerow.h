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

        /*!  Destructor  */
        ~TableRow ();

        /*!
         * \brief           Returns the number of fields.
         * \returns         The number of fields.
         */
        size_t size() const;

        /*!
         * \brief           Overridden index operator.
         * \param idx       The zero-based index of the field.
         * \returns         A reference to the field at the specified index.
         */
        TableField& operator[](const size_t idx);

        /*!
         * \brief           Overridden index operator.
         * \param idx       The zero-based index of the field.
         * \returns         A const reference to the field at the
         * specified index.
         */
        const TableField& operator[](const size_t idx) const;

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
         * \brief           Appends a field to the row.
         * \param new_field A field from which to copy.
         */
        void append_field(const TableField& new_field);

        /*!
         * \brief           Prints a row.
         * \param stream    The ostream to which to print.
         */
        void print(std::ostream& stream) const;

    private:
        /*!  A vector of fields  */
        std::vector<TableField> m_fields;

};              //  class TableRow

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLEROW_H

