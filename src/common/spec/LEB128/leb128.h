//
// Created by 31838 on 7/5/2019.
//

#ifndef UWE_LEB128_H
#define UWE_LEB128_H

#include <common/container/container.h>
#include <common/type.h>

array leb128FromUint64(u64 n);

array leb128FromUint32(u32 n);

#endif //UWE_LEB128_H