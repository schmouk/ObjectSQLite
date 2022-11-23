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


export module osql.databases.attached_database;

import osql.clauses;
import osql.dbconnection;


//===========================================================================
export namespace osql::databases
{
    //=======================================================================
    /** @brief The class of Attached Databases. */
    class AttachedDataBase
    {
        //---   Constructors / Destructor   ---------------------------------
        /** @brief Value constructor.
        *
        * Automatically attaches the database at construction time.
        * @param db_connection: osql::dbconnection::DBConnection
        *   A reference to the db connection to be used for attaching this database.
        * @param schema_name_: std::string
        *   The associated scheam name.
        */
        inline AttachedDataBase(osql::dbconnection::DBConnection& db_connexion,
                                const std::string&                schema_name_)
            : schema_name{ schema_name_ }
            , db_connection_ptr{ &db_connexion }
        {
            m_attach();
        }

        /** @brief Deleted empty constructor. */
        AttachedDataBase() noexcept = delete;

        /** @brief Deleted copy constructor. */
        AttachedDataBase(const AttachedDataBase&) noexcept = delete;

        /** @brief Deleted move constructor. */
        AttachedDataBase(AttachedDataBase&&) noexcept = default;

        /** @brief Destructor. */
        virtual ~AttachedDataBase()
        {
            m_detach();
        }


        //---   Operations   ------------------------------------------------
        /** Attaches this database. */
        void attach();

        //---   Attributes   ------------------------------------------------
        std::string  schema_name;
        osql::dbconnection::DBConnection*  db_connection_ptr;


    private:
        //---   Operations   ------------------------------------------------
        /* Attaches this database. */
        void m_attach();

        /* Detaches this database */
        void m_detach();
    };

}