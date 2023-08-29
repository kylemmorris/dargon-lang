## The Dargon Programming Language

**This is still a work in progress!**

Dargon is a toy language with the sole purpose of *extending the boundaries of programming language design*. To start things off, let’s be clear on what it is, and what it is not:

What it is:
- Fun and artistic
- Free and open-source
- “Always experimental” guaranteed

What it is not:
- The “next general-purpose programming language”
- Chocked-full of user-created libraries
- Built for speed, or memory-critical applications
- A fully-featured environment

The full Dargon experience aims to deliver the following:
- A portable interpreter/REPL.
- Syntax highlighting for popular text editors (Vim, GEdit, etc.)
- Full, local documentation that is always available.
- If possible, a really basic GUI.

See "doc/Dargon Language Specification" for the full documentation.

## Current Roadmap

Dargon is a learning experience for me as an artistic project.
As a result, this roadmap is subject to change. I'll try to make use of GitHub's project system.

- Initial Language Specification.
- Lexical Analysis.
- LL(1) Parser.
- ...
- Example files created (Hello World, Fibbonacci, and 99 Bottels of Beer). 
- Entry created on RosettaCode (https://rosettacode.org/wiki/Rosetta_Code).
- Version 0.1.

## Code Example

```
# This is a simple fibonnaci example. File: fib.dargon

##
Recursive Fibonnaci sequence.
Created by Kyle Morris.
##
fun fib(uint x -> uint) {
    -> x if x < 2;
    -> fib(x-1) + fib(x-2);
}

assert(fib(10) == 55);


```

## Technology Used

- Code::Blocks IDE (version 20.03)
- CMake (verison 3.22.1)
- g++ (using C++17)
- doxygen (for documentation)

