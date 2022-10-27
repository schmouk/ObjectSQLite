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


export module osql.clauses.select_clauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //=======================================================================
    // This module defines:
    //  - class SelectClause
    //  - class SelectAllClause
    //  - class SelectDistinctClause
    //

    //=======================================================================
    using SelectStr = STR<'S', 'E', 'L', 'E', 'C', 'T', 0>;

    /** @brief The class of SQL SELECT clauses as included in SQL statements. */
    class SelectClause : public osql::clauses::Clause<SelectStr>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause<SelectStr>;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline SelectClause(const std::string& select_text) noexcept
            : MyBaseClass(select_text)
        {}

        /** @brief Default empty constructor. */
        SelectClause() noexcept = default;

        /** @brief Default copy constructor. */
        SelectClause(const SelectClause&) noexcept = default;

        /** @brief Default move constructor. */
        SelectClause(SelectClause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~SelectClause() = default;
    };


    //=======================================================================
    using SelectAllStr = STR<'S', 'E', 'L', 'E', 'C', 'T', ' ', 'A', 'L', 'L', 0>;

    /** @brief The class of SQL WITH clauses as included in SQL statements. */
    class SelectAllClause : public osql::clauses::Clause<SelectAllStr>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause<SelectAllStr>;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline SelectAllClause(const std::string& select_text) noexcept
            : MyBaseClass(select_text)
        {}

        /** @brief Empty constructor. */
        inline SelectAllClause() noexcept = default;

        /** @brief Default copy constructor. */
        SelectAllClause(const SelectAllClause&) noexcept = default;

        /** @brief Default move constructor. */
        SelectAllClause(SelectAllClause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~SelectAllClause() = default;
    };


    //=======================================================================
    using SelectDistinctStr = STR<'S', 'E', 'L', 'E', 'C', 'T', ' ', 'D', 'I', 'S', 'T', 'I', 'N', 'C', 'T', 0>;

    /** @brief The class of SQL WITH clauses as included in SQL statements. */
    class SelectDistinctClause : public osql::clauses::Clause<SelectDistinctStr>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause<SelectDistinctStr>;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline SelectDistinctClause(const std::string& select_text) noexcept
            : MyBaseClass(select_text)
        {}

        /** @brief Empty constructor. */
        inline SelectDistinctClause() noexcept = default;

        /** @brief Default copy constructor. */
        SelectDistinctClause(const SelectDistinctClause&) noexcept = default;

        /** @brief Default move constructor. */
        SelectDistinctClause(SelectDistinctClause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~SelectDistinctClause() = default;
    };

}