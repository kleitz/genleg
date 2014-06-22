/*!
 * \file            dbconn.cpp
 * \brief           Implementation of database connection class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "dbconn.h"

using namespace gldb;

DBConn::DBConn(DBConnImp * imp) : m_imp(imp) {
}

DBConn::~DBConn() {
    delete m_imp;
}

void DBConn::query(const std::string& sql_query) {
    m_imp->query(sql_query);
}

Table DBConn::select(const std::string& query) {
    return m_imp->select(query);
}

void DBConn::begin_transaction() {
    m_imp->begin_transaction();
}

void DBConn::rollback_transaction() {
    m_imp->rollback_transaction();
}

void DBConn::commit_transaction() {
    m_imp->commit_transaction();
}

unsigned long long DBConn::last_auto_increment() {
    return m_imp->last_auto_increment();
}

