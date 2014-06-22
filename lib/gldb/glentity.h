/*!
 * \file            glentity.h
 * \brief           Interface to general ledger entity class
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_ENTITY_H
#define PG_GENERAL_LEDGER_ENTITY_H

#include <string>

namespace genleg {

class GLEntity {
    public:
        GLEntity (const size_t id,
                  const std::string& name,
                  const std::string& shortname,
                  const size_t parent,
                  const bool aggregate,
                  const bool enabled) :
            m_id{id},
            m_name{name},
            m_shortname{shortname},
            m_parent{parent},
            m_aggregate{aggregate},
            m_enabled{enabled}
        {}

        size_t id() const { return m_id; }
        const std::string& name() const { return m_name; }
        const std::string& shortname() const { return m_shortname; }
        size_t parent() const { return m_parent; }
        size_t aggregate() const { return m_aggregate; }
        size_t enabled() const { return m_enabled; }

    private:
        const size_t m_id;
        std::string m_name;
        std::string m_shortname;
        const size_t m_parent;
        const bool m_aggregate;
        bool m_enabled;

};              //  class GLEntity

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_ENTITY_H

