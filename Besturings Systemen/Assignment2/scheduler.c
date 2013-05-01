/*
 * File: scheduler.c
 * 
 * This file contains a scheduler implementaion made for the course Operating Systems @ UvA
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 28-04-2013
 */

#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"
#include "pcb.h"
#include "mem_alloc.h"
#include "scheduler.h"

/* This variable will simulate the allocatable memory */
static long memory[MEM_SIZE];

/* The actual CPU scheduler is implemented here */

static void CPU_scheduler()
{
    /* Insert the code for a MLFbQ scheduler here */
}

/* The high-level memory allocation scheduler is implemented here */
static void GiveMemory()
{
    int index;
    long MEM_need, mem_base;
    pcb *proc, *ready_end;

    proc = new_proc;

    if(proc == NULL)
    {
        return;
    }
    MEM_need = get_mem_need(proc);

    if (MEM_need == -1)
    {
        return;
    }

    mem_base = mem_get(MEM_need);
    if (mem_base == -1)
    {
        return; 
    }

    set_mem_base(proc, mem_base);

    new_proc = pcb_remove(proc);
    ready_end = find_end(ready_proc);

    if(ready_end == NULL)
    {
        ready_proc = proc;
    }
    else
    {
        ready_proc = insert_after(proc, ready_end);
    }
}

/* Here we reclaim the memory of a process after it
  has finished */

static void ReclaimMemory()
{
    pcb *proc;
    long MEM_base;

    proc = defunct_proc;

    while (proc) {
        MEM_base = proc->MEM_base;
        if (MEM_base >= 0) {
            mem_free(MEM_base);
            proc->MEM_base = -1;
        }

        if (proc->your_admin) {
            /* Release admin. */
        }

        rm_process(&proc);

        defunct_proc = pcb_remove(proc);
        proc = defunct_proc;
    }
}

/* You may want to have the last word... */

static void my_finale()
{
    /* Your very own code goes here */
}

/* The main scheduling routine */

void schedule(event_type event)
{
    static int first = 1;

    if (first)
    {
        mem_init(memory);
        finale = my_finale;
        first = 0;
        /* Add your own initialisation code here */
    }

    switch (event)
    {
    /* You may want to do this differently
     */
        case NewProcess_event:
        GiveMemory();
        break;
        case Time_event:
        case IO_event:
        CPU_scheduler();
        break;
        case Ready_event:
        break;
        case Finish_event:
        ReclaimMemory();
        GiveMemory();
        CPU_scheduler();
        break;
        default:
        printf("I cannot handle event nr. %d\n", event);
        break;
    }
}