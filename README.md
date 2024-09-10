# 🐇BunArr
A simple c99 dynamic array implementation

## ✅ Features:

- Insert, Append, Remove, Get and more.
- The header file is overly commented with the usage explained in it.
- Set a initial capacity to avoid unnecessary memory reallocations.
- Control array growth once it reaches max size (linear and geometric growth).
- `bunarr_exe(arr, func)` runs a function on all items of the array.
- `bunarr_free(arr)` destroys the array and calls callback function in each item if one is defined.
- +Array cloning functions that allow copying an array or creating an array of pointers to another array.

## 💾 Usage 

- To add to your project simply copy the headers and bunarr.c
- For examples see [tests.c](tests.c)

## ⚠️  Caveats:

- Not made with double pointers in mind, might not work.
- it also requires buntypes.h which is what i personally use for types.
- The current insert implementation does not allow inserting things that are outside of the array length.
This means you should use insert only to insert between things that are already in the list.

## 🗒️ Todo:

- Consider improving inserting functionality
- Proper error handling
- Generate docs with doxygen???
