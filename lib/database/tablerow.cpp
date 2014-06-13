/*!
 * \file            tablerow.cpp
 * \brief           Implementation of table row data structure
 * \details         Implementation of table row data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include "tablerow.h"

using namespace gldb;


/*!
 * \brief           Constructor for TableRow class
 */

TableRow::TableRow() : m_fields() {
}

TableRow::TableRow(const size_t size) : m_fields(size) {
}


/*!
 * \brief           Destructor for TableRow class
 */

TableRow::~TableRow() {
}

size_t TableRow::size() const {
    return m_fields.size();
}

TableField& TableRow::operator[](const size_t idx) {
    return m_fields[idx];
}

const TableField& TableRow::operator[](const size_t idx) const {
    return m_fields[idx];
}

void TableRow::append_field(const char * new_field) {
    m_fields.push_back(new_field);
}

void TableRow::append_field(const std::string& new_field) {
    m_fields.push_back(new_field);
}

void TableRow::append_field(const TableField& new_field) {
    m_fields.push_back(new_field);
}

void TableRow::print(std::ostream& stream) const {
    for ( auto& field : m_fields ) {
        stream << "[" << field << "] ";
    }
    stream << std::endl;
}

