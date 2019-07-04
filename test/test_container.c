#include "common/container/container.h"

int comp(const void* a, const void* b){
  return 0;
}

int main(void){
  array arr = array_init(1,sizeof(int));
  array_destroy(arr);

  buffer buf = buffer_init(sizeof(int));
  buffer_destroy(buf);

  deque deq = deque_init(sizeof(int));
  deque_destroy(deq);

  list lis = list_init(sizeof(int));
  list_destroy(lis);

  set se = set_init(sizeof(int),comp);
  set_destroy(se);

  stack sta = stack_init(sizeof(int));
  stack_destroy(sta);

  vector vec = vector_init(sizeof(vec));
  vector_destroy(vec);

  return 0;
}