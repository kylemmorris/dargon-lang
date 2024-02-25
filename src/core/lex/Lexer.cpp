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

#include <sstream>
#include "Lexer.h"
#include "../Exception.h"
#include "../io/IO.h"

namespace dargon {

    Lexer::Lexer()
    : _data(nullptr), _curr(EOF)
    {}

    Lexer::~Lexer()
    {}

    void Lexer::Buffer(File* file) {
        _data = file;
        _curr = _data->ReadChar();
        _output.clear();
    }

    Token Lexer::Next() {
        // While we are not at the end-of-file
        while(_curr != EOF) {
            // Depends on character
            switch(_curr) {
                // A new line
                case '\n':
                case '\r':
                    // Only return a token IF it's on a line with other valid text
                    // - if it's just on a line by itself, ignore!
                    if(blankLine()) {
                        consume();
                        continue;
                    }
                    consume();
                    return Token(Token::Kind::NEWLINE, _truePos(1));
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
                    return Token(Token::Kind::PAREN_CLOSE, _truePos(1));
                case '(':
                    consume();
                    if(_curr == '#') {
                        consume();
                        commentBlock();
                        break;
                    }
                    return Token(Token::Kind::PAREN_OPEN, _truePos(1));
                // Assignment or equality
                case '=':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::EQUALITY, _truePos(2));
                    }
                    return Token(Token::Kind::ASSIGNMENT, _truePos(1));
                // Inequality or negation
                case '!':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::NEQUALITY, _truePos(2));
                    }
                    return Token(Token::Kind::BANG, _truePos(1));
                // > or >=
                case '>':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::GTE, _truePos(2));
                    }
                    return Token(Token::Kind::GT, _truePos(1));
                // < or <=
                case '<':
                    consume();
                    if(_curr == '=') {
                        consume();
                        return Token(Token::Kind::LTE, _truePos(2));
                    }
                    return Token(Token::Kind::LT, _truePos(1));
                // Beginning of string literal
                case '"':
                    consume();
                    return strLit();
                // Single-character tokens
                case ':': consume(); return Token(Token::Kind::COLON, _truePos(1));
                case '+': consume(); return Token(Token::Kind::PLUS, _truePos(1));
                case '*': consume(); return Token(Token::Kind::STAR, _truePos(1));
                case '/': consume(); return Token(Token::Kind::SLASH, _truePos(1));
                case '?': consume(); return Token(Token::Kind::EXISTS, _truePos(1));
                case '-': consume(); return Token(Token::Kind::MINUS, _truePos(1));
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
                    //consume();
                    return Token(Token::Kind::INVALID, _truePos(1));
            };
        }
        // We have reached end-of-file
        return Token(Token::Kind::END_OF_FILE, _truePos(1));
    }

    TokenList Lexer::GetAllTokens() {
        if(_output.size() != 0) { return _output; }
        // Run through it all
        Token t = Next();
        do {
            _output.push_back(t);
            t = Next();
        }
        while(t.IsValid() && !t.IsEOF());
        // If there was an invalid token, error
        if(!t.IsValid()) {
            std::ostringstream os;
            os << "Invalid token: " << _curr;
            throw new LexerException(
                ErrorCode::INVALID_TOKEN,
                os.str(),
                t.GetPosition());
        }
        return _output;
    }

    FilePosition Lexer::_truePos(int cols) {
        _data->MoveLeft(cols);
        FilePosition ret = _data->CurrentPosition();
        _data->MoveRight(cols);
        return ret;
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
		// Consume and do not return the newline
		consume();
    }

    void Lexer::commentBlock() {
        // Look for the pair '#)' to terminate the block comment
        while(_curr != EOF) {
            while(_curr != '#' && _curr != EOF) { consume(); }
            consume(); // Consume the '#'
            if(_curr == ')') {
                consume(); // Consume the ')'
                // Should also consume any whitespace
                whitespace();
                // if there would be a new line, consume that
                if(_curr == '\n') {
                    consume();
                }
                break;
            }
        }
    }

    bool Lexer::blankLine() {
        std::string line = _data->ReadLine();
        // Erase all whitespace
        RemoveFromString(line, '\n');
        RemoveFromString(line, '\t');
        RemoveFromString(line, ' ');
        return line.empty();
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
		return Token((decimalUsed ? Token::Kind::REAL_LIT : Token::Kind::INTEGER_LIT), buffer, _truePos(buffer.length()));
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
		return Token(Token::Kind::STRING_LIT, buffer, _truePos(buffer.length()));
    }

    Token Lexer::identifier() {
        std::string buffer = "";
		do {
			buffer += _curr;
			consume();
		}
		while(isalpha(_curr) || isdigit(_curr) || _curr == '_');
		return Token(Token::Kind::ID, buffer, _truePos(buffer.length()));
    }

};
