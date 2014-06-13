/*!
 * \file            table.cpp
 * \brief           Implementation of database table data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "table.h"

using namespace gldb;

Table::Table(const TableRow& headers) :
    m_headers(headers), m_records() {
}

Table::~Table() {
}

size_t Table::num_fields() const {
    return m_headers.size();
}

size_t Table::num_records() const {
    return m_records.size();
}

const TableRow& Table::get_headers() const {
    return m_headers;
}

const TableRow& Table::operator[](const size_t idx) const {
    return m_records[idx];
}

void Table::append_record(const TableRow& new_record) {
    if ( new_record.size() != m_headers.size() ) {
        throw "Record does not contain the same number of fields as header.";
    }
    m_records.push_back(new_record);
}

