/*********************************************************************/
/*                                                                   */
/*                           stddef.h                                */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STDDEF_H
#define __STDDEF_H

#ifndef _PTRDIFF_T
#ifdef __EDG__
typedef __EDG_PTRDIFF_TYPE__  ptrdiff_t;
#else
typedef int  ptrdiff_t;
#endif
#endif

#ifndef _SIZE_T
#define _SIZE_T
#ifdef __EDG__
typedef __EDG_SIZE_TYPE__  size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T
#if (__CHAR_BIT__==32)
typedef int wchar_t;
#else
typedef short wchar_t;
#endif
#endif
#endif

#ifndef NULL
#define NULL    0
#endif

#ifndef offsetof
#define offsetof( s_name, m_name )  ((size_t)(char*)&(((s_name*)0)->m_name))
#endif

#endif /*__STDDEF_H*/
