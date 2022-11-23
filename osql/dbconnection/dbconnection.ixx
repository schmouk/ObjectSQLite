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

#include <memory>
#include <string>
#include <vector>

#include "sqlite3.h"
#include "osql/osql.h"


export module osql.dbconnection;

import osql.common.object_base;


//===========================================================================
export namespace osql::dbconnection
{
    //=======================================================================
    /** @brief The default class for connections to SQLite databases.
    *
    * @sa RODBConnection, RWDBConnection, MemoryDBConnexion.
    */
    class DBConnection : public osql::common::ObjectBase
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::common::ObjectBase;  //!< wrapper to the base class


        //---   OPENING FLAGS   ---------------------------------------------
        // see https://www.sqlite.org/c3ref/c_open_autoproxy.html

        static inline constexpr int CREATE                = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
        static inline constexpr int EXTENDED_RESULT_CODES = SQLITE_OPEN_EXRESCODE;
        static inline constexpr int MEMORY_DB             = SQLITE_OPEN_MEMORY;
        static inline constexpr int MT_MANY_CONNECTIONS   = SQLITE_OPEN_NOMUTEX;
        static inline constexpr int MT_SERIALIZED         = SQLITE_OPEN_FULLMUTEX;
        static inline constexpr int PRIVATE_CACHE         = SQLITE_OPEN_PRIVATECACHE;
        static inline constexpr int READ_ONLY             = SQLITE_OPEN_READONLY;
        static inline constexpr int READ_WRITE            = SQLITE_OPEN_READWRITE;
        static inline constexpr int SHARED_CACHE          = SQLITE_OPEN_SHAREDCACHE;
        static inline constexpr int SYMLINK_NOT_ALLOWED   = SQLITE_OPEN_NOFOLLOW;
        static inline constexpr int URI_ALLOWED           = SQLITE_OPEN_URI;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor with UTF-8 chars filename.
        *
        * @param filename: std::string
        *   A reference to the filename for this database.
        * @param flags: int
        *   The  combination  of flags to be used while opening/creating a
        *   new database file. Defaults to CREATE bit-and URI_ALLOWED. See
        *   https://www.sqlite.org/c3ref/c_open_autoproxy.html  for a full
        *   list  of  available  SQLite flags,  which can be directly used 
        *   here.
        * @param vfs_module: std::string
        *   Defines the VFS to be used for this database. Defaults here to 
        *   "win32". See https://www.sqlite.org/vfs.html
        * 
        * Notice: VFS (Virtual File System?) is to be  understood  as  the
        *   underlying Operating System.
        * 
        * See https://www.sqlite.org/c3ref/open.html
        */
        inline DBConnection(const std::string& filename                         ,
                            const int          flags      = CREATE | URI_ALLOWED,
                            const std::string& vfs_module = "win32"              ) noexcept
            : MyBaseClass()
        {
            _last_error_code = sqlite3_open_v2(filename.c_str(), &_cnx_handle, flags, vfs_module.c_str());
            // notice: attributes '_last_error_code' and '_cnx_handle' are inherited from base class osql::common::ObjectBase
        }

        /** @brief Default empty constructor. */
        DBConnection() noexcept = default;

        /** @brief Deleted copy constructor. */
        DBConnection(const DBConnection&) noexcept = delete;

        /** @brief Deleted move constructor. */
        DBConnection(DBConnection&&) noexcept = delete;

        /** @brief Destructor. */
        inline virtual ~DBConnection() noexcept
        {
            close();
        }


        //---   Assignments   -----------------------------------------------
        /** @brief Deleted copy assignment. */
        DBConnection& operator= (const DBConnection&) noexcept = delete;

        /** @brief Deleted move assignment. */
        DBConnection& operator= (DBConnection&&) noexcept = delete;


        //---   Accessors   -------------------------------------------------
        /** @brief Gets access to the sqlite3 connection handle. */
        inline sqlite3* get_handle() const noexcept
        {
            return _cnx_handle;
        }


        //---   Operations   ------------------------------------------------
        /** @brief Closes this connection. Ends any pending transaction also.
        *
        * @return the associated error code if any, or SQLITE_OK if no error.
        */
        int close() noexcept;


        //===   Run Time Limits   ===========================================
        // see https://www.sqlite.org/limits.html for explanations about 
        // setting  (and  lowering)  lengths or values limits while they
        // are already been set per default in sqlite3 code.

