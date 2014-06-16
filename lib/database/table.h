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
 * \brief       No such field exception class
 * \ingroup     database
 */
class TableNoSuchField : public TableException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableNoSuchField(const std::string& msg) :
            TableException(msg) {};
};

/*!
 * \brief       No such record exception class
 * \ingroup     database
 */
class TableNoSuchRecord : public TableException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableNoSuchRecord(const std::string& msg) :
            TableException(msg) {};
};

/*!
 * \brief       Mismatched record length exception class
 * \ingroup     database
 */
class TableMismatchedRecordLength : public TableException {
    public:
        /*!
         * \brief           Constructor
         * \param msg       Database error message
         */
        explicit TableMismatchedRecordLength(const std::string& msg) :
            TableException(msg) {};
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

        /*!
         * \brief           Constructor with move semantics.
         * \param headers   Table row containing field names.
         */
        explicit Table (TableRow&& headers);

        /*!
         * \brief           Copy constructor.
         * \bug             `explicit` removed from here after failure to
         * compile at end of MySQL query function.
         * \param table     Table to copy.
         */
        Table (const Table& table);

        /*!
         * \brief           Move constructor.
         * \param table     Table to move.
         */
        explicit Table (Table&& table);

        /*!
         * \brief           Copy assignment operator.
         * \param table     Table to copy.
         * \returns         Reference to the assigned-to table.
         */
        Table& operator=(const Table& table);

        /*!
         * \brief           Move assignment operator.
         * \param table     Table to move.
         * \returns         Reference to the assigned-to table.
         */
        Table& operator=(Table&& table);

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
        void set_quoted(const std::vector<bool>& vec);

        /*!
         * \brief           Sets the quote flags for the records with move
         * semantics.
         * \param vec       A vector of bools. The size must match the
         * size of the records.
         */
        void set_quoted(std::vector<bool>&& vec);

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
         * \brief               Appends a record to the table with move
         * semantics.
         * \param new_record    The record to append.
         */
        void append_record(TableRow&& new_record);

        /*!
         * \brief               Creates a table from an input file.
         * \param filename      The name of the input file.
         * \param delim         The delimiting character.
         * \returns             The table.
         * \throws              TableBadInputFile on badly formed input file.
         * \throws              TableCouldNotOpenInputFile on bad filename.
         */
        static Table create_from_file(const std::string& filename,
                                      const char delim);

        /*!
         * \brief               Creates an SQL INSERT query from a table record.
         * \param table_name    The name of the table into which to INSERT.
         * \param idx           The index of the record.
         * \returns             A string containing the query.
         */
        std::string insert_query(const std::string& table_name,
                                 const size_t idx);

        /*!
         * \brief               Gets a field from a record by field name.
         * \param field_name    The name of the field.
         * \param row_index     The index of the row.
         * \returns             The contents ofthe field.
         * \throws              TableNoSuchField if `field_name` is not a
         * valid field name.
         * \throws              TableNoSuchRecord if there is no record
         * at index `row_index`.
         */
        std::string get_field(const std::string& field_name,
                              const size_t row_index);

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
