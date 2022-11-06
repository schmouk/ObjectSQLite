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


export module osql.clauses.deferrable_clauses;

import osql.clauses;


//===========================================================================
namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with tables contraints,
    //         associated with foreign keys specifications.
    //

    //=======================================================================
    /** @brief STR definition for DEFERRABLE clauses. */
    using DeferrableStr = STR< 'D', 'E', 'F', 'E', 'R', 'R', 'A', 'B', 'L', 'E', 0 >;

    /** @brief STR definition for NOT DEFERRABLE clauses. */
    using NotDeferrableStr = STR< 'N', 'O', 'T', ' ', 'D', 'E', 'F', 'E', 'R', 'R', 'A', 'B', 'L', 'E', 0 >;

    /** @brief STR definition for INITIALLY DEFERRED spec. */
    using InitiallyDeferred = STR< 'I', 'N', 'I', 'T', 'I', 'A', 'L', 'L', 'Y', ' ', 'D', 'E', 'F', 'E', 'R', 'R', 'E', 'D', 0 >;

    /** @brief STR definition for INITIALLY IMMEDIATE spec. */
    using InitiallyImmediate = STR< 'I', 'N', 'I', 'T', 'I', 'A', 'L', 'L', 'Y', ' ', 'I', 'M', 'M', 'E', 'D', 'I', 'A', 'T', 'E', 0 >;


    //=======================================================================
    /** @brief The base class for DEFERRABLE clauses.
    *
    * @sa DeferrableDeferredClause, DeferrableDeferredClause,
    *     NotDeferrableDeferredClause and NotDeferrableDeferredClause
    *     which should be used rather than this base class.
    */
    export template<typename PrefixT, typename SuffixT>
    using DeferrableBaseClause = Clause<PrefixT, SuffixT>;


    //=======================================================================
    /** @brief The base class for INITIALLY DEFERRED DEFERRABLE clauses. */
    export using DeferrableDeferredClause = DeferrableBaseClause< DeferrableStr, InitiallyDeferred >;

    /** @brief The base class for INITIALLY IMMEDIATE DEFERRABLE clauses. */
    export using DeferrableImmediateClause = DeferrableBaseClause< DeferrableStr, InitiallyImmediate >;


    //=======================================================================
    /** @brief The base class for INITIALLY DEFERRED NOT DEFERRABLE clauses. */
    export using NotDeferrableDeferredClause = DeferrableBaseClause< NotDeferrableStr, InitiallyDeferred >;

    /** @brief The base class for INITIALLY IMMEDIATE NOT DEFERRABLE clauses. */
    export using NotDeferrableImmediateClause = DeferrableBaseClause< NotDeferrableStr, InitiallyImmediate >;

}