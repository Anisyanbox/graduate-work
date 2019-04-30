/************************************************************************
 *
 * adi_types.h
 *
 ************************************************************************/
/*   Generic Type Definitions  */

/*       Type definitions for fixed width integer types
 *       Type definitions for floating-point types
 *       Type definition for a Boolean type
 *
 *       These are type definitions that also comply with MISRA Rule 6.3.
 *       (this file is used as the basis for misra_types.h)
 */

#ifndef __ADI_TYPES_H__
#define __ADI_TYPES_H__

/* obtain integer types ... */
#include <stdint.h>

/* obtain boolean types ... */
#include <stdbool.h>

/* define required types that are not provided by stdint.h or stdbool.h ... */
typedef char                char_t;
typedef float               float32_t;
#ifdef __DOUBLES_ARE_FLOATS__
typedef long double         float64_t;
#else
typedef double              float64_t;
#endif


#endif /* __ADI_TYPES_H__ */

