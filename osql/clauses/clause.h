#pragma once
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
#include <format>
#include <sstream>
#include <string>


//===========================================================================
namespace osql::clauses
{
    //=======================================================================
    /** @brief Returns a string set with a single char. */
    template<char C>
    [[nodiscard]] constexpr std::string STRCHAR() noexcept
    {
        return std::string(1, C);
    };


    /** @brief Returns a string set from a sequence of chars. */
    template<char C, char... Cs>
    struct STR
    {
        static std::string get_text()
        {
            return (STRCHAR<C>() + STR<Cs...>::get_text());
        }
    };

    /** @brief Specialization of STR with null char. */
    template<>
    struct STR<'\0'>
    {
        static std::string get_text()
        {
            return "";
        }
    };


    //=======================================================================
    /** @brief The base class for SQL clauses as included in SQL statements. */
    template<typename PREFIX, typename SUFFIX = STR<'\0'>>
    class Clause
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline Clause(const std::string& core_text) noexcept
            : _text(core_text)
        {}

        /** @brief Default empty constructor. */
        Clause() noexcept = default;

        /** @brief Default copy constructor. */
        Clause(const Clause&) noexcept = default;

        /** @brief Default move constructor. */
        Clause(Clause&&) noexcept = default;

        /** @brief Destructor. */
        inline virtual ~Clause() = default;


        //---   Operators   -------------------------------------------------
        /** @brief Default copy assignment. */
        Clause& operator= (const Clause&) noexcept = default;

        /** @brief Default move assignment. */
        Clause& operator= (Clause&&) noexcept = default;

        /** @brief Text assignment. */
        inline Clause& operator= (const std::string& core_text) noexcept
        {
            set_text(core_text);
            return *this;
        }

        /** @brief Unmutable std::string casting operator. */
        inline operator const std::string() const noexcept
        {
            return get_text();
        }


        //---   Operations   ------------------------------------------------
        /** @brief Gets the full text of this clause. */
        const std::string get_text() const noexcept;

        /** @brief Sets the text associated with this clause. */
        inline void set_text(const std::string& core_text) noexcept
        {
            _text = core_text;
        }


    protected:
        //---   Attributes   ------------------------------------------------
        std::string _text{};  //!< the core text of this clause

    
    private:
        static inline std::string m_prefix = PREFIX::get_text();
        static inline std::string m_suffix = SUFFIX::get_text();
    };


    //===   TEMPLATES IMPLEMENTATIONS   =====================================
    /* Gets the full text of this clause. */
    template<typename PREFIX, typename SUFFIX>
    const std::string Clause<PREFIX, SUFFIX>::get_text() const noexcept
    {
        std::ostringstream os;

        if (m_prefix != "")
            os << m_prefix << ' ';
        os << _text;
        if (m_suffix != "")
            os << ' ' << m_suffix;

        return os.str();
    }

}