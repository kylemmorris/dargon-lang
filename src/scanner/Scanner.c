/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Scanner.c
* @author Kyle Morris
* @since v0.1
* @section Description
* Implements the scanner.
*
*****************************************************************/

#include <stdbool.h>
#include <string.h>
#include "Scanner.h"

/*****************************************************************
* Types
*****************************************************************/

typedef struct {
    const char* start;      // ptr to start of lexeme
    const char* current;    // ptr to char being worked on
    int line;               // line number
    int column;             // column in line
} D_Scanner;

static D_Scanner _sc;

/*****************************************************************
* Utils
*****************************************************************/

inline static bool D_AtEnd(void) {
    return *_sc.current == '\0';
}

inline static bool D_IsDigit(char c) {
    return c >= '0' && c <= '9';
}

inline static bool D_IsAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_');
}

inline static D_Token D_NewToken(D_TokenType type) {
    D_Token token;
    token.type = type;
    token.start = _sc.start;
    token.length = (int)(_sc.current - _sc.start);
    token.line = _sc.line;
    token.column = _sc.column;
    return token;
}

/*****************************************************************
* Consume Functions
*****************************************************************/

inline static char D_Peek(void) {
    return *_sc.current;
}

inline static char D_PeekNext(void) {
    if(D_AtEnd()) return '\0';
    return _sc.current[1];
}

inline static char D_Consume(void) {
    // Increment pointer
    _sc.current++;
    _sc.column++;
    // Return previous char
    return _sc.current[-1];
}

inline static bool D_ConsumeIfMatch(char expected) {
    if(D_AtEnd()) return false;
    if(*_sc.current != expected) return false;
    _sc.current++;
    return true;
}

inline static void D_ConsumeWhitespaces(void) {
    for(;;) {
        switch(D_Peek()) {
            case '(': {
                if(D_PeekNext() == '#') {
                    // Consume the '(' and '#'
                    D_Consume();
                    D_Consume();
                    // Block comment ends when '#)' is found
                    // (# test #)
                    while(!D_AtEnd()) {
                        if(D_Peek() == '#' && D_PeekNext() == ')') {
                            // Consume both and exit
                            D_Consume();
                            D_Consume();
                            break;
                        }
                        D_Consume();
                    }
                    // If we were at the end, it means we never found a matching
                    // closing brace
                }
                else {
                    return;
                }
                break;
            }
            case '#': {
                if(D_Peek() == '!') {
                    // TODO-style comment
                }
                // Comment goes till end of line
                while(D_Peek() != '\n' && !D_AtEnd()) {
                    D_Consume();
                }
                break;
            }
            case ' ': case '\r': case '\t':
                D_Consume();
                break;
            default:
                return;
        }
    }
}

inline static D_TokenType D_CompareWithKeyword(int start, int length, const char* rest, D_TokenType type) {
    if(_sc.current - _sc.start == start + length && 0 == memcmp(_sc.start + start, rest, length)) {
        return type;
    }
    return D_TokenType_IDENTIFIER;
}

