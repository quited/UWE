#include <stdio.h>
#include <stdlib.h>

#include "common/container/byte_buffer/byte_buffer.h"
#include "parser/parser.h"
#include "common/type.h"

int main(int argc,char *argv[]) {
  if(argc!=2) return -1;
  byte_buffer byte_buffer_ins = byte_buffer_init();
  FILE *file = fopen(argv[1],"rb");
  if(!file) return -1;

  byte *buffer = malloc(sizeof(byte));
  while (fread(buffer,sizeof(byte),1,file))
    byte_buffer_write_byte(byte_buffer_ins, *buffer);
  free(buffer);
  fclose(file);

  parse(byte_buffer_ins);
  byte_buffer_destroy(byte_buffer_ins);
  return 0;
}