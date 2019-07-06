#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "common/container/byte_buffer/byte_buffer.h"
#include "common/wasmobj/wasmobj.h"

wasmobj parse(byte_buffer wasm_raw);

#endif