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

/*!
 * \brief               General ledger entity class.
 * \ingroup             gldatabase
 */
class GLEntity {
    public:

        /*!
         * \brief           Constructor.
         * \param id        Entity ID.
         * \param name      Entity name.
         * \param shortname Entity short name.
         * \param parent    Parent entity ID.
         * \param aggregate Aggregate entity flag.
         * \param enabled   Enabled flag.
         */
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

        /*!
         * \brief               Returns the entity ID.
         * \returns             The entity ID.
         */
        size_t id() const { return m_id; }

        /*!
         * \brief               Returns the entity name.
         * \returns             The entity name.
         */
        const std::string& name() const { return m_name; }

        /*!
         * \brief               Returns the entity short name.
         * \returns             The entity short name.
         */
        const std::string& shortname() const { return m_shortname; }

        /*!
         * \brief               Returns the parent entity ID.
         * \returns             The parent entity ID.
         */
        size_t parent() const { return m_parent; }

        /*!
         * \brief               Returns the aggregate entity flag.
         * \returns             The aggregate entity flag.
         */
        size_t aggregate() const { return m_aggregate; }

        /*!
         * \brief               Returns the enabled flag.
         * \returns             The enabled flag.
         */
        size_t enabled() const { return m_enabled; }

    private:

        /*!  Entity ID  */
        const size_t m_id;

        /*!  Entity name  */
        std::string m_name;

        /*!  Entity short name  */
        std::string m_shortname;

        /*!  Parent entity ID  */
        const size_t m_parent;

        /*!  Aggregate entity flag  */
        const bool m_aggregate;

        /*!  Enabled flag  */
        bool m_enabled;

};              //  class GLEntity

}               //  namespace genleg

#endif          //  PG_GENERAL_LEDGER_ENTITY_H

