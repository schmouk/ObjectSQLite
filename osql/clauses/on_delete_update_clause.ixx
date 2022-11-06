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


export module osql.clauses.on_delete_update_clauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with tables contraints.
    //

    //=======================================================================
    /** @brief The base class of On-Delete and On-Update clauses. */
    template<typename PrefixT, typename SuffixT>
    using OnDeleteUpdateClause = osql::clauses::Clause<PrefixT, SuffixT>;


    //=======================================================================
    /** @brief The base class for ON DELETE clauses. */
    template<typename SuffixT>
    using OnDeleteClause = OnDeleteUpdateClause< osql::clauses::STR<'O', 'N', ' ', 'D', 'E', 'L', 'E', 'T', 'E', 0>, SuffixT >;

    /** @brief The CASCADE directive on ON DELETE foreign-key specification. */
    using OnDeleteCascadeClause = OnDeleteClause< osql::clauses::STR<'C', 'A', 'S', 'C', 'A', 'D', 'E', 0> >;

    /** @brief The NO ACTION directive on ON DELETE foreign-key specification. */
    using OnDeleteNoActionClause = OnDeleteClause< osql::clauses::STR<'N', 'O', ' ', 'A', 'C', 'T', 'I', 'O', 'N', 0> >;

    /** @brief The RESTRICT directive on ON DELETE foreign-key specification. */
    using OnDeleteRestrictClause = OnDeleteClause< osql::clauses::STR<'R', 'E', 'S', 'T', 'R', 'I', 'C', 'T', 0> >;

    /** @brief The SET DEFAULT directive on ON DELETE foreign-key specification. */
    using OnDeleteSetDefaultClause = OnDeleteClause< osql::clauses::STR<'S', 'E', 'T', ' ', 'D', 'E', 'F', 'A', 'U', 'L', 'T', 0> >;

    /** @brief The SET NULL directive on ON DELETE foreign-key specification. */
    using OnDeleteSetNullClause = OnDeleteClause< osql::clauses::STR<'S', 'E', 'T', ' ', 'N', 'U', 'L', 'L', 0> >;


    //=======================================================================
    /** @brief The base class for ON UPDATE clauses. */
    template<typename SuffixT>
    using OnUpdateClause = OnDeleteUpdateClause< osql::clauses::STR<'O', 'N', ' ', 'U', 'P', 'D', 'A', 'T', 'E', 0>, SuffixT >;

    /** @brief The CASCADE directive on ON DELETE foreign-key specification. */
    using OnUpdateCascadeClause = OnUpdateClause< osql::clauses::STR<'C', 'A', 'S', 'C', 'A', 'D', 'E', 0> >;

    /** @brief The NO ACTION directive on ON DELETE foreign-key specification. */
    using OnUpdateNoActionClause = OnUpdateClause< osql::clauses::STR<'N', 'O', ' ', 'A', 'C', 'T', 'I', 'O', 'N', 0> >;

    /** @brief The RESTRICT directive on ON DELETE foreign-key specification. */
    using OnUpdateRestrictClause = OnUpdateClause< osql::clauses::STR<'R', 'E', 'S', 'T', 'R', 'I', 'C', 'T', 0> >;

    /** @brief The SET DEFAULT directive on ON DELETE foreign-key specification. */
    using OnUpdateSetDefaultClause = OnUpdateClause< osql::clauses::STR<'S', 'E', 'T', ' ', 'D', 'E', 'F', 'A', 'U', 'L', 'T', 0> >;

    /** @brief The SET NULL directive on ON DELETE foreign-key specification. */
    using OnUpdateSetNullClause = OnUpdateClause< osql::clauses::STR<'S', 'E', 'T', ' ', 'N', 'U', 'L', 'L', 0> >;

}