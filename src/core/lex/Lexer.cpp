/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Lexer.cpp
 *
 * DESCRIPTION: Implementation of Lexer.
 *
 * SINCE: v0.1
 *
 */

#include "Lexer.h"
#include "../Exception.h"

namespace dargon {

    Lexer::Lexer()
    : _input(""), _inputLen(0), _index(0), _char(EOF), _pos(1,1)
    {}

	void Lexer::Input(const std::string& data) {
		_input.clear();
		_index = 0;
		_pos.line = 1;
		_pos.col = 1;
		_input = data;
		_char = _input.at(_index);
		_inputLen = _input.length();
	}

	Token Lexer::GetNextToken() {
        // Given the current character, produce a token.
        while(_char != EOF) {
            switch(_char) {
                case '\n': case '\r': { // Increment line number & ignore
                    _consume();
                    break;
                }
                case ' ': { // Ignore whitespace
                    _whitespace();
                    break;
                }
                case '\t': {  // Ignore whitespace
                    _whitespace();
                    break;
                }
                case '#': { // All types of comments live here
                    _consume();
                    if(_char != EOF) {
                        if(_char == '#') { // Block comment
                            _consume();
                            _blockComment();
                        }
                        else if(_char == '>') { // Conditional comment
                            // TODO
                        }
                        else { // Line comment
                            _lineComment();
                        }
                    }
                    break;
                }
                case ',': _consume(); return Token(TokenType::COMMA, ",", _pos);
                case ';': _consume(); return Token(TokenType::STMT_END, ";", _pos);
                case '(': _consume(); return Token(TokenType::LPAREN, "(", _pos);
                case ')': _consume(); return Token(TokenType::RPAREN, ")", _pos);
                case '{': _consume(); return Token(TokenType::LBLOCK, "[", _pos);
                case '}': _consume(); return Token(TokenType::RBLOCK, "]", _pos);
                case '[': _consume(); return Token(TokenType::LBRACK, "{", _pos);
                case ']': _consume(); return Token(TokenType::RBRACK, "}", _pos);
                case '+': _consume(); return Token(TokenType::OP_PLUS, "+", _pos);
                case '*': _consume(); return Token(TokenType::OP_MULT, "*", _pos);
                case '/': _consume(); return Token(TokenType::OP_DIV, "/", _pos);
                case '\'': _consume(); return _strLit();
                case '-': {
                    _consume();
                    if(_char == '>') {
                        _consume();
                        return Token(TokenType::FLOW_R, "->", _pos);
                    }
                    return Token(TokenType::OP_MINUS, "-", _pos);
                }
                case '=': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::OP_EQ, "==",_pos);
                    }
                    return Token(TokenType::OP_EQ, "=", _pos);
                }
                case '~': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::OP_NEQ, "~=", _pos);
                    }
                    return Token(TokenType::TILDE, "~", _pos);
                }
                case '>': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::GTE, ">=", _pos);
                    }
                    return Token(TokenType::GT, ">", _pos);
                }
                case '<': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::LTE, "<=", _pos);
                    }
                    else if(_char == '-') {
                        _consume();
                        return Token(TokenType::FLOW_L, "<-", _pos);
                    }
                    return Token(TokenType::LT, "<", _pos);
                }
                case '.': {
                    _consume();
                    if(_char == '.') {
                        _consume();
                        return Token(TokenType::RANGE, "..", _pos);
                    }
                    return Token(TokenType::PERIOD, ".", _pos);
                }
                // Anything else must be an identifier/keyword
                default: {
                    // Identifier
                    if(isalpha(_char) || _char == '_') {
                        return _identifier();
                    }
                    // Number literal
                    else if(isdigit(_char)) {
                        return _numLit();
                    }
                    return Token();
                }
            };
        }
        return Token(TokenType::EOF_TYPE, "EOF");
	}

	void Lexer::_consume() {
        // Update metadata
        if(_char == '\n' || _char == '\r') {
            _pos.line++;
            _pos.col = 1;
        }
        else {
            _pos.col += (_char == '\t' ? 3 : 1);
        }
        _index++;
        _char = (_index >= _inputLen ? EOF : _input[_index]);
    }

    void Lexer::_whitespace() {
        do {
            _consume();
        }
        while(_char == ' ' || _char == '\t');
    }

    void Lexer::_lineComment() {
        while(_char != '\n' && _char != EOF) {
			_consume();
		}
    }

    void Lexer::_blockComment() {
        while(_char != '#' && _char != EOF) {
			_consume();
		}
		if(_char != EOF) {
			// Should be '##' syntax
			_consume();
			_consume();
		}
    }

    Token Lexer::_numLit() {
        bool decimalUsed = false;
		std::string buffer = "";
		do {
			if (_char == '.' && !decimalUsed) {
				decimalUsed = true;
			}
			buffer += _char;
			_consume();
		} while (isdigit(_char) || (_char == '.' && !decimalUsed));
		return Token((decimalUsed ? TokenType::REAL_LITERAL : TokenType::INT_LITERAL), buffer, _pos);
    }

    Token Lexer::_strLit() {
        std::string buffer = "";
		do {
			if (_char == EOF) {
				// TODO: New exception type that includes file position information.
				throw new Exception("NO END OF STRING LITERAL FOUND");
			}
			buffer += _char;
			_consume();
		} while (_char != '\'');
		_consume();
		return Token(TokenType::STR_LITERAL, buffer, _pos);
    }

    Token Lexer::_identifier() {
        std::string buffer = "";
		do {
			buffer += _char;
			_consume();
		}
		while(isalpha(_char) || isdigit(_char) || _char == '_' || _char == '?');
		TokenType t = IsKeyword(buffer);
		if(t != TokenType::INVALID) {
			return Token(t, "$" + buffer, _pos);
		}
		return Token(TokenType::IDENTIFIER, buffer, _pos);
    }

};
