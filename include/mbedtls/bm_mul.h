/**
 * \file bm_mul.h
 *
 * \brief  Multiplication for arm64, asm macros
 *
 *  Copyright (C) 2017 by Marco BODRATO, All Rights Reserved
 */

#define MULADDC_INIT                             \
    asm(

#define MULADDC_CORE                             \
            "ldr    x5, [%2], #8         \n\t"   \
            "ldr    x9, [%1]             \n\t"   \
            "umulh  x6, %3, x5           \n\t"   \
            "adds   x9, x9, %0           \n\t"   \
            "mul    x7, %3, x5           \n\t"   \
            "cinc   x6, x6, cs           \n\t"   \
            "adds   x9, x9, x7           \n\t"   \
            "str    x9, [%1], #8         \n\t"   \
            "cinc   %0, x6, cs           \n\t"

#define MULADDC_STOP                             \
         : "+r" (c),  "+r" (d), "+r" (s)         \
         : "r" (b)                               \
         : "x5", "x6", "x7", "x9", "cc", "memory"\
         );
