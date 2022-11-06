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


export module osql.columns.column_constraints;

import osql.clauses;
import osql.clauses.conflict_clauses;



//===========================================================================
export namespace osql::columns
{
    //
    // Notice: these constraints are used with columns definitions.
    //

    //===   CHECK   =========================================================
    /** @brief the STR value for CHECK. */
    using CheckStr = osql::clauses::STR<'C', 'H', 'E', 'C', 'K', 0>;

    /** @brief The class of Check Clauses as included in columns definitions. */
    class CheckClause : public osql::clauses::Clause< CheckStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< CheckStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        CheckClause(const std::string& check_expr) noexcept
            : MyBaseClass(std::format("({:s})", check_expr))
        {}
    };


    //===   DEFAULT   =======================================================
    /** @brief the STR value for DEFAULT. */
    using DefaultStr = osql::clauses::STR<'D', 'E', 'F', 'A', 'U', 'L', 'T', 0>;

    /** @brief The class of Default Clauses as included in columns definitions. */
    class DefaultClause : public osql::clauses::Clause< DefaultStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< DefaultStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        DefaultClause(const std::string& value) noexcept
            : MyBaseClass(value)
        {}

        DefaultClause() noexcept = delete;  //!< deleted empty constructor.
    };

    /** @brief The class of Default Clauses with an expression as included in columns definitions. */
    class DefaultExprClause : public osql::clauses::Clause< DefaultStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< DefaultStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        DefaultExprClause(const std::string& default_expr) noexcept
            : MyBaseClass(std::format("({:s})", default_expr))
        {}

        DefaultExprClause() noexcept = delete;  //!< deleted empty constructor.
    };


    //===   NOT NULL   ======================================================
    /** @brief the STR value for NOT NULL. */
    using NotNullStr = osql::clauses::STR<'N', 'O', 'T', ' ', 'N', 'U', 'L', 'L', 0>;

    /** @brief The class of Not Null Clauses as included in columns definitions. */
    template<typename ConflictClauseT>
    class NotNullClause : public osql::clauses::Clause< NotNullStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< NotNullStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        NotNullClause() noexcept
            : MyBaseClass(osql::clauses::T<ConflictClauseT>())
        {}
    };


    //===   PRIMARY KEY   ===================================================
    /** @brief the STR value for PRIMARY KEY. */
    using PrimaryKeyStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', 0 >;

    /** @brief the STR value for PRIMARY KEY ASC. */
    using PrimaryKeyAscStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y',' ', 'A', 'S', 'C', 0 >;

    /** @brief the STR value for PRIMARY KEY DESC. */
    using PrimaryKeyDescStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', ' ', 'D', 'E', 'S', 'C', 0 >;


    /** @brief The class of Primary Key Clauses as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    template<typename ConflictClauseT>
    class PrimaryKeyClause : public osql::clauses::Clause< PrimaryKeyStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        PrimaryKeyClause(const bool auto_incr = false) noexcept
            : MyBaseClass(osql::clauses::T<ConflictClauseT>() + (auto_incr ? " AUTOINCREMENT" : ""))
        {}
    };


    /** @brief The class of Primary Key Clauses with specifier ASC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    template<typename ConflictClauseT>
    class PrimaryKeyAscClause : public osql::clauses::Clause< PrimaryKeyAscStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyAscStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        PrimaryKeyAscClause(const bool auto_incr = false) noexcept
            : MyBaseClass(osql::clauses::T<ConflictClauseT>() + (auto_incr ? " AUTOINCREMENT" : ""))
        {}
    };


    /** @brief The class of Primary Key Clauses with specifier DESC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    template<typename ConflictClauseT>
    class PrimaryKeyDescClause : public osql::clauses::Clause< PrimaryKeyDescStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyDescStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        PrimaryKeyDescClause(const bool auto_incr = false) noexcept
            : MyBaseClass(osql::clauses::T<ConflictClauseT>() + (auto_incr ? " AUTOINCREMENT" : ""))
        {}
    };


    //===   UNIQUE   ========================================================
    using UniqueStr = osql::clauses::STR<'U', 'N', 'I', 'Q', 'U', 'E', 0>;

    /** @brief The class of Unique Clauses as included in columns definitions. */
    template<typename ConflictClauseT>
    class UniqueClause : public osql::clauses::Clause< UniqueStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< UniqueStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        UniqueClause() noexcept
            : MyBaseClass(osql::clauses::T<ConflictClauseT>())
        {}
    };

}