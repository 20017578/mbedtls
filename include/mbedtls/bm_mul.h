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

#define MULADDC_HUIT                             \
            "ldp    x5, x7, [%2], #64    \n\t"   \
            "ldp    x6, x9, [%1], #64    \n\t"   \
            "adds   x6, x6, %0           \n\t"   \
            "umulh  %0, %3, x5           \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x9, x9, %0           \n\t"   \
            "umulh  %0, %3, x7           \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x6, x5, x6           \n\t"   \
            "adcs   x9, x7, x9           \n\t"   \
            "stp    x6, x9, [%1, #-64]   \n\t"   \
            "ldp    x6, x9, [%1, #-48]   \n\t"   \
            "ldp    x5, x7, [%2, #-48]   \n\t"   \
            "adcs   x6, x6, %0           \n\t"   \
            "umulh  %0, %3, x5           \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x9, x9, %0           \n\t"   \
            "umulh  %0, %3, x7           \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x6, x5, x6           \n\t"   \
            "adcs   x9, x7, x9           \n\t"   \
            "stp    x6, x9, [%1, #-48]   \n\t"   \
            "ldp    x6, x9, [%1, #-32]   \n\t"   \
            "ldp    x5, x7, [%2, #-32]   \n\t"   \
            "adcs   x6, x6, %0           \n\t"   \
            "umulh  %0, %3, x5           \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x9, x9, %0           \n\t"   \
            "umulh  %0, %3, x7           \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x6, x5, x6           \n\t"   \
            "adcs   x9, x7, x9           \n\t"   \
            "stp    x6, x9, [%1, #-32]   \n\t"   \
            "ldp    x6, x9, [%1, #-16]   \n\t"   \
            "ldp    x5, x7, [%2, #-16]   \n\t"   \
            "adcs   x6, x6, %0           \n\t"   \
            "umulh  %0, %3, x5           \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x9, x9, %0           \n\t"   \
            "umulh  %0, %3, x7           \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x6, x5, x6           \n\t"   \
            "adcs   x9, x7, x9           \n\t"   \
            "stp    x6, x9, [%1, #-16]   \n\t"   \
            "cinc   %0, %0, cs           \n\t"

#define MULADDC_STOP                             \
         : "+r" (c),  "+r" (d), "+r" (s)         \
         : "r" (b)                               \
         : "x5", "x6", "x7", "x9", "cc", "memory"\
         );
