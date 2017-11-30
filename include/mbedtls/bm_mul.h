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

#if 1 /* 4-way */
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
#else /* no 4-way, use 8-way */
#define MULADDC_HUIT                             \
            "ldp    x4, x5, [%2], #64    \n\t"   \
            "ldp    x6, x7, [%2, #-48]   \n\t"   \
            "mul    x15, %3, x4          \n\t"   \
            "umulh  x4, %3, x4           \n\t"   \
            "mul    x13, %3, x5          \n\t"   \
            "umulh  x5, %3, x5           \n\t"   \
            "mul    x14, %3, x6          \n\t"   \
            "adds   x15, x15, %0         \n\t"   \
            "ldp    x8, x9, [%2, #-32]   \n\t"   \
            "ldp    x10, x11, [%2, #-16] \n\t"   \
            "adcs   x4, x4, x13          \n\t"   \
            "umulh  x6, %3, x6           \n\t"   \
            "mul    x13, %3, x7          \n\t"   \
            "umulh  x7, %3, x7           \n\t"   \
            "mul    x12, %3, x8          \n\t"   \
            "adcs   x5, x5, x14          \n\t"   \
            "adcs   x6, x6, x13          \n\t"   \
            "umulh  x8, %3, x8           \n\t"   \
            "mul    x13, %3, x9          \n\t"   \
            "umulh  x9, %3, x9           \n\t"   \
            "mul    x14, %3, x10         \n\t"   \
            "adcs   x7, x7, x12          \n\t"   \
            "adcs   x8, x8, x13          \n\t"   \
            "umulh  x10, %3, x10         \n\t"   \
            "mul    x13, %3, x11         \n\t"   \
            "umulh  %0, %3, x11          \n\t"   \
            "ldp    x11, x12, [%1], #64  \n\t"   \
            "adcs   x9, x9, x14          \n\t"   \
            "adcs   x10, x10, x13        \n\t"   \
            "ldp    x13, x14, [%1, #-48] \n\t"   \
            "cinc   %0, %0, cs           \n\t"   \
            "adds   x15, x11, x15        \n\t"   \
            "adcs    x4, x12, x4         \n\t"   \
            "ldp    x11, x12, [%1, #-32] \n\t"   \
            "adcs    x5, x13, x5         \n\t"   \
            "adcs    x6, x14, x6         \n\t"   \
            "ldp    x13, x14, [%1, #-16] \n\t"   \
            "adcs    x7, x11, x7         \n\t"   \
            "adcs    x8, x12, x8         \n\t"   \
            "adcs    x9, x13, x9         \n\t"   \
            "adcs   x10, x14, x10        \n\t"   \
            "stp    x15,  x4, [%1, #-64] \n\t"   \
            "stp     x5,  x6, [%1, #-48] \n\t"   \
            "stp     x7,  x8, [%1, #-32] \n\t"   \
            "stp     x9, x10, [%1, #-16] \n\t"   \
            "cinc    %0,  %0, cs         \n\t"

#define MULADDC_STOP                             \
         : "+r" (c),  "+r" (d), "+r" (s)         \
         : "r" (b)                               \
         : "x4", "x5", "x6", "x7", "x8", "x9",   \
           "x10", "x11", "x12", "x13", "x14",    \
           "x15", "cc", "memory"                 \
         );
#endif
