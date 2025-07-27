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

void D_InitScanner(const char* const source);
D_Token D_GetNextToken(void);

#endif // DRG_H_SCANNER
