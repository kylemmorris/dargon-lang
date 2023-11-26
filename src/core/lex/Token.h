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

#ifndef DARGON_HEADER_TOKEN
#define DARGON_HEADER_TOKEN

#include <map>
#include <vector>
#include "../Exception.h"
#include "../FilePosition.h"

namespace dargon {

    /// @brief A lexical token.
    /// @author Kyle Morris
    /// @since v0.1
    class Token {
    public:
        /// @brief The kind of token.
        enum class Kind {
            END_OF_FILE = 0,    ///< End-of-File (EOF)
            INVALID,            ///< An invalid token
            __CONSTRUCTS__,     ///< Constructs that the language uses
            NEWLINE,            ///< The newline character
            ID,                 ///< Identifier
            COLON,              ///< Colon (:)
            PAREN_OPEN,         ///< Open Parenthesis (
            PAREN_CLOSE,        ///< Close Paranthesis )
            __OPERATORS__,      ///< Anything past this is an operator
            ASSIGNMENT,         ///< Assignment (=)
            EQUALITY,           ///< Equality (==)
            NEQUALITY,          ///< Negated Equality (!=)
            LT, GT,             ///< Comparisons < and >
            LTE, GTE,           ///< Comparisons <= and >=
            MINUS,              ///< Plus (+)
            PLUS,               ///< Minus (-)
            SLASH,              ///< Division (/)
            STAR,               ///< Multiplication (*)
            BANG,               ///< Negation
            EXISTS,             ///< Existence
            __KEYWORDS__,       ///< Anything past this line is a keyword
            CONST_MUT,          ///< Constant mutability (const)
            VAR_MUT,            ///< Variable mutability (var)
            FUN_DECL,           ///< Function declaration (fun)
            TYPE_DECL,          ///< Type declaration (type)
            IF, ELIF, ELSE,     ///< if, elif, and else
            WHEN,               ///< Pattern matching 'when'
            LOOP,               ///< Loop construct 'loop'
            __LITERALS__,       ///< Anything past this is a literal
            NUMBER_LIT,         ///< Numeric literal
            FRACTIONAL_LIT,     ///< Numeric literal with decimal point
            BOOL_T_LIT,         ///< The boolean literal 'true'
            BOOL_F_LIT,         ///< The boolean literal 'false'
            STRING_LIT          ///< String literal "blablabla"
        };

        /// @brief The invalid token constructor.
        Token();

        /// @brief The general constructor. This will auto-populate
        /// the value of operators.
        Token(const Kind& kind = Kind::INVALID, const FilePosition& pos = FilePosition());

        /// @brief Constructor for tokens that contain values.
        /// This is reserved for literals and identifiers.
        Token(const Kind& kind, const std::string& value, const FilePosition& pos);

        /// @brief Returns the token type.
        Kind GetKind() const { return _type; }

        /// @brief Returns the token's value, if any.
        std::string GetValue() const { return _value; }

        /// @brief Returns the token's file position.
        FilePosition GetPosition() const { return _location; }

        /// @brief Returns if this token is valid or not.
        /// An invalid token is defined as either INVALID or EOF.
        bool IsValid() const;

        /// @brief Returns if this token is the EOF token.
        bool IsEOF() const;

        /// @brief Returns the string representation of this token.
        std::string ToString() const;

        /// @brief Static function for returning a type's string representation.
        static std::string GetKindName(const Kind& type);
    private:
        Kind _type;                 ///< Token's type
        std::string _value;         ///< Token's value, if any
        FilePosition _location;     ///< Location of the token in the file
    };

    /// @brief A Token vector.
    typedef std::vector<Token> TokenList;

    /// @brief The map of keywords.
    static const std::map<std::string, Token::Kind> Keywords = {
        {"const", Token::Kind::CONST_MUT},
        {"var", Token::Kind::VAR_MUT}
    };

};

#endif
