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
#include <iostream>

#include <sqlite3.h>

#include "osql/clauses/clause.h"

import osql.dbconnection;
using namespace osql::dbconnection;

import osql.clauses;
import osql.clauses.collate_clauses;
import osql.clauses.conflict_clauses;
import osql.clauses.ordering_clauses;
import osql.clauses.ordering_terms;
import osql.clauses.select_clauses;
import osql.clauses.with_clauses;

import osql.columns.column_constraints;


osql::clauses::SelectDistinctClause clause;


int main()
{
    std::cout << "Let's test ObjectSQLite with sqlite3 version " << SQLITE_VERSION << "!\n";

    DBConnection test_db{ "tests/db_test", DBConnection::CREATE };
    std::cout << "creation of first test db, error result = " << test_db.get_error_code() << ", " << test_db.get_error_msg() << std::endl;

    MemoryDBConnection test_mem_db{};
    std::cout << "creation of memory test db, error result = " << test_mem_db.get_error_code() << ", " << test_mem_db.get_error_msg() << std::endl;

    osql::clauses::WithRecursiveClause wr_clause("test text");
    std::cout << "Recursive With Clause content: " << osql::clauses::T(wr_clause) << std::endl;

    std::cout << "Empty Select Distinct Clause content: " << T(clause) << std::endl;

    std::cout << "Collate Clause: " << osql::clauses::T(osql::clauses::CollateClause("Latin1_General_CS_AS_KS_WS")) << std::endl;

    std::cout << "Ordering Clause: " << osql::clauses::T(osql::clauses::OrderingClause(
                                                                        osql::clauses::AscOrderingTerm("SQL-expression-1",
                                                                                                       osql::clauses::CollateClause("Latin1_General_CS_AS_KS_WS"),
                                                                                                       true),
                                                                        osql::clauses::DescOrderingTerm("SQL-expression-2", false),
                                                                        osql::clauses::NullsFirstOrderingTerm("SQL-expression-3",
                                                                                                              osql::clauses::CollateClause("Latin1_General_CS_AS_KS_WS"),
                                                                                                              false),
                                                                        osql::clauses::OrderingTerm("SQL-expression-4",
                                                                                                    osql::clauses::CollateClause("Latin1_General_CS_AS_KS_WS"),
                                                                                                    true, false)))
        << std::endl;

    osql::columns::PrimaryKeyClause<osql::clauses::ConflictIgnoreClause>  prim_key_clause( true );
    std::cout << "Column Primary Key Clause: " << osql::clauses::T(prim_key_clause) << std::endl;

    osql::columns::PrimaryKeyClause<osql::clauses::ConflictIgnoreClause>  prim_key_clause2 = prim_key_clause;
    std::cout << "Column Primary Key Clause: " << osql::clauses::T(prim_key_clause2) << std::endl;
}
