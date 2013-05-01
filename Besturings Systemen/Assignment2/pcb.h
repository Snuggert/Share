pcb *pcb_remove(pcb *item);
pcb *pcb_get_next(pcb *item);
pcb *pcb_get_prev(pcb *item);
long get_mem_need(pcb *item);
int set_mem_base(pcb *item, long MEM_base);
pcb *find_start(pcb *item);
pcb *find_end(pcb *item);
pcb *insert_after(pcb *item, pcb *after);