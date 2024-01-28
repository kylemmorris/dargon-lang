# Dargon EBNF Grammar

Conventions follows [ISO 14977](https://www.cl.cam.ac.uk/~mgk25/iso-14977.pdf).

### Grammar

```ebnf
(* Dargon v0.1 *)
script = { use_decl }, { decl | stmt } ;
use_decl = "use", identifier, {"." identifier}, end ;
decl = elem_decl | elemf_decl | func_decl | type_decl ;

elem_decl = ["fixed"] (uninit_elem_decl | init_elem_decl), end ;
uninit_elem_decl = type_spec, identifier ;
init_elem_decl = type_spec, identifier, "=", expr ;
elemf_decl = expr, "as", ["fixed"], [type_spec], identifier, end ;

func_decl = "fun", identifier, func_type, "{", {decl | expr}, "}" ;
func_type = "(", {in_param_list}, ["->", {out_param_list}], ")" ;
func_shorthand = "fun", func_type ;
in_param_list = uninit_elem_decl, {",", in_param_list} ;
out_param_list = (type_spec, {",", out_param_list}) | (in_param_list) ;

type_decl = "type", identifier, {subtype_decl}, "{", type_body, "}" ;
subtype_decl = "<", identifier, {",", identifier} ;
type_body = ;

type_spec = type, ["?"] ;
type = "int" | "real" | "bool" | "string" | func_shorthand ;
identifier = (?alpha? | "_"), {?alphanumeric? | "_"} ;
end = ?newline? ;

(* ----- OLD BELOW ----- *)

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

(* Expressions *)
expression = equality ;
equality = comparison ( ("!=" | "==") comparison )* ;
comparison = term ( (">" | ">=" | "<" | "<=") term)* ;
term = factor ( ("-" | "+") factor)* ;
factor = unary ( ("/" | "*") factor)* ;
unary = ("not" | "-") unary | primary ;
primary = NUMBER | STRING | "true" | "false" | "(" expression ")" ;

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
and          Logical AND
as           Stack variable allocation
bool         Built-in boolean type
continue     Next loop iterat
defer        Defer a statement until scope exit
else         Branch
fixed        Constant declaration
fun          Function/lambda declaration
if           Branch
in           Inclusion
int          Built-in integer type
is           Pattern-matching case; type comparison
loop         Main loop construct
module       Module declaration
or           Logical OR
pattern      Pattern definition
private      Denotes private fields of type
protected    Denotes protected fields of type
public       Denotes public fields of type
real         Built-in floating-point type
stop         Stop a loop/process
string       Build-in string type
to           Type conversion
type         Type definition
use          Module import
when         Pattern-matching
with         Closure capture list
xor          Logical XOR
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

### Operator Precedence

| Name           | Operators | Associates |
|:-------------- | --------- | ---------- |
| Value Equality | == !=     | Left       |
| Comparison     | > >= < <= | Left       |
| Term           | - +       | Left       |
| Factor         | / *       | Left       |
| Unary          | ! -       | Right      |
