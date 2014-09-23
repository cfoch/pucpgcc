#include <stdio.h>
#include <stdlib.h>
#include "pucpgccutils.h"

void
LOG_ARRAY_INT (int * array, unsigned int len)
{
  int i;
  printf ("LOG_ARRAY_INT: \n\t");
  for (i = 0; i < len; i++) {
    printf ("%d ", array[i]);
    if (i > 0 && i % 10 == 0)
      printf ("\n\t");
  }
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

int
cmp_int_a_func (int a, int b)
{
  return a - b;
}

int
cmp_int_b_func (int a, int b)
{
  return b - a;
}

void
array_int_selection_sort (int * array, unsigned int len, CmpFunc cmp_func)
{
  int i, j, min_index;
  for (i = 0; i < len - 1; i++) {
    min_index = i;
    for (j = i + 1; j < len; j++)
      if (cmp_func (array[j], array[min_index]) < 0)
        min_index = j;
    int_swap (&array[i], &array[min_index]);
  }
}


static void
_merge (int * array, int start_index, int middle_index, int end_index,
    CmpFunc cmp_func)
{
  int left_start_index, left_end_index, right_start_index, right_end_index;
  int l, r, i, k;
  int helper_array_len;
  int *helper_array;

  left_start_index = start_index;
  left_end_index = middle_index;
  right_start_index = middle_index + 1;
  right_end_index = end_index;

  helper_array_len = end_index - start_index + 1;
  helper_array = malloc (helper_array_len * sizeof (int));


  l = left_start_index;
  r = right_start_index;
  i = 0;

  while ((l <= left_end_index) && (r <= right_end_index)) {
    if (cmp_func (array[l], array[r]) >= 0) {
      helper_array[i] = array[r];
      r++;
    }
    else {
      helper_array[i] = array[l];
      l++;      
    }
    i++;
  }

  while (l <= left_end_index)
    helper_array[i++] = array[l++];

  while (r <= right_end_index)
    helper_array[i++] = array[r++];

  for (i = 0; i < helper_array_len; i++)
    array[i + start_index] = helper_array[i];

  free (helper_array);
}

static void
_array_int_merge_sort (int * array, unsigned int len, int start_index,
    int end_index, CmpFunc cmp_func)
{
  int middle_index;

  if (start_index >= end_index)
    return;

  middle_index = (end_index + start_index) / 2;
  _array_int_merge_sort (array, len, start_index, middle_index, cmp_func);
  _array_int_merge_sort (array, len, middle_index + 1, end_index, cmp_func);
  _merge (array, start_index, middle_index, end_index, cmp_func);
}

void
array_int_merge_sort (int * array, unsigned len, CmpFunc cmp_func)
{
  _array_int_merge_sort (array, len, 0, len - 1, cmp_func);
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

int
array_int_is_desc (int * array, unsigned len)
{
  int i;
  for (i = 0; i < len - 1; i++)
    if (array[i] < array[i + 1])
      return 0;
  return 1;
}

int *
array_int_copy (int * array, unsigned int len)
{
  int i, *ret = malloc (len * sizeof (int));

  for (i = 0; i < len; i++)
    ret[i] = array[i];
  return ret;
}

int
array_int_count_element (int * array, unsigned len, int element)
{
  int i, ret = 0;
  for (i = 0; i < len; i++)
    if (array[i] == element)
      ret++;
  return ret;
}


