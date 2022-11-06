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

#include <format>
#include <string>

#include "osql/clauses/clause.h"


export module osql.clauses.type_name_clauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns definitions.
    //

    //=======================================================================
    /** @brief The class of Type Name Clauses as included in columns and tables constraints. */
    class TypeNameClause : public NoPrefixClause<>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = NoPrefixClause<>;  //!< wrapper to the base class


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with sole name of type).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause(const std::string& name) noexcept
            : MyBaseClass(name)
        {}

        /** @brief Value constructor (with type name and one signed integer).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause(const std::string& name, const int32_t num) noexcept
            : MyBaseClass(std::format("{:s}({:d})", name, num))
        {}

        /** @brief Value constructor (with type name and two signed integers).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause(const std::string& name, const int32_t min_num, const int32_t max_num) noexcept
            : MyBaseClass(std::format("{:s}({:d}, {:d})", name, min_num, max_num))
        {}

        /** @brief Deleted empty/default constructor. */
        TypeNameClause() noexcept = delete;

        /** @brief Default copy constructor. */
        TypeNameClause(const TypeNameClause&) noexcept = default;

        /** @brief Default move constructor. */
        TypeNameClause(TypeNameClause&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~TypeNameClause() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] TypeNameClause& operator= (const TypeNameClause&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] TypeNameClause& operator= (TypeNameClause&&) noexcept = default;
    };

}