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


export module osql.common.object_base;


//===========================================================================
export namespace osql::common
{
    //=======================================================================
    /** @brief The base class for SQLite objects. */
    class ObjectBase
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline ObjectBase(sqlite3* db_handle) noexcept
            : _db_handle(db_handle)
        {}

        /** @brief Default empty constructor. */
        ObjectBase() noexcept = default;

        /** @brief Default copy constructor. */
        ObjectBase(const ObjectBase&) noexcept = default;

        /** @brief Default move constructor. */
        ObjectBase(ObjectBase&&) noexcept = default;

        /** @brief Destructor. */
        virtual ~ObjectBase() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        [[nodiscard]] ObjectBase& operator= (const ObjectBase&) noexcept = default;

        /** @brief Default move assignment. */
        [[nodiscard]] ObjectBase& operator= (ObjectBase&&) noexcept = default;


        //---   Error Operations   ------------------------------------------
        /** @brief Returns true if things are fine, or false in case of any type of error. */
        [[nodiscard]] inline const bool is_ok() const noexcept
        {
            return _last_error_code == SQLITE_OK;
        }

        /** @brief Returns the last error code value. */
        [[nodiscard]] inline const int get_error_code() const noexcept
        {
            return _last_error_code;
        }

        /** @brief Returns the last error message - UTF-8. */
        [[nodiscard]] inline const std::string get_error_msg() const noexcept
        {
            return sqlite3_errmsg(_db_handle);
        }

        /** @brief Returns the last error message - UTF-16. */
        [[nodiscard]] inline const std::wstring get_error_wmsg() const noexcept
        {
            return static_cast<const wchar_t*>(sqlite3_errmsg16(_db_handle));
        }


    protected:
        //---   Attributes   ------------------------------------------------
        sqlite3* _db_handle{ nullptr };          //!< The sqlite3 handle to the associatted database.
        int      _last_error_code{ SQLITE_OK };  //!< the code of the last encountered error.
    };

}