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

/*
#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
*/
#include <iterator>
#include <cstddef>

#include "sqlite3.h"


export module osql.statements.result;

import osql.statements.result_row;


//===========================================================================
export namespace osql::statements
{
    //===   RESULT COLUMN<T>   ==============================================
    /** @brief The class of results from SQL statements processing. */
    class Result
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @param statement: sqlite3_stmt*
        *   A pointer to the related SQLite statement.
        */
        inline Result(sqlite3_stmt* statement_ptr) noexcept
            : _sqlite_statement_ptr{ statement_ptr }
        {}

        /** @brief Deleted Empty constructor. */
        Result() noexcept = delete;

        /** @brief Deleted copy constructor. */
        Result(const Result&) noexcept = delete;

        /** @brief Deleted move constructor. */
        Result(Result&&) noexcept = delete;

        /** @brief Default Destructor. */
        inline virtual ~Result() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        Result& operator= (const Result&) noexcept = default;

        /** @brief Default move assignment. */
        Result& operator= (Result&&) noexcept = default;


        //---   Accessors   -------------------------------------------------
        /** @brief Gets the value of the last sqlite3 error that happened while fetching rows.
        *
        * @return SQLITE_OK if last fetching call was not erroneous. This
        *   is another correct way to check the completion of  a  fetches
        *   series when method fetch() has just returned false.
        */
        inline const int error_code() const noexcept
        {
            return (_sqlite_error_code == SQLITE_DONE || _sqlite_error_code == SQLITE_ROW)
                        ? SQLITE_OK
                        : _sqlite_error_code;
        }


        //---   Iterator   --------------------------------------------------
        /** @brief The class of internal input iterator applied to ResultRow instances.
        *
        * This is a correct way to run through rows that  are  resulting
        * from the processing of an SQL statement.
        * Reminder:  input  iterators  are  iterators  that  are  scanned
        * forward only once with no way to modify the data they point to.
        */
        class iterator
        {
        public:
            //---   Wrappers   ----------------------------------------------
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = osql::statements::ResultRow;
            using pointer           = value_type*;
            using reference         = value_type&;


            //---   Constructors / Destructor   -----------------------------
            /** @brief Value constructor. */
            inline iterator(sqlite3_stmt* statement_ptr) noexcept
                : m_sqlite_statement_ptr{ statement_ptr }
                , m_result_row{ statement_ptr }
                , m_current_row_index{ 0 }
            {
                m_fetch_next_row();  // just to get the first resulting row
            }

            /** @brief Default destructor. */
            virtual ~iterator() noexcept = default;


            //---   Operations   --------------------------------------------
            /** @brief Returns true when no more rows are available for fetching, or false otherwise. */
            inline const bool is_completed() const noexcept
            {
                return (m_sqlite_statement_ptr == nullptr ||
                        m_result_row.is_completed() ||
                        !m_result_row.is_ok());
            }


            //---   Operators   ---------------------------------------------
            /** @brief Indirection operator - returns a reference to the current resulting row. */
            reference operator* ()
            {
                return m_result_row;
            }

            /** @brief Dereference operator - returns a pointer to the current resulting row. */
            pointer operator-> ()
            {
                return &m_result_row;
            }

            /** @brief Prefix increment operator. */
            [[nodiscard]] inline iterator& operator++() noexcept
            {
                m_fetch_next_row();
                return *this;
            }

            /** @brief Postfix increment operator. */
            [[nodiscard]] inline iterator operator++(int) noexcept
            {
                iterator mem = *this;
                m_fetch_next_row();
                return mem;
            }

            /** @brief Returns true if both iterators get the same status, or false otherwise. */
            friend bool operator== (const iterator& lhs, const iterator& rhs)
            {
                return lhs.m_sqlite_statement_ptr == rhs.m_sqlite_statement_ptr &&
                       lhs.m_current_row_index == rhs.m_current_row_index;
            }

            /** @brief Returns true if both iterators are not the same. */
            friend bool operator!= (const iterator& lhs, const iterator& rhs)
            {
                return !(lhs == rhs);
            }


        private:
            /* fetches next available row on the prepared statement. */
            void m_fetch_next_row()
            {
                if (m_sqlite_statement_ptr != nullptr && m_result_row.is_ok())
                {
                    m_result_row.fetch();
                    ++m_current_row_index;
                }

            }
            sqlite3_stmt*                m_sqlite_statement_ptr{ nullptr };
            osql::statements::ResultRow  m_result_row{};
            uint32_t                     m_current_row_index{ 0 };

        };


        //---   Operations   ------------------------------------------------
        /** @brief Starting point for iterations.
        *
        * Checking the end of the iterations may  be  done  by  testing 
        * the returned value of method '.is_completed()' applied to the
        * iterator intantiated-by and returned-on call to '.begin()'.
        */
        [[nodiscard]] inline iterator begin() noexcept
        {
            return iterator(_sqlite_statement_ptr);
        }

        /** @brief End of iterations marker.
        *
        * Checking the end of the iterations may also be done by testing 
        * the  returned value of method '.is_completed()' applied to the
        * iterator intantiated-by and returned-on call to '.begin()'.
        */
        [[nodiscard]] inline iterator end() noexcept
        {
            return iterator(nullptr);
        }


        //---   Operators   -------------------------------------------------


    protected:
        //---   Internal attributes   ---------------------------------------
        sqlite3_stmt*  _sqlite_statement_ptr{ nullptr };
        int            _sqlite_error_code{ SQLITE_OK };
    };

}
