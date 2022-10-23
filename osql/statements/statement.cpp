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
#include "sqlite3.h"


module osql.statements;

import osql.dbconnection;


//===========================================================================
namespace osql::statements
{
    /* Value constructor (1/2). */
    Statement::Statement(const std::string&                 sql_text,
                         osql::dbconnection::DBConnection&  db_connection) noexcept
        : MyBaseClass(db_connection.get_handle())
    {
        const char* unused_{ nullptr };
        _last_error_code = sqlite3_prepare_v2(db_connection.get_handle(),
                                              sql_text.c_str(),
                                              sql_text.size() + 1,
                                              &_stmt_handle,
                                              &unused_);
    }

    /* Value constructor (2/2). */
    Statement::Statement(const std::string&                sql_text,
                         osql::dbconnection::DBConnection& db_connection,
                         const unsigned int                prepare_flags) noexcept
    {
        const char* unused_{ nullptr };
        _last_error_code = sqlite3_prepare_v3(db_connection.get_handle(),
                                              sql_text.c_str(),
                                              sql_text.size() + 1,
                                              prepare_flags,
                                              &_stmt_handle,
                                              &unused_);
    }

}