#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "mem_alloc.h"
#include "address.h"

static long *memory;

void mem_init(long mem[MEM_SIZE])
{
   memory = mem;

   memory[BLOCK_MAX_INDEX] = MEM_SIZE;
   memory[ADDR_COUNT_INDEX] = 0;

   memory[BLOCK_START] = memory[BLOCK_MAX_INDEX];
   memory[memory[BLOCK_MAX_INDEX]] = memory[BLOCK_MAX_INDEX] | 1 << 31;
   printf("%ld\n", memory[BLOCK_MAX_INDEX]);
}

long mem_get(long request)
{
   if(request < 1)
   {
      return -1;
   }

   long index, new_index;
   index = BLOCK_START;
   while(1)
   {
      if(block_is_used(memory[index]) == 0)
      {
         if(request < (get_index(memory[index]) - index))
         {
            new_index = index + request + 1;
            if(new_index < memory[BLOCK_MAX_INDEX])
            {
               memory[new_index] = memory[index];
               memory[index] = set_address(new_index, 1);
               return index + 1;          
            }
         }
      }

      index = get_index(memory[index]);
      if(index == memory[BLOCK_MAX_INDEX])
      {
         return -1;
      }
   }
}

void mem_free(long index)
{
   if(index >= 3)
   {
      memory[index - 1] = set_address(memory[index - 1], 0);
      remove_double_gaps(memory);
   }
}

void mem_available(long *empty, long *large, long *n_holes)
{
   *empty = get_free_space(memory);
   *large = get_largest_gap(memory);
   *n_holes = get_number_of_holes(memory);
}

void mem_exit()
{
   printf("exit\n");
}
