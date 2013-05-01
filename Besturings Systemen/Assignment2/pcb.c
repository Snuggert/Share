#include <stdlib.h>

#include "schedule.h"
#include "pcb.h"

 // Remove a PCB from the linked list, then return the start of the linked list 
pcb *pcb_remove(pcb *item) 
{
	pcb *next, *new_start;
	if (item == NULL)
	{
		return NULL;
	}
	if (item->next == NULL) {
		new_start = item->prev;
		item->prev = NULL;

		if(new_start)
		{
			new_start->next = NULL;
		}

		return new_start;
	}
	else
	{
		next = item->next;
		next->prev = item->prev;
			if (item->prev)
			{
				item->prev->next = next;
			}
		// remove links to linked list.
		item->next = item->prev = NULL;
	}

	return find_start(next);
}

// Get the item in the linked list after the item PCB struct.
pcb *pcb_next(pcb *item) 
{
	if (item == NULL)
	{
		return NULL;
	}

	return item->next;
}

// Get the item in the linked list before the item PCB struct.
pcb *pcb_prev(pcb *item) 
{
	if (item == NULL)
	{
		return NULL;
	}

	return item->prev;
}

// return the memory needed by a PCB.
long get_mem_need(pcb *item) 
{
	if (item == NULL)
	{
		return -1;
	}

	return item->MEM_need;
}

 // set the memory base of the item PCB struct. 
int set_mem_base(pcb *item, long MEM_base) {
	if (item == NULL)
	{
		return -1;
	}

	item->MEM_base = MEM_base;
	return 0;
}


pcb *find_start(pcb *item) 
{
	if (item == NULL)
	{
		return NULL;
	}

	while (item->prev)
	{
		item = pcb_prev(item);
	}

	return item;
}

pcb *find_end(pcb *item) 
{
	if (item == NULL)
	{
		return NULL;
	}

	while (item->next)
	{
		item = pcb_next(item);
	}

	return item;
}

pcb *insert_after(pcb *item, pcb *after) 
{
	if (item == NULL)
	{
		return NULL;
	}

	if (after == NULL)
	{
		return NULL;
	}

	item->next = after->next;
	after->next = item;

	if (item->next)
		item->next->prev = item;

	item->prev = after;

	return find_start(item);
}