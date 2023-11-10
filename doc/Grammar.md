# Dargon BNF Grammar

If you're unfamilar with BNF or its derivatives (which this is), see [the wikipedia article]([Extended Backus–Naur form - Wikipedia](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form)).

### Convention

Conventions used are as follows:

- Rules are formated in the form: rule = definition ;

- terminals are surrounded in quotation marks ( " )

- Multiple productions of the same rule are separated using the pipe ( | ) character.

- Productions are grouped with parenthesis.

- Postfix "*" means the sequence or grouping of sequences can be repeated 0 or more times.

- Postfix "+" means the sequence or grouping of sequences can be repeated 1 or more times.

- Postfix "?" means the sequence or grouping of sequences can appear either 0 or 1 times.

- Fully-capitalized non-terminals refer to varying, or special sequences (simlar to ?..? syntax in EBNF). These special non-terminals should be self-explanatory, but will be explained if they're not.

### Grammar

```ebnf
(* This group of rules represents declarations *)
declaration = element_decl | function_decl | type_decl ;
(* An element is a constant or variable *)
element_decl = mutability IDENTIFIER (type "?" end | "=" value end) ;
(* A function declaration *)
function_decl = "fun" IDENTIFIER "(" (inputs ("->" outputs)?) ")" block ;
(* A type declaration *)
type_decl = "type" IDENTIFIER def_block ;

(* An expression is a statement that produces a value *)
function_header = "fun" "(" (inputs ("->" outputs)?) ")" ;
block = "[" (declaration | expression)* "]" ;
def_block = "[" (declaration)* "]" ;
value = literal | expression ;
expression = literal | unary | binary | exprGroup ;
unary = ( "-" | "!" ) expression ;
binary = expression operator expression ;
exprGroup = "(" expression ")" ;

(* Below are rules produced throughout the grammar *)
literal = NUMBER | STRING | "true" | "false" ;
mutability = "const" | "var" ;
operator = "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;
type = ":" IDENTIFIER ;
(* The end of a statement *)
end = (NEWLINE | "..." NEWLINE) ;
```

### Keywords + Meaning

```
var        Variable declaration
const      Constant declaration
fun        Function declaration
type       Type declaration
operator   Custom operator declaration
if
else
when       Pattern-matching
is         Pattern-matching case; type comparison
loop       Main loop construct
continue   Next iteration in loop
stop       Stop a loop/process
defer      Defer an expression until after a scope
to         Type conversion
as         Alias
with       Closure
use        Module import
```

### Available Operators

```
+
-
*
/
>
<
>=
<=
==
!=
and
or
not
=
..
->
<-
?
!
.
>>
<<
~
to
as
```
