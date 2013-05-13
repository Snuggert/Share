/*
 * File: next-fit.c
 * 
 * This file contains a memory management application implementing the best-fit algorithm.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 28-04-2013
 */
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
   long index, new_index, best_fit, difference, last_diff;
   printf("request:%ld\n", request);
   if(request < 1)
   {
      return -1;
   }

   index = BLOCK_START;
   difference = memory[BLOCK_MAX_INDEX];
   best_fit = 0;

   while(1)
   {
      if(block_is_used(memory[index]) == 0)
      {
         last_diff = get_index(memory[index]) - index - request;
         if(request < (get_index(memory[index]) - index) && last_diff < difference && last_diff > 0)
         {
            best_fit = index;
            difference = last_diff;
         }
      }
      index = get_index(memory[index]);
      if(index >= memory[BLOCK_MAX_INDEX])
      {
         break;
      }
   }
   if(difference == memory[BLOCK_MAX_INDEX] && best_fit == 0)
   {
      return -1;
   }
   else
   {
      new_index = best_fit + request + 1;
      if(new_index < memory[BLOCK_MAX_INDEX])
      {
         memory[new_index] = memory[best_fit];
         memory[best_fit] = set_address(new_index, 1);
         printf("difference:%ld best_index:%ld\n", difference, best_fit);
         return best_fit + 1;          
      }
      else
      {
         return -1;
      }
   }
}

void mem_free(long index)
{
   printf("remove:%ld\n", index-1);
   if(index > BLOCK_START)
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
