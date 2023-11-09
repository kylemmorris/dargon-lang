/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Token.h
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * A 'token' is what the source program is converted into by the lexer, and
 * it can represent any number of characters in a sequence (identifiers, keywords, etc.).
 *
 */

#ifndef DARGON_TOKEN_H
#define DARGON_TOKEN_H

#include <map>
#include "../Exception.h"
#include "../FilePosition.h"

namespace dargon {

    /// @brief A lexical token.
    /// @author Kyle Morris
    /// @since v0.1
    class Token final {
    public:
        /// @brief The kind of token.
        enum class Kind {
            END_OF_FILE = 0,    ///< End-of-File (EOF)
            INVALID,            ///< An invalid token
            NEWLINE,            ///< The newline character
            ID,                 ///< Identifier
            __KEYWORDS__,       ///< Anything past this line is a keyword
            CONST_MUT,          ///< Constant mutability (const)
            VAR_MUT,            ///< Variable mutability (var)
            __OPERATORS__,      ///< Anything past this is an operator
            ASSIGNMENT,         ///< Assignment (=)
            __LITERALS__,       ///< Anything past this is a literal
            NUMBER_LIT,         ///< Numeric literal
            FRACTIONAL_LIT,     ///< Numeric literal with decimal point
            BOOL_T_LIT,         ///< The boolean literal 'true'
            BOOL_F_LIT,         ///< The boolean literal 'false'
            STRING_LIT          ///< String literal "blablabla"
        };

        /// @brief The general constructor.
        Token(const Kind& kind = Kind::INVALID, const FilePosition& pos);

        /// @brief Constructor for tokens that contain values.
        /// This is reserved for literals and identifiers.
        Token(const Kind& kind, const std::string& value, const FilePosition& pos);

        /// @brief Returns if this token is valid or not.
        /// An invalid token is defined as either INVALID or EOF.
        bool Valid() const;

        /// @brief Returns the string representation of this token.
        std::string ToString() const;

        /// @brief Static function for returning a type's string representation.
        static std::string GetKindName(const Kind& type);
    private:

        /// @brief The map of keywords.
        static const std::map<std::string, Kind> _keywords = {
            {"const", Kind::CONST_MUT},
            {"var", Kind::VAR_MUT}
        };

        Kind _type;                 ///< Token's type
        std::string _value;         ///< Token's value, if any
        FilePosition _location;     ///< Location of the token in the file
    };

};

#endif
