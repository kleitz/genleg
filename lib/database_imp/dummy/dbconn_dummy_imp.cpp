/*!
 * \file            dbconn_dummy_imp.cpp
 * \brief           Implementation of Dummy database connection implementation class
 * \details         Implementation of Dummy database connection implementation class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <sstream>
#include "dbconn_dummy_imp.h"

using namespace gldb;

DBConnDummy::DBConnDummy(const std::string database,
        const std::string hostname, const std::string username,
        const std::string password) {
    (void)database;
    (void)hostname;
    (void)username;
    (void)password;
}

DBConnDummy::~DBConnDummy() {
}

Table DBConnDummy::select(std::string query) {
    const size_t num_fields = 4, num_records = 6;

    TableRow field_names(num_fields);
    for ( size_t i = 0; i < num_fields; ++i ) {
        std::ostringstream ss;
        ss << "Dummy header " << i + 1 << std::flush;
        field_names[i] = ss.str();
    }

    Table table(field_names);

    for ( size_t i = 0; i < num_records; ++i ) {
        TableRow record(num_fields);
        for ( size_t j = 0; j < num_fields; ++j ) {
            std::ostringstream ss;
            ss << "Dummy data " << i + 1 << "," << j + 1;
            record[j] = ss.str();
        }
        table.append_record(record);
    }

    (void)query;
    return table;
}


