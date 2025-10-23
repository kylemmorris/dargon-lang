- H files describe interfaces, C files describe implementations (pretty standard)
- `#include`s will appear AFTER header guard, and in the following order:
	- Standard Library includes
	- External 3rd Party Library Includes
	- Source Includes
- C preprocessor stuff starts with `DRG`_
- Customizations outside the C preprocessor, e.g. functions, typedefs, and enumerations, start with `D_` and use `PascalCase`.
- Constants are fully capitalized
- Static-local variables start with an underscore
- Local variables use `camelCase`.

Example:
```c
#ifndef DRG_H_EXAMPLE
#define DRG_H_EXAMPLE

#include <stdio.h>
#include <stdlib.h>

#include <somelibrary.h>

#include "Token.h"

typedef enum {
	D_State_IDLE,
	D_State_RUNNING,
	D_State_STOP
} D_State;

typedef struct {
	D_State state;
	int number;
} D_MyStruct;

static const int D_CONSTANT = 12;

static D_MyStruct _staticVar;

void D_Fun(void) {
	int localVariable = 0;
}

#endif // DRG_H_EXAMPLE
```
