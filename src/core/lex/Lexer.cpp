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
#include "../Output.h"
#include <sstream>

namespace dargon {

    Lexer::Lexer()
    : _data(""), _pos(), _index(0), _len(0), _curr(EOF), _error(false)
    {}

    Lexer::~Lexer()
    {}

    void Lexer::Buffer(const std::string& data) {
        // Re-initialize all data.
        _data.clear();
        _index = 0;
        _pos = FilePosition(1,1);
        _data = data;
        _curr = _data.at(0);
        _len = _data.length();
        _error = false;
    }

    Token Lexer::Next() {
        try {
            // While we're not at the end of file
            while(!_error && _curr != EOF) {
                // Depends on character
                switch(_curr) {
                    // A new line + increment position row.
                    case '\n': case '\r': {
                        consume();
                        return Token(Token::Kind::NEWLINE, _pos);
                    }
                    // Ignore whitespace
                    case ' ': case '\t': {
                        whitespace();
                        break;
                    }
                    // Line Comment
                    case '#': {
                        consume();
                        commentLine();
                        break;
                    }
                    // Parenthesis OR block comment
                    case ')': consume(); return Token(Token::Kind::PAREN_CLOSE, _pos);
                    case '(': {
                        consume();
                        if(_curr == '#') {
                            consume();
                            commentBlock();
                            break;
                        }
                        return Token(Token::Kind::PAREN_OPEN, _pos);
                    }
                    // Assignment or equality
                    case '=': {
                        consume();
                        if(_curr == '=') {
                            consume();
                            return Token(Token::Kind::EQUALITY, _pos);
                        }
                        return Token(Token::Kind::ASSIGNMENT, _pos);
                    }
                    // Inequality
                    case '!': {
                        consume();
                        if(_curr == '=') {
                            consume();
                            return Token(Token::Kind::NEQUALITY, _pos);
                        }
                        return Token(Token::Kind::BANG, _pos);
                    }
                    // Colon
                    case ':': consume(); return Token(Token::Kind::COLON, _pos);
                    case '+': consume(); return Token(Token::Kind::PLUS, _pos);
                    case '*': consume(); return Token(Token::Kind::STAR, _pos);
                    case '/': consume(); return Token(Token::Kind::SLASH, _pos);
                    case '?': consume(); return Token(Token::Kind::EXISTS, _pos);
                    case '-': {
                        consume();
                        //if(_curr == '>') {
                            //consume();
                            // TODO
                        //}
                        return Token(Token::Kind::MINUS, _pos);
                    }
                    case '>': {
                        consume();
                        if(_curr == '=') {
                            consume();
                            return Token(Token::Kind::GTE, _pos);
                        }
                        return Token(Token::Kind::GT, _pos);
                    }
                    case '<': {
                        consume();
                        if(_curr == '=') {
                            consume();
                            return Token(Token::Kind::LTE, _pos);
                        }
                        return Token(Token::Kind::LT, _pos);
                    }
                    case '"': {
                        // Beginning of string literal
                        consume();
                        return strLit();
                    }
                    // Defualt - alphanumerics and keywords.
                    default: {
                        // Identifiers mauy start with underscore
                        if(isalpha(_curr) || _curr == '_') {
                            return identifier();
                        }
                        // Number literal
                        else if(isdigit(_curr)) {
                            return numLit();
                        }
                        // Invalid token
                        //consume();
                        throw error("Invalid token");
                        //return Token(Token::Kind::INVALID, _pos);
                    }
                };
            }
        }
        catch(LexerException* l) {
            delete l;
        }
        // Reached end-of-file
        return Token(Token::Kind::END_OF_FILE, _pos);
    }

    TokenList Lexer::GetAllTokens() {
        TokenList lst;
        Token t = Next();
        do {
            lst.push_back(t);
            t = Next();
        }
        while(!t.IsEOF());
        return lst;
    }

    LexerException* Lexer::error(const std::string& msg) {
        // TODO: Commonize 'DIR ERROR>' output between Lexer and Parser.
        std::ostringstream os;
        os << "DIR ERROR> " << msg << " at line " << _pos.line << ": " << _curr;
        out(os.str());
        DARGON_LOG_ERROR(os.str());
        _error = true;
        throw new LexerException(msg);
    }

    void Lexer::consume() {
        // Update metadata
        if(_curr == '\n' || _curr == '\r') {
            _pos.line++;
            _pos.col = 1;
        }
        else {
            _pos.col += (_curr == '\t' ? 3 : 1);
        }
        _index++;
        _curr = (_index >= _len ? EOF : _data[_index]);
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
		return Token((decimalUsed ? Token::Kind::FRACTIONAL_LIT : Token::Kind::NUMBER_LIT), buffer, _pos);
    }

    Token Lexer::strLit() {
        std::string buffer = "";
		do {
			if (_curr == EOF) {
				throw error("No end of string literal found");
			}
			buffer += _curr;
			consume();
		} while (_curr != '\'');
		consume();
		return Token(Token::Kind::STRING_LIT, buffer, _pos);
    }

    Token Lexer::identifier() {
        std::string buffer = "";
		do {
			buffer += _curr;
			consume();
		}
		while(isalpha(_curr) || isdigit(_curr) || _curr == '_');
		return Token(Token::Kind::ID, buffer, _pos);
    }

};
