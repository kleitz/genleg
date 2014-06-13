/*!
 * \file            tablerow.h
 * \brief           Interface to table row data structure
 * \details         Interface to table row data structure
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

class TableRow {
    public:
        TableRow ();
        TableRow (const size_t size);
        ~TableRow ();
        size_t size() const;
        TableField& operator[](const size_t idx);
        const TableField& operator[](const size_t idx) const;
        void append_field(const char * new_field);
        void append_field(const std::string& new_field);
        void append_field(const TableField& new_field);
        void print(std::ostream& stream) const;

    private:
        std::vector<TableField> m_fields;

};              //  class TableRow

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLEROW_H

