#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "pucpgccutils.h"


/* colors */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_SUCCESS  (ANSI_COLOR_GREEN "SUCCESS" ANSI_COLOR_RESET)
#define PRINT_FAIL    (ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET)

#define randomtest(msg, expr) do { expr ? printf ("%s: %s\n", msg, PRINT_SUCCESS): \
                                   printf ("%s: %s\n", msg, PRINT_FAIL); } while (0)


static int
compare_same_elements (int * a, int * b, int len)
{
  int i;

  for (i = 0; i < len; i++) {
    if (array_int_count_element (a, len, a[i]) !=
        array_int_count_element (b, len, a[i]))
      return 0;
  }
  return 1;
}

/*
  test_array_int_create_random:
  creates a random array of integer of size 10

  TODO: Try negative values.

  returns: new allocated array of integer
*/

// APLICABLE SOLO PARA MERGE SORT & SELECTION SORT
int *
test_array_int_create_random (int len)
{
  int i;
  int *array;

  /* len = rand () % 100 + 1; */
  /* This is arbitrary */

  array = malloc ((len + 1) * sizeof (int));
  for (i = 0; i < len; i++) {
    /* Random numbers between 1 and 100 */
    array[i] = rand ();
  }
  return array;
}

// APLICABLE SOLO PARA BIT-INDEX SORT
static int *
test_array_int_create_random_non_repeated (int len)
{
  int i, element;
  int *array;

  /* *len = rand () % 100 + 1; */
  /* This is arbitrary */

  array = malloc (len * sizeof (int));

  for (i = 0; i < len; i++) {
    /* This <rand () % (len * 5) + 1)> is arbitrary */
    while ((element = rand () % (len * 5) + 1) &&
        array_int_count_element (array, i + 1, element) != 0);
    array[i] = element;
  }
  return array;
}

static int
test_sort_asc (void (* sort_func) (int *, unsigned int, CmpFunc), int len)
{
  int *array, *b;
  clock_t start;
  double time_sort;
  int asc = 1, same_elements = 1;

  printf ("INPUT:\n\t");
  array = test_array_int_create_random (len);
  //b = array_int_copy (array, len);

  LOG_ARRAY_INT (array, len);

  start = clock();
  sort_func (array, len, cmp_int_a_func);
  time_sort = ((double) clock() - start) / CLOCKS_PER_SEC;
  LOG_ARRAY_INT (array, len);
  /*
  asc = array_int_is_asc (array, len);
  same_elements = compare_same_elements (array, b, len);

  randomtest ("\tArray is ascending", asc);
  randomtest ("\tArray has same elements that sorted array", same_elements);

  free (b);
  */
  free (array);

  printf ("\tTime Sort: %f\n", time_sort);
  return asc && same_elements;
}

static int
test_sort_desc (void (* sort_func) (int *, unsigned int, CmpFunc), int len)
{
  int *array, *b;
  int desc = 1, same_elements = 1;
  clock_t start;
  double time_sort;

  printf ("INPUT:\n\t");
  array = test_array_int_create_random (len);
  //b = array_int_copy (array, len);

  LOG_ARRAY_INT (array, len);

  printf ("OUTPUT:\n\t");

  start = clock();
  sort_func (array, len, cmp_int_b_func);
  time_sort = ((double) clock() - start) / CLOCKS_PER_SEC;
  LOG_ARRAY_INT (array, len);
  /*
  desc = array_int_is_desc (array, len);
  same_elements = compare_same_elements (array, b, len);

  randomtest ("\tArray is descending", desc);
  randomtest ("\tArray has same elements that sorted array", same_elements);


  free (b);
  */
  free (array);
  printf ("\tTime Sort: %f\n", time_sort);
  return desc && same_elements;
}

static int
test_sort_bit_index (int asc, int len)
{
  int *array, *b;
  int desc = 1, same_elements = 1;
  clock_t start;
  double time_sort;

  printf ("INPUT:\n\t");
  array = test_array_int_create_random_non_repeated (len);
  assert (array_int_duplicated_elements (array, len) == 0);
  b = array_int_copy (array, len);

  LOG_ARRAY_INT (array, len);

  printf ("OUTPUT:\n\t");

  start = clock();
  array_int_bit_index_sort (array, len, asc);
  time_sort = ((double) clock() - start) / CLOCKS_PER_SEC;
  LOG_ARRAY_INT (array, len);
  desc = array_int_is_desc (array, len);
  same_elements = compare_same_elements (array, b, len);

  randomtest ("\tArray is descending", desc);
  randomtest ("\tArray has same elements that sorted array", same_elements);


  free (b);
  free (array);
  printf ("\tTime Sort: %f\n", time_sort);
  return desc && same_elements;
}

static void
show_help ()
{
  printf ("-help\n\tDisplay help\n");
  printf ("\n");
  printf ("-selection-sort\n\tTest the selection sort algorithm with random values\n");
  printf ("-merge-sort\n\tTest the merge sort algorithm with random values\n");
  printf ("-asc\n\tSort ascending.\n");
  printf ("-desc\n\tSort descending.\n");
}

int
main (int argc, char ** argv)
{
  srand (time (NULL));
  int len = atoi (argv[3]);

  printf ("%d\n", len);

  if (!argv[1] || strcmp ("-help", argv[1]) == 0) {
    show_help ();
  } else if (strcmp ("-selection-sort", argv[1]) == 0) {
    if (!argv[2]) {
      show_help ();
    } else if (strcmp ("-asc", argv[2]) == 0) {
      randomtest ("Selection Sort: ", test_sort_asc (array_int_selection_sort, len));
    } else if (strcmp ("-desc", argv[2]) == 0) {
      randomtest ("Selection Sort: ", test_sort_desc (array_int_selection_sort, len));
    } else
      show_help ();
  } else if (strcmp ("-merge-sort", argv[1]) == 0) {
    if (!argv[2]) {
      show_help ();
    } else if (strcmp ("-asc", argv[2]) == 0) {
      randomtest ("Merge Sort: ", test_sort_asc (array_int_merge_sort, len));
    } else if (strcmp ("-desc", argv[2]) == 0) {
      randomtest ("Merge Sort: ", test_sort_desc (array_int_merge_sort, len));
    } else
      show_help ();
  } else if (strcmp ("-bit-index-sort", argv[1]) == 0) {
    if (!argv[2]) {
      show_help ();
    } else if (strcmp ("-asc", argv[2]) == 0) {
      randomtest ("Bit index Sort: ", test_sort_bit_index (1, len));
    } else if (strcmp ("-desc", argv[2]) == 0) {
      randomtest ("Bit index Sort: ", test_sort_bit_index (-1, len));
    } else
      show_help ();
  } else
    show_help ();

  return 1;
}
