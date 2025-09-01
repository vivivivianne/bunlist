<h1 align=center>🐇BunList</h1> 
<p align=center>A simple c99 dynamic list implementation</p>
<div align=center>
  
  ![GitHub last commit](https://img.shields.io/github/last-commit/vivivivianne/bunlist?style=for-the-badge&labelColor=101418&color=9ccbfb)
  ![GitHub Repo stars](https://img.shields.io/github/stars/vivivivianne/bunlist?style=for-the-badge&labelColor=101418&color=b9c8da)
  ![GitHub repo size](https://img.shields.io/github/repo-size/vivivivianne/bunlist?style=for-the-badge&labelColor=101418&color=d3bfe6)

</div>

## ✅ Features:

- Insert, Append, Remove, Get and more.
- The header file is overly commented with the usage explained in it.
- Set a initial capacity to avoid unnecessary memory reallocations.
- Control array growth once it reaches max size (linear and geometric growth).
- `bunlist_exe(arr, func)` runs a function on all items of the array.
- `bunlist_free(arr)` destroys the array and calls callback function in each item if one is defined.
- +Array cloning functions that allow copying an array or creating an array of pointers to another array.

## 💾 Usage 

- To add to your project simply copy the headers and bunlist.c
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
