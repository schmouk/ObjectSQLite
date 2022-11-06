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


export module osql.clauses.match_clauses;

import osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with tables constraints.
    //

    //=======================================================================
    /** @brief The class of Match Clauses as included in columns and tables constraints. */
    class MatchClause : public osql::clauses::Clause< osql::clauses::STR<'M', 'A', 'T', 'C', 'H', 0> >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< osql::clauses::STR<'M', 'A', 'T', 'C', 'H', 0> >;  //!< wrapper to the base class


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline MatchClause(const std::string& name) noexcept
            : MyBaseClass(name)
        {}

        /** @brief Deleted empty/default constructor. */
        MatchClause() noexcept = delete;
    };

}