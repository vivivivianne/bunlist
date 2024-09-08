#include "bunarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static i32 xsort(const void *p1, const void *p2);
static i32 ysort(const void *p1, const void *p2);
static i32 pfind(const void *p1, const void *p2);
static void printstuff(usize index, void *item);

typedef struct point {
	i32 x, y;
} point;

int main(void)
{
	printf("\n\n_________Initializing Array___________\n ");

	srand(time(0));
	bunarr *points = bunarr_create(sizeof(point), 16, NULL);

	printf("\n\n_________Testing bunarr_append()_________\n ");

	for (usize i = 0; i < points->cap; i++) {
		point p = { i, i + rand() % 200 };

		printf("\n Appending point[%lu] = {%d,%d}", i, p.x, p.y);
		bunarr_append(points, &p);
	}

	printf("\n\n_________Testing bunarr_get()_________\n ");

	for (usize i = 0; i < points->len; i++) {
		point *p = bunarr_get(points, i);
		printf("\nGet point[%lu] = {%d,%d}", i, p->x, p->y);
	}

	printf("\n\n_________Testing Removal___________\n ");

	bunarr_remove(points, 0);
	bunarr_remove(points, 5);
	bunarr_remove(points, 8);

	// Test errors by removing indexes > arr->len
	bunarr_remove(points, points->cap);
	bunarr_remove(points, 555);

	bunarr_remove(points, points->len);

	printf("\n\n_________Testing Execute_____________\n ");

	bunarr_exe(points, printstuff);

	printf("\n\n_________Testing Insertion_____________\n ");

	point np5 = { 99, 99 };
	point np6 = { 55, 55 };
	bunarr_insert(points, &np5, 0);

	// Test errors by inserting indexes > arr->len
	bunarr_insert(points, &np5, 5555);
	bunarr_insert(points, &np5, points->cap);

	bunarr_insert(points, &np5, points->len);

	bunarr_exe(points, printstuff);

	printf("\n\n__________Testing X Sorting and Searching__________\n");

	bunarr_qsort(points, xsort);
	bunarr_exe(points, printstuff);

	point key = { 99, 99 };
	point *result = bunarr_bsearch(points, &key, pfind);

	if (result != NULL) {
		printf("\nResult Point found: {%d,%d}", result->x, result->y);
	}

	printf("\n\n_____testing subarray pointer from 2->6(incl)_______\n");

	bunarr *subarr = bunarr_subarr(points, 2, 6, false);

	bunarr_exe(subarr, printstuff);

	printf("\n\n_____testing subarray clone from 4->10(incl)_________\n");

	bunarr *subarrcl = bunarr_subarr(points, 4, 10, false);
	bunarr_exe(subarrcl, printstuff);

	printf("\n\n_____testing insertions into cloned subarray_________\n");
	bunarr_insert(subarrcl, &np5, 0);
	bunarr_append(subarrcl, &np5);
	bunarr_exe(subarrcl, printstuff);
	fflush(stdout);

	printf("\n\n________Items after clear________\n");

	bunarr_clear(points);
	bunarr_exe(points, printstuff);

	printf("\n______freeing and exiting program______\n");
	bunarr_destroy(points);

	return 0;
}

static i32 xsort(const void *p1, const void *p2)
{
	return ((point *)p1)->x - ((point *)p2)->x;
}

static i32 ysort(const void *p1, const void *p2)
{
	return ((point *)p1)->y - ((point *)p2)->y;
}

static i32 pfind(const void *p1, const void *p2)
{
	return (((point *)p1)->y - ((point *)p2)->y);
}

static void printstuff(usize index, void *item)
{
	point *point0 = item;
	printf("\npoint[%lu] = {%d,%d}", index, point0->x, point0->y);
}
