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


export module osql.clauses.ordering_clauses;

import osql.clauses;
import osql.clauses.ordering_terms;


//===========================================================================
namespace osql::clauses
{
    /** @brief The STR expression associated with ordering clauses - internal usage. */
    using OrderingStr = osql::clauses::STR< 'O', 'R', 'D', 'E', 'R', ' ', 'B', 'Y', 0 >;
    

    //=======================================================================
    /** @brief The class of SQL ORDER BY clauses as included in SQL statements. */
    export class OrderingClause : public osql::clauses::Clause< OrderingStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< OrderingStr >;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename... OrderingTermsT> 
        OrderingClause(const OrderingTermsT&... ordering_terms) noexcept
            : MyBaseClass(get_terms(ordering_terms...))
        {}


        //---   Operations   ------------------------------------------------
        /** @brief Returns the whole string of ordering terms separated with commas. */
        template<typename FirstOrderingTerm, typename... OrderingTermsT>
        [[nodiscard]] const std::string get_terms(const FirstOrderingTerm& first, const OrderingTermsT... rest) const noexcept
        {
            return first.get_text() + ", " + get_terms(rest...);
        }

        /** @brief Returns the very last ordering term text. */
        template<typename OrderingTermT>
        [[nodiscard]] const std::string get_terms(const OrderingTermT& term) const noexcept
        {
            return term.get_text();
        }
    };

}