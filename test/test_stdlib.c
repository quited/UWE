#include <unity.h>
#include <type.h>

#include <stdlib.h>

void test_memory_allocate() {
  void *a = malloc(sizeof(int));
  TEST_ASSERT_EQUAL(true, (bool) a);
  free(a);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_memory_allocate);
  UNITY_END();
}