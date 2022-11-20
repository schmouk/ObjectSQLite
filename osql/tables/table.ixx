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

#include <concepts>
#include <string>

#include "sqlite3.h"


export module osql.tables.table;

import osql.common.object_base;


//===========================================================================
export namespace osql::tables
{
    //=======================================================================
    /** @brief The base class for SQL tables. */
    class Table : public osql::common::ObjectBase
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::common::ObjectBase;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename... ColumnsT>
        Table(const std::string& name, ColumnsT&... columns) noexcept;

        /** @brief Value constructor. */
        template<typename... ColumnsT>
        Table(const std::string& attached_database, const std::string& name, ColumnsT&... columns) noexcept;

        /** @brief Default empty constructor. */
        Table() noexcept = default;

        /** @brief Deleted copy constructor. */
        Table(const Table&) noexcept = delete;

        /** @brief Deleted move constructor. */
        Table(Table&&) noexcept = delete;

        /** @brief Destructor. */
        virtual ~Table() noexcept;


        //---   Assignments   -----------------------------------------------
        /** @brief Deleted copy assignment. */
        Table& operator= (const Table&) noexcept = delete;

        /** @brief Deleted move assignment. */
        Table& operator= (Table&&) noexcept = delete;


        //---   Attributes   ------------------------------------------------
        //std::vector< osql::columns::ColumnBase* >  columns;

    };

}