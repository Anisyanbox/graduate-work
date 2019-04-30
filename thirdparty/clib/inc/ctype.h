/*********************************************************************/
/*                                                                   */
/*                           ctype.h                                 */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __CTYPE_H
#define __CTYPE_H

#include <stdarg.h>

#define  __BB_MASK  0x80    /* BEL, BS, etc                       */
#define  __CN_MASK  0x40    /* CR, FF, HT, VT                     */
#define  __DI_MASK  0x20    /* '0' - '9'                          */
#define  __LO_MASK  0x10    /* 'a' - 'z'                          */
#define  __PU_MASK  0x08    /* punctuation                        */
#define  __SP_MASK  0x04    /* space                              */
#define  __UP_MASK  0x02    /* 'A' - 'Z'                          */
#define  __XD_MASK  0x01    /* '0' - '9', 'A' - 'F' , 'a' - 'f'   */


#define  isalnum(c)   (__get_ctyp(c) & ( __DI_MASK | __LO_MASK | __UP_MASK ) )
#define  isalpha(c)   (__get_ctyp(c) & ( __LO_MASK | __UP_MASK ) )
#define  iscntrl(c)   (__get_ctyp(c) & ( __BB_MASK | __CN_MASK ) )
#define  isdigit(c)   (__get_ctyp(c) & ( __DI_MASK ) )
#define  isgraph(c)   (__get_ctyp(c) & ( __DI_MASK | __LO_MASK | __UP_MASK | __PU_MASK) )
#define  islower(c)   (__get_ctyp(c) & ( __LO_MASK ) )
#define  isprint(c)   (__get_ctyp(c) & ( __DI_MASK | __LO_MASK | __UP_MASK | __PU_MASK | __SP_MASK) )
#define  ispunct(c)   (__get_ctyp(c) & ( __PU_MASK ) )
#define  isspace(c)   (__get_ctyp(c) & ( __CN_MASK | __SP_MASK) )
#define  isupper(c)   (__get_ctyp(c) & ( __UP_MASK ) )
#define  isxdigit(c)  (__get_ctyp(c) & ( __XD_MASK ) )


/* Function name modifications for different char/double sizes */
#define __get_ctyp  __C_FUN(__get_ctyp)
#define toupper     __C_FUN(toupper)
#define tolower     __C_FUN(tolower)


#if defined(__cplusplus)
extern "C" {
#endif

extern char __get_ctyp(int c);

extern int (isalnum) (int c);
extern int (isalpha) (int c);
extern int (iscntrl) (int c);
extern int (isdigit) (int c);
extern int (isgraph) (int c);
extern int (islower) (int c);
extern int (isprint) (int c);
extern int (ispunct) (int c);
extern int (isspace) (int c);
extern int (isupper) (int c);
extern int (isxdigit)(int c);
extern int (toupper) (int c);
extern int (tolower) (int c);

#if defined(__cplusplus)
}
#endif


#endif /*__CTYPE_H*/
