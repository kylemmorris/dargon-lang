# The Dargon Programming Language - v0.0

**This is still a work in progress - Dargon is not ready!**

Dargon is a small toy language and (for now) solo project with a focus on being:

- Fun
- Artistic and "always experimental"
- Free and open-source (FOSS)

Dargon is currently not aiming to be:

- The next general-purpose programming language
- Built for speed or critical applications

The full Dargon experience aims to deliver the following:

- A portable interpreter/REPL
- Syntax highlighting for popular text editors (Vim, Notepad++, etc.)
- Full, local documentation that is always available
- A basic text editor GUI, build specifically for Dargon

## Where to Start

Dargon is not ready for any form of distribution or usage. I am currently working on gathering initial documentation, including a tutorial on how I think Dargon shuold preform (almost like a requirements document), a language specification, grammar definition, and UML diagrams. All of these can be found in the [doc](doc) directory of this repository.

## Current Roadmap

Dargon is a learning experience for me as an artistic project; I am currently working on this project by myself and during my free time. As a result, this roadmap is not 100% fleshed out and is subject to change.

- Initial documentation
- Lexer
- Abstract Syntax Tree (AST) generation
- LL(1) Recursive-Descent Parser.
- ... *More here*
- Example files created (Hello World, Fibbonacci, and 99 Bottels of Beer). 
- Entry created on RosettaCode (https://rosettacode.org/wiki/Rosetta_Code).
- Version 0.1.

## Verison 0.1

0.1 will be the initial, internal release. It will include, at a minimum, an initial stab at a *very basic* Dargon Interpreter (DIR) and Dargon Toolkit (DTK) (whatever that is!). More to come on this front!

## Basic Code Example

```
# This is a simple fibonnaci example. File: fib.dargon

##
Recursive Fibonnaci sequence.
Created by Kyle Morris.
##
fun fib(x :int -> int) [
    -> x if(x < 2) else fib(x-1) + fib(x-2);
]

assert(fib(10) == 55);
```

## Technology Used

- Code::Blocks IDE (version 20.03)
- CMake (verison 3.22.1)
- g++ (using C++17)
- Umbrello (UML editor)
- doxygen (for documentation)
