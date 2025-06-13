# List of non-type keywords

| Keyword    | Description                                                                                                                         |
| ---------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| alias      | Alias definition                                                                                                                    |
| const      | Constant declaration or definition                                                                                                  |
| var        | Variable declaration or definition                                                                                                  |
| copy       | Pass by copy                                                                                                                        |
| ref        | Pass by reference                                                                                                                   |
| readonly   | Read only `record` fields                                                                                                           |
| private    | `record` fields hidden to all except `open` functions within the same file as the `record` definition (i.e. that `record`'s "home") |
| open       | Reveals a `record`'s private fields to a function                                                                                   |
| include    | Includes a module in this file                                                                                                      |
| module     | Declares this source file as part of a module                                                                                       |
| export     | Exposes a definition to the public portion of a module                                                                              |
| if, else   | Branching construct                                                                                                                 |
| when, is   | Pattern-matching construct                                                                                                          |
| loop       | Looping construct, combined with `if` to add conditional looping                                                                    |
| return     | Returns a value from a function                                                                                                     |
| stop       | Loop terminating expression                                                                                                         |
| defer      | Defers the execution of a function or expression for scope exit                                                                     |
| to, by     | Bounded loop: variable `to` max `by` increment                                                                                      |
| try, throw | Error handling code                                                                                                                 |
| none       | References the `none` or null type                                                                                                  |
| vm         | Inline bytecode                                                                                                                     |
# List of File Types

| Name               | Extension | Description                                               |
| ------------------ | --------- | --------------------------------------------------------- |
| Dargon Source File | dg        | A source file that contains Dargon code                   |
| Dargon Project     | dgprj     | A simple config file that defines a project and workspace |
| Dargon Module      | dgm       | A Dargon Project that has been exported                   |
# Hello World
```
print("Hello World!");
```
# Comments
There are 4 types of comments:
```
# This is a single line comment.

(#
	This comment
	extents
	multiple lines!
#)

#! Todo-style comment (shows up in compiler output as a warning)
```

In addition, metadata can be stored within block comments to during automated documentation generation:
```
(#
$summary:      Does something to each element of an array.
$param(array): The array to do something with.
$param(func):  The function that replaces an int in the array\
			   with a new value.
$returns:      True on success, false on error, and could
			   throw an error.
#)
fun doSomething(
	var int[]                 array,
	const fun(const int: int) myFunc
	: bool!) 
{ ... }
```
# Types
| Keyword | Description                             | Literal          | Default Value |
| ------- | --------------------------------------- | ---------------- | ------------- |
| intX    | 8, 16, 32, and 64-bit integers          | -12              | 0             |
| int     | Alias for `int32`                       | -12              | 0             |
| uintX   | 8, 16, 32, and 64-bit unsigned integers | 12               | 0             |
| uint    | Alias for `uin32`                       | 12               | 0             |
| realX   | 32 and 64-bit floating point number     | 12.3             | 0.0           |
| real    | Alias for `real32`                      | 12.3             | 0.0           |
| char    | ???                                     | 'A'              | ''            |
| str     | String type                             | "ABC"            | ""            |
| bool    | Boolean (true or false)                 | true             | false         |
| fun     | Function definition                     | fun(X,Y:Z) {...} | none          |
| record  | Record type                             | record X { ... } | none          |
# Decorators
Types can be given up to 2 decorators: maybe (`?`) and/or exception (`!`). Since these are aspects of the type system, none of the following are equivalent:
- `type`, a normal type
- `type?`, a "maybe" type
- `type!`, an "exception" type
- `type!?` (can also be `type?!`), called a "panic" type
# Declarations
- `<mutability> <type> name;` : Given the default value
- `<mutability> <type> name = <expr>;` : Given the value from expression
- `<mutability> name = <expr>;` : Type optional when an expression

There are two mutability settings:
- **const**: A constant, cannot change once assigned
- **var**: A variable, *can* change once assigned

```
var int myInt;             # defaults to '0'
var bool flag = true;      # given a value
flag = false;              # OK, 'flag' is defined
const real pi = 3.14;      # OK
#pi = 4.112;               # <- ERROR: Can't modify a constant

# types can be omitted when assigning
const myName = "Dard";     # string literal, so type is 'str'
var a = 360 * 14;          # type is 'int' because expression results in int 
var retCode = func();      # 'retCode' has type of whatever 'func()' returns
const f = fun(int a : int) { return a + 2; }; # is type 'fun(int:int)'
```

When declaring multiple constants / variables, it can be cumbersome to write out `const` or `var` and even the type, each time. The following syntax can be used to help with this:
```
# instead of:
var int a = 12;
var int b = 13;
var int c = 14;
var int d = 15;

# you can do:
var int {
	a = 12, b = 13, 
	c = 14, d = 15
}; # <- don't forget semicolon

# if they're different types:
const {
	str b = "b",
	str c = "c",
	bool f = false,
	real lat = -99.1214121
}; # <- don't forget semicolon
```

For types that have valid literals, the type can also be inferred:
```
var a = 1; # int
var b = 3.23; # real
var c = false; # boolean
var d = "hello"; # str
const f = fun(int a : int) { return a + 2; };
```
# Arrays
To declare an *array*, or a sequential collection of basic types, use the following syntax:
- `<mutability> <type>[<num_elements>] name;` : A constant-sized array with default values
- `<mutability> <type>[*] name;` : A variable-sized array, initial size is zero
- `<mutability> <type>[<num_elements>] name = <expr>;` : A constant-sized array initialized with values
- `<mutability> <type>[] name = <literal>` : A constant-sized array that is set to a literal, so size is not needed
- `<mutability> <type>[*] name = <expr>;` : An unknown-sized array, initialized with values

*Note:* Arrays are indexed starting from 1. It's just how humans work!
```
const int[5] myArray = [1,2,3,4,5];
print(myArray[1]); # 1
print(myArray[2]); # 2
print(myArray);    # [1,2,3,4,5]

var int[3] something = [10, 20, 30];
something[2] = 100;
print(something);  # [10, 100, 30]

# If using a literal, the number is not needed
const bool[] flags = [true, false, true, true];

# These are resizable arrays
var int[*] list = [1,2,3,4];
```

Resizable arrays can be modified using the following built-in functions:
```
var int[*] array = [1,2,3,4];
print(array);      #[1,2,3,4]

arrayAdd(array, 10);
print(array);      #[1,2,3,4,10]

try arrayRem(array, 3);   # more on 'try' later
print(array);      #[1,2,4,10]

var count = arrayLen(array);
print(count);      #4
```
# Maps
To declare a map, which is a hash-map collection that maps one type to another, use the following syntax:
- `<mutability> [<type1>:<type2>] name;`
- `<mutability> [<type1>:<type2>] name = <expr>;`

```
# [str:int] means "map a string to an int"
var [str:int] map = [0 : "0", 1: "1"];

# The following built-in functions exist

try mapAdd()

map[2] = "2";
map[3] = "3";
print(map[0] + map[2]); #02
```

# Functions
Functions are first-class, as in they can be passed to other functions, and can even be **variable**. Here is a basic function with no parameters, and no return values:
```
fun doSomething {
	#...
};

```

This kind of declaration is just syntactic sugar for this:
```
const fun doSomething = fun {

};
```
Both are equivalent.

Functions can have multiple parameters (input), take this `add` function:
```
fun add(const int x, const int y) {
	const int z = x + y;
};

add(1,2); # Great! But what happened...?
```

Functions can also have an output. A colon sign is used to distinguish between the inputs and the output of a function:
```
fun add(const int x, const int y : int) {
	return x + y;
};

const int z = add(1,2);
print(z); # 3
```

The above is equivalent to:
```
const fun(const int x, const int y : int) add = {
	return x + y;
};
# ...
```

When there are outputs, but no inputs, the following syntax can be used:
```
#same as: fun createSomething(:Something), but parenthesis are optional
fun createSomething : Something {
	return Something;
};

# Above is the same as:
const fun(:Something) createSomething = {
	return Something{};
};
# in the above case, the parenthesis are required
```

Passing these output-only functions to other functions looks like:
```

fun test(const int a, const fun(:int) iFun) {
	# ...
}

```

A one-line function can use this shortcut syntax:
```
fun add(const int a, const int b : int) {
	return a + b;
};

# equivalent to:
fun add(const int a, const int b : int) = a + b;

# can also use multi-declaration shortcuts to make this even shorter:
fun add(const int {a,b} : int) = a + b;
```
# Function Input Parameter Passing
There are different ways to pass a parameter to a function.

By using **const**, this means an input parameter cannot be changed inside the function. In addition, for containers (arrays, maps) and compound types (records), a *reference* will be passed instead of a making a copy.
```
fun add(const int x, const int y : int) {
	# x = 12; <- ERROR
	return x + y;
};

fun printBigRecord(const bigRecord o) {
	# o is a reference, not copied
};
```

If copying behavior is ever necessary, which it seldom is, use the keyword `copy`:
```
fun printBigRecord(copy const bigRecord o) {
	# a copy of o is made for this function, but it's still readonly
};
```

By using **var**, the inputted parameter *can* be changed. Again, for basic types (`int`, `char`, `real`, etc.), a copy is made and can then be modified in the function. If you want to modify the original value (i.e. pass a basic type by-reference), use the `ref` keyword:
```
fun work(var int input) {
	input = (input * 2) + 12;
};

fun workRef(ref var int input) {
	input = (input * 2) + 12;
};

var int a = 12;
work(a);
print(a); # 12

workRef(a);
print(a); # 36

const int b = 24;
#work(b); <- ERROR, const cannot be ignored
#workRef(b); <- ERROR, const cannot be ignored
```

For containers and compound types, a reference is still passed - this means the original object *will* be modified:
```
record Point {
	var int x;
	var int y;
};

fun work(var Point p) {
	p.x = p.x * 2;
	p.y = p.y * 2;
};

var Point one = {x = 1, y = 1};
work(one);
print(one); # {x:2, y:2}
```

To negate this case, and to create a copy that you can still use in the function, again use the `copy` keyword:
```
fun workNoRef(copy var Point p) {
	p.x *= 2;
	p.y *= 2;
};

var Point one = {x = 1, y = 1};
workNoRef(one);
print(one); # {x:1, y:1}
```

This table summarizes the different kinds of parameter passing:

| Passing Technique | Basic Types                | Compound Types            |
| ----------------- | -------------------------- | ------------------------- |
| `const`           | Equivalent to `copy const` | Equivalent to `ref const` |
| `var`             | Equivalent to `copy var`   | Equivalent to `ref var`   |
| `copy const`      | Readonly copy              | Readonly copy             |
| `copy var`        | Variable copy              | Variable copy             |
| `ref const`       | Readonly reference         | Readonly reference        |
| `ref var`         | Variable reference         | Variable reference        |
# Function Output

Functions can only return a single output, and "out" parameters are not supported. The output is determined by the `return` keyword:
```
record Point { var int { x = 0, y = 0 }; };

fun getMult(const Point p : int) {
	return p.x * p.y;
}

const Point p = {x = 1, y = 2};
const int m = getMult(p);
```
# Compound Types
Users can create their own types that are made up of other types, called `records`. Here is a basic record for a Date:
```
# Declare it here
record Date {
	const int month;
	const int day;
	const int year;
};

# Instantiate here
const Date zero; # Will be given all zeros

# Constructor syntax
const Date today = {
	month = 1,
	day = 10,
	year = 2025
};

print(zero); # {month:0, day:0, year:0}
print(today); # {month:1, day:10, year:2025}
```

Similar to `fun`, the following in syntactic sugar:
```
record Date {
	const int month;
	const int day;
	const int year;
};

# same as...

const record Date = record {
	const int month;
	const int day;
	const int year;
};
```

You can also use the multi-declaration syntax shown previously:
```
record Date {
	const int {
		month, day, year
	};
};
```

Dargon is not object oriented, so records cannot be given functions (also called 'methods'). They do borrow one idea from OOP in the form of *access properties*:
```
record Person {
	# Anyone can give you a nickname
	var str nickname;

	# A person can change their own name, but nobody else can!
	readonly var str name;

	# Nobody can access our credit card pin!
	private var int pin;
};

# Assuming this is in the same file...
# You can't do this in any other file!
var Person me = {
	nickname = "Bob",
	name = "Robert",
	pin = 12
};

me.nickname = "Bobby"; # All good
print(me.name); # All good
# me.name = "Richard"; <- ERROR
# me.pin = 1234; <- ERROR
```

For large structures, multi-declaration can be used in conjunction with access properties:
```
record ReadOnlyMessage {
	readonly str {
		author,
		date,
		time,
		header = "HEADER",
		contents,
		footer = "FOOTER",
		signature = "<blank>"
	};
};
```

The scope of access properties belongs to the file in which the record is defined - no other file has access to the `private` fields of a record, nor can modify their `readonly` fields.
# Aliases
Types can be given alternate names, or aliases, using the `alias` declaration. The format is `alias <new-name> = <original-type>`:

```
alias int = int32; # <- This is from the standard library
alias intArray = int[*];
alias PersonList = Person[*];
alias Phonebook = [PhoneNumber:Person]; # Can help shorten names!
```

`packages` can also be given aliases:
```
import myAwesomeMathUtilLibrary alias mlib;
```
# Data hiding
Nothing can modify the `readonly` fields of a record, and nothing can read or write the `private` fields. The only functions that *can* access them are the ones within the same file that the `record` was declared:

```
#! file: person.dg
...
fun nothingSecret(const Person p) {
	print(p.name); # OK
	print(p.ssn);  # OK
	# p.name = "Joe"; <- ERROR
};

fun legallyChangeName(var Person p, const str newName) {
	print("{p.name}: I am changing my name to...");
	p.name = newName;
	print("{p.name}!\n");
};

#! file: test.dg
include person;

const Person joe = { name = "Joe" };
nothingSecret(joe); # "Joe"
legallyChangeName(joe, "Bob"); # "Joe: I am changing my name to...Bob!"
nothingSecret(joe); # "Bob"
```
# First-class Functions

Functions are *first-class* in Dargon - this means they can be passed as arguments to other functions, and can even be variables. Take this example of a function that maps another function to an array:
```
package map_utils;

# maps a function to an integer array
fun mapIntArr(var int[*] array, const fun(const int a : int) mapFunc) {
	iterate(var int value = array) {
		value = mapFunc(value);
	}
};
```

As you can see, all the information about a function is encapsulated within the `fun(<info>)` syntax. You can even declare variable functions that you can change later:
```
include map_utils alias mu;

var int[*] myCoolArray = [1,2,3,4,5];

var fun(const int a : int) mappingFunction = {
	return a + 1;
};

print(myCoolArray); # [1,2,3,4,5];
mu.mapIntArr(myCoolArray, mappingFunction);
print(myCoolArray); # [2,3,4,5,6];

# can of course assign with function shorthand notation
mappingFunction = a * 2;

mu.mapIntArr(myCoolArray, mappingFunction);
print(myCoolArray); # [4,6,8,10,12]


```

# Operators
The pre-built operators include:

| Operator | Description                       |
| -------- | --------------------------------- |
| A + B    | Addition                          |
| A - B    | Subtraction                       |
| A * B    | Multiplication                    |
| A / B    | Division                          |
| A = B    | Assignment                        |
| A += B   | Addition-then-assignment          |
| A -= B   | Subtraction-then-assignment       |
| A *= B   | Multiplication-then-assignment    |
| A /= B   | Division-then-assignment          |
| A > B    | Greater than                      |
| A < B    | Less than                         |
| A >= B   | Greater than or equal to          |
| A <= B   | Less than or equal to             |
| A ^ B    | Exponential (A to the power of B) |
| A eq B   | Equality                          |
| A neq B  | Inequality (Not Equal)            |
| A and B  | Logical AND                       |
| A or B   | Logical OR                        |
| A xor B  | Logical XOR                       |
| not A    | Logical NOT                       |
| A mod B  | Modulus                           |
| A[B]     | Index (arrays & maps)             |
| A.B      | Property access & package access  |
There are no `A++` or `++A` operators in Dargon. Instead, use `A += 1` and code structure. In addition, operators cannot be overloaded or defined for user-defined types (`records`). It is advised instead to just create functions.

# Flow control
Dargon supports if-else branching via `if`, and `else`:
```
const int a = 12;
if(a eq 12) {
	print("a is 12");
}
else if(a eq 14) {
	print("Won't happen");
}
else {
	print("Won't happen");
}
```

The ternary operator, `if(<condition>) <true_result> else <false_result>`, is also supported:
```
const int a = 12;
const char someLogic = if(a eq 12) 'a' else 'b';
```

# Loops & iteration
Many different kinds of loops can be described using the `loop` keyword. For instance, to loop while a given condition is true (a traditional `while` loop):
```
var int value = 1024;
loop if(value > 0) {
	println(value);
	value /= 2;
}
```

To perform an loop at least once before starting to check for the condition, simply move the `if` (a traditional `do-while` loop):
```
# this loop will print '1' and then immediately exit

var int value = 1;
loop {
	println(value);
	value += 1;
} if(value mod 2 neq 0); # notice semicolon at end
```

To place bounds on a loop, use the following syntax (like a traditional `for` loop):
```
# prints for each value in array
const int[10] values = [1,2,3,4,5,6,7,8,9,10];
# this means "increment i from 0 to arLen(values) by 1 each loop"
loop(var int i = 0 to arrayLen(values) by 1) {
	println(values[i]);
}
```

An infinite loop can be accomplished via:
```
loop {
	# Will never end!
}
```

Dargon also offers a nicer syntax for iterating over collections:
```
# prints for each value in array
const int[10] values = [1,2,3,4,5,6,7,8,9,10];
loop(const int i : values) {
	println(i);
}

# type can also be inferred
loop(i : values) {
	println(i);
}
```

Finally, you can stop out of a loop via the `stop` keyword:
```
fun has1(const int[*] arr = bool) {
	var bool ret = false;

	loop(var int i : arr) {
		if(i eq 1) {
			ret = true;
			stop;
		}
	}

	return ret;
}
```

# Deferring Execution

Sometimes things might fail in a function, especially in I/O. When you want specific functions to always get called at the end of a scope, especially for clearing used resources, use the `defer` statement:
```
include io;

fun config {
	var io.file file = readMyConfigFile();
	defer io.close(file); # <- ALWAYS do this!

	# .. code that uses the file ..
	
} # file guarenteed to be closed after function exit

```

# Memory Management

Dargon does not use a garbage collector (GC), so memory must be manually managed. Dynamic collections (`int[*]`, `str`, etc.) offer dynamic memory allocation, and cover most cases.

# Nullable types
In Dargon, everything declared is given its default value, for example `var int a;` assigns variable 'a' the integer value 0, since that is the default. In some cases, we want/must allow for possible nulls, or `none`. This is done using the "maybe" decorator (`?`):

```
var int a; # 0
var int? b; # 'none'

# const c = a + b; <- ERROR! Cannot perform addition with an 'int?'

# 'int' and 'int?' are not the same
print(type(a) eq type(b)); # false

# give it a value, and it becomes 'int'
b = 12;

const c = a + b;
print(c); # 12
```

Nullable types become non-null when they are assigned a non-null value, OR when they are explicitly checked using the existence operator `exists`:

```
include math.max;

fun getTileMax(const Tile?[*] tiles : real) {
	var ret = 0.0;
	loop(tile : tiles) {		
		ret = if(tile exists) math.max(ret,tile.height) else ret;
	}
	return ret;
}
```

# Error handling

Like any language, Dargon is never free entirely of errors, however code can be marked to hint at possible errors and somewhat enforce their checking, using the exception (`!`) decorator. Similar to the "maybe" (`?`) decorator, that signifies something can be `none`, the exception decorator signifies an expression may throw an exception. And yes, you can combine these decorators like this: `int!? a = 1`. And just like the other decorator, `int!?` is NOT the same as `int?` nor `int`. 

To verify an exception, use the `try` construct, which will turn `type!` to just `type`, if it's not an exception. If it is, it can be handled up the chain appropriately using the built-in function `errHandle`.

```
# This function MAY throw an error!
fun readFile(const str path : str!) {
	# ... some implementation
}

# When calling said function, you MUST use 'try' 
# or decorate with '!' and handle later.
const str p = "test/path/file.txt";
try const str contents = readFile(p);

# The above is syntactic sugar for:
const str! contents = readFile(p);
try(contents) {
	print(contents); # verified
}
else {
	# if you cannot handle it...
	throw contents;
	# if you can...
	errHandle(contents);
}
```

In the above, `try` means the potential error has been resolved. You must use either `try` or decorate the value with `!`, if the function or its return value is marked with it and handle it later or let the caller handle it using `throw`.

Unlike the maybe decorator, the error decorator can be attached to a function even if it does not return a value. In this case you have to use `try`:
```
fun! accessMemory {
	# ...
}

try accessMemory();
```

# Namespaces and Accessibility 
When a Dargon file is created within a Dargon project (e.g. `myProj.dgp`), all of its definitions are accessible to the entire project. In addition, a `module` definition can be defined at the top of the file, working both as a namespace, as well as a critical part of the modularity of Dargon (explained in next section). See this example:
*File: test.dg*
```
module my;

private const int _innerThing = 12534;

export fun add(const int { a, b } : int) {
	return a + b;
}

export fun sub(const int { a, b } : int) {
	return a - b;
}

record test {
	var int a = 0;
	readonly int b = 12;
	private int c = 13;
}

fun special(open var test) {
	test.c += _innerThing;
}
```

- No other files can access `_innerThing`
- Any file in the project can access the `my.add` and `my.sub` functions, and any other project using the exported module
- Any file in the project can create a `my.test` record, but can't write to `b` nor access `c`
- Any file in the project can access the `my.special` function, but no other file can declare a new function that `open`s the `my.test` record.

*Note:* You cannot mix the `export` and `private` keyword - it must be one, the other, or none.

# Exporting Modules

One of Dargon's core goals is to make modular code easily to implement, and supported with excellent tooling. The snippets thus far have been just that - snippets of code in a wider module. A *module* is simply a collection of Dargon source files (e.g. `myFile.dg`) marked using the `module` keyword.

A module can be compiled in its entirety, forming a Dargon module file (e.g. `myModule.dgm`). DGM files can be included within a Dargon project, exposing the functions and definitions of that module. Modules also come with built-in support for automated documentation and versioning, making working with other DGMs a breeze.

It is not always necessary to expose every function and definition within a module. Of course, encapsulation and data-hiding exists for `records`, but sometimes whole functions or record definitions might want to remain hidden. To expose a function, definition, or declaration to the public module API, use the `export` keyword:

```
module math.graph.point;

# This can be included as: 'math.graph.point.point32' in files
export record point32 {
	var real32 {
		x = 0, 
		y = 0
	};
}

# math.graph.point.one()
export fun one: point32 {
	return point32 { x = 1, y = 1 };
}

# Will not show up as math.graph.something() to the exported
# module, HOWEVER it will show up in the project itself since 
# it's not labeled `private`.
fun something {
	#...
}
```

# Putting it all together - Tooling
The only tool a Dargon developer needs is `dargon`:
- `dargon <command> <flags> <input>`

Commands:
- `dargon init <flags>`: Initializes a Dargon project in this directory
- `dargon run <input>`: Runs a Dargon file or project
- `dargon export <flags> <prj>`: Exports a Dargon project as a dedicated module
- `dargon`: Runs an interactive interpreter

Flags:
- `-allow-vm`: Allows for the `vm` expression when used in `dargon compile`.

# Advanced

Raw bytecode can be inserted using the `vm` expression. This should only be used by power users, and requires the `-allow-vm` flag:

```
fun add(const int {a, b} : int) {
	vm {
		...
	}
}
```