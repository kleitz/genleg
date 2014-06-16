/*!
 * \file            tablefield.cpp
 * \brief           Implementation of database table field class
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

TableField::TableField() : m_data("") {} 

TableField::TableField(const char * data) : m_data (data) {}

TableField::TableField(const std::string& data) : m_data (data) {}

TableField::TableField(std::string&& data) : m_data (std::move(data)) {}

TableField::TableField(const TableField& field) : m_data (field.m_data) {}

TableField::TableField(TableField&& field)
    : m_data (std::move(field.m_data)) {}

TableField::~TableField() {
}

TableField& TableField::operator=(const char * data) {
    m_data = data;
    return *this;
}

TableField& TableField::operator=(const std::string& data) {
    m_data = data;
    return *this;
}

TableField& TableField::operator=(std::string&& data) {
    m_data = std::move(data);
    return *this;
}

TableField& TableField::operator=(const TableField& field) {
    m_data = field.m_data;
    return *this;
}

TableField& TableField::operator=(TableField&& field) {
    m_data = std::move(field.m_data);
    return *this;
}

TableField& TableField::operator+=(const char c) {
    m_data += c;
    return *this;
}

TableField& TableField::operator+=(const std::string& data) {
    m_data += data;
    return *this;
}

