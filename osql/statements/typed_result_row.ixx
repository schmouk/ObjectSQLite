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

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include "sqlite3.h"


export module osql.statements.typed_result_row;

import osql.statements.result_column;
import osql.statements.result_row;
import osql.statements.statement;


//===========================================================================
export namespace osql::statements
{
    //===   RESULT COLUMN<T>   ==============================================
    /** @brief The class of SQLite rows that result from SQL statements processing. */
    template<typename... ColumnTs>
    class TypedResultRow : public osql::statements::ResultRow
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @param statement: sqlite3_stmt*
        *   A pointer to the related SQLite statement.
        */
        inline TypedResultRow(sqlite3_stmt* statement_ptr) noexcept
            : _sqlite_statement_ptr{ statement_ptr }
        {}

        /** @brief Empty constructor. */
        TypedResultRow() noexcept = default;

        /** @brief Default copy constructor. */
        TypedResultRow(const TypedResultRow&) noexcept = default;

        /** @brief Default move constructor. */
        TypedResultRow(TypedResultRow&&) noexcept = default;

        /** @brief Default Destructor. */
        inline virtual ~TypedResultRow() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] TypedResultRow& operator= (const TypedResultRow&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] TypedResultRow& operator= (TypedResultRow&&) noexcept = default;

        /** @brief Sets the sqlite statement pointer associated with this result-row. */
        [[nodiscard]] TypedResultRow& operator= (sqlite3_stmt* statement_ptr) noexcept
        {
            _sqlite_statement_ptr = statement_ptr;
            return *this;
        }


        //---   Operators   -------------------------------------------------
        /** @brief Returns the value contained in an indexed result column. */
        template<typename ColumnT>
        ColumnT operator[] (const uint32_t column_index) const
        {
            osql::statements::ResultColumn<ColumnT> result_column(_sqlite_statement_ptr, column_index);
            return result_column.get();
        }
    };

}

