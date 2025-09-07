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
    D_TokenType_ASSIGN,
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
    D_TokenType_IDENTIFIER,
    // Keywords
    D_TokenType_KW_alias,
    D_TokenType_KW_and,
    D_TokenType_KW_bool,
    D_TokenType_KW_copy,
    D_TokenType_KW_defer,
    D_TokenType_KW_else,
    D_TokenType_KW_eq,
    D_TokenType_KW_exists,
    D_TokenType_KW_export,
    D_TokenType_KW_false,
    D_TokenType_KW_fun,
    D_TokenType_KW_if,
    D_TokenType_KW_int,
    D_TokenType_KW_is,
    D_TokenType_KW_loop,
    D_TokenType_KW_module,
    D_TokenType_KW_neq,
    D_TokenType_KW_not,
    D_TokenType_KW_or,
    D_TokenType_KW_private,
    D_TokenType_KW_readonly,
    D_TokenType_KW_real,
    D_TokenType_KW_ref,
    D_TokenType_KW_string,
    D_TokenType_KW_struct,
    D_TokenType_KW_then,
    D_TokenType_KW_true,
    D_TokenType_KW_try,
    D_TokenType_KW_var,
    D_TokenType_KW_vm,
    D_TokenType_KW_when,
    D_TokenType_KW_xor,
    // Count
    D_TokenType_Count
} D_TokenType;

typedef struct {
    const char* start;
    int length;
    D_TokenType type;
    int line;
    int column;
} D_Token;



#endif // DRG_H_TOKEN
