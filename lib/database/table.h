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
#include <stdexcept>

#include "tablerow.h"

namespace gldb {

/*!
 * \brief       Base database connection exception class
 * \ingroup     database
 */
class TableException : public std::runtime_error {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableException(const std::string& msg) :
            std::runtime_error(msg) {};
};

/*!
 * \brief       Could not connect to database exception class.
 * \ingroup     database
 */
class TableBadInputFile : public TableException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableBadInputFile(const std::string& msg) :
            TableException(msg) {};
};

/*!
 * \brief       Could not connect to database exception class.
 * \ingroup     database
 */
class TableCouldNotOpenInputFile : public TableException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableCouldNotOpenInputFile(const std::string& msg) :
            TableException(msg) {};
};

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
         * \brief           Sets the quote flags for the records
         * \param vec       A vector of bools. The size must match the
         * size of the records.
         */
        void set_quoted(std::vector<bool>& vec);

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

        /*!
         * \brief               Creates a table from an input file.
         * \param filename      The name of the input file.
         * \param delim         The delimiting character.
         * \returns             The table.
         * \throws              TableBadInputFile on badly formed input file.
         * \throws              TableCouldNotOpenInputFile on bad filename.
         */
        static Table create_from_file(const std::string filename,
                                      const char delim);

        /*!
         * \brief               Creates an SQL INSERT query from a table record.
         * \param table_name    The name of the table into which to INSERT.
         * \param idx           The index of the record.
         * \returns             A string containing the query.
         */
        std::string insert_query(const std::string table_name,
                                 const size_t idx);

    private:
        /*!  The names of the fields  */
        TableRow m_headers;

        /*!  A vector of the records  */
        std::vector<TableRow> m_records;

        /*!  A vector to show if fields should be quoted for INSERT  */
        std::vector<bool> m_quoted;

};              //  class Table

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLE_H
