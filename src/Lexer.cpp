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

#include "../include/Lexer.h"

namespace dargon {

    Lexer::Lexer()
    : _input(""), _inputLen(0), _index(0), _lineNum(0), _char(EOF)
    {}

	void Lexer::Input(const std::string& data) {
		_input.clear();
		_index = 0;
		_lineNum = 1;
		_input = data;
		_char = _input.at(_index);
		_inputLen = _input.length();
		InfoLog("Lexer initialized.");
	}

	Token Lexer::GetNextToken() {
        // Given the current character, produce a token.
        while(_char != EOF) {
            switch(_char) {
                case '\n': case '\r': { // Increment line number
                    _lineNum++;
                    _consume();
                    break;
                }
                case ' ': case '\t': {  // Ignore whitespace
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
                case ',': _consume(); return Token(TokenType::COMMA);
                case ';': _consume(); return Token(TokenType::STMT_END);
                case '(': _consume();return Token(TokenType::LPAREN);
                case ')': _consume(); return Token(TokenType::RPAREN);
                case '{': _consume(); return Token(TokenType::LBLOCK);
                case '}': _consume(); return Token(TokenType::RBLOCK);
                case '[': _consume(); return Token(TokenType::LBRACK);
                case ']': _consume(); return Token(TokenType::RBRACK);
                case '+': _consume(); return Token(TokenType::OP_PLUS);
                case '-': _consume(); return Token(TokenType::OP_MINUS);
                case '*': _consume(); return Token(TokenType::OP_MULT);
                case '=': _consume(); return Token(TokenType::OP_EQ);
                case '\'': _consume(); return _strLit();
                case '>': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::GTE);
                    }
                    return Token(TokenType::GT);
                }
                case '<': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::LTE);
                    }
                    return Token(TokenType::LT);
                }
                case ':': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::ASSIGN);
                    }
                    return Token(TokenType::INVALID);
                }
                case '.': {
                    _consume();
                    if(_char == '.') {
                        _consume();
                        return Token(TokenType::RANGE);
                    }
                    return Token(TokenType::PERIOD);
                }
                case '/': {
                    _consume();
                    if(_char == '=') {
                        _consume();
                        return Token(TokenType::OP_NEQ);
                    }
                    return Token(TokenType::OP_DIV);
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
                    return Token(TokenType::INVALID);
                }
            };
        }
        return Token(TokenType::EOF_TYPE);
	}

	void Lexer::_consume() {
        _index++;
        _char = (_index >= _inputLen ? EOF : _input[_index]);
    }

    void Lexer::_whitespace() {
        while(_char == ' ' || _char == '\t') {
            _consume();
        }
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
		return Token((decimalUsed ? TokenType::REAL_LITERAL : TokenType::INT_LITERAL), buffer);
    }

    Token Lexer::_strLit() {
        std::string buffer = "";
		do {
			if (_char == EOF) {
				// TODO No end of string literal found error
				return Token(TokenType::INVALID, "NO END OF STRING LITERAL FOUND");
			}
			buffer += _char;
			_consume();
		} while (_char != '\'');
		_consume();
		return Token(TokenType::STR_LITERAL, buffer);
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
			return Token(t, "$" + buffer);
		}
		return Token(TokenType::IDENTIFIER, buffer);
    }

};
