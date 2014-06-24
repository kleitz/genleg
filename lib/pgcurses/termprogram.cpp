/*!
 * \file            termprogram.cpp
 * \brief           Implementation of main terminal program class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "termprogram.h"
#include "termprogramimp.h"

using namespace pgcurses;

TermProgram::TermProgram() :
    m_imp{std::unique_ptr<TermProgramImp> (new TermProgramImp)}
{
}

/*  Implemented here to allow for deletion of m_imp  */
TermProgram::~TermProgram()
{
}

void TermProgram::set_main_window(std::unique_ptr<TPMainWindow> mainwin)
{
    m_imp->set_main_window(std::move(mainwin));
}

void TermProgram::run() {
    m_imp->run();
}

void TermProgram::sleep(const unsigned int secs) const
{
    m_imp->sleep(secs);
}

