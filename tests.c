#include <time.h>
#include "bunarr.h"

static i32 xsort(const void *p1, const void *p2);
static i32 ysort(const void *p1, const void *p2);
static i32 pfind(const void *p1, const void *p2);
void printstuff(usize index, void *item);

typedef struct point {
	i32 x, y;
} point;

int main(int argc, char *argv[])
{
	srand(time(0));
	bunarr *points = bunarr_create_ex(sizeof(point), 10, 15, true, false);
	for (i32 i = 0; i < 16; i++) {
		point p = { i, i + rand() % 200 };

		bunarr_append(points, &p);
	}

	bunarr_exe(points, printstuff);

	printf("\n_________Testing Deletion___________\n ");
	bunarr_remove(points, 0);

	bunarr_remove(points, 5);

	bunarr_remove(points, 8);
	bunarr_remove(points, points->cap);

	bunarr_remove(points, 555);

	bunarr_remove(points, points->len);

	printf("\n_________Testin Insertion_____________\n ");
	point np5 = { 99, 99 };
	bunarr_insert(points, &np5, 0);
	bunarr_insert(points, &np5, 5555);
	bunarr_insert(points, &np5, points->len);
	bunarr_append(points, &np5);

	point *np99 = bunarr_get(points, 99);

	bunarr_qsort(points, xsort);
	// qsort(points->items, points->len, points->isize, ysort);
	bunarr_exe(points, printstuff);

	printf("\n\n________testing bsort key=99__________\n");

	bunarr_qsort(points, ysort);
	point key = { 99, 99 };
	point *result = bunarr_bsearch(points, &key, pfind);
	if (result != NULL) {
		printf("\nResult Point found: {%d,%d}", result->x, result->y);
	}

	bunarr_qsort(points, xsort);
	printf("\n\n_____testing subarray pointer from 2->6(incl)_______\n");
	bunarr *subarr = bunarr_subarr(points, 2, 6, false);
	bunarr_exe(subarr, printstuff);

	printf("\n\n_____testing subarray clone from 4->10(incl)_________\n");
	bunarr *subarrcl = bunarr_subarr(points, 4, 10, false);
	bunarr_insert(subarrcl, &np5, 0);
	bunarr_append(subarrcl, &np5);
	bunarr_exe(subarrcl, printstuff);

	fflush(stdout);

	bunarr_clear(points);

	printf("\n________Items after clear________\n");
	bunarr_exe(points, printstuff);
	printf("\n______freeing and exiting program______\n");
	bunarr_free(points);
	return 0;
}

static i32 xsort(const void *p1, const void *p2)
{
	return ((point *)p1)->x - ((point *)p2)->x;
};

static i32 ysort(const void *p1, const void *p2)
{
	return ((point *)p1)->y - ((point *)p2)->y;
};

static i32 pfind(const void *p1, const void *p2)
{
	return (((point *)p1)->y - ((point *)p2)->y);
};

void printstuff(usize index, void *item)
{
	point *point0 = item;
	printf("\npoint[%lu] = {%d,%d}", index, point0->x, point0->y);
}
