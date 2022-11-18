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


export module osql.columns.constraints.as;

import osql.clauses;
import osql.columns.constraints.bases;


//===========================================================================
namespace osql::columns::constraints
{
    /** @brief the internal STR value for clause AS. */
    using AsStr = osql::clauses::STR<'A', 'S', 0>;


    //===   AS   ============================================================
    /** @brief The class of As Clauses as included in columns definitions. */
    export using AsClause = osql::columns::constraints::NonEmptyParenthesisColumnConstraint< AsStr >;


    //===   AS STORED   =====================================================
    /** @brief The class of As Clauses with suffix STORED as included in columns definitions. */
    export class AsStoredClause : public osql::columns::constraints::NonEmptyParenthesisColumnConstraint< AsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::columns::constraints::NonEmptyParenthesisColumnConstraint< AsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AsStoredClause(const std::string& as_expr) noexcept
            : MyBaseClass(as_expr, "STORED")
        {}
    };


    //===   AS VIRTUAL   ====================================================
    /** @brief The class of As Clauses with suffix VIRTUAL as included in columns definitions. */
    export class AsVirtualClause : public osql::columns::constraints::NonEmptyParenthesisColumnConstraint< AsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::columns::constraints::NonEmptyParenthesisColumnConstraint< AsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline AsVirtualClause(const std::string& as_expr) noexcept
            : MyBaseClass(as_expr, "VIRTUAL")
        {}
    };

}