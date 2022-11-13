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
#include <string>

#include "osql/clauses/clause.h"


export module osql.clauses.foreign_table_subclauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with tables definitions.
    //

    //=======================================================================
    /** @brief The  class for all Foriegn Table subclauses of Foreign Key Clauses, as included in columns and tables constraints.
    *
    * @see https://www.sqlite.org/foreignkeys.html to get  explanations
    *   about the use of FOREIGN KEYs in sqlite: they may be parsed but
    *   take  no  effect  or even they may be forbidden and trig errors
    *   according to defined macros used at sqlite compilation time.
    */
    class ForeignTableSubclause : public osql::clauses::NoPrefixClause<>
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (table name with no specified columns). */
        template<typename ...ColNamesT>
        //requires std::same_as<ColNamesT..., std::string>
        ForeignTableSubclause(const std::string& table_name) noexcept
            : osql::clauses::NoPrefixClause<>()
        {
            m_set_text(table_name);
        }

        /** @brief Value constructor (table name with at least one specified columns). */
        template<typename ...ColNamesT>
        //requires std::same_as<ColNamesT..., std::string>
        ForeignTableSubclause(const std::string& table_name, const ColNamesT&... columns_names) noexcept
            : osql::clauses::NoPrefixClause<>()
        {
            m_set_text(table_name, columns_names...);
        }

        /** @brief Deleted empty constructor. */
        ForeignTableSubclause() noexcept = delete;

        /** @brief Default copy constructor. */
        ForeignTableSubclause(const ForeignTableSubclause&) noexcept = default;

        /** @brief Default move constructor. */
        ForeignTableSubclause(ForeignTableSubclause&&) noexcept = default;

        /** @brief Destructor. */
        virtual ~ForeignTableSubclause() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] ForeignTableSubclause& operator= (const ForeignTableSubclause&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] ForeignTableSubclause& operator= (ForeignTableSubclause&&) noexcept = default;


    private:
        //---   Operations   ------------------------------------------------
        /** @brief Gets the text of the list of columns names. */
        template<typename FirstColNameT, typename ...ColNamesT>
        [[nodiscard]] std::string m_get_cols_names(const FirstColNameT& first_col_name, const ColNamesT&... col_names) noexcept
        {
            return std::string(first_col_name) + ", " + m_get_cols_names(col_names...);
        }

        /** @brief Gets the text of the very last columns name in list. */
        template<typename LastColNameT>
        [[nodiscard]] std::string m_get_cols_names(const LastColNameT& last_col_name) noexcept
        {
            return last_col_name;
        }

        /** @brief Sets the text associated with this subclause (1/2). */
        template<typename ...ColNamesT>
        inline void m_set_text(const std::string& table_name) noexcept
        {
            set_text(table_name);  // notice: method inherited from base class osql::Clause
        }

        /** @brief Sets the text associated with this subclause (2/2). */
        template<typename ...ColNamesT>
        inline void m_set_text(const std::string& table_name, const ColNamesT&... columns_names) noexcept
        {
            set_text(table_name + '(' + m_get_cols_names(columns_names...) + ')');  // notice: method inherited from base class osql::Clause
        }
    };

}
