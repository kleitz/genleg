/*!
 * \file            dbsqlstatements.cpp
 * \brief           Implementation of SQL statement class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <sstream>
#include "dbsqlstatements.h"

using namespace genleg;

DBSQLStatements::DBSQLStatements() {
}

DBSQLStatements::~DBSQLStatements() {
}

std::string DBSQLStatements::create_table(const std::string& table_name) const {
    std::string query;

    if ( table_name == "standing_data" ) {
        query = "CREATE TABLE standing_data ("
        "    organization   VARCHAR(100)    NOT NULL,"
        "    current_year   INTEGER         NOT NULL,"
        "    current_period INTEGER         NOT NULL,"
        "    num_periods    INTEGER         NOT NULL,"
        "  CONSTRAINT standing_data_pk"
        "    PRIMARY KEY (organization)"
        ");";
    }
    else if ( table_name == "users" ) {
        query = "CREATE TABLE users ("
        "    id         INTEGER     NOT NULL AUTO_INCREMENT,"
        "    user_name  VARCHAR(30) NOT NULL UNIQUE,"
        "    first_name VARCHAR(30) NOT NULL,"
        "    last_name  VARCHAR(30) NOT NULL,"
        "    pass_hash  VARCHAR(30) NOT NULL DEFAULT 'Not set',"
        "    pass_salt  VARCHAR(30) NOT NULL DEFAULT 'XX',"
        "    enabled    BOOLEAN     NOT NULL DEFAULT FALSE,"
        "    created    TIMESTAMP   NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "  CONSTRAINT users_pk"
        "    PRIMARY KEY (id)"
        ");";
    }
    else if ( table_name == "perms" ) {
        query = "CREATE TABLE perms ("
        "    id             INTEGER         NOT NULL AUTO_INCREMENT,"
        "    name           VARCHAR(10)     NOT NULL UNIQUE,"
        "    description    VARCHAR(100)    NOT NULL,"
        "  CONSTRAINT perms_pk"
        "    PRIMARY KEY (id)"
        ");";
    }
    else if ( table_name == "user_perms" ) {
        query = "CREATE TABLE user_perms ("
        "    userid         INTEGER         NOT NULL,"
        "    permid         INTEGER         NOT NULL,"
        "    addedby        INTEGER         NOT NULL,"
        "    created        TIMESTAMP       NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "  CONSTRAINT user_perms_pk"
        "    PRIMARY KEY (userid, permid),"
        "  CONSTRAINT user_perms_userid_fk"
        "    FOREIGN KEY (userid)"
        "    REFERENCES users(id),"
        "  CONSTRAINT user_perms_permid_fk"
        "    FOREIGN KEY (permid)"
        "    REFERENCES perms(id),"
        "  CONSTRAINT user_perms_addedby_fk"
        "    FOREIGN KEY (addedby)"
        "    REFERENCES users(id)"
        ");";
    }
    else if ( table_name == "entities" ) {
        query = "CREATE TABLE entities ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    name       VARCHAR(100)    NOT NULL,"
        "    shortname  VARCHAR(10)     NOT NULL,"
        "    currency   CHAR(30)        NOT NULL DEFAULT 'USD',"
        "    parent     INT             NOT NULL,"
        "    aggregate  BOOLEAN         NOT NULL DEFAULT FALSE,"
        "    enabled    BOOLEAN         NOT NULL DEFAULT TRUE,"
        "  CONSTRAINT entities_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT entities_parent_fk"
        "    FOREIGN KEY (parent)"
        "    REFERENCES entities(id)"
        ");";
    }
    else if ( table_name == "jesrcs" ) {
        query = "CREATE TABLE jesrcs ("
        "    name           VARCHAR(10)     NOT NULL,"
        "    description    VARCHAR(100)    NOT NULL,"
        "  CONSTRAINT jesrcs_pk"
        "    PRIMARY KEY (name)"
        ");";
    }
    else if ( table_name == "nomaccts" ) {
        query = "CREATE TABLE nomaccts ("
        "    num            VARCHAR(20)     NOT NULL,"
        "    description    VARCHAR(100)    NOT NULL,"
        "    enabled        BOOLEAN         NOT NULL DEFAULT TRUE,"
        "  CONSTRAINT nomaccts"
        "    PRIMARY KEY (num)"
        ");";
    }
    else if ( table_name == "jes" ) {
        query = "CREATE TABLE jes ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    user       INTEGER         NOT NULL,"
        "    period     INTEGER         NOT NULL,"
        "    year       INTEGER         NOT NULL,"
        "    source     VARCHAR(10)     NOT NULL,"
        "    entity     INTEGER         NOT NULL,"
        "    memo       VARCHAR(100)    NOT NULL,"
        "    posted     TIMESTAMP       NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "  CONSTRAINT jes_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT jes_user_fk"
        "    FOREIGN KEY (user)"
        "    REFERENCES users(id),"
        "  CONSTRAINT jes_entity_fk"
        "    FOREIGN KEY (entity)"
        "    REFERENCES entities(id),"
        "  CONSTRAINT jes_source_fk"
        "    FOREIGN KEY (source)"
        "    REFERENCES jesrcs(name)"
        ");";
    }
    else if ( table_name == "jelines" ) {
        query = "CREATE TABLE jelines ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    je         INTEGER         NOT NULL,"
        "    account    VARCHAR(20)     NOT NULL,"
        "    amount     DECIMAL(20,2)   NOT NULL,"
        "  CONSTRAINT jelines_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT jes_je_fk"
        "    FOREIGN KEY (je)"
        "    REFERENCES jes(id),"
        "  CONSTRAINT jes_account_fk"
        "    FOREIGN KEY (account)"
        "    REFERENCES nomaccts(num)"
        ");";
    }
    else {
        throw "Unrecognized table.";
    }

    return query;
}

std::string DBSQLStatements::drop_table(const std::string& table_name) const {
    std::ostringstream ss;
    ss << "DROP TABLE " << table_name;
    return ss.str();
}

std::string DBSQLStatements::create_view(const std::string& view_name) const {
    std::string query;

    if ( view_name == "current_trial_balance" ) {
        query = "CREATE VIEW current_trial_balance AS"
        "  SELECT"
        "    j.entity AS 'Entity',"
        "    a.num AS 'A/C No.',"
        "    a.description AS 'Description',"
        "    sum(l.amount) AS 'Balance'"
        "    FROM nomaccts AS a"
        "    LEFT OUTER JOIN jelines AS l"
        "      ON a.num = l.account"
        "    INNER JOIN jes AS j"
        "      ON l.je = j.id"
        "    GROUP BY j.entity, a.num"
        "    ORDER BY j.entity ASC, l.account ASC";
    }
    else if ( view_name == "check_total" ) {
        query = "CREATE VIEW check_total AS"
        "  SELECT"
        "    Entity,"
        "    sum(Balance) AS 'Check Total'"
        "    FROM current_trial_balance"
        "    GROUP BY Entity"
        "    ORDER BY Entity ASC";
    }
    else if ( view_name == "all_jes" ) {
        query = "CREATE VIEW all_jes AS"
        "  SELECT"
        "    l.je AS 'JE',"
        "    j.entity AS 'En',"
        "    l.account AS 'A/C No.',"
        "    a.description AS 'Description',"
        "    l.amount AS 'Amount'"
        "    FROM jelines AS l"
        "    INNER JOIN jes AS j"
        "      ON j.id = l.je"
        "    INNER JOIN nomaccts AS a"
        "      ON a.num = l.account"
        "    ORDER BY j.id ASC, l.account ASC";
    }

    return query;
}

std::string DBSQLStatements::drop_view(const std::string& view_name) const {
    std::ostringstream ss;
    ss << "DROP VIEW " << view_name;
    return ss.str();
}

std::string DBSQLStatements::user_by_id(const std::string& user_id) const {
    std::ostringstream ss;
    ss << "SELECT * FROM users WHERE id = " << user_id;
    return ss.str();
}

std::string DBSQLStatements::user_by_username(const std::string& user_name) const {
    std::ostringstream ss;
    ss << "SELECT * FROM users WHERE user_name = '" << user_name << "'";
    return ss.str();
}

std::string DBSQLStatements::update_user(const GLUser& user) const {
    std::ostringstream ss;
    std::string enabled = (user.enabled() ? "TRUE" : "FALSE");
    ss << "UPDATE users SET user_name = '" << user.username()
       << "', first_name = '" << user.firstname()
       << "', last_name = '" << user.lastname()
       << "', pass_hash = '" << user.pass_hash()
       << "', pass_salt = '" << user.pass_salt()
       << "', enabled = " << enabled
       << " WHERE id = " << user.id();
    return ss.str();
}

std::string DBSQLStatements::post_je(const unsigned int user,
                    const unsigned int entity,
                    const int period,
                    const int year,
                    const std::string& source,
                    const std::string& memo) const
{
    std::ostringstream ss;
    ss << "INSERT INTO jes "
       << "  (user, period, year, source, entity, memo)"
       << "  VALUES ("
       << user << ", " << period << ", " << year << ", '"
       << source << "', " << entity << ", '" << memo << "')";
   return ss.str(); 
}

std::string DBSQLStatements::post_je_line(const unsigned long long je,
        const std::string account,
        const std::string amount) const
{
    std::ostringstream ss;
    ss << "INSERT INTO jelines "
       << "  (je, account, amount)"
       << "  VALUES ("
       << je << ", '" << account << "', " << amount << ")";
    return ss.str();
}

std::string DBSQLStatements::get_perms(const std::string& user_id) const {
    std::ostringstream ss;
    ss << "SELECT p.name AS Permission FROM perms AS p "
       << "INNER JOIN user_perms AS u ON u.permid = p.id "
       << "WHERE u.userid = " << user_id << " "
       << "ORDER BY name ASC";
    return ss.str();
}

std::string DBSQLStatements::grant(const std::string& user_id,
                                   const std::string& perm) const {
    std::ostringstream ss;
    ss << "INSERT INTO user_perms(userid, permid, addedby) "
       << "SELECT u.id, p.id, 1 "
       << "FROM users AS u "
       << "LEFT OUTER JOIN perms AS p "
       << "ON p.name = '" << perm << "' "
       << "WHERE u.id = " << user_id;
    return ss.str();
}

std::string DBSQLStatements::revoke(const std::string& user_id,
                                    const std::string& perm) const {
    std::ostringstream ss;
    ss << "DELETE FROM user_perms "
       << "WHERE userid IN "
       << "  (SELECT id FROM users WHERE id = " << user_id << ")"
       << "AND permid IN "
       << "  (SELECT id FROM perms WHERE name = '" << perm << "')";
    return ss.str();
}

std::string DBSQLStatements::currenttb() const {
    return "SELECT * FROM current_trial_balance";
}

std::string DBSQLStatements::currenttb_by_entity(
        const std::string& entity) const
{
    return std::string{"SELECT * FROM current_trial_balance WHERE Entity = "} +
           entity;
}

std::string DBSQLStatements::listusers() const {
    std::ostringstream ss;
    ss << "SELECT"
       << "  id AS 'ID',"
       << "  user_name AS 'Username',"
       << "  first_name AS 'First Name',"
       << "  last_name AS 'Last Name',"
       << "  CASE enabled"
       << "    WHEN TRUE"
       << "      THEN 'Yes'"
       << "    WHEN FALSE"
       << "      THEN 'No'"
       << "    ELSE 'Unknown'"
       << "  END"
       << "    AS 'Enabled?'"
       << "  FROM users"
       << "  ORDER BY id ASC";
    return ss.str();
}


