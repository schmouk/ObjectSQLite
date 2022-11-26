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

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include "sqlite3.h"


export module osql.statements.result_column;

import osql.statements.statement;


//===========================================================================
export namespace osql::statements
{
    //===   RESULT COLUMN<T>   ==============================================
    /** @brief The class of SQLite columns in rows that result from SQL statements processing. */
    template<typename T>
    class ResultColumn
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @param statement: sqlite3_stmt*
        *   A pointer to the related SQLite statement.
        * @param column_index: uint32_t
        *   The index of the column in the raws resulting
        *   from the associated statement processing.
        */
        inline ResultColumn(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : _sqlite_statement_ptr{ statement_ptr }
            , _column_index{ column_index }
        {}

        /** @brief Empty constructor. */
        ResultColumn() noexcept = default;

        /** @brief Default copy constructor. */
        ResultColumn(const ResultColumn&) noexcept = default;

        /** @brief Default move constructor. */
        ResultColumn(ResultColumn&&) noexcept = default;

        /** @brief Default Destructor. */
        inline virtual ~ResultColumn() noexcept = default;


        //---   Assignments   -----------------------------------------------
        /** @brief Default copy assignment. */
        ResultColumn& operator= (const ResultColumn&) noexcept = default;

        /** @brief Default move assignment. */
        ResultColumn& operator= (ResultColumn&&) noexcept = default;


        //---   Accessors   -------------------------------------------------


        //---   Operations   ------------------------------------------------
        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual T get() const = 0;


    protected:
        //---   Internal attributes   ---------------------------------------
        sqlite3_stmt*  _sqlite_statement_ptr;
        uint32_t       _column_index;
    };


    //===   ResultColumn< char >   ==========================================
    /** @brief char specialization of column result. */
    class ResultColumnChar : public ResultColumn<char>
    {
    public:

        using value_type = char;

        /** @brief Value constructor. */
        inline ResultColumnChar(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>( statement_ptr, column_index )
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return sqlite3_column_text(_sqlite_statement_ptr, _column_index)[0];
        }
    };


    //===   ResultColumn< unsigned char >   =================================
    /** @brief char specialization of column result. */
    class ResultColumnUChar : public ResultColumn<unsigned char>
    {
    public:

        using value_type = unsigned char;

