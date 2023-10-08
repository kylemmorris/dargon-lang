# Dargon Tutorial - v0.1

Dargon is a lightweight, simple interpreted programming language aimed at being fun and intuitive. It tries to balance the thin line of pushing the boundaries of language design while also being desirable and enjoyable to use. It adds a lot of cool features and syntactic sugar, but it's also cozy and familiar. 

This tutorial will go through the basics of the language, and assumes you have the Dargon Interpreter (DIR) setup. A  number of different files will be created throughout this tutorial. For those who would rather learn by example, these files can all be accessed []("Here").

## Audience

This tutorial assumes no programming experience, and attempts to explain advanced computer science concepts in simple terms. Some familiarity with programming certainly helps, but is not required.

## Environment

All you need to start coding in Dargon is a text editor and the Dargon Interpreter (DIR). Simply pass DIR a script file with the *.dargon extension and it will run it with the "run" command. Using the "go" command like so will begin Dargon's interactive mode, more commonly referred to as a "Read-Eval-Print-Loop" (REPL):

```
~/home/demo$ ./dargon go
DIR>
```

Here, DIR will await your input and then run that input. This is great for testing out things, or just messing with the language.

## Hello Dargon!

Let's jump right in starting with an established tradition with our own little twist. Start by creating a new text file called "Hello.dargon":

*File: Hello.dargon*

```
print("Hello Dargon!");
```

The Dargon Interpreter (DIR) comes with a set of pre-defined *functions*, one of which is "print". This function takes a string and outputs it to the console. Let's use DIR's "run" command to execute this file:

```
~/home/demo$ ./dargon run Hello.dargon
Hello Dargon!
~/home/demo$ 
```

Great! But this is not all that Dargon is capable of. Before we go too much further, let's go over Dargon's syntax more thoroughly.

## Comments

A "comment" refers to a piece of code that is set to be intentionally ignored, which is useful for documenting your code for yourself and others. In Dargon, there are 3 kinds of comments. Lines that start with the pound ("#") character are *line comments*, in which the entire line is ignored. If two pound characters are next to eachother, it creates a *block comment* that can extend as many lines as you want, given the end is also marked. See below for some examples:

```
# This is a line comment and therefore ignored
Dargon code...

##
Here's a block comment that
can extend multiple lines.
Wow!
##
Dargon code...
```

The third type of comment is the *conditional comment*. The conditional comment marks a line/block of code as valid **only if** the associated Dargon flag (explained later) is configured. For example, there is a Dargon flag named "DEBUG", and below, the following block will become valid code when that flag is "true":

```
##<DEBUG>
# Yes, this is a comment inside a conditional comment block.
print("Debugging!");
##
```

The conditional comment might not seem amazing right now, but its use cases will be described in future chapters.

## Declarations

In programming languages, a **declaration** is a statement which declares a constant, variable, function, or some other programming element to the environment. Dargon allows you to declare **variables**, meaning that it's value can change throughout the code, or **constants**, meaning that its value cannot change once initialized. Create a new file named "Declare.dargon" and plug in the following lines:

*File: Declare.dargon*

```
const pi :real = 3.14;
var code :int = 0;
print("Variable 'code' is: {code}");
```

This file so far declares two things: a constant **real** number named "pi", and a variable **integer** named "code". It also assigns each one a value. It then prints the contents of the "code" variable to the screen by *insterting* its value into the string via the curly brace syntax (described later). Run this via DIR:

```
~/home/demo$ ./dargon run Declare.dargon
Variable 'code' is 0
~/home/demo$ 
```




