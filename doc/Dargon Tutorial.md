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

All declarations (excluding some functions) follow this syntax, where its **mutability** is defined, then its **name**, and then its **type**. Dargon is *statically-typed*, meaning the type of each variable must be given (i.e. Dargon does not "guess" what the type is).

The one case where a type is *not* required is in these kinds of declarations. While the mutability and name is always required, its type is optional *only if* a valid literal is present. The following change to "Declare.dargon" is valid:

*File: Declare.dargon*

```
# Allowed
const pi = 3.14;
var code = 0;
print("Variable 'code' is {code});
```

Finally, to wrap this section up, when something is declared, if it is not given a value, it uses its *default* value. Note that for these kinds of declarations, the type is required. For integers and reals, this is 0 and 0.0 respectively, for booleans this is false, and for strings this is the empty string (""). Everything always has a value in Dargon - no nulls are allowed.

*File: Declare.dargon*

```
const pi :real;
var code :int;
const name = "Hey";
# Not allowed
# const something;
```

**In Dargon, the rule of thumb is: if you, the programmer, cannot deduce the type of a declaration, then Dargon cannot and will not allow it.**

Finally, Dargon also allows multiple declarations per line:

*File: Declare.dargon*

```
const one, two, three = 1, 2, 3;
var name, nickname :string = "Robert", "Bob";
const myName :string, myAge :int = "Kyle", 24;
const x :int, var err :bool = 12, false;
```

## Functions

*Functions* are blocks of code that take any number of inputs and produce any number of outputs. Dargon provides a few neat features, for example: any number of different outputs, named output variables, and *first-class functions*. In layman's terms, this means functions can be passed around, just like any other variable (in fact, a function that is declared as a variable can "change" its implementation - more on that later). 

Create a file named "Functions.dargon" and let's explore what Dargon's functions look like:

*File: Functions.dargon*

```
# Returns input^2
fun square(input :int -> int) [
    -> (input * input);
]
```

The above code is a *function declaration*, It declares a function named "square" that takes 1 integer input, named "input", and returns an integer result. denoted by the arrow syntax. Anything to the left of the arrow is the inputs to the function, and anything to the right is its outputs. Then, the brackets denote the *body* of the function and, since this function returns something, that is denoted with the arrow syntax as well.

Now that this is declared, we call is like this:

*File: Functions.dargon*

```
const myNumber = 8;
const sixtyFour = square(myNumber);
assert(sixtyFour == 64);
print("8^2 = {sixtyFour});
```

The previous code snippet is also using another built-in function, *assert*. This function makes sure, or "asserts" its input expression and, if it's not true, it throws an error. In this case, 8*8 is 64, so this assertion should pass.

While functions can become complicated and include multiple inputs and outputs, Dargon emphasizes readability. Take the following example:

*File: Functions.dargon*

```
# Safely divides x by y, includes error for div by zero.
fun safeDivide(x :int, y :int -> real, bool) [
    ...
]
```

Just from reading the function declaration, you can see that it takes in two integer numbers, x and y, and returns a real number and a boolean (true or false), where if this is true, there was an error. This could be better though.

In Dargon, function inputs can be split by type using the comma (",") operator (operators will be described in more detail later). In addition, outputs can be named. In this case, instead of using the arrow (->) to "return" the value, the function must set each named output. See the following, new declaration, as well as how functions with multiple outputs are used:

*File: Functions.dargon*

```
# Safely divides x by y, includes error for div by zero.
fun safeDivide(x, y :int -> output :real, error :bool) [
    ...
]
const a, b :int = 12, 0;
const c :real, er :bool = safeDivide(a,b);
```

## Scope

"Scope" is a term that refers to the lifetime and accessability of a programming element (variable/constant/function/etc.). An "inner scope" refers to a scope that is inside another scope. In general, an inner scope has access to all of the elements in its outer scope. In Dargon, we call scopes *blocks*, like other languages do. In fact, a Dargon file is itself a scope, sometimes called the *global scope*.
