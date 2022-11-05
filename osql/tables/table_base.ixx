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


export module osql.tables;

import osql.common;


//===========================================================================
export namespace osql::tables
{
    //=======================================================================
    /** @brief The base class for SQL tables. */
    class TableBase : public osql::common::ObjectBase
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::common::ObjectBase;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        TableBase(const std::string& name) noexcept;

        /** @brief Value constructor. */
        TableBase(const std::string& attached_database, const std::string& name) noexcept;

        /** @brief Default empty constructor. */
        TableBase() noexcept = default;

        /** @brief Deleted copy constructor. */
        TableBase(const TableBase&) noexcept = delete;

        /** @brief Deleted move constructor. */
        TableBase(TableBase&&) noexcept = delete;

        /** @brief Destructor. */
        inline virtual ~TableBase() noexcept;


        //---   Assignments   -----------------------------------------------
        /** @brief Deleted copy assignment. */
        TableBase& operator= (const TableBase&) noexcept = delete;

        /** @brief Deleted move assignment. */
        TableBase& operator= (TableBase&&) noexcept = delete;


    protected:
        //---   Attributes   ------------------------------------------------
    };

}