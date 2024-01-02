/**
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * @file Lexer.cpp
 * @author Kyle Morris
 * @since v0.1
 * @section Description
 * This is the first phase of the interpreter. It takes an input
 * file and outputs a stream of Tokens, which are used in the
 * parsing phase.
 *
 */

#include "Lexer.h"
#include "../Exception.h"
#include "../IO.h"
#include <sstream>

namespace dargon {

    Lexer::Lexer()
    : _data(nullptr), _curr(EOF)
    {}

    Lexer::~Lexer()
    {}

    void Lexer::Buffer(File* file) {
        _data = file;
        _curr = _data->ReadChar();
    }

    Token Lexer::Next() {
        // While we are not at the end-of-file
        while(_curr != EOF) {
            // Depends on character
            switch(_curr) {
                // A new line
                case '\n':
                case '\r':
                    consume();
                    return Token(Token::Kind::NEWLINE, _data->CurrentPosition());
                // Ignore whitespace
                case ' ':
                case '\t':
                    whitespace();
                    break;
                // Line Comment
                case '#':
                    consume();
                    commentLine();
                    break;
                // Parenthesis OR block comment
                case ')':
                    consume();
                    return Token(Token::Kind::PAREN_CLOSE, _data->CurrentPosition());
                case '(':
                    consume();
                    if(_curr == '#') {
                        consume();
                        commentBlock();
                        break;
                    }
                    return Token(Token::Kind::PAREN_OPEN, _data->CurrentPosition());
                // Assignment or equality
                case '=':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::EQUALITY, _data->CurrentPosition());
                    }
                    return Token(Token::Kind::ASSIGNMENT, _data->CurrentPosition());
                // Inequality or negation
                case '!':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::NEQUALITY, _data->CurrentPosition());
                    }
                    return Token(Token::Kind::BANG, _data->CurrentPosition());
                // > or >=
                case '>':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::GTE, _data->CurrentPosition());
                    }
                    return Token(Token::Kind::GT, _data->CurrentPosition());
                // < or <=
                case '<':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::LTE, _data->CurrentPosition());
                    }
                    return Token(Token::Kind::LT, _data->CurrentPosition());
                // Beginning of string literal
                case '"':
                    consume();
                    return strLit();
                // Single-character tokens
                case ':': consume(); return Token(Token::Kind::COLON, _data->CurrentPosition());
                case '+': consume(); return Token(Token::Kind::PLUS, _data->CurrentPosition());
                case '*': consume(); return Token(Token::Kind::STAR, _data->CurrentPosition());
                case '/': consume(); return Token(Token::Kind::SLASH, _data->CurrentPosition());
                case '?': consume(); return Token(Token::Kind::EXISTS, _data->CurrentPosition());
                case '-': consume(); return Token(Token::Kind::MINUS, _data->CurrentPosition());
                // Defualt - alphanumerics and keywords.
                default:
                    // Identifiers may start with underscore
                    if(isalpha(_curr) || _curr == '_') {
                        return identifier();
                    }
                    // Number literal
                    else if(isdigit(_curr)) {
                        return numLit();
                    }
                    // Invalid token
                    consume();
                    return Token(Token::Kind::INVALID, _data->CurrentPosition());
            };
        }
        // We have reached end-of-file
        return Token(Token::Kind::END_OF_FILE, _data->CurrentPosition());
    }

    Error Lexer::Work() {
        // This is the return value
        Error e;
        // Run through it all
        Token t = Next();
        do {
            _output.push_back(t);
            t = Next();
        }
        while(t.IsValid() && !t.IsEOF());
        // If there was an invalid token, error
        if(!t.IsValid()) {
            e.code = ECode::INVALID_TOKEN;
            std::ostringstream os;
            os << "Invalid token: " << t.ToString();
            e.msg = os.str();
            // Set the file position too
            e.where = t.GetPosition();
            return e;
        }
        return e;
    }

    void Lexer::consume() {
        // Moving right is how we go through the file
        if(_data->MoveRight()) {
            _curr = _data->ReadChar();
        }
        else {
            _curr = EOF;
        }
    }

    void Lexer::whitespace() {
        do {
            consume();
        }
        while(_curr == ' ' || _curr == '\t');
    }

    void Lexer::commentLine() {
        while(_curr != '\n' && _curr != EOF) {
			consume();
		}
    }

    void Lexer::commentBlock() {
        // Look for the pair '#)' to terminate the block comment
        while(_curr != EOF) {
            while(_curr != '#' && _curr != EOF) { consume(); }
            consume(); // Consume the '#'
            if(_curr == ')') {
                consume(); // Consume the ')'
                break;
            }
        }
    }

    Token Lexer::numLit() {
        bool decimalUsed = false;
		std::string buffer = "";
		do {
			if (_curr == '.' && !decimalUsed) {
				decimalUsed = true;
			}
			buffer += _curr;
			consume();
		} while (isdigit(_curr) || (_curr == '.' && !decimalUsed));
		return Token((decimalUsed ? Token::Kind::FRACTIONAL_LIT : Token::Kind::NUMBER_LIT), buffer, _data->CurrentPosition());
    }

    Token Lexer::strLit() {
        std::string buffer = "";
		do {
			if (_curr == EOF) {
				//throw error("No end of string literal found");
			}
			buffer += _curr;
			consume();
		} while (_curr != '\'');
		consume();
		return Token(Token::Kind::STRING_LIT, buffer, _data->CurrentPosition());
    }

    Token Lexer::identifier() {
        std::string buffer = "";
		do {
			buffer += _curr;
			consume();
		}
		while(isalpha(_curr) || isdigit(_curr) || _curr == '_');
		return Token(Token::Kind::ID, buffer, _data->CurrentPosition());
    }

};
