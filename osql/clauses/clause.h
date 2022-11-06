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
#include <sstream>
#include <string>


//===========================================================================
namespace osql::clauses
{
    /** @brief Returns a string set with a single char. */
    template<char C>
    [[nodiscard]] constexpr std::string STRCHAR() noexcept
    {
        return std::string(1, C);
    };


    /** @brief Templatization of a sequence of chars as a string. */
    template<char C, char... Cs>
    struct STR
    {
        [[nodiscard]] static std::string get_text()
        {
            return (STRCHAR<C>() + STR<Cs...>::get_text());
        }
    };


    /** @brief Specialization of STR with sole null char. */
    template<>
    struct STR<'\0'>
    {
        [[nodiscard]] static std::string get_text()
        {
            return "";
        }
    };

}


/** @brief Evaluates the text associated with an osql clause. */
template<typename ClauseT>
[[nodiscard]] inline std::string T(const ClauseT& clause) noexcept
{
    return clause.get_text();
}
