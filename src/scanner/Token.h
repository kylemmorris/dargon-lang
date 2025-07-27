/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Token.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Definition of a token, produced by the scanner to be ingested
* by the compiler.
*
*****************************************************************/

#ifndef DRG_H_TOKEN
#define DRG_H_TOKEN

typedef enum {
    D_TokenType_UNKNOWN = -2,     // Unknown token
    D_TokenType_INVALID = -1,     // Error token
    D_TokenType_EOF = 0,          // End-of-File
    D_TokenType_NEWLINE,
    D_TokenType_LPAREN,
    D_TokenType_RPAREN,
    D_TokenType_LBRACE,
    D_TokenType_RBRACE,
    D_TokenType_MINUS,
    D_TokenType_PLUS,
    D_TokenType_SLASH,
    D_TokenType_STAR,
    D_TokenType_GT,
    D_TokenType_LT,
    D_TokenType_GTE,
    D_TokenType_LTE,
    D_TokenType_STRING_LITERAL,
    D_TokenType_INTEGER_LITERAL,
    D_TokenType_REAL_LITERAL,
    D_TokenType_IDENTIFIER
} D_TokenType;

typedef struct {
    const char* start;
    int length;
    D_TokenType type;
    int line;
    int column;
} D_Token;

#endif // DRG_H_TOKEN
