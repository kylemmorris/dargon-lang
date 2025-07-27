/*****************************************************************
* Dargon Programming Language
* (C) Kyle Morris 2025 - See LICENSE.txt for license information.
*
* @file Scanner.h
* @author Kyle Morris
* @since v0.1
* @section Description
* Implements the scanner.
*
*****************************************************************/

#ifndef DRG_H_SCANNER
#define DRG_H_SCANNER

#include "Token.h"

typedef struct {
    const char* start;      // ptr to start of lexeme
    const char* current;    // 
    int line;               // line number
    int column;             // column in line
} D_Scanner;

D_Token D_GetNextToken(D_Scanner* const scanner);

#endif // DRG_H_SCANNER
