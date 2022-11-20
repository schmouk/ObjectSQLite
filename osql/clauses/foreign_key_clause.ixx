/*
MIT License

Copyright (c) 2022 Philippe Schmouker, ph.schmouker (at) gmail.com

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//===========================================================================
module;

#include <concepts>
#include <format>

#include "osql/clauses/clause.h"


export module osql.clauses.foreign_key_clauses;

import osql.clauses;
import osql.clauses.deferrable_clauses;
import osql.clauses.foreign_key_subclauses;
import osql.clauses.foreign_table_subclauses;


//===========================================================================
namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with tables definitions.
    //

    //=======================================================================
    /** @brief STR definition for REFERENCES clauses. */
    using ReferencesStr = osql::clauses::STR< 'R', 'E', 'F', 'E', 'R', 'E', 'N', 'C', 'E', 'S', 0 >;


    //=======================================================================
    /** @brief The class of Foreign Key Clauses as included in columns and tables constraints. */
    export class ForeignKeyClause : public osql::clauses::Clause< ReferencesStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< ReferencesStr >;  //!< Wrapper to the base class.


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value Constructor (with sole foreign table specification). */
        inline ForeignKeyClause(const osql::clauses::ForeignTableSubclause& foreign_table_subclause) noexcept
            : MyBaseClass(foreign_table_subclause.get_text())
        {}

        /** @brief Value constructor (foreign-table and deferrable subclauses specs. */
        template<typename DefPrefixT, typename DefSuffixT>
        inline ForeignKeyClause(const osql::clauses::ForeignTableSubclause&                    foreign_table_subclause,
                                const osql::clauses::DeferrableClause<DefPrefixT, DefSuffixT>& deferrable_subclause) noexcept
            : MyBaseClass(std::format("{:s}  {:s}", foreign_table_subclause.get_text(), deferrable_subclause.get_text()))
        {}

        /** @brief Value constructor (foreign-table and at least one ForeignKeySubclause specs. */
        template<typename... SubclausesT>
        inline ForeignKeyClause(const osql::clauses::ForeignTableSubclause& foreign_table_subclause,
                                const SubclausesT&...                              subclauses) noexcept
            : MyBaseClass()
        {
            set_text(std::format("{:s}  {:s}", foreign_table_subclause.get_text(), m_get_subclauses_text(subclauses...)));
        }

        /** @brief Value constructor (foreign-table, at least one ForeignKeySubclause and deferrable specs. */
        template<typename DefPrefixT, typename DefSuffixT, typename... SubclausesT>
            requires std::derived_from<osql::clauses::ForeignKeySubclause, SubclausesT...>
            //requires std::derived_from<SubclausesT..., osql::clauses::ForeignKeySubclause>
        ForeignKeyClause(const osql::clauses::ForeignTableSubclause&                    foreign_table_subclause,
                         const SubclausesT&...                                          subclauses,
                         const osql::clauses::DeferrableClause<DefPrefixT, DefSuffixT>& deferrable_subclause) noexcept
            : MyBaseClass()
        {
            set_text(std::format("{:s}  {:s}  {:s}", foreign_table_subclause.get_text(), m_get_subclauses_text(subclauses), deferrable_subclause.get_text()));
        }

        /** @brief Deleted empty constructor. */
        ForeignKeyClause() noexcept = delete;

        /** @brief Default copy constructor. */
        ForeignKeyClause(const ForeignKeyClause&) noexcept = default;

        /** @brief Default move constructor. */
        ForeignKeyClause(ForeignKeyClause&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~ForeignKeyClause() noexcept = default;


        //---   Assignments operatorsd   ------------------------------------
        /** Brief Default copy assignment. */
        ForeignKeyClause& operator= (const ForeignKeyClause&) noexcept = default;

        /** @brief Default move assignment. */
        ForeignKeyClause& operator= (ForeignKeyClause&&) noexcept = default;


    private:
        //---   Operations   ------------------------------------------------
                /** @brief Gets the text of the list of columns names. */
        template<typename FirstSubclauseT, typename ...SubclausesT>
        [[nodiscard]] std::string m_get_subclauses_text(const FirstSubclauseT& first_subclause, const SubclausesT&... subclauses) noexcept
        {
            return std::format("{}  {}", first_subclause.get_text(), m_get_subclauses_text(subclauses...));
        }

        /** @brief Gets the text of the very last columns name in list. */
        template<typename LastSubclauseT>
        [[nodiscard]] std::string m_get_subclauses_text(const LastSubclauseT& last_subclause) noexcept
        {
            return last_subclause.get_text();
        }

    };

}