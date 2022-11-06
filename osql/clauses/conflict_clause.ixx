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


export module osql.clauses.conflict_clauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used for columns constraints and for tables contraints.
    //
    
    //=======================================================================
    /** @brief the templated string for the prefix of every conflict clauses. */
    using OnConflictPrefixStr = osql::clauses::STR< 'O', 'N', ' ', 'C', 'O', 'N', 'F', 'L', 'I', 'C', 'T', 0 >;


    //=======================================================================
    /** @brief The base class for all constraint clauses.
    *
    * @sa ConflictAbortClause, ConflictFailClause, ConflictIgnoreClause,
    *     ConflictReplaceClause, ConflictRollbackClause and NoConflictClause
    *     which should be used instead.
    */
    template< typename PrefixT, typename SuffixT>
    using ConflictBaseClause = osql::clauses::Clause< PrefixT, SuffixT >;

    //=======================================================================
    /** @brief The class of ABORT Conflict Clauses as included in SQL statements. */
    using ConflictAbortClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'A', 'B', 'O', 'R', 'T', 0> >;

    //=======================================================================
    /** @brief The class of FAIL Conflict Clauses as included in SQL statements. */
    using ConflictFailClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'F', 'A', 'I', 'L', 0> >;

    //=======================================================================
    /** @brief The class of IGNORE Conflict Clauses as included in SQL statements. */
    using ConflictIgnoreClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'I', 'G', 'N', 'O', 'R', 'E', 0> >;

    //=======================================================================
    /** @brief The class of REPLACE Conflict Clauses as included in SQL statements. */
    using ConflictReplaceClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'R', 'E', 'P', 'L', 'A', 'C', 'E', 0> >;

    //=======================================================================
    /** @brief The class of ROLLBACK Conflict Clauses as included in SQL statements. */
    using ConflictRollbackClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'R', 'O', 'L', 'L', 'B', 'A', 'C', 'K', 0> >;

    //=======================================================================
    /** @brief The class of NO Conflict Clauses as included in SQL statements. */
    using NoConflictClause = ConflictBaseClause< osql::clauses::STR<0>, osql::clauses::STR<0> >;

}