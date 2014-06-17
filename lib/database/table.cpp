/*!
 * \file            table.cpp
 * \brief           Implementation of database table data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "table.h"
#include "stringhelp/stringhelp.h"

using namespace gldb;
using namespace pgstring;

Table::Table(const TableRow& headers) :
    m_headers(headers), m_records(), m_quoted(headers.size()) {
    for ( size_t i = 0; i < m_quoted.size(); ++i ) {
        m_quoted[0] = true;
    }
}

Table::Table (TableRow&& headers) :
    m_headers(std::move(headers)), m_records(), m_quoted(m_headers.size()) {
    for ( size_t i = 0; i < m_quoted.size(); ++i ) {
        m_quoted[0] = true;
    }
}

Table::Table (const Table& table) :
    m_headers(table.m_headers),
    m_records(table.m_records),
    m_quoted(table.m_quoted)
{
}

Table::Table (Table&& table) :
    m_headers(std::move(table.m_headers)),
    m_records(std::move(table.m_records)),
    m_quoted(std::move(table.m_quoted))
{
}

Table& Table::operator=(const Table& table) {
    m_headers = table.m_headers;
    m_records = table.m_records;
    m_quoted = table.m_quoted;
    return *this;
}

Table& Table::operator=(Table&& table) {
    m_headers = std::move(table.m_headers);
    m_records = std::move(table.m_records);
    m_quoted = std::move(table.m_quoted);
    return *this;
}

Table::~Table() {
}

void Table::set_quoted(const std::vector<bool>& vec) {
    if (vec.size() != m_quoted.size()) {
        throw TableMismatchedRecordLength(std::to_string(vec.size()));
    }
    m_quoted = vec;
}

void Table::set_quoted(std::vector<bool>&& vec) {
    if (vec.size() != m_quoted.size()) {
        throw TableMismatchedRecordLength(std::to_string(vec.size()));
    }
    m_quoted = std::move(vec);
}

const TableRow& Table::operator[](const size_t idx) const {
    if ( idx >= m_records.size() ) {
        throw TableNoSuchRecord(std::to_string(idx));
    }
    return m_records[idx];
}

void Table::append_record(const TableRow& new_record) {
    if ( new_record.size() != m_headers.size() ) {
        throw TableMismatchedRecordLength(std::to_string(new_record.size()));
    }
    m_records.push_back(new_record);
}

void Table::append_record(TableRow&& new_record) {
    if ( new_record.size() != m_headers.size() ) {
        throw TableMismatchedRecordLength(std::to_string(new_record.size()));
    }
    m_records.push_back(std::move(new_record));
}

Table Table::create_from_file(const std::string& filename, const char delim) {
    std::ifstream ifs;
    ifs.open(filename);

    if ( ifs.is_open() ) {
        std::vector<std::vector<std::string>> vec;
        pgstring::split_lines(vec, ifs, delim);
        if ( vec.size() < 3 ) {
            throw TableBadInputFile(filename);
        }

        Table table{TableRow(std::move(vec[0]))};

        if ( vec[1].size() != table.num_fields() ) {
            throw TableBadInputFile(filename);
        }

        std::vector<bool> quotes(table.num_fields());
        for ( size_t i = 0; i < quotes.size(); ++i ) {
            if ( vec[1][i] == "unquoted" ) {
                quotes[i] = false;
            }
            else if ( vec[1][i] == "quoted" ) {
                quotes[i] = true;
            }
            else {
                throw TableBadInputFile(filename);
            }
        }
        table.set_quoted(std::move(quotes));

        for ( size_t i = 2; i < vec.size(); ++i ) {
            if ( vec[i].size() != table.num_fields() ) {
                throw TableBadInputFile(filename);
            }

            table.append_record(TableRow{std::move(vec[i])});
        }

        ifs.close();
        return table;
    }
    else {
        throw TableCouldNotOpenInputFile(filename);
    }
}

std::string Table::insert_query(const std::string& table_name,
                                const size_t idx) {
    std::ostringstream ss;
    ss << "INSERT INTO " << table_name << " "
       << "(" << m_headers.record_string() << ") "
       << "VALUES (" << m_records[idx].record_string(m_quoted) << ")";
    return ss.str();
}

std::string Table::get_field(const std::string& field_name,
                             const size_t row_index) {
    size_t col = 0;
    bool found = false;
    for ( size_t i = 0; i < m_headers.size(); ++i ) {
        std::string header = m_headers[i];
        if ( header == field_name ) {
            found = true;
            col = i;
            break;
        }
    }
    if ( !found ) {
        throw TableNoSuchField(field_name);
    }

    if ( row_index >= m_records.size() ) {
        throw TableNoSuchRecord(std::to_string(row_index));
    }
    return m_records[row_index][col];
}
 
