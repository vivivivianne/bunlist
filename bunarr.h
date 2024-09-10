#pragma once
#include "buntypes.h"

#define BARR_D_INCR 15
#define BARR_D_MULT false


typedef struct bunarr {
	void *items; 				/**< points to the start of the memory block where the items of the array are stored */
	usize isize; 				/**< the size of each item */
	usize len; 				/**< the number of items currently held by the array */
	usize cap; 				/**< the number of items the array can hold */
	u32 incr; 				/**< how much the list will be increased by when it reaches maxsize */
	bool mult; 				/**< percentage - if true the increase value will be used as a multiplyer of the array capacity: newcap = cap * (incr/10) */
	bool subarr; 				/**< set to true if this is a subarray */
	void (*free_fn)( usize i, void *itm); 	/**< NULL or function to be called on item removal */

} bunarr;

/** \brief creates an dynamic array 
 * \param isize The size in bytes of each item,
 * \param cap The initial capacity of the array,
 * \param free_fn NULL or a pointer to a callback function that's called on items when they are removed, meant to free other pointers contained in each item.
 * \returns bunarr the created array
 * \sa bunarr_create_ex */
bunarr *bunarr_create(usize isize, usize cap,
		      void (*free_fn)(usize i, void *itm));

/** \brief creates an dynamic array with but with extra arguments
 * \param isize the size in bytes of each item,
 * \param cap the initial capacity of the array
 * \param incr how much the array will grow / increase once  it's resized
 * \param mult if true the incr value will be used as a multiplyer of the array capacity: newcap = cap * (incr/10) 
 * \param subarr - if true this will be treated as a subarray, which means it will not allow memory reallocations 
 * \param free_fn NULL or a pointer to a callback function that's called on items when they are removed, meant to free other pointers contained in each item.
 * \returns bunarr the created array */
bunarr *bunarr_create_ex(usize isize, usize cap, u32 incr, bool mult,
			 bool subarr, void (*free_fn)(usize i, void *itm));

/** \brief Destroys the array, also calls the free_fn passed in bunarr_create in each item, if it's not NULL. 
 * \param arr array to be destroyed
 * \returns bool true if it worked, false if an error happened 
 * \sa bunarr_clear */
bool bunarr_destroy(bunarr *arr);

/** \brief Appends item to bunarr by copying 
 * \param arr array where itm will be appended to
 * \param itm item to be appended to array
 * \returns i index of the appended item */
usize bunarr_append(bunarr *arr, void *itm);

/** \brief Appends item to bunarr by copying, and then runs free(itm) 
 * \param arr array where itm will be appended to
 * \param itm item to be appended to array
 * \returns i index of the appended item */
usize bunarr_append_free(bunarr *arr, void *itm);

/** \brief inserts an item at index, works by dividing the array at index 
 * and moving the second half one item forward and then inserting in the created opening
 * \param arr the array where itm will be inserted into
 * \param *item - Pointer to the item we wish to insert.
 * \param i - index of insertion 
 * \returns bool true if it worked, false if an error happened */
bool bunarr_insert(bunarr *arr, void *item, usize i);

/** \brief same as bunarr_insert ,but runs free(itm) to free the original memory afterwards 
 * \param arr the array where itm will be inserted into
 * \param *item - Pointer to the item we wish to insert.
 * \param i - index of insertion 
 * \returns bool true if it worked, false if an error happened */
bool bunarr_insert_free(bunarr *arr, void *itm, usize i);

/** \brief removes item i from the array 
 * \param i the index of the item we wish to remove. 
 * \returns bool True if it worked, false if an error happened */
bool bunarr_remove(bunarr *arr, usize i);
/** \brief lazy remove, copys last item into the index and reduces the list size 
 * \param arr the array where i will be removed
 * \param i the index of the item we wish to remove. 
 * \returns bool if true it worked, if false an error happened */
bool bunarr_remove_lazy(bunarr *arr, usize i);

/** \brief Clears the array by setting everything to 0 
 * \param arr the array to be cleared*/
bool bunarr_clear(bunarr *arr);

/** \brief Get a void pointer the item of the given index from the array 
 * \param arr the array we will get the item from
 * \param i the item's index
 * \returns ptr to array item */
void *bunarr_get(bunarr *arr, usize i);

/** \brief copy src array to dst array 
 * \param dst_arr the destination array were data will be copied into 
 * \param src_arr the array were data will be copied from */
void bunarr_cpy(bunarr *dst_arr, bunarr *scr_arr);

/** \brief clones the src array and returns the new dst array 
 * \param src_array array to be cloned 
 * \returns ptr arr new array */
bunarr *bunarr_clone(bunarr *src_arr);

/** \brief Loops trough the array and executes the given function on every item, 
 * also passes the index to the function 
 * \param arr the array that will be parsed 
 * \param function the function that will be executed in every item of the array */
void bunarr_exe(bunarr *arr, void (*function)(usize i, void *itm));

/** \brief runs bsearch on the array and returns the requested key, ensure the array is sorted properly
 * \param key the desired item you want to find
 * \param compar_fn_t comparison function
 * \returns ptr a pointer to the found item, or NULL if nothing that matches the key was found. */
void *bunarr_bsearch(bunarr *arr, void *key,
		     i32 (*fn)(const void *, const void *));

/** \brief Runs quick sort on the array using the given compare function
 * \param arr array to be sorted
 * \param fn function that receives pointers to two items of the arr and returns the result of the comparison */
void bunarr_qsort(bunarr *arr, i32 (*fn)(const void *, const void *));

/** \brief creates a subarray from the given array, optionally clone it instead of creating a pointer 
 * \param arr source for the creation of the subarray
 * \param start starting point of the subarray 
 * \param end end point of the subarray 
 * \param clone if true it returns an subarray with a copy of a portion of memory of the original array, 
 * if false it returns an array of pointers to items of the original array 
 * \returns subarr a pointer to the created subarray */
bunarr *bunarr_subarr(bunarr *arr, usize start, usize end, bool clone);
