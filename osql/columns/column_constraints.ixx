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

#include "osql/clauses/clause.h"


export module osql.columns.column_constraints;

import osql.clauses;
import osql.clauses.conflict_clauses;
import osql.clauses.foreign_key_clauses;



//===========================================================================
export namespace osql::columns
{
    //
    // Notice: these constraints are used with columns definitions.
    //

    //=======================================================================
    /** @brief The specific type traits for Column Constraints. */
    template<typename T>
    struct is_column_constraint {
        static inline constexpr bool value = true;
    };

    /** @brief Wrapper to the type traits value for Column Constraints. */
    template<typename T>
    inline constexpr bool is_column_constraint_v() {
        return is_column_constraint<T>::value;
    }

    /** @brief Type traits specialization for external FOREIGN KEY clause. */
    template<>
    struct is_column_constraint<osql::clauses::ForeignKeyClause> {
        static inline constexpr bool value = true;
    };


    //===   AS   ============================================================
    /** @brief the STR value for clause AS. */
    using AsStr = osql::clauses::STR<'A', 'S', 0>;

    /** @brief The class of As Clauses as included in columns definitions. */
    class AsClause : public osql::clauses::Clause< AsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< AsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        AsClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s})", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses AS. */
    template<>
    struct is_column_constraint<AsClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of As Clauses with suffix STORED as included in columns definitions. */
    class AsStoredClause : public osql::clauses::Clause< AsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< AsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        AsStoredClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s}) STORED", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses AS stored. */
    template<>
    struct is_column_constraint<AsStoredClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of As Clauses with suffix VIRTUAL as included in columns definitions. */
    class AsVirtualClause : public osql::clauses::Clause< AsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< AsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        AsVirtualClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s}) VIRTUAL", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses AS virtual. */
    template<>
    struct is_column_constraint<AsVirtualClause> {
        static inline constexpr bool value = true;
    };


    //===   CHECK   =========================================================
    /** @brief the STR value for clause CHECK. */
    using CheckStr = osql::clauses::STR<'C', 'H', 'E', 'C', 'K', 0>;

    /** @brief The class of Check Clauses as included in columns definitions. */
    class CheckClause : public osql::clauses::Clause< CheckStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< CheckStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        CheckClause(const std::string& check_expr) noexcept
            : MyBaseClass(std::format("({:s})", check_expr))
        {}
    };

    /** @brief Type traits specialization for clauses CHECK. */
    template<>
    struct is_column_constraint<CheckClause> {
        static inline constexpr bool value = true;
    };


    //===   DEFAULT   =======================================================
    /** @brief the STR value for clause DEFAULT. */
    using DefaultStr = osql::clauses::STR<'D', 'E', 'F', 'A', 'U', 'L', 'T', 0>;

    /** @brief The class of Default Clauses as included in columns definitions. */
    class DefaultClause : public osql::clauses::Clause< DefaultStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< DefaultStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        DefaultClause(const std::string& value) noexcept
            : MyBaseClass(value)
        {}

        DefaultClause() noexcept = delete;  //!< deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses DEFAULT. */
    template<>
    struct is_column_constraint<DefaultClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of Default Clauses with an expression as included in columns definitions. */
    class DefaultExprClause : public osql::clauses::Clause< DefaultStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< DefaultStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        DefaultExprClause(const std::string& default_expr) noexcept
            : MyBaseClass(std::format("({:s})", default_expr))
        {}

        DefaultExprClause() noexcept = delete;  //!< deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses DEFAULT with expressions. */
    template<>
    struct is_column_constraint<DefaultExprClause> {
        static inline constexpr bool value = true;
    };


    //===   GENERATED ALWAYS AS   ===========================================
    /** @brief the STR value for clause GENERATED ALWAYS AS. */
    using GeneratedAsStr = osql::clauses::STR<'G', 'E', 'N', 'E', 'R', 'A', 'T', 'E', 'D', ' ', 'A', 'L', 'W', 'A', 'Y', 'S', ' ', 'A', 'S', 0>;

    /** @brief The class of Generated Always As Clauses as included in columns definitions. */
    class GeneratedAsClause : public osql::clauses::Clause< GeneratedAsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< GeneratedAsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        GeneratedAsClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s})", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses Generated Always As. */
    template<>
    struct is_column_constraint<GeneratedAsClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of Generated Always As Clauses with suffix STORED as included in columns definitions. */
    class GeneratedAsStoredClause : public osql::clauses::Clause< GeneratedAsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< GeneratedAsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        GeneratedAsStoredClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s}) STORED", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses Generated Always As stored. */
    template<>
    struct is_column_constraint<GeneratedAsStoredClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of Generated Always As Clauses with suffix VIRTUAL as included in columns definitions. */
    class GeneratedAsVirtualClause : public osql::clauses::Clause< GeneratedAsStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< GeneratedAsStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        GeneratedAsVirtualClause(const std::string& as_expr) noexcept
            : MyBaseClass(std::format("({:s}) VIRTUAL", as_expr))
        {}
    };

    /** @brief Type traits specialization for clauses Generated Always As virtual. */
    template<>
    struct is_column_constraint<GeneratedAsVirtualClause> {
        static inline constexpr bool value = true;
    };


    //===   NOT NULL   ======================================================
    /** @brief the STR value for clause NOT NULL. */
    using NotNullStr = osql::clauses::STR<'N', 'O', 'T', ' ', 'N', 'U', 'L', 'L', 0>;

    /** @brief The class of Not Null Clauses as included in columns definitions. */
    class NotNullClause : public osql::clauses::Clause< NotNullStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< NotNullStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename PrefixT, typename SuffixT>
        NotNullClause(const osql::clauses::ConflictBaseClause<PrefixT, SuffixT>& conflict_clause) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause))
        {}

        NotNullClause() noexcept = delete;  //!< Deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses Not Null. */
    template<>
    struct is_column_constraint<NotNullClause> {
        static inline constexpr bool value = true;
    };


    //===   PRIMARY KEY   ===================================================
    /** @brief the STR value for clause PRIMARY KEY. */
    using PrimaryKeyStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', 0 >;

    /** @brief the STR value for PRIMARY KEY ASC. */
    using PrimaryKeyAscStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y',' ', 'A', 'S', 'C', 0 >;

    /** @brief the STR value for PRIMARY KEY DESC. */
    using PrimaryKeyDescStr = osql::clauses::STR< 'P', 'R', 'I', 'M', 'A', 'R', 'Y', ' ', 'K', 'E', 'Y', ' ', 'D', 'E', 'S', 'C', 0 >;


    /** @brief The class of Primary Key Clauses as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    class PrimaryKeyClause : public osql::clauses::Clause< PrimaryKeyStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations
        *   about the use of AUTOINCREMENT on INTEGER PRIMARY KEYS and 
        *   why it should be avoided as often as possible.
        */
        template<typename PrefixT, typename SuffixT>
        PrimaryKeyClause(const osql::clauses::ConflictBaseClause<PrefixT, SuffixT>& conflict_clause,
                         const bool                                                 auto_incr = false) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause) + (auto_incr ? " AUTOINCREMENT" : ""))
        {}

        PrimaryKeyClause() noexcept = delete;  //!< Deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses Primary Key. */
    template<>
    struct is_column_constraint<PrimaryKeyClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of Primary Key Clauses with specifier ASC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    class PrimaryKeyAscClause : public osql::clauses::Clause< PrimaryKeyAscStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyAscStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations
        *   about the use of AUTOINCREMENT on INTEGER PRIMARY KEYS and 
        *   why it should be avoided as often as possible.
        */
        template<typename PrefixT, typename SuffixT>
        PrimaryKeyAscClause(const osql::clauses::ConflictBaseClause<PrefixT, SuffixT>& conflict_clause,
                            const bool                                                 auto_incr) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause) + (auto_incr ? " AUTOINCREMENT" : ""))
        {}

        PrimaryKeyAscClause() noexcept = delete;  //!< Deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses Primary Key ASC. */
    template<>
    struct is_column_constraint<PrimaryKeyAscClause> {
        static inline constexpr bool value = true;
    };


    /** @brief The class of Primary Key Clauses with specifier DESC as included in columns definitions.
    *
    * CAUTION: Primary Key clauses for columns definitions are not  the  same
    *          as Primary Key clauses for tables definitions.  Always use the
    *          the namespace as a prefix when instantiating PrimaryKeyClause.
    */
    class PrimaryKeyDescClause : public osql::clauses::Clause< PrimaryKeyDescStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< PrimaryKeyDescStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * @see https://www.sqlite.org/autoinc.html to get explanations
        *   about the use of AUTOINCREMENT on INTEGER PRIMARY KEYS and 
        *   why it should be avoided as often as possible.
        */
        template<typename PrefixT, typename SuffixT>
        PrimaryKeyDescClause(const osql::clauses::ConflictBaseClause<PrefixT, SuffixT>& conflict_clause,
                             const bool                                                 auto_incr) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause) + (auto_incr ? " AUTOINCREMENT" : ""))
        {}

        PrimaryKeyDescClause() noexcept = delete;  //!< Deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses Primary Key DESC. */
    template<>
    struct is_column_constraint<PrimaryKeyDescClause> {
        static inline constexpr bool value = true;
    };


    //===   UNIQUE   ========================================================
    /** @brief the STR value for clause UNIQUE. */
    using UniqueStr = osql::clauses::STR<'U', 'N', 'I', 'Q', 'U', 'E', 0>;

    /** @brief The class of Unique Clauses as included in columns definitions. */
    class UniqueClause : public osql::clauses::Clause< UniqueStr >
    {
    public:
        //---   Wrappers   --------------------------------------------------
        using MyBaseClass = osql::clauses::Clause< UniqueStr >;  //!< wrapper to the base class

        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        template<typename PrefixT, typename SuffixT>
        UniqueClause(const osql::clauses::ConflictBaseClause<PrefixT, SuffixT>& conflict_clause) noexcept
            : MyBaseClass(osql::clauses::T(conflict_clause))
        {}

        UniqueClause() noexcept = delete;  //!< Deleted empty constructor.
    };

    /** @brief Type traits specialization for clauses Unique. */
    template<>
    struct is_column_constraint<UniqueClause> {
        static inline constexpr bool value = true;
    };

}