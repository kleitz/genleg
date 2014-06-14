/*!
 * \file            tablerow.cpp
 * \brief           Implementation of database table row data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sstream>
#include "tablerow.h"
#include "stringhelp/stringhelp.h"

using namespace gldb;

TableRow::TableRow() : m_fields() {
}

TableRow::TableRow(const size_t size) : m_fields(size) {
}

TableRow::TableRow(std::vector<std::string>& vec) : m_fields(vec.size()) {
    for ( size_t i = 0; i < vec.size(); ++i ) {
        m_fields[i] = vec[i];
    }
}

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
    TableField nf(new_field);
    m_fields.push_back(nf);
}

void TableRow::append_field(const std::string& new_field) {
    TableField nf(new_field);
    m_fields.push_back(nf);
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

std::string TableRow::record_string(const std::vector<bool>& quoted) {
    std::vector<std::string> vec;
    for ( size_t i = 0; i < m_fields.size(); ++i ) {
        std::ostringstream field;
        std::string q = quoted[i] ? "'" : "";
        field << q << m_fields[i] << q;
        vec.push_back(field.str());
    }
    std::string result;
    pgstring::join(vec, result, ',');
    return result;
}

std::string TableRow::record_string() {
    std::vector<std::string> vec;
    for ( size_t i = 0; i < m_fields.size(); ++i ) {
        vec.push_back(m_fields[i]);
    }
    std::string result;
    pgstring::join(vec, result, ',');
    return result;
}

