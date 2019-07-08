//
// Created by 31838 on 7/7/2019.
//

#ifndef UWE_ENDIAN_H
#define UWE_ENDIAN_H

#include <common/container/array/array.h>

//1 le;0 be
int host_endian();

byte revert_endian(byte b);

array revert_array(array arr);

#endif //UWE_ENDIAN_H
