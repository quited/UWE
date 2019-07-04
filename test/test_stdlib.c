#include <stdlib.h>

int main(void){
  void* a = malloc(sizeof(int));
  free(a);
  return 0;
}