# 🐇BunArr - A simple c99 dynamic array implementation


## ✅ Features and Usage:
- The code is overly commented with the usage explained in it.
- Set a initial capacity to avoid unnecessary memory reallocations.
- Control array growth once it reaches max size (linear and geometric progression).
- use bunarr_exe() to run a function on all the items of the array.
- bunarr_free() destroys the array.
- to use simply copy the headers and bunarr.c


## ⚠️  Caveats:

- Not made with double pointers in mind, might not work.
- it also requires buntypes.h which is what i personally use for types.
- The current insert implementation does not allow inserting things that are outside of the array length.
This means you should use insert only to insert between things that are already in the list.

## 🗒️ Todo:
- Clear reduntant code into less functions
