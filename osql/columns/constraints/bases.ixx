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


export module osql.columns.constraints.bases;

import osql.clauses;
import osql.clauses.conflict_clauses;


//===========================================================================
// This module defines:
// 
//  - class ColumnConstraint
//  - class NonEmptyColumnConstraint
//  - class NonEmptyParenthesisColumnConstraint
//  - class ConflictClauseColumnConstraint
//
// These classes are the base classes of all column constraint classes.
//


//===========================================================================
export namespace osql::columns::constraints
{
    //=======================================================================
    /** @brief Any conflict clause should inherit from this class.
    *
    * This origin class will be used to further check requirements.
    */
    struct ColumnConstraintType
    {};


    //=======================================================================
    /** @brief The base class for any Columns Constraints. */
    template<typename PrefixT>
    class ColumnConstraint : public osql::clauses::Clause< PrefixT >, public ColumnConstraintType
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrefixT >;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline ColumnConstraint(const std::string& core_text) noexcept
            : MyBaseClass(core_text)
            , ColumnConstraintType()
        {}

        /** @brief Default empty constructor. */
        ColumnConstraint() noexcept = default;

        /** @brief Default copy constructor. */
        ColumnConstraint(const ColumnConstraint&) noexcept = default;

        /** @brief Default move constructor. */
        ColumnConstraint(ColumnConstraint&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~ColumnConstraint() noexcept = default;
    };


    //=======================================================================
    /** @brief The base class for Columns Constraints with a mandatory core object. */
    template<typename PrefixT>
    class NonEmptyColumnConstraint : public ColumnConstraint< PrefixT >
    {
    public:
        //---   Constructors   ----------------------------------------------
        /** @brief Value constructor. */
        template<typename CoreT> requires std::convertible_to<CoreT, std::string>
        inline NonEmptyColumnConstraint(const CoreT& core_text) noexcept
            : ColumnConstraint<PrefixT>((std::string)core_text)
        {}

        /** @brief Specialization of value constructor. */
        template<>
        inline NonEmptyColumnConstraint(const std::string& core_text) noexcept
            : ColumnConstraint<PrefixT>(core_text)
        {}

        /** @brief Deleted empty constructor. */
        NonEmptyColumnConstraint() noexcept = delete;
    };


    //=======================================================================
    /** @brief The base class for Columns Constraints with a mandatory core text embedded in enclosing parenthesis. */
    template<typename PrefixT>
    class NonEmptyParenthesisColumnConstraint : public NonEmptyColumnConstraint< PrefixT >
    {
    public:
        //---   Constructors   ----------------------------------------------
        /** @brief Value constructor (1/2). */
        inline NonEmptyParenthesisColumnConstraint(const std::string& core_text) noexcept
            : NonEmptyColumnConstraint<PrefixT>(std::format("({:s})", core_text))
        {}

        /** @brief Value constructor (2/2). */
        inline NonEmptyParenthesisColumnConstraint(const std::string& core_text,
                                                   const std::string& core_suffix) noexcept
            : NonEmptyColumnConstraint<PrefixT>(std::format("({:s}) {:s}", core_text, core_suffix))
        {}
    };


    //=======================================================================
    /** @brief The base class for Columns Constraints associated with a Conflict Clause. */
    template<typename PrefixT>
    class ConflictClauseColumnConstraint : public NonEmptyColumnConstraint< PrefixT >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = NonEmptyColumnConstraint< PrefixT >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (1/2). */
        template<typename ConflictClauseT> requires std::derived_from<ConflictClauseT, osql::clauses::ConflictClauseType>
        ConflictClauseColumnConstraint(const ConflictClauseT conflict_clause) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause))
        {}

        /** @brief Value constructor (2/2). */
        template<typename ConflictClauseT> requires std::derived_from<ConflictClauseT, osql::clauses::ConflictClauseType>
        ConflictClauseColumnConstraint(const ConflictClauseT& conflict_clause,
                                       const std::string&     added_text) noexcept
            : MyBaseClass(std::format("{:s} {:s}", osql::clauses::T(conflict_clause), added_text))
        {}
    };

}