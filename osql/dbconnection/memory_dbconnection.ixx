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


export module osql.dbconnection.memory_dbconnection;

import osql.dbconnection;


//===========================================================================
export namespace osql::dbconnection
{
    //=======================================================================
    /** @brief The connections to SQLite databases that are opened in memory.
    *
    * Such databases are opened into memory. They are automatically
    * destroyed at destruction time.
    */
    class MemoryDBConnection : public osql::dbconnection::DBConnection
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
        inline MemoryDBConnection(const std::string&  filename = "",
                                  const int           flags = CREATE,
                                  const std::string&  vfs_module = "win32") noexcept
            : osql::dbconnection::DBConnection(filename, flags | MEMORY_DB, vfs_module)
        {}

        /** @brief Default destructor. */
        virtual ~MemoryDBConnection() noexcept = default;
    };
}