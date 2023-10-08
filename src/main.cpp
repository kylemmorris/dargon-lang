/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: main.cpp
 *
 * DESCRIPTION: Main file.
 *
 * SINCE: v0.1
 */

#include <vector>
#include "core/Output.h"
#include "core/Log.h"
#include "core/CLI.h"
#include "core/ast/Expr.h"
//#include "core/ast/ASTPrinter.h"

int main(int argc, char* argv[]) {
    using namespace dargon;

    // TODO: Add this to testing framework.
//    // TEST (* (- 123) (group 45.67))
//    LiteralExpr l1("123");
//    LiteralExpr l2("45.67");
//    UnaryExpr neg(Token(TokenType::OP_MINUS,"-"), &l1);
//    GroupingExpr g(&l2);
//    BinaryExpr exp(&neg, Token(TokenType::OP_MULT, "*"), &g);
//    ASTPrinter printer;
//    out("");
//    printer.Print(&exp);
//    out("");
//    out("");
//    return 0;

    // Starting up
    out(VersionString());
    out("(C) Kyle Morris 2023 - See LICENSE.txt for license information.\n");
    InfoLog(VersionString() + " starting.");

    // Collect inputs
    std::vector<std::string> inputs;
    for(int i = 1; i < argc; i++) {
        inputs.push_back(std::string(argv[i]));
    }

    // The Command-Line Interface. To be built upon as we go.
    CLI cli = CLI(inputs);

    return cli.Run();
}
