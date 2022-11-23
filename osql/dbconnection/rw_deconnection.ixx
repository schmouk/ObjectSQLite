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


export module osql.dbconnection.rw_dbconnection;

import osql.dbconnection;


//===========================================================================
export namespace osql::dbconnection
{
    //=======================================================================
    /** @brief The Read-Write connections to SQLite databases.
    *
    * Such databases are opened for read/write operations and must already
    * exist at opening time.
    */
    class RWDBConnection : public osql::dbconnection::DBConnection
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
        inline RWDBConnection(const std::string&  filename,
                              const int           flags = URI_ALLOWED,
                              const std::string&  vfs_module = "win32") noexcept
            : osql::dbconnection::DBConnection(filename, flags | (READ_WRITE & ~(READ_ONLY | CREATE)), vfs_module)
        {}

        /** @brief Default destructor. */
        virtual ~RWDBConnection() noexcept = default;
    };

}