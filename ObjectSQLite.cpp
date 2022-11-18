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
import osql.clauses.deferrable_clauses;
import osql.clauses.foreign_key_clauses;
import osql.clauses.foreign_table_subclauses;
import osql.clauses.match_clauses;
import osql.clauses.on_delete_update_clauses;
import osql.clauses.ordering_clauses;
import osql.clauses.ordering_terms;
import osql.clauses.select_clauses;
import osql.clauses.type_name_clauses;
import osql.clauses.with_clauses;

import osql.columns.column;
import osql.columns.constraints.bases;
import osql.columns.constraints.as;
import osql.columns.constraints.check;
import osql.columns.constraints.default;
import osql.columns.constraints.generated_as;
import osql.columns.constraints.not_null;
import osql.columns.constraints.primary_key;
import osql.columns.constraints.unique;


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

    osql::columns::constraints::PrimaryKeyClause  prim_key_clause(osql::clauses::CONFLICT_ROLLBACK_CLAUSE, "added_text");
    std::cout << "Column Primary Key Clause: " << osql::clauses::T(prim_key_clause) << std::endl;

    osql::columns::constraints::PrimaryKeyDescClause  prim_key_clause2(osql::clauses::NO_CONFLICT_CLAUSE);
    std::cout << "Column Primary Key Clause: " << osql::clauses::T(prim_key_clause2) << std::endl;

    osql::columns::constraints::PrimaryKeyAscAutoincrClause  prim_key_clause3(osql::clauses::CONFLICT_ABORT_CLAUSE);
    std::cout << "Column Primary Key ASC Clause: " << osql::clauses::T(prim_key_clause3) << std::endl;

    osql::clauses::ForeignTableSubclause ftsu_1("foreign_table_1", "col_A", "col_B", "col_C", std::string("col_E"));
    std::cout << "Foreign Table subclause 1: " << osql::clauses::T(ftsu_1) << std::endl;

    osql::clauses::DeferrableImmediateClause dic_1;
    std::cout << "Deferrable Immediate clause 1: " << osql::clauses::T(dic_1) << std::endl;

    osql::clauses::ForeignKeyClause fkc_1(ftsu_1);
    std::cout << "Foreign Key clause 1: " << osql::clauses::T(fkc_1) << std::endl;

    osql::clauses::ForeignKeyClause fkc_2(ftsu_1, dic_1);
    std::cout << "Foreign Key clause 2: " << osql::clauses::T(fkc_2) << std::endl;

    osql::clauses::ForeignKeyClause fkc_3(ftsu_1,
                                          osql::clauses::OnDeleteSetNullClause(),
                                          osql::clauses::MatchClause("match_string"),
                                          osql::clauses::OnUpdateCascadeClause(),
                                          dic_1);
    std::cout << "Foreign Key clause 3: " << osql::clauses::T(fkc_3) << std::endl;


    osql::columns::Column column_1("columnName1");
    std::cout << "column_1: " << osql::clauses::T(column_1) << std::endl;

    osql::columns::Column column_2("columnName2", osql::clauses::TypeNameClause("INT"));
    std::cout << "column_2: " << osql::clauses::T(column_2) << std::endl;

    osql::columns::Column column_3("columnName3", osql::clauses::TypeNameClause("CHAR", 10));
    std::cout << "column_3: " << osql::clauses::T(column_3) << std::endl;

    osql::columns::Column column_4("columnName4", osql::clauses::TypeNameClause("REAL", 10, 20));
    std::cout << "column_4: " << osql::clauses::T(column_4) << std::endl;

    osql::columns::Column column_5("columnName5",
                                   osql::clauses::TypeNameClause("CHAR", 10),
                                   osql::columns::constraints::NotNullClause(osql::clauses::CONFLICT_FAIL_CLAUSE));
    std::cout << "column_5: " << osql::clauses::T(column_5) << std::endl;

    osql::columns::Column column_6("columnName6",
                                   osql::clauses::TypeNameClause("CHAR", 10),
                                   osql::columns::constraints::NotNullClause(osql::clauses::CONFLICT_FAIL_CLAUSE),
                                   osql::columns::constraints::UniqueClause(osql::clauses::CONFLICT_ABORT_CLAUSE),
                                   osql::columns::constraints::DefaultClause("<unset>"));
    std::cout << "column_6: " << osql::clauses::T(column_6) << std::endl;

}
