//
// Created by 31838 on 7/5/2019.
//

#ifndef UWE_LEB128_H
#define UWE_LEB128_H

#include <common/container/container.h>
#include <common/type.h>

array Leb128FromUint64(u64 n);

array Leb128FromInt64(i64 n);

u64 Leb128ToUint64(byte_buffer buf);

i64 Leb128ToInt64(byte_buffer buf);

#endif //UWE_LEB128_H
