#pragma once
#include "buntypes.h"

typedef struct bunlist {
	void *items; /**< points to the start of the memory block where the items of the list are stored */
	usize isize; /**< the size of each item */
	usize len; /**< the number of items currently held by the list */
	usize cap; /**< the number of items the list can hold */
	u32 incr; /**< how much the list will be increased by when it reaches maxsize */
	bool mult; /**< percentage - if true the increase value will be used as a multiplyer of the list capacity: newcap = cap * (incr/10) */
	bool sublist; /**< set to true if this is a sublist */
	void (*free_fn)(
		usize i,
		void *itm); /**< NULL or function to be called on item removal */

} bunlist;

/** \brief creates a dynamic list 
 * \param isize The size in bytes of each item,
 * \param cap The initial capacity of the list,
 * \param free_fn NULL or a pointer to a callback function that's called on items when they are removed, meant to free other pointers contained in each item.
 * \returns bunlist the created list
 * \sa bunlist_create_ex */
bunlist *bunlist_create(usize isize, usize cap,
			void (*free_fn)(usize i, void *itm));

/** \brief creates an dynamic list with but with extra arguments
 * \param isize the size in bytes of each item,
 * \param cap the initial capacity of the list
 * \param incr how much the list will grow / increase once  it's resized
 * \param mult if true the incr value will be used as a multiplyer of the list capacity: newcap = cap * (incr/10) 
 * \param subarr - if true this will be treated as a sublist, which means it will not allow memory reallocations 
 * \param free_fn NULL or a pointer to a callback function that's called on items when they are removed, meant to free other pointers contained in each item.
 * \returns bunlist the created list */
bunlist *bunlist_create_ex(usize isize, usize cap, u32 incr, bool mult,
			   bool subarr, void (*free_fn)(usize i, void *itm));

/** \brief Destroys the list, also calls the free_fn passed in bunlist_create in each item, if it's not NULL. 
 * \param arr list to be destroyed
 * \returns bool true if it worked, false if an error happened 
 * \sa bunlist_clear */
bool bunlist_destroy(bunlist *arr);

/** \brief Appends item to bunlist by copying 
 * \param arr list where itm will be appended to
 * \param itm item to be appended to list
 * \returns i index of the appended item */
usize bunlist_append(bunlist *arr, void *itm);

/** \brief Appends item to bunlist by copying, and then runs free(itm) 
 * \param arr list where itm will be appended to
 * \param itm item to be appended to list
 * \returns i index of the appended item */
usize bunlist_append_free(bunlist *arr, void *itm);

/** \brief inserts an item at index, works by dividing the list at index 
 * and moving the second half one item forward and then inserting in the created opening
 * \param arr the list where itm will be inserted into
 * \param *item - Pointer to the item we wish to insert.
 * \param i - index of insertion 
 * \returns bool true if it worked, false if an error happened */
bool bunlist_insert(bunlist *arr, void *item, usize i);

/** \brief same as bunlist_insert ,but runs free(itm) to free the original memory afterwards 
 * \param arr the list where itm will be inserted into
 * \param *item - Pointer to the item we wish to insert.
 * \param i - index of insertion 
 * \returns bool true if it worked, false if an error happened */
bool bunlist_insert_free(bunlist *arr, void *itm, usize i);

/** \brief removes item i from the list 
 * \param i the index of the item we wish to remove. 
 * \returns bool True if it worked, false if an error happened */
bool bunlist_remove(bunlist *arr, usize i);
/** \brief lazy remove, copys last item into the index and reduces the list size 
 * \param arr the list where i will be removed
 * \param i the index of the item we wish to remove. 
 * \returns bool if true it worked, if false an error happened */
bool bunlist_remove_lazy(bunlist *arr, usize i);

/** \brief Clears the list by setting everything to 0 
 * \param arr the list to be cleared*/
bool bunlist_clear(bunlist *arr);

/** \brief Get a void pointer the item of the given index from the list 
 * \param arr the list we will get the item from
 * \param i the item's index
 * \returns ptr to list item */
void *bunlist_get(bunlist *arr, usize i);

/** \brief copy src list to dst list 
 * \param dst_arr the destination list were data will be copied into 
 * \param src_arr the list were data will be copied from */
void bunlist_cpy(bunlist *dst_arr, bunlist *scr_arr);

/** \brief clones the src list and returns the new dst list 
 * \param src_list list to be cloned 
 * \returns ptr arr new list */
bunlist *bunlist_clone(bunlist *src_arr);

/** \brief Loops trough the list and executes the given function on every item, 
 * also passes the index to the function 
 * \param arr the list that will be parsed 
 * \param function the function that will be executed in every item of the list */
void bunlist_exe(bunlist *arr, void (*function)(usize i, void *itm));

/** \brief runs bsearch on the list and returns the requested key, ensure the list is sorted properly
 * \param key the desired item you want to find
 * \param compar_fn_t comparison function
 * \returns ptr a pointer to the found item, or NULL if nothing that matches the key was found. */
void *bunlist_bsearch(bunlist *arr, void *key,
		      i32 (*fn)(const void *, const void *));

/** \brief Runs quick sort on the list using the given compare function
 * \param arr list to be sorted
 * \param fn function that receives pointers to two items of the arr and returns the result of the comparison */
void bunlist_qsort(bunlist *arr, i32 (*fn)(const void *, const void *));

/** \brief creates a sublist from the given list, optionally clone it instead of creating a pointer 
 * \param arr source for the creation of the sublist
 * \param start starting point of the sublist 
 * \param end end point of the sublist 
 * \param clone if true it returns an sublist with a copy of a portion of memory of the original list, 
 * if false it returns an list of pointers to items of the original list 
 * \returns subarr a pointer to the created sublist */
bunlist *bunlist_subarr(bunlist *arr, usize start, usize end, bool clone);