        //---   Getters   ---------------------------------------------------
        /** @brief Gets maximum size of any string or BLOB or table row, in bytes. */
        [[nodiscard]] inline const int get_length_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_LENGTH, -1);
        }

        /** @brief Gets the maximum length of an SQL statement, in bytes. */
        [[nodiscard]] inline const int get_sql_length_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_SQL_LENGTH, -1);
        }

        /** @brief Gets the maximum number of columns in a table definition or in the result set of a SELECT or the maximum number of columns in an index or in an ORDER BY or GROUP BY clause. */
        [[nodiscard]] inline const int get_columns_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_COLUMN, -1);
        }

        /** @brief Gets the maximum depth of the parse tree on any expression. */
        [[nodiscard]] inline const int get_expr_depth_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_EXPR_DEPTH, -1);
        }

        /** @brief Gets the maximum number of terms in a compound SELECT statement. */
        [[nodiscard]] inline const int get_compound_select_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_COMPOUND_SELECT, -1);
        }

        /** @brief Gets the maximum number of instructions in a virtual machine program used to implement an SQL statement. */
        [[nodiscard]] inline const int get_virtual_machine_instructions_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_VDBE_OP, -1);
        }

        /** @brief Gets the maximum number of arguments on a function. */
        [[nodiscard]] inline const int get_function_args_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_FUNCTION_ARG, -1);
        }

        /** @brief Gets the maximum number of attached databases. */
        [[nodiscard]] inline const int get_attached_databases_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_ATTACHED, -1);
        }

        /** @brief Gets the maximum length of the pattern argument to the LIKE or GLOB operators. */
        [[nodiscard]] inline const int get_like_pattern_length_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_LIKE_PATTERN_LENGTH, -1);
        }

        /** @brief Gets the maximum index number of any parameter in an SQL statement. */
        [[nodiscard]] inline const int get_variable_number_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_VARIABLE_NUMBER, -1);
        }

        /** @brief Gets the maximum depth of recursion for triggers. */
        [[nodiscard]] inline const int get_trigger_recursion_depth_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_TRIGGER_DEPTH, -1);
        }

        /** @brief Gets the maximum number of auxiliary worker threads that a single prepared statement may start. */
        [[nodiscard]] inline const int get_worker_threads_limit() const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_WORKER_THREADS, -1);
        }


        //---   Setters   ---------------------------------------------------
        /** @brief Gets maximum size of any string or BLOB or table row, in bytes. */
        inline const int set_length_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_LENGTH, new_limit);
        }

        /** @brief Gets the maximum length of an SQL statement, in bytes. */
        inline const int set_sql_length_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_SQL_LENGTH, new_limit);
        }

        /** @brief Gets the maximum number of columns in a table definition or in the result set of a SELECT or the maximum number of columns in an index or in an ORDER BY or GROUP BY clause. */
        inline const int set_columns_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_COLUMN, new_limit);
        }

        /** @brief Gets the maximum depth of the parse tree on any expression. */
        inline const int set_expr_depth_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_EXPR_DEPTH, new_limit);
        }

        /** @brief Gets the maximum number of terms in a compound SELECT statement. */
        inline const int set_compound_select_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_COMPOUND_SELECT, new_limit);
        }

        /** @brief Gets the maximum number of instructions in a virtual machine program used to implement an SQL statement.
        *
        * If sqlite3_prepare_v2() or the equivalent tries to allocate  space
        * for more than this many opcodes in a single prepared statement, an
        * SQLITE_NOMEM error is returned. */
        inline const int set_virtual_machine_instructions_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_VDBE_OP, new_limit);
        }

        /** @brief Gets the maximum number of arguments on a function. */
        inline const int set_function_args_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_FUNCTION_ARG, new_limit);
        }

        /** @brief Gets the maximum number of attached databases. */
        inline const int set_attached_databases_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_ATTACHED, new_limit);
        }

        /** @brief Gets the maximum length of the pattern argument to the LIKE or GLOB operators. */
        inline const int set_like_pattern_length_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_LIKE_PATTERN_LENGTH, new_limit);
        }

        /** @brief Gets the maximum index number of any parameter in an SQL statement. */
        inline const int set_variable_number_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_VARIABLE_NUMBER, new_limit);
        }

        /** @brief Gets the maximum depth of recursion for triggers. */
        inline const int set_trigger_recursion_depth_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_TRIGGER_DEPTH, new_limit);
        }

        /** @brief Gets the maximum number of auxiliary worker threads that a single prepared statement may start. */
        inline const int set_worker_threads_limit(const int new_limit) const
        {
            return sqlite3_limit(get_handle(), SQLITE_LIMIT_WORKER_THREADS, new_limit);
        }


    protected:
        //---   Attributes   ------------------------------------------------
        sqlite3* _cnx_handle{ nullptr }; //!< the handle to the associated SQLite connection.
        int      _last_error_code{};    //!< the code of the very last SQLite error.
    };

}