/*
 * Copyright (C) 2024 pdnguyen of the HCMC University of Technology
 */
/*
 * Source Code License Grant: Authors hereby grants to Licensee 
 * a personal to use and modify the Licensed Source Code for 
 * the sole purpose of studying during attending the course CO2018.
 */
//#ifdef MM_TLB
/*
 * Memory physical based TLB Cache
 * TLB cache module tlb/tlbcache.c
 *
 * TLB cache is physically memory phy
 * supports random access 
 * and runs at high speed
 */


#include "mm.h"
#include <stdlib.h>
#include <pthread.h>
#define init_tlbcache(mp,sz,...) init_memphy(mp, sz, (1, ##__VA_ARGS__))
pthread_mutex_t entry_lock = PTHREAD_MUTEX_INITIALIZER;;
pthread_mutex_t cache_lock = PTHREAD_MUTEX_INITIALIZER;
/*
 *  tlb_cache_read read TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
static struct cache_entry{
    int valid;
    int pid;
    int tag;
} tlb_cache[MAX_CACHE_INDEX];
int insert_cache_entry(struct pcb_t * proc,  int pgnum){
   int index = pgnum % MAX_CACHE_INDEX;
   int tag = pgnum / MAX_CACHE_INDEX;
   pthread_mutex_lock(&entry_lock);
   tlb_cache[index].valid = 1;
   tlb_cache[index].pid = proc->pid;
   tlb_cache->tag = tag;
   pthread_mutex_unlock(&entry_lock);
   return 0;
}
int tlb_cache_read(struct pcb_t * proc, int pgnum, int offset, BYTE * value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
    */
   int index = pgnum % MAX_CACHE_INDEX;
   int tag = pgnum / MAX_CACHE_INDEX;
   if(tlb_cache[index].valid == 1 && tlb_cache[index].pid == proc->pid && tlb_cache[index].tag == tag){
      int addr = pgnum * PAGING_PAGESZ + offset;
      TLBMEMPHY_read(proc->tlb,addr,value);
      return 0;
   }
   return -1;
}

/*
 *  tlb_cache_write write TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
int tlb_cache_write(struct pcb_t * proc,  int pgnum, int offset, BYTE value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
    */
   int index = pgnum % MAX_CACHE_INDEX;
   int tag = pgnum / MAX_CACHE_INDEX;
   if(tlb_cache[index].valid == 1 && tlb_cache[index].pid == proc->pid && tlb_cache[index].tag == tag){
      int addr = pgnum * PAGING_PAGESZ + offset;
      TLBMEMPHY_write(proc->tlb,addr,value);
      _cache_page(proc->tlb,pgnum,proc->mram,PAGING_FPN_PRESENT(proc->mm->pgd[pgnum]));
      return 0;
   }
   return -1;
}

/*
 *  TLBMEMPHY_read natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @value: obtained value
 */
int TLBMEMPHY_read(struct memphy_struct * mp, int addr, BYTE *value)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   *value = mp->storage[addr];

   return 0;
}


/*
 *  TLBMEMPHY_write natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @data: written data
 */
int TLBMEMPHY_write(struct memphy_struct * mp, int addr, BYTE data)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   mp->storage[addr] = data;

   return 0;
}

/*
 *  TLBMEMPHY_format natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 */


int TLBMEMPHY_dump(struct memphy_struct * mp)
{
   /*TODO dump memphy contnt mp->storage 
    *     for tracing the memory content
    */
   printf("Memory Physical Content:\n");
    for (int i = 0; i < mp->maxsz; i++) {
        printf("%d ", mp->storage[i]);
        if ((i + 1) % 16 == 0) 
            printf("\n");
    }
    printf("\n");
   return 0;
}

/*
 *  Init TLBMEMPHY struct
 */
int init_tlbmemphy(struct memphy_struct *mp, int max_size)
{
   mp->storage = (BYTE *)malloc(max_size*sizeof(BYTE));
   mp->maxsz = max_size;
   mp->rdmflg = 1;
   for(int index = 0; index < MAX_CACHE_INDEX; index++){
      tlb_cache[index].valid = 0;
   }
   return 0;
}

//#endif
