#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "minunit.h"

#define ARRAY_INT_MAX		10000

int tests_run = 0;

void
LOG_ARRAY_INT (int * array, unsigned int len)
{
  int i;
  printf ("LOG_ARRAY_INT: ");
  for (i = 0; i < len; i++)
    printf ("%d ", array[i]);
  printf ("\n");
}

static void
int_swap (int * a, int * b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void
array_int_sort_selection_asc (int * array, unsigned int len)
{
  int i, j, min;
  for (i = 0; i < len - 1; i++) {
    min = i;
    for (j = i + 1; j < len; j++)
      if (array[j] < array[i])
        min = j;
    int_swap (&array[i], &array[min]);
  }
}

int *
test_array_int_create_random (int * len)
{
  int i;
  int *array;
  srand (time (NULL));

  *len = rand () % 100 + 1;

  assert (*len >= 0);

  array = malloc (*len * sizeof (int));
  for (i = 0; i < *len; i++) {
    srand (time (NULL));
    array[i] = rand () % 100 + 1;
  }
  return array;
}

int
array_int_is_asc (int * array, unsigned len)
{
  int i;
  for (i = 0; i < len - 1; i++)
    if (array[i] > array[i + 1])
      return 0;
  return 1; 
}

static char *
test_array_int_sort_selection_asc ()
{
  int a[] = {3, 2, 1, 0};
  int b[] = {0, 1, 2, 3};
  int c[] = {0, -1, -2, -3};
  int d[] = {8};
  int first_d;

  array_int_sort_selection_asc (a, 4);
  mu_assert ("Error sorting {3, 2, 1, 0}.\n", array_int_is_asc (a, 4));

  array_int_sort_selection_asc (b, 4);
  mu_assert ("Error sorting {0, 1, 2, 3}.\n", array_int_is_asc (b, 4));

  array_int_sort_selection_asc (c, 4);
  mu_assert ("Error sorting {0, -1, -2, -3}.\n", array_int_is_asc (c, 4));

  first_d = d[0];
  array_int_sort_selection_asc (d, 1);
  mu_assert ("Error sorting {8}.\n", first_d == d[0]);

  return 0;
}

static char *
all_tests ()
{
  mu_run_test (test_array_int_sort_selection_asc);
  return 0;
}

int
main (int argc, char ** argv)
{
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);
 
  return result != 0;
}
