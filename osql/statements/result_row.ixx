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


export module osql.statements.result_row;

import osql.statements.result_column;
import osql.statements.statement;


//===========================================================================
export namespace osql::statements
{
    //===   RESULT COLUMN<T>   ==============================================
    /** @brief The class of SQLite rows that result from SQL statements processing. */
    class ResultRow
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @param statement: sqlite3_stmt*
        *   A pointer to the related SQLite statement.
        */
        inline ResultRow(sqlite3_stmt* statement_ptr) noexcept
            : _sqlite_statement_ptr{ statement_ptr }
        {}

        /** @brief Empty constructor. */
        ResultRow() noexcept = default;

        /** @brief Default copy constructor. */
        ResultRow(const ResultRow&) noexcept = default;

        /** @brief Default move constructor. */
        ResultRow(ResultRow&&) noexcept = default;

        /** @brief Default Destructor. */
        inline virtual ~ResultRow() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] ResultRow& operator= (const ResultRow&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] ResultRow& operator= (ResultRow&&) noexcept = default;

        /** @brief Sets the sqlite statement pointer associated with this result-row. */
        [[nodiscard]] ResultRow& operator= (sqlite3_stmt* statement_ptr) noexcept
        {
            _sqlite_statement_ptr = statement_ptr;
            return *this;
        }


        //---   Accessors   -------------------------------------------------
        /** @brief Gets the value of the last sqlite3 error that happened while fetching rows.
        *
        * @return SQLITE_OK if last fetching call was not erroneous. This
        *   is another correct way to check the completion of  a  fetches
        *   series when method fetch() has just returned false.
        */
        inline const int error_code() const noexcept
        {
            return (_sqlite_error_code == SQLITE_DONE || _sqlite_error_code == SQLITE_ROW) ? SQLITE_OK : _sqlite_error_code;
        }


        //---   Operations   ------------------------------------------------
        /** @brief Fetches another raw as evaluated by the statement processing.
        *
        * @return   true if another raw was available for this fetching,
        *   or false in case of completion of the fetching or in case of 
        *   any type of sqlite3 error.
        *   When returning false, check either is_completed() to get the
        *   completing  of  this  fetching  or  error_code()  to get the
        *   actual sqliteE3 error code.
        */
        inline const bool fetch() noexcept
        {
            _sqlite_error_code = sqlite3_step(_sqlite_statement_ptr);
            return _sqlite_error_code == SQLITE_ROW;
        }

        /** @brief Checks for the completion of a fetches series.
        *
        * @return  true if no more raws are to be fetched after the processing
        *   of a statement, or false otherwise. When this method returns false
        *   while method fetch() has also just returned false means that  some
        *   sqlite error has happened.  Method error_code() informs then about
        *   the type of the occuring error.
        */
        inline const bool is_completed() const noexcept
        {
            return _sqlite_error_code == SQLITE_DONE;
        }

        /** @brief Returns true if this result row error status is SQLITE_OK, or false otherwise. */
        [[nodiscard]] inline const bool is_ok() const noexcept
        {
            return error_code() == SQLITE_OK;
        }

        /** @brief Sets the sqlite statement pointer associated with this result-row. */
        inline void set(sqlite3_stmt* statement_ptr) noexcept
        {
            _sqlite_statement_ptr = statement_ptr;
        }


        //---   Operators   -------------------------------------------------
        /** @brief Returns the value contained in an indexed result column. */
        template<typename ResultColumnT>
        ResultColumnT::value_type operator[] (const uint32_t column_index) const
        {
            const ResultColumnT result_column(_sqlite_statement_ptr, column_index);
            return result_column.get();
        }


    protected:
        //---   Internal attributes   ---------------------------------------
        sqlite3_stmt* _sqlite_statement_ptr{ nullptr };
        int           _sqlite_error_code{ SQLITE_OK };
    };

}
