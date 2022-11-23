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


export module osql.clauses.attach_database_clause;

import osql.clauses;


//===========================================================================
// This module defines:
//  - class AttachDatabaseClause<>
//  - class AttachMainDatabaseClause
//  - class AttachMemoryDatabaseClause
//  - class AttachTemporaryDatabaseClause
//  - class AttachTempTablesDatabaseClause
//

//===========================================================================
namespace osql::clauses
{
    //=======================================================================
    /** @brief the STR value for ATTACH DATABASE. */
    using CollateStr = osql::clauses::STR< 'A', 'T', 'T', 'A', 'C', 'H', ' ', 'D', 'A', 'T', 'A', 'B', 'A', 'S', 'E', 0 >;


    //=======================================================================
    /** @brief The base class for SQL Attach Database clauses as included in SQL statements.
    *
    * See https://www.sqlite.org/lang_attach.html to get explanations on
    * ATTACHE DATABASE statement with SQLite.
    */
    export struct AttachDataBaseClause : osql::clauses::NonEmptyClause< CollateStr >
    {
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::NonEmptyClause< CollateStr >;  //!< wrapper to the base class.

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AttachDataBaseClause(const std::string& core_expr_, const std::string& schema_name_) noexcept
            : MyBaseClass(std::format("{:s} AS {:s}", core_expr_, schema_name_))
        {}
    };


    //=======================================================================
    /** @brief The class of SQL Attach Database clauses for the main database. */
    export class AttachMainDatabaseClause : public AttachDataBaseClause
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::AttachDataBaseClause;  //!< wrapper to the base class.

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AttachMainDatabaseClause(const std::string& schema_name) noexcept
            : MyBaseClass("main", schema_name)
        {}
    };


    //=======================================================================
    /** @brief The class of SQL Attach Database clauses for databases set in memory. */
    export class AttachMemoryDatabaseClause : public AttachDataBaseClause
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::AttachDataBaseClause;  //!< wrapper to the base class.

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AttachMemoryDatabaseClause(const std::string& schema_name) noexcept
            : MyBaseClass(":memory:", schema_name)
        {}
    };


    //=======================================================================
    /** @brief The class of SQL Attach Database clauses for new temporary databases. */
    export class AttachTemporaryDatabaseClause : public AttachDataBaseClause
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::AttachDataBaseClause;  //!< wrapper to the base class.

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AttachTemporaryDatabaseClause(const std::string& schema_name) noexcept
            : MyBaseClass("", schema_name)
        {}
    };


    //=======================================================================
    /** @brief The class of SQL Attach Database clauses for the temporary tables database. */
    export class AttachTempTablesDatabaseClause : public AttachDataBaseClause
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::AttachDataBaseClause;  //!< wrapper to the base class.

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AttachTempTablesDatabaseClause(const std::string& schema_name) noexcept
            : MyBaseClass("temp", schema_name)
        {}
    };

}