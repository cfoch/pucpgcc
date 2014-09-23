typedef int (* CmpFunc) (int, int);

#define cmp_int_a_le_b ()

void LOG_ARRAY_INT (int * array, unsigned int len);
static void int_swap (int * a, int * b);
void array_int_selection_sort (int * array, unsigned int len, CmpFunc cmp_fun);
void array_int_merge_sort (int * array, unsigned int len, CmpFunc cmp_fun);
int array_int_is_asc (int * array, unsigned len);
int array_int_is_desc (int * array, unsigned len);
int * array_int_copy (int * array, unsigned int len);
int array_int_count_element (int * array, unsigned len, int element);
int cmp_int_a_func (int a, int b);
int cmp_int_b_func (int a, int b);
