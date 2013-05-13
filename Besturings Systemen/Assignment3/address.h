#define BLOCK_START 2
#define BLOCK_MAX_INDEX 0
#define ADDR_COUNT_INDEX 1

int block_is_used(long address);
long get_index(long last_index);
long set_address(long new_index, int used);
void remove_double_gaps(long *memory);
long get_free_space(long *memory);
long get_largest_gap(long *memory);
long get_number_of_holes(long *memory);