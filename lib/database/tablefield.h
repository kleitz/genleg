/*!
 * \file            tablefield.h
 * \brief           Interface to table field class
 * \details         Interface to table field class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DATABASE_DATASTRUCT_TABLEFIELD_H
#define PG_DATABASE_DATASTRUCT_TABLEFIELD_H

#include <iostream>
#include <string>

namespace gldb {

class TableField {
    public:
        TableField ();
        TableField (const char * data);
        TableField (const std::string& data);
        ~TableField ();

        size_t length() const;

        operator std::string () const;
        TableField& operator=(const char * data);
        TableField& operator=(const std::string& data);
        char& operator[](const size_t idx);
        const char& operator[](const size_t idx) const;
        TableField& operator+=(const char& c);
        TableField& operator+=(const std::string& data);

        friend std::ostream& operator<< (std::ostream& out,
                const TableField& field);

    private:
        std::string m_data;

};              //  class TableField

std::ostream& operator<< (std::ostream& out, const TableField& field);

}               //  namespace gldb

#endif          //  PG_DATABASE_DATASTRUCT_TABLEFIELD_H
