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


export module osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //=======================================================================
    // This module defines:
    //  - class WithClause (not recursive)
    //  - class WithRecursiveClause (recursive)
    //

    //=======================================================================
    /** @brief The class of SQL WITH clauses as included in SQL statements. */
    class WithClause : public osql::clauses::Clause
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline WithClause(const std::string& common_table_expressions_text) noexcept
            : MyBaseClass(_PREFIX, common_table_expressions_text)
        {}

        /** @brief Empty constructor. */
        inline WithClause() noexcept
            : osql::clauses::Clause(_PREFIX, "")
        {}

        /** @brief Default copy constructor. */
        WithClause(const WithClause&) noexcept = default;

        /** @brief Default move constructor. */
        WithClause(WithClause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~WithClause() = default;

    private:
        static inline std::string _PREFIX{ "WITH" };
    };


    //=======================================================================
    /** @brief The class of SQL WITH clauses as included in SQL statements. */
    class WithRecursiveClause : public osql::clauses::Clause
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline WithRecursiveClause(const std::string& common_table_expressions_text) noexcept
            : osql::clauses::Clause(_PREFIX, common_table_expressions_text)
        {}

        /** @brief Empty constructor. */
        inline WithRecursiveClause() noexcept
            : osql::clauses::Clause(_PREFIX, "")
        {}

        /** @brief Default copy constructor. */
        WithRecursiveClause(const WithRecursiveClause&) noexcept = default;

        /** @brief Default move constructor. */
        WithRecursiveClause(WithRecursiveClause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~WithRecursiveClause() = default;

    private:
        static inline std::string _PREFIX{ "WITH RECURSIVE" };

    };

}