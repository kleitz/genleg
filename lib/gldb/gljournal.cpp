/*!
 * \file            gljournal.cpp
 * \brief           Implementation of journal entry classes
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include "gljournal.h"
#include "glexception.h"

using namespace genleg;
using pgutils::Currency;
using pgutils::split_lines;
using pgutils::currency_from_string;

bool GLJournal::balances() const
{
    Currency sum;
    for ( const auto& line : m_lines ) {
        sum += line.amount();
    }
    return sum == Currency{0, 0};
}

GLJournal genleg::journal_from_stream(std::istream& ifs)
try
{
    std::vector<std::vector<std::string>> vec;
    split_lines(vec, ifs, ':');
    if ( vec.size() < 6 ) {
        throw GLDBException("Not enough lines in JE stream");
    }

    if ( vec[0][0] != "Entity" ) {
        throw GLDBException("First line of JE stream was not for 'Entity'");
    }
    const unsigned int entity = std::stoi(vec[0][1]);

    if ( vec[1][0] != "Period" ) {
        throw GLDBException("Second line of JE stream was not for 'Period'");
    }
    const int period = std::stoi(vec[1][1]);

    if ( vec[2][0] != "Year" ) {
        throw GLDBException("Third line of JE stream was not for 'Year'");
    }
    const int year = std::stoi(vec[2][1]);

    if ( vec[3][0] != "Source" ) {
        throw GLDBException("Fourth line of JE stream was not for 'Source'");
    }
    const std::string source{vec[3][1]};

    if ( vec[4][0] != "Memo" ) {
        throw GLDBException("Fifth line of JE stream was not for 'Memo'");
    }
    const std::string memo{vec[4][1]};

    GLJournal j{entity, period, year, source, memo};
    for ( size_t i = 5; i < vec.size(); ++i ) {
        j.add_line(vec[i][0], currency_from_string(vec[i][1]));
    }
        

    return j;
}
catch ( const GLDBException& e ) {
    throw e;
}
catch ( const std::invalid_argument& e ) {
    throw GLDBException("Invalid numeric argument");
}
catch ( ... ) {
    throw GLDBException("Unknown exception in journal_from_stream()");
}

