# Comments
```
# Single line comment
(# Multi-line comment #)
#! Todo comment
```

# Declarations
```
# Immutable is default - use 'var' to make mutable
# The following are all constants
int a = 0
real pi = 3.14
bool b = true
string c = "hey! I can
	span multiple lines..."

fun(int,bool:string) f = { (#....#) }

# This can change once assigned
var real calc = 3.1314
```

# Arrays
```
int[3] array = [1,2,3]
bool[] bits = [true, false, true
	,false, false]
```

# Functions
```
fun foo1 {
	# ...
}

fun foo2(int a, int b) {
	# ...
}

fun foo3(int a : string) {
	# ...
	return "90"
}

fun foo4: bool {
	# ...
	return true
}

fun foo5(fun(int,int) func: bool) {
	# ...
	return true
}
```

# Parameter passing
```
# For primitives, pass-by-value is default. Use 'ref' to pass by ref
fun foo1(ref bool flagOut) { (#...#) }

# For arrays and structs, pass-by-ref is default. Use 'copy' to 
# pass-by-value instead
fun foo2(copy int[200] bigArray) { (#...#) }

# Immutable is default - must use 'var' to be able to modify
# value within function
fun foo3(var ref int[200] bigArray) { (#...#) }
# same...
#fun foo3(var int[200] bigArray) { (#...#) }
```

# Basic Polymorphism
```
fun foo1(int|string input) {
	when input {
		is string print(input)
		is int {
			int b = input + 2
			print(b)
		}
	}
}

fun foo2(Person|Entity|int input: bool) { ... }
```

# Compound Types
```
# Components of struct inherit the object's mutability
struct Date {
	int month
	int day
	int year
}

# Can apply additional constraints as to who can read/write what
# parts of the struct. The only place where these constraints
# are lifted is within the module the type is contained in.
struct Person {
	string nickname
	readonly string name
	private int pin
}
```

# Aliases
```
alias GuestList = Person[200]
alias float = real32
alias double = real64
```

# Operators
```
Assignment:
A = B

Arithmatic:
A + B
A - B
A * B
A / B
A ^ B
A % B

Comparison
A > B
A < B
A <= B
A >= B
A eq B
A neq B

Logical:
A and B
A or B
A xor B
not A

Access:
A[B]
A.B
```

# Flow Control
```
if(...) {
	...
}
else if(...) {
	...
}
else {
	...
}

if(...) { ... }

# Ternary
int a = if(...) 10 else 11

when(...) {
	eq value1 {...}
	eq value2 ...
	eq value3 {...}
	else {...}
}
```

# Loops
```
loop if(...) {
	...
}

loop {
	...
} if(...)

loop(...) {
	...
}
```

# Defer
```
IO.File f = ReadConfigFile()
defer IO.CloseFile(f)
```

# Nullable Types
```
int? a

if(a exists) {
	# a is now 'int'
}
```

# Exceptions
```
fun foo1(string path: string!) { ... }

try string s = foo1("...")

# or

string! s = foo1("...")
try(s) {
	# s is now 'string'
}
else {
	# s is still an error type
	# do what you want!
}
```

# Modules
```
module MathUtils

fun foo1() {...}
fun foo2() {...}
struct foobar {...}

export foo1
export foobar
```

# Inline Bytecode
```
fun LowLevelFunc {
	vm {
		...
	}
}
```