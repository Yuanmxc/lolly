#ifndef LOLLY_TBOX_MACROS_H
#define LOLLY_TBOX_MACROS_H

#include "doctest/doctest.h"
#include "string.hpp"

inline void
string_eq (string left, string right) {
  if (left != right) {
    cout << "left : " << left << LF;
    cout << "right: " << right << LF;
  }
  CHECK_EQ (left == right, true);
}

#define TEST_MEMORY_LEAK_ALL                                                   \
  TEST_CASE ("test memory leak above") { CHECK_EQ (mem_used (), mem_lolly); }

#define TEST_MEMORY_LEAK_INIT                                                  \
  int mem_lolly= 0;                                                            \
  TEST_CASE ("read before test") { mem_lolly= mem_used (); }

#endif
