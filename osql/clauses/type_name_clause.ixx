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

#include <cassert>
#include <cstdint>
#include <format>
#include <string>

#include "osql/clauses/clause.h"


export module osql.clauses.type_name_clauses;

import osql.clauses;


//===========================================================================
// This module defines:
//
//  - class TypeNameClause
//  - class TypeNameClause1
//  - class TypeNameClause2
// 
//  - class TypeInt
//  - class TypeInt2
//  - class TypeInt4
//  - class TypeInt8
//  - class TypeInteger
//  - class TypeTinyInt
//  - class TypeSmallInt
//  - class TypeMediumInt
//  - class TypeBigInt
//  - class TypeUnsignedInt
//  - class TypeUnsignedInt2
//  - class TypeUnsignedInt4
//  - class TypeUnsignedInt8
//  - class TypeUnsignedInteger
//  - class TypeUnsignedTinyInt
//  - class TypeUnsignedSmallInt
//  - class TypeUnsignedMediumInt
//  - class TypeUnsignedBigInt
//
//  - class TypeChar
//  - class TypeVaryingChar
//  - class TypeNativeChar
//  - class TypeNativeVaryingChar
//  - class TypeText
//  - class TypeCLOB
//
//  - class TypeBLOB
//
//  - class TypeReal
//  - class TypeFloat
//  - class TypeDouble
//
//  - class TypeNumeric
//  - class TypeDecimal
//  - class TypeBoolean
//  - class TypeDate
//  - class TypeDateTime


//===========================================================================
export namespace osql::clauses
{
    //
    // Notice: these clauses are used with columns and with expressions definitions.
    //

    /** @brief The generic (base) type for all Type name clause. */
    struct TypeName : osql::clauses::NoPrefixClause<>
    {
        TypeName(const std::string& name)
            : osql::clauses::NoPrefixClause<>(name)
        {}
    };


