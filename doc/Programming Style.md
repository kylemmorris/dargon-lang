- Using `camelCase` notation
- Functions, etc. that shouldn't be used, but must be in the header, will start with `_drg`, e.g. `_drgLog()`, etc.
- Customizations via the C preprocessor will start with `DRG`, i.e. macros, header guards, and function-like macros. E.g. `DRG_DEBUG`
- Customizations outside the C preprocessor, e.g. functions, typedefs, and enumerations, will start with `drg`. E.g. `drgLog`, `drgToken`, etc.
- H files describe interfaces, C files describe implementations (pretty standard)
- `#include`s will appear AFTER header guard, and in the following order:
	- Standard Library includes
	- External 3rd Party Library Includes
	- Source Includes
```c
#ifndef DRG_H_EXAMPLE
#define DRG_H_EXAMPLE

#include <stdio.h>
#include <stdlib.h>

#include <somelibrary.h>

#include "token.h"

...

#endif // DRG_H_EXAMPLE
```
- ..