inline static D_TokenType D_CheckIfKeyword(void) {
    switch(_sc.start[0]) {
        case 'a': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'l': return D_CompareWithKeyword(2, 3, "ias", D_TokenType_KW_alias);
                    case 'n': return D_CompareWithKeyword(2, 1, "d", D_TokenType_KW_and);
                }
            }
            break;
        }
        case 'b': return D_CompareWithKeyword(1, 3, "ool", D_TokenType_KW_bool);
        case 'c': return D_CompareWithKeyword(1, 3, "opy", D_TokenType_KW_copy);
        case 'd': return D_CompareWithKeyword(1, 4, "efer", D_TokenType_KW_defer);
        case 'e': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'l': return D_CompareWithKeyword(2, 2, "se", D_TokenType_KW_else);
                    case 'q': return D_TokenType_KW_eq;
                    case 'x': {
                        if(_sc.current - _sc.start > 2) {
                            switch(_sc.start[2]) {
                                case 'i': return D_CompareWithKeyword(3, 3, "sts", D_TokenType_KW_exists);
                                case 'p': return D_CompareWithKeyword(3, 3, "ort", D_TokenType_KW_export);
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        case 'f': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'a': return D_CompareWithKeyword(2, 3, "lse", D_TokenType_KW_false);
                    case 'u': return D_CompareWithKeyword(2, 1, "n", D_TokenType_KW_fun);
                }
            }
            break;
        }
        case 'i': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'f': return D_TokenType_KW_if;
                    case 'n': return D_CompareWithKeyword(2, 1, "t", D_TokenType_KW_int);
                    case 's': return D_TokenType_KW_is;
                }
            }
            break;
        }
        case 'l': return D_CompareWithKeyword(1, 3, "oop", D_TokenType_KW_loop);
        case 'm': return D_CompareWithKeyword(1, 5, "odule", D_TokenType_KW_module);
        case 'n': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'e': return D_CompareWithKeyword(2, 1, "q", D_TokenType_KW_neq);
                    case 'o': return D_CompareWithKeyword(2, 1, "t", D_TokenType_KW_not);
                }
            }
            break;
        }
        case 'o': return D_CompareWithKeyword(1, 1, "r", D_TokenType_KW_or);
        case 'p': return D_CompareWithKeyword(1, 6, "rivate", D_TokenType_KW_private);
        case 'r': {
            // rea   donly
            // rea   l
            // ref
            if(_sc.current - _sc.start > 2 && _sc.start[1] == 'e') {
                switch(_sc.start[2]) {
                    case 'a': {
                        if(_sc.current - _sc.start > 3) {
                            switch(_sc.start[3]) {
                                case 'd': return D_CompareWithKeyword(4, 4, "only", D_TokenType_KW_readonly);
                                case 'l': return D_TokenType_KW_real;
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        case 's': {
            // str  ing
            // str  uct
            if(_sc.current - _sc.start > 3 && _sc.start[1] == 't' && _sc.start[2] == 'r') {
                switch(_sc.start[3]) {
                    case 'i': return D_CompareWithKeyword(4, 2, "ng", D_TokenType_KW_string);
                    case 'u': return D_CompareWithKeyword(4, 2, "ct", D_TokenType_KW_struct);
                }
            }
            break;
        }
        case 't': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'h': return D_CompareWithKeyword(2, 2, "en", D_TokenType_KW_then);
                    case 'r': {
                        if(_sc.current - _sc.start > 2) {
                            switch(_sc.start[2]) {
                                case 'u': return D_CompareWithKeyword(2, 1, "e", D_TokenType_KW_true);
                                case 'y': return D_TokenType_KW_try;
                            }
                        }
                    }
                }
            }
            break;
        }
        case 'v': {
            if(_sc.current - _sc.start > 1) {
                switch(_sc.start[1]) {
                    case 'a': return D_CompareWithKeyword(2, 1, "r", D_TokenType_KW_var);
                    case 'm': return D_TokenType_KW_vm;
                }
            }
            break;
        }
        case 'w': return D_CompareWithKeyword(1, 3, "hen", D_TokenType_KW_when);
        case 'x': return D_CompareWithKeyword(1, 2, "or", D_TokenType_KW_xor);
    }
    return D_TokenType_IDENTIFIER;
}

/*****************************************************************
* Scanner
*****************************************************************/

void D_InitScanner(const char* const source) {
    _sc.start = source;
    _sc.current = source;
    _sc.line = 1;
    _sc.column = 0;
}

D_Token D_GetNextToken(void) {
    // Ignore all whitespace
    D_ConsumeWhitespaces();

    // Each call scans a complete token, so we set
    // 'start' to point to the current char so we
    // remember where the lexeme we're about to 
    // scan starts.
    _sc.start = _sc.current;

    // If we're at the end, return EOF token
    if(D_AtEnd()) {
        return D_NewToken(D_TokenType_EOF);
    }

    // Get the current character
    char currentChar = D_Consume();

    // Check for identifiers
    if(D_IsAlpha(currentChar)) {
        // Consume all alphanumerics
        while(D_IsAlpha(D_Peek()) || D_IsDigit(D_Peek())) {
            D_Consume();
        }
        return D_NewToken(D_CheckIfKeyword());
    }

    // Check for numeric literals
    if(D_IsDigit(currentChar)) {
        // Is an integer unless there's a fractional part
        D_TokenType type = D_TokenType_INTEGER_LITERAL;
        // Consume all digits
        while(D_IsDigit(D_Peek())) D_Consume();
        // If there's a fractional part...
        if(D_Peek() == '.' && D_IsDigit(D_PeekNext())) {
            type = D_TokenType_REAL_LITERAL;
            // Consume the period
            D_Consume();
            // Get all the digits after the period
            while(D_IsDigit(D_Peek())) D_Consume();
        }
        return D_NewToken(type);
    }

    // Everything else
    switch(currentChar) {
        case '\n': {
            _sc.line++;
            D_Token ret = D_NewToken(D_TokenType_NEWLINE);
            _sc.column = 0;
            return ret;
        }
        case '(': {
            if(D_Peek() == '#') {
                // Multi-line comment, (# ... #)
            }
            return D_NewToken(D_TokenType_LPAREN);
        }
        case '=': return D_NewToken(D_TokenType_ASSIGN);
        case ')': return D_NewToken(D_TokenType_RPAREN);
        case '{': return D_NewToken(D_TokenType_LBRACE);
        case '}': return D_NewToken(D_TokenType_RBRACE);
        case '-': return D_NewToken(D_TokenType_MINUS);
        case '+': return D_NewToken(D_TokenType_PLUS);
        case '/': return D_NewToken(D_TokenType_SLASH);
        case '*': return D_NewToken(D_TokenType_STAR);
        // -- 2 chars
        case '<':
            return D_NewToken(D_ConsumeIfMatch('=')
                ? D_TokenType_LTE : D_TokenType_LT);
        case '>':
            return D_NewToken(D_ConsumeIfMatch('=')
                ? D_TokenType_GTE : D_TokenType_GT);
        // -- Literals (could be any # chars)
        case '"': {
            // While we're within the string and not at end...
            while(D_Peek() != '"' && !D_AtEnd()) {
                if(D_Peek() == '\n') {
                    _sc.line++;
                }
                D_Consume();
            }
            // Unterminated
            if(D_AtEnd()) {
                return D_NewToken(D_TokenType_INVALID);
            }
            // Closing quote
            D_Consume();
            return D_NewToken(D_TokenType_STRING_LITERAL);
        }
    }

    // Unknown token
    return D_NewToken(D_TokenType_UNKNOWN);
}