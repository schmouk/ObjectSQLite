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


export module osql.clauses.ordering_terms;

import osql.clauses;
import osql.clauses.collate_clauses;


//===========================================================================
export namespace osql::clauses
{
    //=======================================================================
    /** @brief The base class of ordering terms.
    *
    * @see https://www.sqlite.org/syntax/ordering-term.html
    * @sa NullsOrderingTerm, NullsFisrtOrderingTerm, NullsLastOrderingTerm,
    *     AscendingOrderingTerm, AscOrderingTerm and DescOrderingTerm
    */
    class OrderingTerm : public NoPrefixClause<>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = NoPrefixClause<>;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor (1/6). */
        inline OrderingTerm(const std::string& expr) noexcept
            : MyBaseClass(expr)
        {}

        /** @brief Constructor (2/6). */
        inline OrderingTerm(const std::string& expr,
                            const osql::clauses::CollateClause& collate_clause) noexcept
            : MyBaseClass(std::format("{} {}", expr,
                                               collate_clause.get_text()))
        {}

        /** @brief Constructor (3/6). */
        inline OrderingTerm(const std::string& expr,
                            const osql::clauses::CollateClause& collate_clause,
                            const bool                          b_ascending) noexcept
            : MyBaseClass(std::format("{} {} {}", expr,
                                                  collate_clause.get_text(),
                                                  b_ascending ? "ASC" : "DESC"))
        {}

        /** @brief Constructor (4/6). */
        inline OrderingTerm(const std::string& expr,
                            const osql::clauses::CollateClause& collate_clause,
                            const bool                          b_ascending,
                            const bool                          b_nulls_first) noexcept
            : MyBaseClass(std::format("{} {} {} NULLS {}", expr,
                                                           collate_clause.get_text(),
                                                           b_ascending ? "ASC" : "DESC",
                                                           b_nulls_first ? "FIRST" : "LAST"))
        {}

        /** @brief Constructor (5/6). */
        inline OrderingTerm(const std::string& expr,
                            const bool         b_ascending) noexcept
            : MyBaseClass(std::format("{} {}", expr,
                                               b_ascending ? "ASC" : "DESC"))
        {}

        /** @brief Constructor (6/6). */
        inline OrderingTerm(const std::string& expr,
                            const bool         b_ascending,
                            const bool         b_nulls_first) noexcept
            : MyBaseClass(std::format("{} {} NULLS {}", expr,
                                                        b_ascending ? "ASC" : "DESC",
                                                        b_nulls_first ? "FIRST" : "LAST"))
        {}

        /** @brief Default empty constructor. */
        OrderingTerm() noexcept = default;

        /** @brief Default copy constructor. */
        OrderingTerm(const OrderingTerm&) noexcept = default;

        /** @brief Default move constructor. */
        OrderingTerm(OrderingTerm&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~OrderingTerm() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] OrderingTerm& operator= (const OrderingTerm&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] OrderingTerm& operator= (OrderingTerm&&) noexcept = default;
    };


    //=======================================================================
    /** @brief The class of ordering terms with specified ordering of NULLs.
    *
    * @sa NullsFirstOrderingTerm and NullsLastOrderingterm.
    */
    template<const bool NULLS_FIRST = true>
    class NullsOrderingTerm : public OrderingTerm
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = OrderingTerm;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor (1/4). */
        inline NullsOrderingTerm(const std::string& expr) noexcept
            : MyBaseClass(std::format("{} NULLS {}", expr, NULLS_FIRST ? "FIRST" : "LAST"))
        {}

        /** @brief Constructor (2/4). */
        inline NullsOrderingTerm(const std::string&                  expr,
                                 const osql::clauses::CollateClause& collate_clause) noexcept
            : MyBaseClass(std::format("{} {} NULLS {}", expr, collate_clause.get_text(), NULLS_FIRST ? "FIRST" : "LAST"))
        {}

        /** @brief Constructor (3/4). */
        inline NullsOrderingTerm(const std::string&                  expr,
                                 const osql::clauses::CollateClause& collate_clause,
                                 const bool                          b_ascending) noexcept
            : MyBaseClass(expr, collate_clause, b_ascending, NULLS_FIRST)
        {}

        /** @brief Constructor (4/4). */
        inline NullsOrderingTerm(const std::string& expr,
                                 const bool         b_ascending) noexcept
            : MyBaseClass(expr, b_ascending, NULLS_FIRST)
        {}

        /** @brief Default empty constructor. */
        NullsOrderingTerm() noexcept = default;

        /** @brief Default copy constructor. */
        NullsOrderingTerm(const NullsOrderingTerm&) noexcept = default;

        /** @brief Default move constructor. */
        NullsOrderingTerm(NullsOrderingTerm&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~NullsOrderingTerm() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] NullsOrderingTerm& operator= (const NullsOrderingTerm&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] NullsOrderingTerm& operator= (NullsOrderingTerm&&) noexcept = default;

    };


    //=======================================================================
    /** @brief Specialization of NullsOrderingTerm with NULLs FIRST ordering. */
    using NullsFirstOrderingTerm = NullsOrderingTerm<true>;

    /** @brief Specialization of NullsOrderingTerm with Nulls LAST ordering. */
    using NullsLastOrderingTerm = NullsOrderingTerm<false>;


    //=======================================================================
    /** @brief The class of ASCending or DESCending ordering terms.
    *
    * @see https://www.sqlite.org/syntax/ordering-term.html
    * @sa AscOrderingTerm and DescOrderingTerm which should
    *     be the preferred ways to name the related classes.
    */
    template<const bool ASC = true>
    class AscendingOrderingTerm : public OrderingTerm
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = OrderingTerm;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor (1/4). */
        inline AscendingOrderingTerm(const std::string& expr) noexcept
            : MyBaseClass(expr, ASC)
        {}

        /** @brief Constructor (2/4). */
        inline AscendingOrderingTerm(const std::string& expr,
                                     const osql::clauses::CollateClause& collate_clause) noexcept
            : MyBaseClass(expr, collate_clause, ASC)
        {}

        /** @brief Constructor (3/4). */
        inline AscendingOrderingTerm(const std::string& expr,
                                     const osql::clauses::CollateClause& collate_clause,
                                     const bool                          b_nulls_first) noexcept
            : MyBaseClass(expr, collate_clause, ASC, b_nulls_first)
        {}


        /** @brief Constructor (4/4). */
        inline AscendingOrderingTerm(const std::string& expr,
                                     const bool         b_nulls_first) noexcept
            : MyBaseClass(expr, ASC, b_nulls_first)
        {}

        /** @brief Default empty constructor. */
        AscendingOrderingTerm() noexcept = default;

        /** @brief Default copy constructor. */
        AscendingOrderingTerm(const AscendingOrderingTerm&) noexcept = default;

        /** @brief Default move constructor. */
        AscendingOrderingTerm(AscendingOrderingTerm&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~AscendingOrderingTerm() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] AscendingOrderingTerm& operator= (const AscendingOrderingTerm&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] AscendingOrderingTerm& operator= (AscendingOrderingTerm&&) noexcept = default;
    };


    //=======================================================================
    /** @brief Specialization of AscendingOrderingTerm with ASC ordering. */
    using AscOrderingTerm = AscendingOrderingTerm<true>;

    /** @brief Specialization of AscendingOrderingTerm with DESC ordering. */
    using DescOrderingTerm = AscendingOrderingTerm<false>;

}