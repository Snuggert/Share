#include <stdio.h>
#include <math.h>

#include "address.h"

int block_is_used(long address)
{
	/* Turn off all irrelevant bits. */
	address = address & (long)pow(2, 31);

	/* Move the bit the the 1st place. */
	address = address >> 31;
	return (int)address;
}

long get_index(long last_index)
{
	long index, mask;
	mask = (long)pow(2, 31) - 1;

	index = last_index & mask;

	return index;
}

long set_address(long new_index, int used)
{
	long used_mask, address;

	used_mask = used & 1;
	used_mask = used_mask << 31;

	new_index = get_index(new_index);

	address = new_index | used_mask;

	return address;
}

/* function to merge two empty gaps if they are next to each other. */
void remove_double_gaps(long *memory)
{
	long index;
	index = BLOCK_START;
	while(1)
	{
		if(block_is_used(memory[index]) == 0 && block_is_used(memory[get_index(memory[index])]) == 0)
		{
			memory[index] = set_address(memory[get_index(memory[index])], 0); 
			/* to take care of a removal between to empty gaps. */
			remove_double_gaps(memory);
			break;
		}

		index = get_index(memory[index]);
		if(index >= memory[BLOCK_MAX_INDEX])
		{
			break;
		}
	}
}

/* function to get the amount of free space in the memory. */
long get_free_space(long *memory)
{
	long empty, index;
	empty = 0;
	index = BLOCK_START;
	while(1)
	{
		if(block_is_used(memory[index]) == 0)
		{
			empty += memory[index] - index;
		}
		index = get_index(memory[index]);
		if(index >= memory[BLOCK_MAX_INDEX])
		{
			break;
		}
	}
	return empty;
}

/* function to get the largest gap in the memory. */
long get_largest_gap(long *memory)
{
	long largest, index;
	largest = 0;
	index = BLOCK_START;
	while(1)
	{
		if(block_is_used(memory[index]) == 0)
		{
			if(memory[index] - index > largest)
			{
				largest = memory[index] - index;
			}
		}
		index = get_index(memory[index]);
		if(index >= memory[BLOCK_MAX_INDEX])
		{
			break;
		}
	}
	return largest;
}

/* function to get the number of memory blocks in the memory. */
long get_number_of_holes(long *memory)
{
	long holes, index;
	holes = 0;
	index = BLOCK_START;
	while(1)
	{
		holes ++;
		index = get_index(memory[index]);
		if(index >= memory[BLOCK_MAX_INDEX])
		{
			break;
		}
	}
	return holes;
}