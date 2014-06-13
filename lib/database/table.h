/*!
 * \file            table.h
 * \brief           Interface to table data structure
 * \details         Interface to table data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DATASTRUCT_TABLE_H
#define PG_DATABASE_DATASTRUCT_TABLE_H

#include <vector>

#include "tablerow.h"

namespace gldb {

class Table {
    public:
        Table (const TableRow& headers);
        ~Table ();
        size_t num_fields() const;
        size_t num_records() const;
        const TableRow& get_headers() const;
        const TableRow& operator[](const size_t idx) const;
        void append_record(const TableRow& new_record);

    private:
        TableRow m_headers;
        std::vector<TableRow> m_records;

};              //  class Table

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLE_H
