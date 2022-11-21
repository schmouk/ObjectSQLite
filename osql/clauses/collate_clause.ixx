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

#include "osql/clauses/clause.h"


export module osql.clauses.collate_clauses;

import osql.clauses;


//===========================================================================
namespace osql::clauses
{
    //=======================================================================
    /** @brief the STR value for COLLATE. */
    using CollateStr = osql::clauses::STR< 'C', 'O', 'L', 'L', 'A', 'T', 'E', 0 >;

    /** @brief The class of SQL COLLATE clauses as included in SQL statements.
    *
    *   @see https://www.sqlshack.com/the-collate-sql-command-overview/  or
    *   https://dev.mysql.com/doc/refman/8.0/en/charset-collate.html to get
    *   explanations about the charsets collation  concept  in  SQL.  These
    *   charsets  names  are  to  be used as the 'core_expr' of the collate 
    *   clause at its creation time.
    */
    export class CollateClause : public osql::clauses::Clause< CollateStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< CollateStr >;  //!< wrapper to the base class.

        //---   Constructors   ----------------------------------------------
        /** @brief Value constructor. */
        inline CollateClause(const std::string collation_name) noexcept
            : MyBaseClass(collation_name)
        {}

        CollateClause() noexcept = delete;  //!< Deleted empty constructor.
    };

}