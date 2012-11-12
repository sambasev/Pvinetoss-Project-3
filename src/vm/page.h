#ifndef PAGE_H
#define PAGE_H

#include <hash.h>

#define NEW_PAGE 1 
/* Very similar to the frame table entries
   Each thread has its own supplemental page table (spt)
   spt keeps track of all pages accessed/modified by thread
*/

struct sup_page_table {
   /* Current thread's pdbr (CR3) */
   uint8_t pd;
   /* Our SPT is a hash table containing pages */
   struct hash *pages;
};

/* Each page contains the address of the actual page
   and the associated bits. i.e. it is actually a pte 
*/
struct page
{ 
   struct hash_elem hash_elem;
   /* Address of the actual page */
   void *addr;
   /* Dirty set when page modified*/
   uint8_t dirty; 
   /* Set when page has been read/written after creation */
   uint8_t accessed; 
};

 struct page * map_frame_to_page (void *page_frame, int flags);
 void set_page_accessed(struct page * page);
 void set_page_dirty(struct page * page);

 unsigned page_hash (const struct hash_elem *p_, void *aux);
 bool page_less (const struct hash_elem *a_, const struct hash_elem *b_, void *aux);
 struct page * page_lookup (const void *address);

#endif