    //===   TYPENAME CLAUSE   ===============================================
    /** @brief The class of Type Name Clauses with ZERO specified unsigned integers. */
    class TypeNameClause : public TypeName
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with sole name of type).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause(const std::string& name) noexcept
            : TypeName(name)
        {}

        /** @brief Deleted empty/default constructor. */
        TypeNameClause() noexcept = delete;
    };


    //===   TYPENAME CLAUSE 1   =============================================
    /** @brief The class of Type Name Clauses with ZERO or ONE specified unsigned integers. */
    class TypeNameClause1 : public TypeName
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with sole name of type).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause1(const std::string& name) noexcept
            : TypeName(name)
        {}

        /** @brief Value constructor (with type name and one signed integer).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause1(const std::string& name, const int32_t num) noexcept
            : TypeName(std::format("{:s}({:d})", name, num))
        {}

        /** @brief Deleted empty/default constructor. */
        TypeNameClause1() noexcept = delete;
    };



    //===   TYPENAME CLAUSE 2   =============================================
    /** @brief The class of Type Name Clauses with ZERO to TWO specified unsigned integers. */
    class TypeNameClause2 : public TypeName
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor (with type name and two signed integers).
        *
        * Notice: The name definition may embed spaces and tabs characters.
        */
        inline TypeNameClause2(const std::string& name, const int32_t min_num, const int32_t max_num) noexcept
            : TypeName(std::format("{:s}({:d}, {:d})", name, min_num, max_num))
        {}

        /** @brief Deleted empty/default constructor. */
        TypeNameClause2() noexcept = delete;
    };


    //===   INTEGER AFFINITY TYPENAMES   ====================================

    /** @brief Generic Integer typename class. */
    struct TypeInt : TypeNameClause
    {
        inline TypeInt() : TypeNameClause("INT") {}
    };

    /** @brief Generic Integer typename class. */
    using TypeInteger = TypeInt;

    /** @brief 2-Bytes Integer typename class. */
    struct TypeInt2 : TypeNameClause
    {
        inline TypeInt2() : TypeNameClause("INT2") {}
    };

    /** @brief 4-Bytes Integer typename class. */
    struct TypeInt4 : TypeNameClause
    {
        inline TypeInt4() : TypeNameClause("INT4") {}
    };

    /** @brief 8-Bytes Integer typename class. */
    struct TypeInt8 : TypeNameClause
    {
        inline TypeInt8() : TypeNameClause("INT8") {}
    };

    /** @brief Tiny Integer typename class. */
    struct TypeTinyInt : TypeNameClause
    {
        inline TypeTinyInt() : TypeNameClause("TINYINT") {}
    };

    /** @brief Small Integer typename class. */
    struct TypeSmallInt : TypeNameClause
    {
        inline TypeSmallInt() : TypeNameClause("SMALLINT") {}
    };

    /** @brief Medium Integer typename class. */
    struct TypeMediumInt : TypeNameClause
    {
        inline TypeMediumInt() : TypeNameClause("MEDIUMINT") {}
    };

    /** @brief Big Integer typename class. */
    struct TypeBigInt : TypeNameClause
    {
        inline TypeBigInt() : TypeNameClause("BIGINT") {}
    };

    /** @brief Generic Unsigned Integer typename class. */
    struct TypeUnsignedInt : TypeNameClause
    {
        inline TypeUnsignedInt() : TypeNameClause("UNSIGNED INT") {}
    };

    /** @brief Generic Unsigned Integer typename class. */
    using TypeUnsignedInteger = TypeUnsignedInt;

    /** @brief 2-Bytes Unsigned Integer typename class. */
    struct TypeUnsignedInt2 : TypeNameClause
    {
        inline TypeUnsignedInt2() : TypeNameClause("UNSIGNED INT2") {}
    };

    /** @brief 4-Bytes Unsigned Integer typename class. */
    struct TypeUnsignedInt4 : TypeNameClause
    {
        inline TypeUnsignedInt4() : TypeNameClause("UNSIGNED INT4") {}
    };

    /** @brief 8-Bytes Unsigned Integer typename class. */
    struct TypeUnsignedInt8 : TypeNameClause
    {
        inline TypeUnsignedInt8() : TypeNameClause("UNSIGNED INT8") {}
    };

    /** @brief Unsigned Tiny Integer typename class. */
    struct TypeUnsignedTinyInt : TypeNameClause
    {
        inline TypeUnsignedTinyInt() : TypeNameClause("UNSIGNED TINYINT") {}
    };

    /** @brief Unsigned Small Integer typename class. */
    struct TypeUnsignedSmallInt : TypeNameClause
    {
        inline TypeUnsignedSmallInt() : TypeNameClause("UNSIGNED SMALLINT") {}
    };

    /** @brief Unsigned Medium Integer typename class. */
    struct TypeUnsignedMediumInt : TypeNameClause
    {
        inline TypeUnsignedMediumInt() : TypeNameClause("UNSIGNED MEDIUMINT") {}
    };

    /** @brief Unsigned Big Integer typename class. */
    struct TypeUnsignedBigInt : TypeNameClause
    {
        inline TypeUnsignedBigInt() : TypeNameClause("UNSIGNED BIGINT") {}
    };


    //===   TEXT AFFINITY TYPENAMES   =======================================

    /** @brief Character typename class. */
    struct TypeChar : TypeNameClause1
    {
        inline TypeChar() : TypeNameClause1("CHAR") {}  // notice: width defaults to 1
        inline TypeChar(const int32_t max_width) : TypeNameClause1("CHAR", max_width) {}
    };

    /** @brief Varying Character typename class. */
    struct TypeVaryingChar : TypeNameClause1
    {
        inline TypeVaryingChar() : TypeNameClause1("VARCHAR") {}  // notice: width defaults to 1
        inline TypeVaryingChar(const int32_t max_width) : TypeNameClause1("VARCHAR", max_width) {}
    };

    /** @brief Native Character typename class. */
    struct TypeNativeChar : TypeNameClause1
    {
        inline TypeNativeChar() : TypeNameClause1("NCHAR") {}  // notice: width defaults to 1
        inline TypeNativeChar(const int32_t max_width) : TypeNameClause1("NCHAR", max_width) {}
    };

    /** @brief Native Varying Character typename class. */
    struct TypeNativeVaryingChar : TypeNameClause1
    {
        inline TypeNativeVaryingChar() : TypeNameClause1("NVARCHAR") {}  // notice: width defaults to 1
        inline TypeNativeVaryingChar(const int32_t max_width) : TypeNameClause1("NVARCHAR", max_width) {}
    };

    /** @brief Text typename class. */
    struct TypeText : TypeNameClause
    {
        inline TypeText() : TypeNameClause("TEXT") {}
    };

    /** @brief Characters Large OBjects typename class. */
    struct TypeCLOB : TypeNameClause
    {
        inline TypeCLOB() : TypeNameClause("CLOB") {}
    };


    //===   BINARY LARGE OBJECTS AFFINITY TYPENAMES   =======================

    /** @brief Binary Large OBjects typename class. */
    struct TypeBLOB : TypeNameClause
    {
        inline TypeBLOB() : TypeNameClause("BLOB") {}
    };


    //===   REAL AFFINITY TYPENAMES   =======================================

    /** @brief Real typename class. */
    struct TypeReal : TypeNameClause
    {
        inline TypeReal() : TypeNameClause("REAL") {}
    };

    /** @brief Float typename class. */
    struct TypeFloat : TypeNameClause
    {
        inline TypeFloat() : TypeNameClause("FLOAT") {}
    };

    /** @brief Double typename class. */
    struct TypeDouble : TypeNameClause
    {
        inline TypeDouble() : TypeNameClause("DOUBLE") {}
    };


    //===   NUMERIC AFFINITY TYPENAMES   ====================================

    /** @brief Numeric typename class. */
    struct TypeNumeric : TypeNameClause
    {
        inline TypeNumeric() : TypeNameClause("NUMERIC") {}
    };

    /** @brief Decimal typename class. */
    struct TypeDecimal : TypeNameClause2
    {
        inline TypeDecimal(const int32_t overall_width, const int32_t intpart_width)
            : TypeNameClause2("DECIMAL", overall_width, intpart_width)
        { assert(overall_width > intpart_width); }
    };

    /** @brief Boolean typename class. */
    struct TypeBoolean : TypeNameClause
    {
        inline TypeBoolean() : TypeNameClause("BOOLEAN") {}
    };

    /** @brief Date typename class. */
    struct TypeDate : TypeNameClause
    {
        inline TypeDate() : TypeNameClause("DATE") {}
    };

    /** @brief DateTiume typename class. */
    struct TypeDateTime : TypeNameClause
    {
        inline TypeDateTime() : TypeNameClause("DATETIME") {}
    };

}