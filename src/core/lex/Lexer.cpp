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

namespace dargon {

    Lexer::Lexer()
    : _data(""), _pos(), _index(0), _len(0), _curr(EOF)
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
    }

    Token Lexer::Next() {
        // While we're not at the end of file
        while(_curr != EOF) {
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
                // Either line comment or block comment
                case '#': {
                    consume();
                    if(_curr == '#') {
                        consume();
                        commentBlock();
                    }
                    else {
                        commentLine();
                    }
                    break;
                }
                // Colon
                case ':': consume(); return Token(Token::Kind::COLON, _pos);
                // Assignment
                case '=': consume(); return Token(Token::Kind::ASSIGNMENT, _pos);
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
                    consume();
                    return Token(Token::Kind::INVALID, _pos);
                }
            };
        }
        // Reached end-of-file
        return Token(Token::Kind::END_OF_FILE, _pos);
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
        // Look for the next '##" pair.
        // TODO More sophistication here.
        while(_curr != '#' && _curr != EOF) {
			consume();
		}
		if(_curr != EOF) {
			// Should be '##' syntax
			consume(); consume();
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
				// TODO: New exception type that includes file position information.
				throw new LexerException("NO END OF STRING LITERAL FOUND");
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

//
//	Token Lexer::GetNextToken() {
//        // Given the current character, produce a token.
//        while(_char != EOF) {
//            switch(_char) {
//                case '\n': case '\r': { // Increment line number & ignore
//                    _consume();
//                    break;
//                }
//                case ' ': { // Ignore whitespace
//                    _whitespace();
//                    break;
//                }
//                case '\t': {  // Ignore whitespace
//                    _whitespace();
//                    break;
//                }
//                case '#': { // All types of comments live here
//                    _consume();
//                    if(_char != EOF) {
//                        if(_char == '#') { // Block comment
//                            _consume();
//                            _blockComment();
//                        }
//                        else if(_char == '>') { // Conditional comment
//                            // TODO
//                        }
//                        else { // Line comment
//                            _lineComment();
//                        }
//                    }
//                    break;
//                }
//                case ',': _consume(); return Token(TokenType::COMMA, ",", _pos);
//                case ';': _consume(); return Token(TokenType::STMT_END, ";", _pos);
//                case '(': _consume(); return Token(TokenType::LPAREN, "(", _pos);
//                case ')': _consume(); return Token(TokenType::RPAREN, ")", _pos);
//                case '{': _consume(); return Token(TokenType::LBLOCK, "[", _pos);
//                case '}': _consume(); return Token(TokenType::RBLOCK, "]", _pos);
//                case '[': _consume(); return Token(TokenType::LBRACK, "{", _pos);
//                case ']': _consume(); return Token(TokenType::RBRACK, "}", _pos);
//                case '+': _consume(); return Token(TokenType::OP_PLUS, "+", _pos);
//                case '*': _consume(); return Token(TokenType::OP_MULT, "*", _pos);
//                case '/': _consume(); return Token(TokenType::OP_DIV, "/", _pos);
//                case '\'': _consume(); return _strLit();
//                case '-': {
//                    _consume();
//                    if(_char == '>') {
//                        _consume();
//                        return Token(TokenType::FLOW_R, "->", _pos);
//                    }
//                    return Token(TokenType::OP_MINUS, "-", _pos);
//                }
//                case '=': {
//                    _consume();
//                    if(_char == '=') {
//                        _consume();
//                        return Token(TokenType::OP_EQ, "==",_pos);
//                    }
//                    return Token(TokenType::OP_EQ, "=", _pos);
//                }
//                case '~': {
//                    _consume();
//                    if(_char == '=') {
//                        _consume();
//                        return Token(TokenType::OP_NEQ, "~=", _pos);
//                    }
//                    return Token(TokenType::TILDE, "~", _pos);
//                }
//                case '>': {
//                    _consume();
//                    if(_char == '=') {
//                        _consume();
//                        return Token(TokenType::GTE, ">=", _pos);
//                    }
//                    return Token(TokenType::GT, ">", _pos);
//                }
//                case '<': {
//                    _consume();
//                    if(_char == '=') {
//                        _consume();
//                        return Token(TokenType::LTE, "<=", _pos);
//                    }
//                    else if(_char == '-') {
//                        _consume();
//                        return Token(TokenType::FLOW_L, "<-", _pos);
//                    }
//                    return Token(TokenType::LT, "<", _pos);
//                }
//                case '.': {
//                    _consume();
//                    if(_char == '.') {
//                        _consume();
//                        return Token(TokenType::RANGE, "..", _pos);
//                    }
//                    return Token(TokenType::PERIOD, ".", _pos);
//                }
//                // Anything else must be an identifier/keyword
//                default: {
//                    // Identifier
//                    if(isalpha(_char) || _char == '_') {
//                        return _identifier();
//                    }
//                    // Number literal
//                    else if(isdigit(_char)) {
//                        return _numLit();
//                    }
//                    return Token();
//                }
//            };
//        }
//        return Token(TokenType::EOF_TYPE, "EOF");
//	}
//


};
