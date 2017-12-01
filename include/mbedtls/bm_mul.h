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
/* duono */ "ldp    x5, x6, [%2], #64    \n\t"   \
            "ldp    x10, x11, [%1], #64  \n\t"   \
            "umulh  x14, %3, x5          \n\t"   \
/* adDs  */ "adds   x10, x10, %0         \n\t"   \
            "umulh  %0, %3, x6           \n\t"   \
            "ldp    x7, x9, [%2, #-48]   \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x11, x11, x14        \n\t"   \
            "ldp    x12, x13, [%1, #-48] \n\t"   \
            "umulh  x14, %3, x7          \n\t"   \
            "adcs   x12, x12, %0         \n\t"   \
            "umulh  %0, %3, x9           \n\t"   \
            "adcs   x13, x13, x14        \n\t"   \
            "mul    x6, %3, x6           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x10, x10, x5         \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "adcs   x11, x11, x6         \n\t"   \
            "mul    x9, %3, x9           \n\t"   \
            "stp    x10, x11, [%1, #-64] \n\t"   \
            "adcs   x12, x12, x7         \n\t"   \
            "adcs   x13, x13, x9         \n\t"   \
            "stp    x12, x13, [%1, #-48] \n\t"   \
/* duono */ "ldp    x5, x6, [%2, #-32]   \n\t"   \
            "ldp    x10, x11, [%1, #-32] \n\t"   \
            "umulh  x14, %3, x5          \n\t"   \
/* adCs  */ "adcs   x10, x10, %0         \n\t"   \
            "umulh  %0, %3, x6           \n\t"   \
            "ldp    x7, x9, [%2, #-16]   \n\t"   \
            "mul    x5, %3, x5           \n\t"   \
            "adcs   x11, x11, x14        \n\t"   \
            "ldp    x12, x13, [%1, #-16] \n\t"   \
            "umulh  x14, %3, x7          \n\t"   \
            "adcs   x12, x12, %0         \n\t"   \
            "umulh  %0, %3, x9           \n\t"   \
            "adcs   x13, x13, x14        \n\t"   \
            "mul    x6, %3, x6           \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x10, x10, x5         \n\t"   \
            "mul    x7, %3, x7           \n\t"   \
            "adcs   x11, x11, x6         \n\t"   \
            "mul    x9, %3, x9           \n\t"   \
            "stp    x10, x11, [%1, #-32] \n\t"   \
            "adcs   x12, x12, x7         \n\t"   \
            "adcs   x13, x13, x9         \n\t"   \
            "stp    x12, x13, [%1, #-16] \n\t"   \
/* cinc  */ "cinc   %0, %0, cs           \n\t"

#define MULADDC_STOP                             \
         : "+r" (c),  "+r" (d), "+r" (s)         \
         : "r" (b)                               \
         : "x5", "x6", "x7", "x9", "x10", "x11", \
           "x12", "x13", "x14", "cc", "memory"   \
         );
