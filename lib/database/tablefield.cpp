/*!
 * \file            tablefield.cpp
 * \brief           Implementation of table field class
 * \details         Implementation of table field class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include "tablefield.h"


using namespace gldb;

std::ostream& gldb::operator<< (std::ostream& out, const TableField& field) {
    out << field.m_data;
    return out;
}

/*!
 * \brief           Constructor for TableField class
 */

TableField::TableField() : m_data("") {
}

TableField::TableField(const char * data) : m_data (data) {
}

TableField::TableField(const std::string& data) : m_data (data) {
}

TableField::operator std::string () const {
    return m_data;
}

TableField& TableField::operator=(const char * data) {
    m_data = data;
    return *this;
}

TableField& TableField::operator=(const std::string& data) {
    m_data = data;
    return *this;
}

char& TableField::operator[](const size_t idx) {
    return m_data[idx];
}

const char& TableField::operator[](const size_t idx) const {
    return m_data[idx];
}

TableField& TableField::operator+=(const char& c) {
    m_data += c;
    return *this;
}

TableField& TableField::operator+=(const std::string& data) {
    m_data += data;
    return *this;
}

size_t TableField::length() const {
    return m_data.length();
}

/*!
 * \brief           Destructor for TableField class
 */

TableField::~TableField() {
}
