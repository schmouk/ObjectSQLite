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
namespace osql::clauses
{
    //
    // Notice: these clauses are used for columns constraints and for tables contraints.
    //

    //=======================================================================
    /** @brief Any conflict clause should inherit from this class.
    *
    * This origin class will be used to further check requirements.
    */
    export struct ConflictClauseType
    {};


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
    export template< typename PrefixT, typename SuffixT>
    struct ConflictBaseClause : osql::clauses::Clause< PrefixT, SuffixT >, ConflictClauseType
    {};


    //=======================================================================
    /** @brief The class of ABORT Conflict Clauses as included in SQL statements. */
    export using ConflictAbortClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'A', 'B', 'O', 'R', 'T', ' ', 0> >;

    export ConflictAbortClause CONFLICT_ABORT_CLAUSE;  //!< Forced instance of this class.


    //=======================================================================
    /** @brief The class of FAIL Conflict Clauses as included in SQL statements. */
    export using ConflictFailClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'F', 'A', 'I', 'L', ' ', 0> >;

    export ConflictFailClause CONFLICT_FAIL_CLAUSE;  //!< Forced instance of this class.


    //=======================================================================
    /** @brief The class of IGNORE Conflict Clauses as included in SQL statements. */
    export using ConflictIgnoreClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'I', 'G', 'N', 'O', 'R', 'E', ' ', 0> >;

    export ConflictIgnoreClause CONFLICT_IGNORE_CLAUSE;  //!< Forced instance of this class.


    //=======================================================================
    /** @brief The class of REPLACE Conflict Clauses as included in SQL statements. */
    export using ConflictReplaceClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'R', 'E', 'P', 'L', 'A', 'C', 'E', ' ', 0> >;

    export ConflictReplaceClause CONFLICT_REPLACE_CLAUSE;  //!< Forced instance of this class.


    //=======================================================================
    /** @brief The class of ROLLBACK Conflict Clauses as included in SQL statements. */
    export using ConflictRollbackClause = ConflictBaseClause< OnConflictPrefixStr, osql::clauses::STR<'R', 'O', 'L', 'L', 'B', 'A', 'C', 'K', ' ', 0> >;

    export ConflictRollbackClause CONFLICT_ROLLBACK_CLAUSE;  //!< Forced instance of this class.


    //=======================================================================
    /** @brief The class of NO Conflict Clauses as included in SQL statements. */
    export using NoConflictClause = ConflictBaseClause< osql::clauses::STR<0>, osql::clauses::STR<0> >;

    export NoConflictClause NO_CONFLICT_CLAUSE;  //!< Forced instance of this class.


}