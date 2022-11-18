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

#include <string>

#include "osql/clauses/clause.h"


export module osql.columns.column;

import osql.columns.constraints.bases;
import osql.clauses.type_name_clauses;


//===========================================================================
export namespace osql::columns
{
    //=======================================================================
    /** @brief The base of Columns. */
    class Column
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with sole column name) */
        inline Column(const std::string& column_name) noexcept
            : name{ column_name }
            , type_name{}
            , constraints{}
        {}


        /** @brief Value constructor (with column name + type name). */
        inline Column(const std::string&                    column_name,
                      const osql::clauses::TypeNameClause&  type_name_clause)
            : name{ column_name }
            , type_name{ osql::clauses::T(type_name_clause) }
            , constraints{}
        {}


        /** @brief Value constructor (with column name + column constraints). */
        template<typename... ColsConstraintsT>
            //requires std::derived_from<ColsConstraintsT..., osql::columns::constraints::ColumnConstraintType>
        inline Column(const std::string&         column_name,
                      const ColsConstraintsT&... column_constraints) noexcept
            : name{ column_name }
            , type_name{}
            , constraints{}
        {
            constraints = m_get_constraints_text(column_constraints...);
        }


        /** @brief Value constructor (with column name + type name + column constraints). */
        template<typename... ColsConstraintsT>
            //requires std::derived_from<ColsConstraintsT..., osql::columns::constraints::ColumnConstraintType>
        inline Column(const std::string&                    column_name,
                      const osql::clauses::TypeNameClause&  type_name_clause,
                      const ColsConstraintsT&...            column_constraints) noexcept
            : name{ column_name }
            , type_name{ osql::clauses::T(type_name_clause) }
            , constraints{}
        {
            constraints = m_get_constraints_text(column_constraints...);
        }


        /** @brief Deleted empty constructor. */
        Column() noexcept = delete;

        /** @brief Default copy constructor. */
        Column(const Column&) noexcept = default;

        /** @brief Default move constructor. */
        Column(Column&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~Column() noexcept = default;


        //---   Operations / Operators   ------------------------------------
                /** @brief Gets the full text of this clause. */
        [[nodiscard]] const std::string get_text() const noexcept
        {
            std::string s{ name };

            if (!type_name.empty())
                s += " " + type_name;

            if (!constraints.empty())
                s += " " + constraints;

            return s;
        }


        /** @brief Unmutable std::string casting operator. */
        [[nodiscard]] inline operator const std::string() const noexcept
        {
            return get_text();
        }


        //---   Attributes   ------------------------------------------------
        std::string  name;          //!< the name of this column.
        std::string  type_name;     //!< the name of the type that is associated with this column.
        std::string  constraints;   //!< the text of the whole constraints that are associated with this column.


    private:
        /* Gets the text of this column constraints. */
        template< typename FirstConstraintT, typename... ConstraintsT >
        inline std::string  m_get_constraints_text(const FirstConstraintT& first_constraint,
                                                   const ConstraintsT&...  next_constraints)
        {
            return osql::clauses::T(first_constraint) + ' ' + m_get_constraints_text(next_constraints...);
        }

        /* Gets the text of the very last column constraint. */
        template<typename LastConstraintT>
        inline std::string  m_get_constraints_text(const LastConstraintT& last_constraint)
        {
            return osql::clauses::T(last_constraint);
        }
    };

}