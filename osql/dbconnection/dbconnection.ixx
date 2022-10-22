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


export module osql.dbconnection;


//===========================================================================
export namespace osql::dbconnection
{
    //=======================================================================
    /** @brief The default class for connections to SQLite databases.
    *
    * @sa RODBConnection, RWDBConnection, MemoryDBConnexion.
    */
    class DBConnection
    {
    public:
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
        * See https://www.sqlite.org/c3ref/open.html
        */
        inline DBConnection(const std::string& filename                         ,
                            const int          flags      = CREATE | URI_ALLOWED,
                            const std::string& vfs_module = "win32"              ) noexcept
        {
            m_last_error_code = sqlite3_open_v2(filename.c_str(), &m_handle, flags, vfs_module.c_str());
        }

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
        DBConnection operator= (const DBConnection&) noexcept = delete;

        /** @brief Deleted move assignment. */
        DBConnection operator= (DBConnection&&) noexcept = delete;


        //---   Accessors   -------------------------------------------------
        /** @brief Gets access to the sqlite3 connection handle. */
        inline const sqlite3* get_handle() const noexcept
        {
            return m_handle;
        }


        //---   Error Operations   ------------------------------------------
        /** @brief Returns true if things are fine, or false in case of any type of error. */
        inline const bool is_ok() const noexcept
        {
            return m_last_error_code == SQLITE_OK;
        }

        /** @brief Returns the last error code value. */
        inline const int get_error_code() const noexcept
        {
            return m_last_error_code;
        }

        /** @brief Returns the last error message - UTF-8. */
        inline const std::string get_error_msg() const noexcept
        {
            return sqlite3_errmsg(m_handle);
        }

        /** @brief Returns the last error message - UTF-16. */
        inline const std::wstring get_error_wmsg() const noexcept
        {
            return static_cast<const wchar_t*>(sqlite3_errmsg16(m_handle));
        }


        //---   Other Operations   ------------------------------------------
        /** @brief Closes this connection. Ends any pending transaction also.
        *
        * @return the associated error code if any, or SQLITE_OK if no error.
        */
        int close() noexcept;


    private:
        //---   Internal attributes   ---------------------------------------
        sqlite3* m_handle;       //!< The sqlite3 handle to the created database
        int      m_last_error_code; //!< the code of the last encountered error.
    };


    //=======================================================================
    /** @brief The Read-Only connections to SQLite databases.
    * 
    * Such databases are opened for read only operations and must already
    * exist at opening time.
    */
    class RODBConnection : public DBConnection
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor with UTF-8 chars filename.
        *
        * @param filename: std::string
        *   A reference to the filename for this database.
        * @param flags: int
        *   The  combination  of flags to be used while opening/creating a
        *   new database file. Defaults to READ_ONLY and URI_ALLOWED.
        *   Notice: the READ_ONLY flag is always forced, even if READ_WRITE
        *   or CREATE flags are set.
        * @param vfs_module: std::string
        *   Defines the VFS to be used for this database. Defaults here to
        *   "win32". See https://www.sqlite.org/vfs.html
        *
        * See https://www.sqlite.org/c3ref/open.html
        */
        inline RODBConnection(const std::string& filename,
                              const int          flags = URI_ALLOWED,
                              const std::string& vfs_module = "win32") noexcept
            : DBConnection(filename, flags | (READ_ONLY & ~(READ_WRITE | CREATE)), vfs_module)
        {}

        /** @brief Default destructor. */
        virtual ~RODBConnection() noexcept = default;
    };


    //=======================================================================
    /** @brief The Read-Write connections to SQLite databases.
    *
    * Such databases are opened for read/write operations and must already
    * exist at opening time.
    */
    class RWDBConnection : public DBConnection
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor with UTF-8 chars filename.
        *
        * @param filename: std::string
        *   A reference to the filename for this database.
        * @param flags: int
        *   The  combination  of flags to be used while opening/creating a
        *   new database file. Defaults to READ_WRITE and URI_ALLOWED.
        *   Notice: the READ_WRITE flag is always forced, even if READ_ONLY
        *   or CREATE flags are set.
        * @param vfs_module: std::string
        *   Defines the VFS to be used for this database. Defaults here to
        *   "win32". See https://www.sqlite.org/vfs.html
        *
        * See https://www.sqlite.org/c3ref/open.html
        */
        inline RWDBConnection(const std::string& filename,
                              const int          flags = URI_ALLOWED,
                              const std::string& vfs_module = "win32") noexcept
            : DBConnection(filename, flags | (READ_WRITE & ~(READ_ONLY | CREATE)), vfs_module)
        {}

        /** @brief Default destructor. */
        virtual ~RWDBConnection() noexcept = default;
    };


    //=======================================================================
    /** @brief The connections to SQLite databases that are opened in memory.
    *
    * Such databases are opened into memory. They are automatically
    * destroyed at destruction time.
    */
    class MemoryDBConnection : public DBConnection
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Constructor with UTF-8 chars filename.
        *
        * @param filename: std::string
        *   A reference to the filename for this database.  Defaults to the
        *   empty string. It should be set if shared cache mode is enabled,
        *   but the "filename" is otherwise ignored. 
        * @param flags: int
        *   The  combination  of  flags to be used while opening/creating a
        *   new database file. Defaults to CREATE.
        *   Notice: the MEMORY_DB flag is always forced.
        * @param vfs_module: std::string
        *   Defines the VFS to be used for this database.  Defaults here to
        *   "win32". See https://www.sqlite.org/vfs.html
        *
        * See https://www.sqlite.org/c3ref/open.html
        */
        inline MemoryDBConnection(const std::string& filename = "",
                                  const int          flags = CREATE,
                                  const std::string& vfs_module = "win32") noexcept
            : DBConnection(filename, flags | MEMORY_DB, vfs_module)
        {}

        /** @brief Default destructor. */
        virtual ~MemoryDBConnection() noexcept = default;
    };
}