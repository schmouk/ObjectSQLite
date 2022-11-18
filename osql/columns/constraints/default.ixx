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


export module osql.columns.constraints.default;

import osql.clauses;
import osql.columns.constraints.bases;



//===========================================================================
namespace osql::columns::constraints
{
    /** @brief the internal STR value for clause DEFAULT. */
    using DefaultStr = osql::clauses::STR<'D', 'E', 'F', 'A', 'U', 'L', 'T', 0>;


    //===   DEFAULT   =======================================================
    /** @brief The class of Default Clauses as included in columns definitions. */
    export using DefaultClause = osql::columns::constraints::NonEmptyColumnConstraint< DefaultStr >;


    /** @brief The class of Default Clauses with an expression as included in columns definitions. */
    export using DefaultExprClause = osql::columns::constraints::NonEmptyParenthesisColumnConstraint< DefaultStr >;

}