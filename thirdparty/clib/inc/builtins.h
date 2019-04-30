/*********************************************************************/
/*                                                                   */
/*                           builtins.h                              */
/*                                                                   */
/*********************************************************************/

#ifndef __BUILTINS_H
#define __BUILTINS_H

#ifdef __llvm__

// ASHIFT 32
__attribute__((always_inline))
static inline int __builtin_ashift_4x8(int src_1, int src_2)
{
    int res;
    asm("XB%0 = ASHIFT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_ashift_2x16(int src_1, int src_2)
{
    int res;
    asm("XS%0 = ASHIFT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// ASHIFT 64
__attribute__((always_inline))
static inline long long __builtin_ashift_8x8(long long src_1, int src_2)
{
    long long res;
    asm("XB%0 = ASHIFT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_ashift_4x16(long long src_1, int src_2)
{
    long long res;
    asm("XS%0 = ASHIFT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}

// LSHIFT 32
__attribute__((always_inline))
static inline int __builtin_lshift_4x8(int src_1, int src_2)
{
    int res;
    asm("XB%0 = LSHIFT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_lshift_2x16(int src_1, int src_2)
{
    int res;
    asm("XS%0 = LSHIFT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// LSHIFT 64
__attribute__((always_inline))
static inline long long __builtin_lshift_8x8(long long src_1, int src_2)
{
    long long res;
    asm("XB%0 = LSHIFT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_lshift_4x16(long long src_1, int src_2)
{
    long long res;
    asm("XS%0 = LSHIFT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_lshift_2x32(long long src_1, int src_2)
{
    long long res;
    asm("X%0 = LSHIFT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}

// ROT 32
__attribute__((always_inline))
static inline int __builtin_rotate_1x32(int src_1, int src_2)
{
    int res;
    asm("X%0 = ROT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// ROT 64
__attribute__((always_inline))
static inline long long __builtin_rotate_2x32(long long src_1, int src_2)
{
    long long res;
    asm("X%0 = ROT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_rotate_1x64(long long src_1, int src_2)
{
    long long res;
    asm("XL%0 = ROT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}

// FEXT 32
__attribute__((always_inline))
static inline int __builtin_fext_se(int src_1, int src_2)
{
    int res;
    asm("X%0 = FEXT %1 BY %2 (SE) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_fext_ze(int src_1, int src_2)
{
    int res;
    asm("X%0 = FEXT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_fext(int src_1, int src_2)
{
    return __builtin_fext_se(src_1, src_2);
}

// FEXT 32 LC
__attribute__((always_inline))
static inline int __builtin_fext_long_control_se(int src_1, long long src_2)
{
    int res;
    asm("X%0 = FEXT %1 BY %2 (SE) (NF);;" : "=x" (res) : "x" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_fext_long_control_ze(int src_1, long long src_2)
{
    int res;
    asm("X%0 = FEXT %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_fext_long_control(int src_1, long long src_2)
{
    return __builtin_fext_long_control_se(src_1, src_2);
}

// FEXT 64
__attribute__((always_inline))
static inline long long __builtin_fext2_se(long long src_1, int src_2)
{
    long long res;
    asm("XL%0 = FEXT %1 BY %2 (SE) (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_fext2(long long src_1, int src_2)
{
    return __builtin_fext2_se(src_1, src_2);
}
__attribute__((always_inline))
static inline long long __builtin_fext2_ze(long long src_1, int src_2)
{
    long long res;
    asm("XL%0 = FEXT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}

// FEXT 64 LC
__attribute__((always_inline))
static inline long long __builtin_fext2_long_control_se(long long src_1, long long src_2)
{
    long long res;
    asm("XL%0 = FEXT %1 BY %2 (SE) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_fext2_long_control_ze(long long src_1, long long src_2)
{
    long long res;
    asm("XL%0 = FEXT %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_fext2_long_control(long long src_1, long long src_2)
{
    return __builtin_fext2_long_control_se(src_1, src_2);
}

// FDEP 32
__attribute__((always_inline))
static inline int __builtin_fdep(int src_1, int src_2, int src_3)
{
    asm("X%0 += FDEP %1 BY %2 (NF);;" : "+x" (src_1) : "x" (src_2), "x" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline int __builtin_fdep_se(int src_1, int src_2, int src_3)
{
    asm("X%0 += FDEP %1 BY %2 (SE) (NF);;" : "+x" (src_1) : "x" (src_2), "x" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline int __builtin_fdep_zf(int src_1, int src_2, int src_3)
{
    asm("X%0 += FDEP %1 BY %2 (ZF) (NF);;" : "+x" (src_1) : "x" (src_2), "x" (src_3));
    return src_1;
}

// FDEP 32 LC
__attribute__((always_inline))
static inline int __builtin_fdep_long_control(int src_1, int src_2, long long src_3)
{
    asm("X%0 += FDEP %1 BY %2 (NF);;" : "+x" (src_1) : "x" (src_2), "xl" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline int __builtin_fdep_long_control_se(int src_1, int src_2, long long src_3)
{
    asm("X%0 += FDEP %1 BY %2 (SE) (NF);;" : "+x" (src_1) : "x" (src_2), "xl" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline int __builtin_fdep_long_control_zf(int src_1, int src_2, long long src_3)
{
    asm("X%0 += FDEP %1 BY %2 (ZF) (NF);;" : "+x" (src_1) : "x" (src_2), "xl" (src_3));
    return src_1;
}

// FDEP 64
__attribute__((always_inline))
static inline long long __builtin_fdep2(long long src_1, long long src_2, int src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (NF);;" : "+xl" (src_1) : "xl" (src_2), "x" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline long long __builtin_fdep2_se(long long src_1, long long src_2, int src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (SE) (NF);;" : "+xl" (src_1) : "xl" (src_2), "x" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline long long __builtin_fdep2_zf(long long src_1, long long src_2, int src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (ZF) (NF);;" : "+xl" (src_1) : "xl" (src_2), "x" (src_3));
    return src_1;
}

// FDEP 64 LC
__attribute__((always_inline))
static inline long long __builtin_fdep2_long_control(long long src_1, long long src_2, long long src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (NF);;" : "+xl" (src_1) : "xl" (src_2), "xl" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline long long __builtin_fdep2_long_control_se(long long src_1, long long src_2, long long src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (SE) (NF);;" : "+xl" (src_1) : "xl" (src_2), "xl" (src_3));
    return src_1;
}
__attribute__((always_inline))
static inline long long __builtin_fdep2_long_control_zf(long long src_1, long long src_2, long long src_3)
{
    asm("XL%0 += FDEP %1 BY %2 (ZF) (NF);;" : "+xl" (src_1) : "xl" (src_2), "xl" (src_3));
    return src_1;
}

// COMPACT
__attribute__((always_inline))
static inline int __builtin_compact_to_fr4x8(long long src_1)
{
    int res;
    asm("XB%0 = COMPACT S%1 (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_compact_to_fr4x8_trunc(long long src_1)
{
    int res;
    asm("XB%0 = COMPACT S%1 (T) (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_compact_to_fr2x16_trunc(long long src_1)
{
    int res;
    asm("XS%0 = COMPACT %1 (T) (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_compact_to_i4x8(long long src_1)
{
    int res;
    asm("XB%0 = compact S%1 (I) (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_compact_to_i4x8_sat(long long src_1)
{
    int res;
    asm("XB%0 = compact S%1 (IS) (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}

// EXPAND
__attribute__((always_inline))
static inline long long __builtin_expand_fr2x16(int src_1)
{
    long long res;
    asm("X%0 = EXPAND S%1 (NF);;" : "=xl" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_expand_i2x16_ze(int src_1)
{
    long long res;
    asm("X%0 = EXPAND S%1 (IU) (NF);;" : "=xl" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_expand_i4x8(int src_1)
{
    long long res;
    asm("XS%0 = EXPAND B%1 (I);;" : "=xl" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_expand_i4x8_ze(int src_1)
{
    long long res;
    asm("XS%0 = EXPAND B%1 (IU);;" : "=xl" (res) : "x" (src_1));
    return res;
}

// ADD 32
__attribute__((always_inline))
static inline unsigned __builtin_uadd_sat(unsigned src_1, unsigned src_2)
{
    unsigned res;
    asm("X%0 = %1 + %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_add_4x8_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XB%0 = %1 + %2 (S) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_add_u2x16(int src_1, int src_2)
{
    unsigned res;
    asm("XS%0 = %1 + %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_add_u2x16_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XS%0 = %1 + %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_add_u4x8_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XB%0 = %1 + %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// SUB 32
__attribute__((always_inline))
static inline unsigned __builtin_usub_sat(unsigned src_1, unsigned src_2)
{
    unsigned res;
    asm("X%0 = %1 - %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sub_4x8(int src_1, int src_2)
{
    unsigned res;
    asm("XB%0 = %1 - %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sub_4x8_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XB%0 = %1 - %2 (S) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sub_u2x16(int src_1, int src_2)
{
    unsigned res;
    asm("XS%0 = %1 - %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sub_u2x16_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XS%0 = %1 - %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sub_u4x8_sat(int src_1, int src_2)
{
    unsigned res;
    asm("XB%0 = %1 - %2 (SU) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// ADD 64
__attribute__((always_inline))
static inline long long __builtin_add_8x8(long long src_1, long long src_2)
{
    long long res = 0;
    asm("XB%0 = %1 + %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_add_8x8_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = %1 + %2 (S) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_add_4x16_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = %1 + %2 (S) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
static inline unsigned long long __builtin_add_u4x16_sat(unsigned long long src_1, unsigned long long src_2)
{
    unsigned long long res;
    asm("XS%0 = %1 + %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_add_2x32u(unsigned long long src_1, unsigned long long src_2)
{
    long long res;
    asm("X%0 = %1 + %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_add_u2x32_sat(unsigned long long src_1, unsigned long long src_2)
{
    long long res;
    asm("X%0 = %1 + %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_add_u8x8_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = %1 + %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// SUB 64
__attribute__((always_inline))
static inline long long __builtin_sub_8x8(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = %1 - %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_sub_8x8_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = %1 - %2 (S) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_sub_4x16_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = %1 - %2 (S) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_sub_u4x16_sat(unsigned long long src_1, unsigned long long src_2)
{
    unsigned long long res;
    asm("XS%0 = %1 - %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_sub_2x32u(unsigned long long src_1, unsigned long long src_2)
{
    long long res;
    asm("X%0 = %1 - %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_sub_u2x32_sat(unsigned long long src_1, unsigned long long src_2)
{
    long long res;
    asm("X%0 = %1 - %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_sub_u8x8_sat(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = %1 - %2 (SU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// ADD 128
__attribute__((always_inline))
static inline __builtin_quad __builtin_add_4x32(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 + %2 (NF);;"
        "X%1 = %1 + %3 (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_add_4x32_sat(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 + %2 (S) (NF);;"
        "X%1 = %1 + %3 (S) (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_add_u4x32_sat(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 + %2 (SU) (NF);;"
        "X%1 = %1 + %3 (SU) (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}

// SUB 128
__attribute__((always_inline))
static inline __builtin_quad __builtin_sub_4x32(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 - %2 (NF);;"
        "X%1 = %1 - %3 (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_sub_4x32_sat(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 - %2 (S) (NF);;"
        "X%1 = %1 - %3 (S) (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_sub_u4x32_sat(__builtin_quad src_1, __builtin_quad src_2)
{
    long long resLow = __builtin_low_64(src_1);
    long long resHigh = __builtin_high_64(src_1);
    asm(
        "X%0 = %0 - %2 (SU) (NF);;"
        "X%1 = %1 - %3 (SU) (NF);;"
        : "+xl"(resLow), "+xl"(resHigh)
        : "xl"(__builtin_low_64(src_2)), "xl"(__builtin_high_64(src_2))
    );
    return __builtin_compose_128(resLow, resHigh);
}

// ADD BitRev
__attribute__((always_inline))
static inline int __builtin_addbitrev(int src_1, int src_2)
{
    unsigned res;
    asm("%0 = %1 + %2 (BR) (NF);;" : "=j" (res) : "j" (src_1), "j" (src_2));
    return res;
}

// ABS
__attribute__((always_inline))
static inline long long __builtin_abs_4x16(long long src_1)
{
    long long res;
    asm("XS%0 = ABS %1 (NF);;" : "=xl" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_abs_8x8(long long src_1)
{
    long long res;
    asm("XB%0 = ABS %1 (NF);;" : "=xl" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_abs_4x8(int src_1)
{
    int res;
    asm("XB%0 = ABS %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}

// AVG
__attribute__((always_inline))
static inline long long __builtin_llavg(long long src_1, long long src_2)
{
    long long res;
    asm("XL%0 = (%1 + %2) / 2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long __builtin_lavg(long src_1, long src_2)
{
    long res;
    asm("X%0 = (%1 + %2) / 2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long __builtin_lavgt(long src_1, long src_2)
{
    long res;
    asm("X%0 = (%1 + %2) / 2 (T) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_avg(int src_1, int src_2)
{
    int res;
    asm("X%0 = (%1 + %2) / 2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_avgt(int src_1, int src_2)
{
    int res;
    asm("X%0 = (%1 + %2) / 2 (T) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// SUM
__attribute__((always_inline))
static inline int __builtin_sum_4x8(int src_1)
{
    int res;
    asm("X%0 = SUM B%1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sum_2x32(long long src_1)
{
    int res;
    asm("X%0 = %1 + %2 (NF);;" : "=x" (res) : "x" (__builtin_low_32(src_1)), "x" (__builtin_high_32(src_1)));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_sum_8x8(long long src_1)
{
    int res;
    asm("X%0 = SUM B%1 (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}

// CLIP
__attribute__((always_inline))
static inline long __builtin_lclip(long src_1, long src_2)
{
    long res;
    asm("X%0 = CLIP %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_clip_4x16(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = CLIP %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_clip_8x8(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = CLIP %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_llclip(long long src_1, long long src_2)
{
    long long res;
    asm("XL%0 = CLIP %1 BY %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_clip(int src_1, int src_2)
{
    int res;
    asm("X%0 = CLIP %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_clip_2x16(int src_1, int src_2)
{
    int res;
    asm("XS%0 = CLIP %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_clip_4x8(int src_1, int src_2)
{
    int res;
    asm("XB%0 = CLIP %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// NEG
__attribute__((always_inline))
static inline long long __builtin_neg_4x16_sat(long long src_1)
{
    long long res;
    asm("XS%0 = -%1 (NF);;" : "=xl" (res) : "xl" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_neg_8x8_sat(long long src_1)
{
    long long res;
    asm("XB%0 = -%1 (NF);;" : "=xl" (res) : "xl" (src_1));
    return res;
}

// MAX
__attribute__((always_inline))
static inline int __builtin_max_2x16(int src_1, int src_2)
{
    int res;
    asm("XS%0 = MAX(%1, %2) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_max_4x8(int src_1, int src_2)
{
    int res;
    asm("XB%0 = MAX(%1, %2) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_max_4x16(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = MAX(%1, %2) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_max_8x8(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = MAX(%1, %2) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned __builtin_max_u2x16(unsigned src_1, unsigned src_2)
{
    int res;
    asm("XS%0 = MAX(%1, %2) (U) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_max_u4x16(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = MAX(%1, %2) (U) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
/* [***] __attribute__((always_inline))
static inline long long __builtin_max_add(long long src_1, long long src_2, __builtin_quad src_3)
{
    long long res;
    asm(
        "XTR1:0 = %1;;\n"
        "XTR3:2 = %2;;\n"
        "XTR1:0 = MAX (TR1:0 + %3, TR3:2 + %3) (NF);;\n" // need high/low register definition
        "X%0 = TR1:0;;\n"
        : "=xl"(res)
        : "xl"(src_1), "xl"(src_2), "xq"(src_3)
        : // [***] clobber need XTR3:0
    );
    return res;
}*/

// MIN
__attribute__((always_inline))
static inline int __builtin_min_2x16(int src_1, int src_2)
{
    int res;
    asm("XS%0 = MIN(%1, %2) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_min_4x8(int src_1, int src_2)
{
    int res;
    asm("XB%0 = MIN(%1, %2) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_min_4x16(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = MIN(%1, %2) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_min_8x8(long long src_1, long long src_2)
{
    long long res;
    asm("XB%0 = MIN(%1, %2) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned __builtin_min_u2x16(unsigned src_1, unsigned src_2)
{
    int res;
    asm("XS%0 = MIN(%1, %2) (U) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_min_u4x16(long long src_1, long long src_2)
{
    long long res;
    asm("XS%0 = MIN(%1, %2) (U) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// COUNT
__attribute__((always_inline))
static inline long __builtin_lcount_ones(long src_1)
{
    long res;
    asm("X%0 = ONES %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long __builtin_llcount_ones(long long src_1)
{
    long res;
    asm("X%0 = ONES %1 (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}

// LEAD ONES
__attribute__((always_inline))
static inline long __builtin_lead_ones(long src_1)
{
    long res;
    asm("X%0 = LD1 %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long __builtin_lllead_ones(long long src_1)
{
    long res;
    asm("X%0 = LD1 %1 (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}

// LEAD ZERO
__attribute__((always_inline))
static inline long __builtin_lead_zero(long src_1)
{
    long res;
    asm("X%0 = LD0 %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}
__attribute__((always_inline))
static inline long __builtin_lllead_zero(long long src_1)
{
    long res;
    asm("X%0 = LD0 %1 (NF);;" : "=x" (res) : "xl" (src_1));
    return res;
}

// MERGE
__attribute__((always_inline))
static inline long long __builtin_merge_4x8(int src_1, int src_2)
{
    long long res;
    asm("XB%0 = MERGE %1, %2 (NF);;" : "=xl" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// MULT 32
__attribute__((always_inline))
static inline unsigned __builtin_mult_u2x16(unsigned src_1, unsigned src_2)
{
    unsigned long long res;
    asm("X%0 = %1 * %2 (IU) (NF);;" : "=xl" (res) : "xl" (__builtin_compose_64(src_1, 0)), "xl" (__builtin_compose_64(src_2, 0)));
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_mult_fr1x32(int src_1, int src_2)
{
    int res;
    asm("X%0 = %1 * %2 (T) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_mult_fr1x32_sat(int src_1, int src_2)
{
    int res;
    asm("X%0 = %1 * %2 (TS) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// MULT 64
__attribute__((always_inline))
static inline long long __builtin_mult_i2x16_wide(int src_1, int src_2)
{
    __builtin_quad res;
    asm("X%0 = %1 * %2 (I) (NF);;" : "=xq" (res) : "xl" (__builtin_compose_64(src_1, 0)), "xl" (__builtin_compose_64(src_2, 0)));
    return __builtin_low_64(res);
}
__attribute__((always_inline))
static inline long long __builtin_mult_i2x16_wide_sat(int src_1, int src_2)
{
    return __builtin_mult_i2x16_wide(src_1, src_2);
}
__attribute__((always_inline))
static inline long long __builtin_mult_u2x16_wide(int src_1, int src_2)
{
    __builtin_quad res;
    asm("X%0 = %1 * %2 (IU) (NF);;" : "=xq" (res) : "xl" (__builtin_compose_64(src_1, 0)), "xl" (__builtin_compose_64(src_2, 0)));
    return __builtin_low_64(res);
}
__attribute__((always_inline))
static inline long long __builtin_mult_i4x16_sat(long long src_1, long long src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (IS) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_mult_u4x16(unsigned long long src_1, unsigned long long src_2)
{
    unsigned long long res;
    asm("X%0 = %1 * %2 (IU) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_mult_i1x32_wide(int src_1, int src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (I) (NF);;" : "=xl" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline unsigned long long __builtin_mult_u1x32_wide(unsigned src_1, unsigned src_2)
{
    unsigned long long res;
    asm("X%0 = %1 * %2 (IU) (NF);;" : "=xl" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_mult_fr4x16(long long src_1, long long src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (T) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_mult_fr4x16_sat(long long src_1, long long src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (ST) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// MULT 128
__attribute__((always_inline))
static inline __builtin_quad __builtin_mult_i4x16_wide(long long src_1, long long src_2)
{
    __builtin_quad res;
    asm("X%0 = %1 * %2 (I) (NF);;" : "=xq" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_mult_i4x16_wide_sat(long long src_1, long long src_2)
{
    return __builtin_mult_i4x16_wide(src_1, src_2);
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_mult_u4x16_wide(long long src_1, long long src_2)
{
    __builtin_quad res;
    asm("X%0 = %1 * %2 (UI) (NF);;" : "=xq" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// MULTR 32
__attribute__((always_inline))
static inline int __builtin_multr_fr1x32(int src_1, int src_2)
{
    int res;
    asm("X%0 = %1 * %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline int __builtin_multr_fr1x32_sat(int src_1, int src_2)
{
    int res;
    asm("X%0 = %1 * %2 (S) (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// MULTR 64
static inline long long __builtin_multr_fr4x16(long long src_1, long long src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}
static inline long long __builtin_multr_fr4x16_sat(long long src_1, long long src_2)
{
    long long res;
    asm("X%0 = %1 * %2 (S) (NF);;" : "=xl" (res) : "xl" (src_1), "xl" (src_2));
    return res;
}

// CMULT 32
__attribute__((always_inline))
static inline int __builtin_cmult_i2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CI) (NF);;"
        "XS%0 = COMPACT MR3:0 (I) (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmult_i2x16_sat(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CI) (NF);;"
        "XS%0 = COMPACT MR3:0 (IS) (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmult_conj_i2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CIJ) (NF);;\n"
        "XS%0 = COMPACT MR3:0 (I) (NF);;\n"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmult_conj_i2x16_sat(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CIJ) (NF);;"
        "XS%0 = COMPACT MR3:0 (IS) (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmult_fr2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (C) (NF);;"
        "XS%0 = COMPACT MR3:0 (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmult_conj_fr2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CJ) (NF);;"
        "XS%0 = COMPACT MR3:0 (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}

// CMULT 64
static inline long long __builtin_cmult_i2x16_wide(int src_1, int src_2)
{
    long long res;
    asm(
        "XMR1:0 += %1 ** %2 (CI) (NF);;"
        "X%0 = MR1:0 (NF);;"
        : "=xl" (res)
        : "x" (src_1), "x" (src_2)
        : // [***] clobber MR4:0
    );
    return res;
}
static inline long long __builtin_cmult_conj_i2x16_wide(int src_1, int src_2)
{
    long long res;
    asm(
        "XMR1:0 += %1 ** %2 (CIJ) (NF);;"
        "X%0 = MR1:0 (NF);;"
        : "=xl" (res)
        : "x" (src_1), "x" (src_2)
        : // [***] clobber MR4:0
    );
    return res;
}

// CMULTR 32
__attribute__((always_inline))
static inline int __builtin_cmultr_fr2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CR) (NF);;"
        "XS%0 = COMPACT MR3:0 (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmultr_fr2x16_sat(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CR) (NF);;"
        "XS%0 = COMPACT MR3:0 (S) (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
__attribute__((always_inline))
static inline int __builtin_cmultr_conj_fr2x16(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CRJ) (NF);;"
        "XS%0 = COMPACT MR3:0 (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}
static inline int __builtin_cmultr_conj_fr2x16_sat(int src_1, int src_2)
{
    long long res; // [***] need quad
    asm(
        "XMR1:0 += %1 ** %2 (CRJ) (NF);;"
        "XS%0 = COMPACT MR3:0 (S) (NF);;"
        : "=xl" (res) : "x"(src_1), "x"(src_2)
        // [***] clobber need MR4:0
    );
    return __builtin_low_32(res);
}

// LOW/HIGH
__attribute__((always_inline))
static inline unsigned __builtin_low_32u(unsigned long long src_1)
{
    return __builtin_low_32(src_1);
}
__attribute__((always_inline))
static inline unsigned __builtin_high_32u(unsigned long long src_1)
{
    return __builtin_high_32(src_1);
}

// COMPOSE
__attribute__((always_inline))
static inline unsigned long long __builtin_compose_64u(unsigned src_1, unsigned src_2)
{
    return __builtin_compose_64(src_1, src_2);
}
__attribute__((always_inline))
static inline long double __builtin_f_compose_64(float src_1, float src_2)
{
    long long res = __builtin_compose_64(*((int*)&src_1), *((int*)&src_2));
    return *((long double*)&res);
}

// NOP/IDLE
__attribute__((always_inline))
static void __builtin_nop(void)
{
    asm("NOP;;");
}
__attribute__((always_inline))
static void __builtin_idle(void)
{
    asm("IDLE;;");
}
__attribute__((always_inline))
static void __builtin_idle_lp(void)
{
    asm("IDLE (LP);;"); // [***] assembler error
}

// TMAX
__attribute__((always_inline))
static inline int __builtin_tmax(int src_1, int src_2)
{
    int res;
    asm(
        "XTR0 = %1;;"
        "XTR1 = %2;;"
        "X%0 = TMAX(TR0, TR1) (NF);;"
        : "=x" (res)
        : "x" (src_1), "x" (src_2)
        : // [***] clobber need XTR0, XTR1
    );
    return res;
}
__attribute__((always_inline))
static inline int __builtin_tmax_4s(int src_1, int src_2)
{
    int res;
    asm(
        "XTR0 = %1;;"
        "XTR1 = %2;;"
        "XS%0 = TMAX(TR0, TR1) (NF);;"
        : "=x" (res)
        : "x" (src_1), "x" (src_2)
        : // [***] clobber need XTR0, XTR1
    );
    return res;
}

// FAVGF
__attribute__((always_inline))
static inline float __builtin_favgf(float src_1, float src_2)
{
    float res;
    asm("XF%0 = (%1 + %2) / 2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// FCLIPF
__attribute__((always_inline))
static inline float __builtin_fclipf(float src_1, float src_2)
{
    float res;
    asm("XF%0 = CLIP %1 BY %2 (NF);;" : "=x" (res) : "x" (src_1), "x" (src_2));
    return res;
}

// RECIP
__attribute__((always_inline))
static inline float __builtin_recip(float src_1)
{
    float res;
    asm("XF%0 = RECIPS %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}

// RSQRT
__attribute__((always_inline))
static inline float __builtin_rsqrt(float src_1)
{
    float res;
    asm("XF%0 = RSQRTS %1 (NF);;" : "=x" (res) : "x" (src_1));
    return res;
}

// FLOW/FHIGH
__attribute__((always_inline))
static inline float __builtin_f_low_32(long double src_1)
{
    return ((float*)&src_1)[0]; // [***]
}
__attribute__((always_inline))
static inline float __builtin_f_high_32(long double src_1)
{
    return ((float*)&src_1)[1]; // [***]
}

// PERMUTE
__attribute__((always_inline))
static inline long long __builtin_permute_8b(long long src_1, int src_2)
{
    long long res;
    asm("X%0 = PERMUTE(%1, %2) (NF);;" : "=xl" (res) : "xl" (src_1), "x" (src_2));
    return res;
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_permute_8s(long long src_1, int src_2)
{
    __builtin_quad res;
    asm("X%0 = PERMUTE(%1, -%1, %2) (NF);;" : "=xq" (res) : "xl" (src_1), "x" (src_2));
    return res;
}

// ACS
__attribute__((always_inline))
static inline __builtin_quad __builtin_acs_max(long long src_1, long long src_2, int src_3, long long src_4)
{
    __builtin_quad res;
    asm(
        "XTR1:0 = %1;;\n"
        "XTR3:2 = %2;;\n"
        "XTHR1:0 = %4;;\n"
        "XTR3:0 = ACS(TR1:0, TR3:2, %3) (NF);;\n"
        "X%0 = TR3:0;;\n"
        : "=xq"(res)
        : "xl"(src_1), "xl"(src_2), "x"(src_3), "xl"(src_4)
        : // [***] clobber need XTR3:0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_acs_max_8s(long long src_1, long long src_2, int src_3, long long src_4)
{
    __builtin_quad res;
    asm(
        "XTR1:0 = %1;;\n"
        "XTR3:2 = %2;;\n"
        "XTHR1:0 = %4;;\n"
        "XSTR3:0 = ACS(TR1:0, TR3:2, %3) (NF);;\n"
        "X%0 = TR3:0;;\n"
        : "=xq"(res)
        : "xl"(src_1), "xl"(src_2), "x"(src_3), "xl"(src_4)
        : // [***] clobber need XTR3:0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_acs_tmax(long long src_1, long long src_2, int src_3, long long src_4)
{
    __builtin_quad res;
    asm(
        "XTR1:0 = %1;;\n"
        "XTR3:2 = %2;;\n"
        "XTHR1:0 = %4;;\n"
        "XTR3:0 = ACS(TR1:0, TR3:2, %3) (TMAX) (NF);;\n"
        "X%0 = TR3:0;;\n"
        : "=xq"(res)
        : "xl"(src_1), "xl"(src_2), "x"(src_3), "xl"(src_4)
        : // [***] clobber need XTR3:0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_acs_tmax_8s(long long src_1, long long src_2, int src_3, long long src_4)
{
    __builtin_quad res;
    asm(
        "XTR1:0 = %1;;\n"
        "XTR3:2 = %2;;\n"
        "XTHR1:0 = %4;;\n"
        "XSTR3:0 = ACS(TR1:0, TR3:2, %3) (TMAX) (NF);;\n"
        "X%0 = TR3:0;;\n"
        : "=xq"(res)
        : "xl"(src_1), "xl"(src_2), "x"(src_3), "xl"(src_4)
        : // [***] clobber need XTR3:0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_acs_res2(__builtin_quad src_1)
{
    long long res;
    asm("X%0 = THR1:0;;\n" : "=xl"(res) : "xq"(src_1));
    return res;
}

// CIRCLE BUFFER
__attribute__((always_inline))
static inline int __builtin_circindex(int index, int incr, int nitems)
{
    index += incr;
    if (index < 0) index += nitems;
    else if (index >= nitems) index -=nitems;
    return index;
}
__attribute__((always_inline))
static inline void *__builtin_circptr(void *ptr, int incr, void *base, int buflen)
{
    unsigned *res = (unsigned*)ptr;
    res += incr;
    if (res < (unsigned*)base) res += buflen;
    else if (res >= ((unsigned*)base + buflen)) res -= buflen;
    return res;
}

// DESPREAD
__attribute__((always_inline))
static inline int __builtin_despread(__builtin_quad src_1, long long src_2, int src_3)
{
    int res;
    asm(
        "XTHR1:0 = %2;;\n"
        "XTR0 = %3;;\n"
        "XTR0 += DESPREAD (%1, THR1:0) (NF);;\n"
        "X%0 = TR0;;\n"
        : "=x"(res)
        : "xq"(src_1), "xl"(src_2), "x"(src_3)
        : // [***] clobber need XTR0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline int __builtin_despread_i(__builtin_quad src_1, long long src_2, int src_3)
{
    int res;
    asm(
        "XTHR1:0 = %2 (I);;\n"
        "XTR0 = %3;;\n"
        "XTR0 += DESPREAD (%1, THR1:0) (NF);;\n"
        "X%0 = TR0;;\n"
        : "=x"(res)
        : "xq"(src_1), "xl"(src_2), "x"(src_3)
        : // [***] clobber need XTR0 , XTHR1:0
    );
    return res;
}
__attribute__((always_inline))
static inline long long __builtin_despread_res2(int src_1)
{
    long long res;
    asm("X%0 = THR1:0;;\n" : "=xl"(res) : "x"(src_1));
    return res;
}

// BTB
__attribute__((always_inline))
static inline void __builtin_btben(void)
{
    asm("BTBEN;;");
}
__attribute__((always_inline))
static inline void __builtin_btbinv(void)
{
    asm("BTBINV;;");
}

// FIX
__attribute__((always_inline))
static inline int __builtin_fix(float src_1)
{
    int res;
    asm("X%0 = FIX F%1 (NF);;" : "=x"(res) : "x"(src_1));
    return res;
}

// DUAL/QUAD READ/WRITE
__attribute__((always_inline))
static inline long long __builtin_mem_read2(volatile long long *addr)
{
    long long result;
    asm volatile ("X%0 = L[%1 + 0];;" : "=xl"(result): "j"(addr));
    return result;
}
__attribute__((always_inline))
static inline void __builtin_mem_write2(volatile long long *addr, long long value)
{
    asm volatile ("L[%0 + 0] = X%1;;" : : "j"(addr), "xl" (value));
}
__attribute__((always_inline))
static inline __builtin_quad __builtin_mem_read4(volatile __builtin_quad *addr)
{
    __builtin_quad result;
    asm volatile ("X%0 = Q[%1 + 0];;" : "=xq"(result): "j"(addr));
    return result;
}
__attribute__((always_inline))
static inline void __builtin_mem_write4(volatile __builtin_quad *addr, __builtin_quad value)
{
    asm volatile ("Q[%0 + 0] = X%1;;" : : "j"(addr), "xq" (value));
}

#endif // __llvm__

#endif /*__BUILTINS_H*/
