# Dargon Programming Language 
# (C) Kyle Morris 2023

# This utility will be used to generate the expression and statement structures.
# Output: Expr.h

# TODO: Make this a lot cleaner! It'll come with Python experience.

from io import TextIOWrapper

### ------------###
### DEFINITIONS ###
### ------------###

# The file name
fname = './Expr.h'

# The input expressions
exprs = [\
    'Binary: Expr* left, Token op, Expr* right',\
    #'Literal: void* value'\
]

### ------------###
###  FUNCTIONS  ###
### ------------###

# Prints the copywrite info
def printCopywrite(f: TextIOWrapper):
    cwrite = ['/*\n',\
                 ' * Dargon Programming Language\n',\
                 ' * (C) Kyle Morris 2023 - See LICENSE.txt for license information\n',\
                 ' * \n',\
                 ' * FILE: Expr.h\n',\
                 ' * \n',\
                 ' * DESCRIPTION: Expressions.\n',\
                 ' * \n',\
                 ' * SINCE: v0.1\n',\
                 ' * \n',\
                 ' */ \n']
    f.writelines(cwrite)

def printIncludes(f: TextIOWrapper):
    f.write('#ifndef DARGON_EXPR_H\n')
    f.write('#define DARGON_EXPR_H\n\n')
    f.write('#include <string>\n\n')

# Prints the base class
def printBaseClass(f: TextIOWrapper, name: str):
    f.write('namespace dargon {\n\n')
    comment = ['\t/**\n',\
              '\t * @brief The base class of all Expressions.\n',\
              '\t *\n',\
              '\t*/\n'\
              ]
    f.writelines(comment)
    f.write(f'\tstruct {name} ')
    f.write('{ };\n\n')

def defineMembers(f: TextIOWrapper, fields: list[str]):
    for field in fields:
        vtype = field.strip().split()[0]
        vname = field.strip().split()[1]
        f.write(f'\t\tconst {vtype} {vname};\n')

# Creates a new subtype
def createExprSubclass(f: TextIOWrapper, base: str, name: str, fields: list[str]):
    f.write(f'\tstruct {name} : public {base} ')
    f.write('{\n\tpublic:\n')
    defineMembers(f, fields)
    f.write(f'\t\t{name}(')
    firsts = fields[:len(fields)-1]
    end = fields[len(fields)-1]
    #print(firsts)
    #print(end)
    # Build the constructor parameter list
    for field in firsts:
        vtype = field.strip().split()[0]
        vname = field.strip().split()[1]
        f.write(f'{vtype} {vname}, ')
    if end != []:
        vtype = end.strip().split()[0]
        vname = end.strip().split()[1]
        f.write(f'{vtype} {vname}')
    f.write(')\n\t\t: ')
    # Build the initializer list
    for field in firsts:
        vtype = field.strip().split()[0]
        vname = field.strip().split()[1]
        f.write(f'{vname}({vname}), ')
    if end != []:
        vtype = end.strip().split()[0]
        vname = end.strip().split()[1]
        f.write(f'{vname}({vname})')
    f.write('{}\n\t};\n')

# Prints the ending stuff
def printEnd(f: TextIOWrapper):
    f.write('\n};\n#endif')

### ------------###
### MAIN        ###
### ------------###

with open(fname, 'w') as fref:
    printCopywrite(fref)
    base = 'Expr'
    printIncludes(fref)
    printBaseClass(fref, base)
    for expr in exprs:
        name = expr.split(':')[0]
        fields = expr.split(':')[1].split(',')
        createExprSubclass(fref, base, name, fields)
        fref.write('\n')
    printEnd(fref)
