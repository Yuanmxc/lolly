
/******************************************************************************
 * MODULE     : Fast memory allocation using mimalloc
 * DESCRIPTION:
 * COPYRIGHT  : (C) 2023-2024  jingkaimori
 *******************************************************************************
 * This software falls under the GNU general public license version 3 or later.
 * It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
 * in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
 ******************************************************************************/

#include "assert.h"
#include "basic.hpp"
#include "fast_alloc.hpp"
#include <mimalloc.h>

/*****************************************************************************/
// General purpose fast allocation routines
/*****************************************************************************/

void*
safe_malloc (size_t sz) {
  void* ptr= mi_malloc (mi_good_size (sz));
  if (ptr == NULL) {
    cerr << "Fatal error: out of memory\n";
    abort ();
  }
  return ptr;
}

void*
fast_alloc (size_t sz) {
  return safe_malloc (sz);
}

void
fast_free (void* ptr, size_t sz) {
  mi_free (ptr);
}

void*
fast_new (size_t s) {
  return safe_malloc (s);
}

void
fast_delete (void* ptr) {
  mi_free (ptr);
}

/******************************************************************************
 * Statistics
 ******************************************************************************/

bool
visit_mem (const mi_heap_t* heap, const mi_heap_area_t* heapinfo, void* block,
           size_t blocksize, void* arg) {
  int* count= (int*) arg;
  *count+= heapinfo->used;
  return true;
}

int
mem_used () {
  mi_heap_t* heap = mi_heap_get_default ();
  int        count= 0;
  mi_heap_visit_blocks (heap, false, visit_mem, &count);
  return count;
}

void
mem_info () {
  cout << "\n---------------- memory statistics ----------------\n";
  cout << "malloc overrided:" << mi_is_redirected () << "\n";
}
