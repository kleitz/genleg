/*!
 * \file            table.h
 * \brief           Interface to database table data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DATASTRUCT_TABLE_H
#define PG_DATABASE_DATASTRUCT_TABLE_H

#include <vector>

#include "tablerow.h"

namespace gldb {

/*!
 * \brief       Database table class
 * \ingroup     database
 */
class Table {
    public:
        /*!
         * \brief           Constructor.
         * \param headers   Table row containing field names.
         */
        explicit Table (const TableRow& headers);

        /*!  Destructor  */
        ~Table ();

        /*!
         * \brief           Returns the number of fields in each row.
         * \returns         The number of fields in each row.
         */
        size_t num_fields() const;

        /*!
         * \brief           Returns the number of record in the table.
         * \returns         The number of records in the table.
         */
        size_t num_records() const;

        /*!
         * \brief           Returns the field names.
         * \returns         The field names.
         */
        const TableRow& get_headers() const;

        /*!
         * \brief           Overloaded index operator.
         * \param idx       The zero-based index of the record.
         * \returns         The selected record.
         */
        const TableRow& operator[](const size_t idx) const;

        /*!
         * \brief               Appends a record to the table.
         * \param new_record    The record to append.
         */
        void append_record(const TableRow& new_record);

    private:
        /*!  The names of the fields  */
        TableRow m_headers;

        /*!  A vector of the records  */
        std::vector<TableRow> m_records;

};              //  class Table

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLE_H