        /** @brief Value constructor. */
        inline ResultColumnUChar(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, (int64_t)std::numeric_limits<value_type>::lowest(),
                                                 (int64_t)std::numeric_limits<value_type>::max());
        }
    };


    //===   ResultColumn< short >   =========================================
    /** @brief char specialization of column result. */
    class ResultColumnShort : public ResultColumn<short>
    {
    public:

        using value_type = short;

        /** @brief Value constructor. */
        inline ResultColumnShort(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, (int64_t)std::numeric_limits<value_type>::lowest(),
                                                 (int64_t)std::numeric_limits<value_type>::max());
        }
    };


    //===   ResultColumn< unsigned short >   ================================
    /** @brief char specialization of column result. */
    class ResultColumnUShort : public ResultColumn<unsigned short>
    {
    public:

        using value_type = unsigned short;

        /** @brief Value constructor. */
        inline ResultColumnUShort(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, (int64_t)std::numeric_limits<value_type>::lowest(),
                                                 (int64_t)std::numeric_limits<value_type>::max());
        }
    };


    //===   ResultColumn< int >   ===========================================
    /** @brief char specialization of column result. */
    class ResultColumnInt : public ResultColumn<int>
    {
    public:

        using value_type = int;

        /** @brief Value constructor. */
        inline ResultColumnInt(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return sqlite3_column_int(_sqlite_statement_ptr, _column_index);
        }
    };


    //===   ResultColumn< unsigned int >   ==================================
    /** @brief char specialization of column result. */
    class ResultColumnUInt : public ResultColumn<unsigned int>
    {
    public:

        using value_type = unsigned int;

        /** @brief Value constructor. */
        inline ResultColumnUInt(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, (int64_t)std::numeric_limits<value_type>::lowest(),
                                                 (int64_t)std::numeric_limits<value_type>::max());
        }
    };


    //===   ResultColumn< long >   ==========================================
    /** @brief char specialization of column result. */
    using ResultColumnLong = ResultColumnInt;


    //===   ResultColumn< unsigned long >   =================================
    /** @brief char specialization of column result. */
    using ResultColumnULong = ResultColumnUInt;


    //===   ResultColumn< long long >   =====================================
    /** @brief char specialization of column result. */
    class ResultColumnLLong : public ResultColumn<long long>
    {
    public:

        using value_type = long long;

        /** @brief Value constructor. */
        inline ResultColumnLLong(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
        }
    };


    //===   ResultColumn< unsigned long long >   ============================
    /** @brief char specialization of column result. */
    class ResultColumnULLong : public ResultColumn<unsigned long long>
    {
    public:

        using value_type = unsigned long long;

        /** @brief Value constructor. */
        inline ResultColumnULLong(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, 0LL,
                                                 std::numeric_limits<long long>::max());
        }
    };


    //===   ResultColumn< float >   =========================================
    /** @brief char specialization of column result. */
    class ResultColumnFloat : public ResultColumn<float>
    {
    public:

        using value_type = float;

        /** @brief Value constructor. */
        inline ResultColumnFloat(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const double value = sqlite3_column_double(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, (double)std::numeric_limits<value_type>::lowest(),
                                                 (double)std::numeric_limits<value_type>::max());
        }
    };


    //===   ResultColumn< double >   =========================================
    /** @brief char specialization of column result. */
    class ResultColumnDouble : public ResultColumn<double>
    {
    public:

        using value_type = double;

        /** @brief Value constructor. */
        inline ResultColumnDouble(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return sqlite3_column_double(_sqlite_statement_ptr, _column_index);
        }
    };


    //===   ResultColumn< long double >   ===================================
    /** @brief char specialization of column result. */
    class ResultColumnLDouble : public ResultColumn<long double>
    {
    public:

        using value_type = long double;

        /** @brief Value constructor. */
        inline ResultColumnLDouble(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return (value_type)sqlite3_column_double(_sqlite_statement_ptr, _column_index);
        }
    };


    //===   ResultColumn< int8_t >   ========================================
    /** @brief char specialization of column result. */
    class ResultColumnInt8 : public ResultColumn<int8_t>
    {
    public:

        using value_type = int8_t;

        /** @brief Value constructor. */
        inline ResultColumnInt8(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            const int64_t value = sqlite3_column_int64(_sqlite_statement_ptr, _column_index);
            return (value_type)std::clamp(value, -128LL, 127LL);
        }
    };


    //===   ResultColumn< uint8_t >   =======================================
    /** @brief char specialization of column result. */
    using ResultColumnUInt8 = ResultColumnUChar;


    //===   ResultColumn< int16_t >   =======================================
    /** @brief char specialization of column result. */
    using ResultColumnInt16 = ResultColumnShort;


    //===   ResultColumn< uint16_t >   ======================================
    /** @brief char specialization of column result. */
    using ResultColumnUInt16 = ResultColumnUShort;


    //===   ResultColumn< int32_t >   =======================================
    /** @brief char specialization of column result. */
    using ResultColumnInt32 = ResultColumnInt;


    //===   ResultColumn< uint32_t >   ======================================
    /** @brief char specialization of column result. */
    using ResultColumnUInt32 = ResultColumnUInt;


    //===   ResultColumn< int64_t >   =======================================
    /** @brief char specialization of column result. */
    using ResultColumnInt64 = ResultColumnLLong;


    //===   ResultColumn< uint32_t >   ======================================
    /** @brief char specialization of column result. */
    using ResultColumnUInt64 = ResultColumnULLong;


    //===   ResultColumn< std::string >   ===================================
    /** @brief char specialization of column result. */
    class ResultColumnString : public ResultColumn<std::string>
    {
    public:

        using value_type = std::string;

        /** @brief Value constructor. */
        inline ResultColumnString(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return value_type((char*)sqlite3_column_text(_sqlite_statement_ptr, _column_index));
        }
    };


    //===   ResultColumn< std::u8string >   =================================
    /** @brief char specialization of column result. */
    class ResultColumnUString : public ResultColumn<std::u8string>
    {
    public:

        using value_type = std::u8string;
        using pointer    = value_type::pointer;

        /** @brief Value constructor. */
        inline ResultColumnUString(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return value_type((pointer)sqlite3_column_text(_sqlite_statement_ptr, _column_index));
        }
    };


    //===   ResultColumn< std::wstring >   =================================
    /** @brief char specialization of column result. */
    class ResultColumnString16 : public ResultColumn<std::wstring>
    {
    public:

        using value_type = std::wstring;
        using pointer = value_type::pointer;

        /** @brief Value constructor. */
        inline ResultColumnString16(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return value_type((pointer)sqlite3_column_text16(_sqlite_statement_ptr, _column_index));
        }
    };


    //===   ResultColumn< std::u16string >   ================================
    /** @brief char specialization of column result. */
    class ResultColumnUString16 : public ResultColumn<std::u16string>
    {
    public:

        using value_type = std::u16string;
        using pointer = value_type::pointer;

        /** @brief Value constructor. */
        inline ResultColumnUString16(sqlite3_stmt* statement_ptr, const uint32_t column_index) noexcept
            : ResultColumn<value_type>(statement_ptr, column_index)
        {}

        /** @brief Returns the value contained in this column. */
        [[nodiscard]] virtual value_type get()
        {
            return value_type((pointer)sqlite3_column_text16(_sqlite_statement_ptr, _column_index));
        }
    };


    //===   ResultColumn< Blob >   ==========================================
    /** @brief char specialization of column result. */
    using ResultColumnBlob = ResultColumnUString;

}
