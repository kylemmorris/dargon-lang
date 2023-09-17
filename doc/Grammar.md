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
declaration = mutability IDENTIFIER ( type )? ( ";" | "=" expression ";" ) ;
type = ":" IDENTIFIER ;

(* An expression is a statement that produces a value *)
expression = literal | unary | binary | exprGroup ;
unary = ( "-" | "!" ) expression ;
binary = expression operator expression ;
exprGroup = "(" expression ")" ;

(* Below are rules produced throughout the grammar *)
literal = NUMBER | STRING | "true" | "false" ;
mutability = "const" | "var" ;
operator = "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;
```
