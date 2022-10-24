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
#include "sqlite3.h"


export module osql.clauses;


//===========================================================================
export namespace osql::clauses
{
    //=======================================================================
    /** @brief The base class for SQL clauses as included in SQL statements. */
    template<const char PREFIX[]>
    class Clause
    {
    public:
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor. */
        inline Clause(const std::string& text) noexcept
            : _text(text)
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
        Clause& operator= (const std::string& text) noexcept
        {
            set_text(text);
            return *this;
        }

        /** @brief Unmutable std::string casting operator. */
        inline operator const std::string() const noexcept
        {
            return get_text();
        }


        //---   Operations   ------------------------------------------------
        /** @brief Gets the full text of this clause. */
        std::string& get_text() noexcept
        {
            return std::format("{:s} {:s}", PREFIX, _text);
        }

        /** @brief Sets the text associated with this clause. */
        inline void set_text(const std::string& text) noexcept
        {
            _text = text;
        }


    protected:
        //---   Attributes   ------------------------------------------------
        std::string _text{};  //!< the core text of this clause
    };

}