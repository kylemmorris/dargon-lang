# The Dargon Programming Language - v0.1

**This is still a huge work in progress - Dargon is not ready!**

Dargon is a small toy language and (for now) solo project with a focus on being:

- Fun
- Artistic and "always experimental"
- Free and open-source (FOSS)

Dargon is currently not aiming to be:

- The next general-purpose programming language
- Built for speed or critical applications

The full Dargon experience aims to deliver the following:

- The portable Dargon Interpreter (DIR)
- Syntax highlighting for popular text editors (Vim, Notepad++, etc.)
- Full, local documentation that is always available
- A basic text editor GUI, built specifically for Dargon

## Where to Start

Dargon is not ready for any form of distribution or usage. I am currently working on gathering initial documentation, including a tutorial on how I think Dargon should preform (almost like a requirements document), a language specification, grammar definition, and UML diagrams. All of these can be found in the [doc](doc) directory of this repository. Some [example](examples) programs are also available.

## Current Roadmap

Dargon is a learning experience for me as an artistic project; I am currently working on this project by myself and during my free time. As a result, this roadmap is not 100% fleshed out and is subject to change.

- Full definition of language
- Lexer
- AST generation
- LL(1) Parser (might be sufficient)
- Core engine and memory management
- Testing framework
- ... *Much more here* ...
- Entry created on [RosettaCode](https://rosettacode.org/wiki/Rosetta_Code)
- Version 0.1

## Basic Code Example

```
##
File: fib.dargon
Recursive Fibonnaci sequence command line program.
@Author Kyle Morris.
##

fun fib(x :uint -> uint) [
    -> x if(x < 2) else fib(x-1) + fib(x-2)
]

var inp :string = ""
var value :uint = 0
loop [
    print("Fibonnaci calculator (enter 'q' or 'quit' to exit)")
    inp = input("Enter a number between 0 and 10: ")    
    if(inp == "q"|"quit") [
        stop
    ]
    else [
        value = inp to uint;
        if(value?) [
            print("fib({value}) = {fib(value)}")
        ]
        else [
            print("Enter a number silly!")
        ]
    ]
]
```

## Technology Used

- Code::Blocks IDE (version 20.03)
- CMake (verison 3.22.1)
- g++ (using C++17)
- draw.io (UML editor)
- doxygen (for documentation)
