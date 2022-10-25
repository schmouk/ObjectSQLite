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

import osql.dbconnection;
using namespace osql::dbconnection;

import osql.clauses;

osql::clauses::WithClause clause;


int main()
{
    std::cout << "Let's test ObjectSQLite with sqlite3 version " << SQLITE_VERSION << "!\n";

    DBConnection test_db{ "tests/db_test", DBConnection::CREATE };
    std::cout << "creation of first test db, error result = " << test_db.get_error_code() << ", " << test_db.get_error_msg() << std::endl;

    MemoryDBConnection test_mem_db{};
    std::cout << "creation of memory test db, error result = " << test_mem_db.get_error_code() << ", " << test_mem_db.get_error_msg() << std::endl;

    osql::clauses::WithRecursiveClause wr_clause("test text");
    std::cout << "Recursive With Clause content: " << wr_clause.get_text() << std::endl;

    std::cout << "Empty With Clause content: " << clause.get_text() << std::endl;
}
