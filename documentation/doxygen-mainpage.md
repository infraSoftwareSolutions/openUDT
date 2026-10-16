# openUDT

openUDT (Open Unique Data Types) is a collection of reusable C++ data types.
The public headers are under `include/`; include `udt.hpp` to make the
library's aggregate header available, or include a narrower module header.

## Getting started

Add `include/` to your compiler's header search path and include the aggregate
header:

```cpp
#include <udt.hpp>
```

For projects that only need one family of types, include its header instead,
for example `udt/bfs.hpp` or `udt/multidimensional.hpp`. Consult each type's
reference page for its namespace, operations, and any type-specific
requirements.

## Library modules

| Header | Contents |
| --- | --- |
| `udt/bfs.hpp` | Fixed-width binary flag containers: `bfs_8`, `bfs_16`, `bfs_32`, and `bfs_64`. |
| `udt/dynamic.hpp` | Dynamic-value types with different storage and ownership models. |
| `udt/int.hpp` | Extended-width signed and unsigned integer types. |
| `udt/multidimensional.hpp` | One-, two-, and three-dimensional vector containers. |
| `udt/pair.hpp` | Pair-like value types. |
| `udt/string.hpp` | String types and string operations. |
| `udt/tree.hpp` | Binary, ternary, and multi-branch tree types. |
| `udt/triple.hpp` | Triple-like value types. |
| `udt/virtual.hpp` | Fixed-width virtual pointer types and virtual-machine declarations. |
| `udt/net.hpp` | The templated `net<T>` neighbor-network type. |

Most types are declared in the `udt` namespace. The reference pages show the
declaring namespace for each symbol; `net<T>` is currently declared at global
scope.

## API reference

The reference below is generated from the public headers. The detailed pages
include the declarations and any Doxygen comments present beside them.

See the [README](../README.md) for project background.
