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
#include <string>
#include <type_traits>

#include "osql/clauses/clause.h"


export module osql.columns.column;

import osql.columns.constraints.bases;
import osql.clauses.type_name_clauses;


//===========================================================================
namespace osql::columns
{

    //=======================================================================
    /* The internal definition of constraints as associated with columns definitions. */
    class ColumnConstraints
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /* Value constructor. */
        template<typename... ColsConstraintsT>
        inline ColumnConstraints(const ColsConstraintsT&... column_constraints) noexcept
        {
            constraints_text = m_get_constraints_text(column_constraints...);
        }

        ColumnConstraints() noexcept = default;                         // Default empty constructor
        ColumnConstraints(const ColumnConstraints&) noexcept = default; // Default copy constructor
        ColumnConstraints(ColumnConstraints&&) noexcept = default;      // Default move constructor
        virtual ~ColumnConstraints() noexcept = default;                // Default destructor

        //---   Attributes   ------------------------------------------------
        std::string  constraints_text;  // the text of the whole constraints that are associated with a same column.

    private:
        /* Gets the text of this column constraints. */
        template< typename FirstConstraintT, typename... ConstraintsT >
            requires std::derived_from<FirstConstraintT, osql::columns::constraints::ColumnConstraintType>
        inline std::string  m_get_constraints_text(const FirstConstraintT& first_constraint,
                                                   const ConstraintsT&...  next_constraints)
        {
            return osql::clauses::T(first_constraint) + ' ' + m_get_constraints_text(next_constraints...);
        }

        /* Gets the text of the very last constraint for this column. */
        template<typename LastConstraintT>
            requires std::derived_from<LastConstraintT, osql::columns::constraints::ColumnConstraintType>
        inline std::string  m_get_constraints_text(const LastConstraintT& last_constraint)
        {
            return osql::clauses::T(last_constraint);
        }

    };


    //=======================================================================
    /** @brief The class of untyped Columns.
    *
    * Instantiate this class when defining a column with no specified
    * type affinity. Otherwise, see TypedColumn.
    */
    export class Column : public ColumnConstraints
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with sole column name) */
        inline Column(const std::string& column_name) noexcept
            : name{ column_name }
            , ColumnConstraints{}
        {}


        /** @brief Value constructor (with column name + column constraints). */
        template<typename... ColsConstraintsT>
        inline Column(const std::string&         column_name,
                      const ColsConstraintsT&... column_constraints) noexcept
            : name{ column_name }
            , ColumnConstraints{ column_constraints... }
        {}


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
        [[nodiscard]] inline const std::string get_text() const noexcept
        {
            if (constraints_text.empty())
                return name;
            else
                return std::format("{:s} {:s}", name, constraints_text);
        }


        /** @brief Unmutable std::string casting operator. */
        [[nodiscard]] inline operator const std::string() const noexcept
        {
            return get_text();
        }


        //---   Attributes   ------------------------------------------------
        std::string  name;  //!< the name of this column.
    };


    //=======================================================================
    /** @brief The class of typed Columns.
    *
    * Instantiate this class when defining a column with a specified
    * type affinity. Otherwise, see Column.
    */
    export class TypedColumn : public ColumnConstraints
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with column name + type name). */
        inline TypedColumn(const std::string& column_name,
                           const osql::clauses::TypeName& type_name_clause)
            : name{ column_name }
            , type_name{ osql::clauses::T(type_name_clause) }
            , ColumnConstraints{}
        {}


        /** @brief Value constructor (with column name + type name + column constraints). */
        template<typename... ColsConstraintsT>
        inline TypedColumn(const std::string& column_name,
                           const osql::clauses::TypeName& type_name_clause,
                           const ColsConstraintsT&...      column_constraints) noexcept
            : name{ column_name }
            , type_name{ osql::clauses::T(type_name_clause) }
            , ColumnConstraints{ column_constraints... }
        {}


        /** @brief Deleted empty constructor. */
        TypedColumn() noexcept = delete;

        /** @brief Default copy constructor. */
        TypedColumn(const TypedColumn&) noexcept = default;

        /** @brief Default move constructor. */
        TypedColumn(TypedColumn&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~TypedColumn() noexcept = default;


        //---   Operations / Operators   ------------------------------------
        /** @brief Gets the full text of this clause. */
        [[nodiscard]] inline const std::string get_text() const noexcept
        {
            if (constraints_text.empty()) {
                if (type_name.empty())
                    return name;
                else
                    return std::format("{:s} {:s}", name, type_name);
            }
            else {
                if (type_name.empty())
                    return std::format("{:s} {:s}", name, constraints_text);
                else
                    return std::format("{:s} {:s} {:s}", name, type_name, constraints_text);
            }
        }


        /** @brief Unmutable std::string casting operator. */
        [[nodiscard]] inline operator const std::string() const noexcept
        {
            return get_text();
        }


        //---   Attributes   ------------------------------------------------
        std::string  name;       //!< the name of this column.
        std::string  type_name;  //!< the name of the type associated with this column.
    };

}