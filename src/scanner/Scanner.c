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
#include "Scanner.h"

inline static bool D_AtEnd(D_Scanner* const scanner) {
    return *scanner->current == '\0';
}

inline static bool D_IsDigit(char c) {
    return c >= '0' && c <= '9';
}

inline static bool D_IsAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' || c <= 'Z') ||
        (c == '_');
}

inline static D_Token D_NewToken(D_Scanner* const scanner, D_TokenType type) {
    D_Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;
    token.column = scanner->column;
    return token;
}

inline static char D_Peek(D_Scanner* const scanner) {
    return *scanner->current;
}

inline static char D_PeekNext(D_Scanner* const scanner) {
    if(D_AtEnd(scanner)) return '\0';
    return scanner->current[1];
}

inline static char D_Consume(D_Scanner* const scanner) {
    // Increment pointer
    scanner->current++;
    // Return previous char
    return scanner->current[-1];
}

inline static bool D_ConsumeIfMatch(D_Scanner* const scanner, char expected) {
    if(D_AtEnd(scanner)) return false;
    if(*scanner->current != expected) return false;
    scanner->current++;
    return true;
}

inline static void D_ConsumeWhitespaces(D_Scanner* const scanner) {
    for(;;) {
        switch(D_Peek(scanner)) {
            case ' ': case '\r': case '\t':
                D_Consume(scanner);
                break;
            default:
                return;
        }
    }
}

inline static D_TokenType D_CheckIfReservedWord(D_Scanner* const scanner) {
    
}

D_Token D_GetNextToken(D_Scanner* const scanner) {
    // Ignore all whitespace
    D_ConsumeWhitespaces(scanner);

    // Each call scans a complete token, so we set
    // 'start' to point to the current char so we
    // remember where the lexeme we're about to 
    // scan starts.
    scanner->start = scanner->current;

    // If we're at the end, return EOF token
    if(D_AtEnd(scanner)) {
        return D_NewToken(scanner, D_TokenType_EOF);
    }

    // Get the current character
    char currentChar = D_Consume(scanner);

    // Check for identifiers
    if(D_IsAlpha(currentChar)) {
        // Consume all alphanumerics
        while(D_IsAlpha(D_Peek(scanner)) || D_IsDigit(D_Peek(scanner))) {
            D_Consume(scanner);
        }
        return D_NewToken(scanner, D_CheckIfReservedWord(scanner));
    }

    // Check for numeric literals
    if(D_IsDigit(currentChar)) {
        // Is an integer unless there's a fractional part
        D_TokenType type = D_TokenType_INTEGER_LITERAL;
        // Consume all digits
        while(D_IsDigit(D_Peek(scanner))) D_Consume(scanner);
        // If there's a fractional part...
        if(D_Peek(scanner) == '.' && D_IsDigit(D_PeekNext(scanner))) {
            type = D_TokenType_REAL_LITERAL;
            // Consume the period
            D_Consume(scanner);
            // Get all the digits after the period
            while(D_IsDigit(D_Peek(scanner))) D_Consume(scanner);
        }
        return D_NewToken(scanner, type);
    }

    // Everything else
    switch(currentChar) {
        // -- 1 char
        case '#': {
            if(D_Peek(scanner) == '!') {
                // TODO-style comment
            }
            else {
                // Comment goes till end of line
                while(D_Peek(scanner) != '\n' && !D_AtEnd(scanner)) {
                    D_Consume(scanner);
                }
            }
            break;
        }
        case '\n': scanner->line++; return D_NewToken(scanner, D_TokenType_NEWLINE);
        case '(': {
            if(D_Peek(scanner) == '#') {
                // Multi-line comment, (# ... #)
            }
            return D_NewToken(scanner, D_TokenType_LPAREN);
        }
        case ')': return D_NewToken(scanner, D_TokenType_RPAREN);
        case '{': return D_NewToken(scanner, D_TokenType_LBRACE);
        case '}': return D_NewToken(scanner, D_TokenType_RBRACE);
        case '-': return D_NewToken(scanner, D_TokenType_MINUS);
        case '+': return D_NewToken(scanner, D_TokenType_PLUS);
        case '/': return D_NewToken(scanner, D_TokenType_SLASH);
        case '*': return D_NewToken(scanner, D_TokenType_STAR);
        // -- 2 chars
        case '<':
            return D_NewToken(scanner, D_ConsumeIfMatch(scanner, '=')
                ? D_TokenType_LTE : D_TokenType_LT);
        case '>':
            return D_NewToken(scanner, D_ConsumeIfMatch(scanner, '=')
                ? D_TokenType_GTE : D_TokenType_GT);
        // -- Literals (could be any # chars)
        case '"': {
            // While we're within the string and not at end...
            while(D_Peek(scanner) != '"' && !D_AtEnd(scanner)) {
                if(D_Peek(scanner) == '\n') {
                    scanner->line++;
                }
                D_Consume(scanner);
            }
            // Unterminated
            if(D_AtEnd(scanner)) {
                return D_NewToken(scanner, D_TokenType_INVALID);
            }
            // Closing quote
            D_Consume(scanner);
            return D_NewToken(scanner, D_TokenType_STRING_LITERAL);
        }
    }

    // Unknown token
    return D_NewToken(scanner, D_TokenType_UNKNOWN);
}