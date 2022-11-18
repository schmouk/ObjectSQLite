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


export module osql.columns.constraints.primary_key;

import osql.clauses;
import osql.clauses.conflict_clauses;
import osql.columns.constraints.bases;


//===========================================================================
namespace osql::columns::constraints
{
    //===   PRIMARY KEY   ===================================================
    /** @brief the STR value for clause PRIMARY KEY. */
    using PrimaryKeyStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', 0 >;


    /** @brief The class of Primary Key Clauses as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not the  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
    */
    export using PrimaryKeyClause = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyStr >;


    //===   PRIMARY KEY / AUTOINCREMENT   ===================================
    /** @brief The class of Primary Key Clauses with AUTOINCREMENT as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not the  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations  about 
        *      the  use  of  AUTOINCREMENT on INTEGER PRIMARY KEYS and why it 
        *      should be avoided as often as possible.
    */
    export class PrimaryKeyAutoincrClause : public osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename ConflictClauseT>
            requires std::derived_from<ConflictClauseT, osql::clauses::ConflictClauseType>
        PrimaryKeyAutoincrClause(const ConflictClauseT& conflict_clause) noexcept
            : MyBaseClass(conflict_clause, "AUTOINCREMENT")
        {}
    };


    //===   PRIMARY KEY ASC   ===============================================
    /** @brief the STR value for PRIMARY KEY ASC. */
    using PrimaryKeyAscStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', ' ', 'A', 'S', 'C', 0 >;


    /** @brief The class of Primary Key Clauses with specifier ASC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not the  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
    */
    export using PrimaryKeyAscClause = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyAscStr >;


    //===   PRIMARY KEY ASC / AUTOINCREMENT   ===============================
    /** @brief The class of Primary Key Clauses with specifiers ASC and AUTOINCREMENT as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not the  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations  about
        *      the  use  of  AUTOINCREMENT on INTEGER PRIMARY KEYS and why it
        *      should be avoided as often as possible.
    */
    export class PrimaryKeyAscAutoincrClause : public osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyAscStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyAscStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename ConflictClauseT>
            requires std::derived_from<ConflictClauseT, osql::clauses::ConflictClauseType>
        PrimaryKeyAscAutoincrClause(const ConflictClauseT& conflict_clause) noexcept
            : MyBaseClass(conflict_clause, "AUTOINCREMENT")
        {}
    };


    //===   PRIMARY KEY DESC   ==============================================
    /** @brief the STR value for PRIMARY KEY DESC. */
    using PrimaryKeyDescStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', ' ', 'D', 'E', 'S', 'C', 0 >;


    /** @brief The class of Primary Key Clauses with specifier DESC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not the  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
    */
    export using PrimaryKeyDescClause = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyDescStr >;


    //===   PRIMARY KEY DESC / AUTOINCREMENT   ===============================
    /** @brief The class of Primary Key Clauses with specifiers DESC and AUTOINCREMENT as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  he  same
    *          as Primary Key clauses for tables definitions. Always use the
    *          namespace as a prefix when instantiating PrimaryKeyClause.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations  about
        *      the  use  of  AUTOINCREMENT on INTEGER PRIMARY KEYS and why it
        *      should be avoided as often as possible.
    */
    export class PrimaryKeyDescAutoincrClause : public osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyDescStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::columns::constraints::ConflictClauseColumnConstraint< PrimaryKeyDescStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename ConflictClauseT>
            requires std::derived_from<ConflictClauseT, osql::clauses::ConflictClauseType>
        PrimaryKeyDescAutoincrClause(const ConflictClauseT& conflict_clause) noexcept
            : MyBaseClass(conflict_clause, "AUTOINCREMENT")
        {}
    };

}