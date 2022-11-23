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


export module osql.statements.statements;

import osql.common.object_base;
import osql.dbconnection;


//===========================================================================
export namespace osql::statements
{
    //=======================================================================
    /** @brief The default class for all SQLite statements.
    *
    * @sa ...
    */
    class Statement : public osql::common::ObjectBase
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::common::ObjectBase;  //!< wrapper to the base class


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (1/2).
        *
        * You should check the correctness of the preparation  of  this
        * SQL statement by calling method '.is_ok()' after creation.
        * 
        * @param sql_text: std:string
        *   A reference to the SQL statement text. Must be well formed.
        * @param db_connection: DBConnection
        *   A reference to the database connection via  which  the  SQL
        *   statement is to be evaluated.
        */
        Statement(const std::string&                sql_text,
                  osql::dbconnection::DBConnection& db_connection) noexcept;

        /** @brief Value constructor (2/2).
        *
        * You should check the correctness of the preparation  of  this
        * SQL statement by calling method '.is_ok()' after creation.
        *
        * @param sql_text: std:string
        *   A reference to the SQL statement text. Must be well formed.
        * @param db_connection: DBConnection
        *   A reference to the database connection via  which  the  SQL
        *   statement is to be evaluated.
        * @param prepare_flags: int
        *   A bit-or combination of sqlite3 constants SQLITE_PREPARE_PERSISTENT
        *   and SQLITE_PREPARE_NO_VTAB.
        *   See https://www.sqlite.org/c3ref/c_prepare_normalize.html#sqlitepreparepersistent
        *   for explanations on the actions of these flags.
        */
        Statement(const std::string&                sql_text,
                  osql::dbconnection::DBConnection& db_connection,
                  const unsigned int                prepare_flags) noexcept;

        /** @brief Empty constructor. */
        Statement() noexcept = default;

        /** @brief Deleted copy constructor. */
        Statement(const Statement&) noexcept = delete;

        /** @brief Deleted move constructor. */
        Statement(Statement&&) noexcept = delete;

        /** @brief Destructor. */
        inline virtual ~Statement() noexcept
        {
        }


        //---   Assignments   -----------------------------------------------
        /** @brief Deleted copy assignment. */
        Statement& operator= (const Statement&) noexcept = delete;

        /** @brief Deleted move assignment. */
        Statement& operator= (Statement&&) noexcept = delete;


        //---   Accessors   -------------------------------------------------
        /** @brief Returns the handle to the associated sqlite3 prepared statement. */
        inline sqlite3_stmt* get_handle() const noexcept
        {
            return _prepared_stmt_handle;
        }


        //---   Operations   ------------------------------------------------
        /** @brief Executes this statement.
        *
        * Sets the _last_error_code for this object and returns its value.
        */
        const int exec();


        /** @brief Finalizes this statement.
        *
        * Sets the _last_error_code for this object and returns its value.
        * Notice: automatically called a destruction time.
        */
        const int finalize();


    protected:
        //---   Internal attributes   ---------------------------------------
        sqlite3_stmt* _prepared_stmt_handle;  //!< handle to the associated sqlite3 prepared statement
    };

}