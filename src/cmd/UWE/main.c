#include <stdio.h>
#include <stdlib.h>

#include "common/container/byte_buffer/byte_buffer.h"
#include "parser/parser.h"
#include "common/type.h"

int main(int argc, char *argv[]) {
    if (argc != 2) return -1;
    byte_buffer byte_buffer_ins = byte_buffer_init();
    if (byte_buffer_ins)return -1;
    FILE *file = fopen(argv[1], "rb");
    if (!file) return -1;

    {
        array arr = array_init(100, sizeof(byte));
        int read = 0;
        do {
            read = fread(array_get_data(arr), sizeof(byte), array_size(arr), file);
            if (!read)break;
            if (!arr)return -1;
            if (byte_buffer_write(byte_buffer_ins, arr, read))return -1;
        } while (true);
        array_destroy(arr);
    }

    if (fclose(file))return -1;

    parse(byte_buffer_ins);

    byte_buffer_destroy(byte_buffer_ins);
    return 0;
}