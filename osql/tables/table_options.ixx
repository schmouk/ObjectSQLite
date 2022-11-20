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

#include <format>
#include <string>


export module osql.tables.table_options;

import osql.clauses;


//===========================================================================
export namespace osql::tables
{
    //=======================================================================
    /** @brief The base class for SQL tables. */
    class TableOptions : public osql::clauses::NoPrefixClause<>
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::NoPrefixClause<>;


        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline TableOptions(const bool without_rowid = true, const bool strict_typing = false) noexcept
            : MyBaseClass()
        {
            set_text(get_core_text(without_rowid, strict_typing));  // notice: set_text is inherited from base class
        }

        /** @brief Default copy constructor. */
        TableOptions(const TableOptions&) noexcept = default;

        /** @brief Default move constructor. */
        TableOptions(TableOptions&&) noexcept = default;

        /** @brief Default destructor. */
        virtual ~TableOptions() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        TableOptions& operator= (const TableOptions&) noexcept = default;

        /** @brief Default move assignment. */
        TableOptions& operator= (TableOptions&&) noexcept = default;


        //---   Operations   ------------------------------------------------
        /** @brief Gets the core text associated with this table options clause. */
        [[nodiscard]] std::string get_core_text(const bool without_rowid = true, const bool strict_typing = false) const noexcept;


    private:
        static inline const std::string WITHOUT_ROWID{ " WITHOUT ROWID" };
        static inline const std::string STRICT{ " STRICT" };
    };

}