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


export module osql.columns.column_constraints;

import osql.clauses;
import osql.clauses.conflict_clauses;



//===========================================================================
export namespace osql::columns
{
    //
    // Notice: these constraints are used with columns definitions.
    //

    //===   PRIMARY KEY   ===================================================
    /** @brief the STR value for PRIMARY KEY. */
    using PrimaryKeyStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', 0 >;

    /** @brief The class of Primary Key Clauses as included in columns definitions.
    *
    * CAUTION: Primary Key clauses have for columns definitions are  not  the 
    *          same as Primary Key clauses for tables definitions. Always use
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

}