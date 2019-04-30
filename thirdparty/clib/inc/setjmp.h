/*********************************************************************/
/*                                                                   */
/*                            setjmp.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __SETJMP_H
#define __SETJMP_H

#define _JMPBUF_SIZE 41

#pragma data_alignment=16
typedef struct {
  int data[_JMPBUF_SIZE];
} 
#ifdef __llvm__
    __attribute__((__aligned__(16)))
#endif
jmp_buf[1];

/*
 * NOTE: longjmp and setjmp have been implemented assuming
 * that the jmp_buf parameter has been quad word aligned.
 */


#if defined(__cplusplus)
extern "C" {
#endif

extern int  setjmp (jmp_buf env);
extern void longjmp (jmp_buf env,int val);

#if defined(__cplusplus)
}
#endif


#endif /*__SETJMP_H*/
