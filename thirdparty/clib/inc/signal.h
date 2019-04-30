/*********************************************************************/
/*                                                                   */
/*                            signal.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __SIGNAL_H
#define __SIGNAL_H

/* These signal numbers are specific to 1967VC2T and 1967VC3T processors.
** The numbers correspond to the relative priorities and the positions
** of the corresponding bits within the interrupt registers.
*/

#define SIGTIMER0LP   2
#define SIGTIMER1LP   3

#define SIGLINK0      6
#define SIGLINK1      7
#define SIGLINK2      8
#define SIGLINK3      9

#define SIGDMA0      14
#define SIGDMA1      15
#define SIGDMA2      16
#define SIGDMA3      17
#define SIGDMA4      22
#define SIGDMA5      23
#define SIGDMA6      24
#define SIGDMA7      25
#define SIGDMA8      29
#define SIGDMA9      30
#define SIGDMA10     31
#define SIGDMA11     32
#define SIGDMA12     37
#define SIGDMA13     38

#define SIGIRQ0      41
#define SIGIRQ1      42
#define SIGIRQ2      43
#define SIGIRQ3      44

#define SIGVIRPT     48  /* it is not possible to set a handler for this */

#define SIGBUSLK     50
#define SIGTIMER0HP  52
#define SIGTIMER1HP  53

/* Signals defined for all 1967VC*T processors */

#define SIGHW        57
#define SIGSW        62
#define SIGDBG       63

/* Standard signals */

#define SIGABRT 64
#define SIGILL  65
#define SIGINT  66
#define SIGSEGV 67
#define SIGTERM 68
#define SIGFPE  69

#define __SIG_LAST_INTERRUPT    69
#define __SIG_LAST_HW_INTERRUPT 63

#define _SIG_DFL_ASM 0x01
#define _SIG_ERR_ASM 0x02
#define _SIG_IGN_ASM 0x03

#define SIG_DFL ((void (*)(int))_SIG_DFL_ASM)
#define SIG_ERR ((void (*)(int))_SIG_ERR_ASM)
#define SIG_IGN ((void (*)(int))_SIG_IGN_ASM)

#define __SIG_REENABLE_BIT_POS 0
#define __SIG_FAST_BIT_POS     1
#define __SIG_SUPER_BIT_POS    2
#define __SIG_NORMAL_BIT_POS   3
#define __SIG_NONREENT_BIT_POS 4
#define __SIG_ENABLE_BIT_POS   7

#define __SIG_REENABLE (1 << __SIG_REENABLE_BIT_POS)
#define __SIG_NORMAL   (1 << __SIG_NORMAL_BIT_POS)
#define __SIG_FAST     (1 << __SIG_FAST_BIT_POS)
#define __SIG_SUPER    (1 << __SIG_SUPER_BIT_POS)
#define __SIG_NONREENT (1 << __SIG_NONREENT_BIT_POS)
#define __SIG_ENABLE   (1 << __SIG_ENABLE_BIT_POS)

/* arguments for normal_mode() */
#define _NORMAL_MODE_USER  0
#define _NORMAL_MODE_SUPER 1

#if defined(__CMCPPTSH__) /* Hide C code from assembler */
  #ifdef __cplusplus
    extern "C" {
  #endif

  /*
     The following variables can be used by a software exception
     handler (signals 62 and 64-69). The return PC is the address
     of the instruction line following the instruction line that
     caused the exception. The SQSTAT value is the sequencer status
     register.
  */
  extern int _sig_except_pc;   /* return pc */
  extern int _sig_except_stat; /* SQSTAT value */

  typedef int sig_atomic_t;

  /* prototypes for library routines */
  void (*signal(int, void (*func)(int))) (int);
  void (*_Signalf(int, void (*func)(int))) (int);
  void (*_Signals(int, void (*func)(int))) (int);
  void (*signalnr(int, void (*func)(int))) (int);
  void (*_Signalfnr(int, void (*func)(int))) (int);
  void (*_Signalsnr(int, void (*func)(int))) (int);
  void (*_Interrupt(int, void (*func)(int))) (int);
  void (*_Interruptf(int, void (*func)(int))) (int);
  void (*_Interrupts(int, void (*func)(int))) (int);
  void (*_Interruptnr(int, void (*func)(int))) (int);
  void (*_Interruptfnr(int, void (*func)(int))) (int);
  void (*_Interruptsnr(int, void (*func)(int))) (int);
  int raise(int);
  void _normal_mode(int);

  typedef void (*_sig_dispatcher_t)(void);

  void (*_Signal(int, int, void (*func)(int),
        _sig_dispatcher_t, _sig_dispatcher_t)) (int);
  void _Libc_super(void (*func)(), int);
  void _Libc_normal_mode(void);

  /* interrupt dispatchers */

  void __Libc_disp_hw__r(void);  //
  void __Libc_disp_hw_nr(void);
  void __Libc_disp_hw_fr(void);
  void __Libc_disp_hw_sr(void);

  void __Libc_disp_hw__d(void);  //
  void __Libc_disp_hw_nd(void);
  void __Libc_disp_hw_fd(void);
  void __Libc_disp_hw_sd(void);

  void __Libc_disp_hw__r_nr(void);  //
  void __Libc_disp_hw_nr_nr(void);
  void __Libc_disp_hw_fr_nr(void);
  void __Libc_disp_hw_sr_nr(void);

  void __Libc_disp_hw__d_nr(void);  //
  void __Libc_disp_hw_nd_nr(void);
  void __Libc_disp_hw_fd_nr(void);
  void __Libc_disp_hw_sd_nr(void);

  void __Libc_disp_sw(void);

  /* inline definitions of some library functions */

  __inline void (*signal (int _sig, void (*func)(int))) (int)
      { return _Signal(_sig, __SIG_NORMAL, func,
                       __Libc_disp_hw_nd, __Libc_disp_sw); }
  __inline void (*signalf (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_FAST, func,
                        __Libc_disp_hw_fd, __Libc_disp_sw); }
  __inline void (*signals (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_SUPER, func,
                        __Libc_disp_hw_sd, __Libc_disp_sw); }

  __inline void (*signalnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_NORMAL, func,
                        __Libc_disp_hw_nd_nr, __Libc_disp_sw); }
  __inline void (*signalfnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_FAST, func,
                        __Libc_disp_hw_fd_nr, __Libc_disp_sw); }
  __inline void (*signalsnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_SUPER, func,
                        __Libc_disp_hw_sd_nr, __Libc_disp_sw); }

  __inline void (*interrupt (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_REENABLE | __SIG_NORMAL,
                        func, __Libc_disp_hw_nr, __Libc_disp_sw);}
  __inline void (*interruptf (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_REENABLE | __SIG_FAST,
                        func, __Libc_disp_hw_fr, __Libc_disp_sw);}
  __inline void (*interrupts (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_REENABLE | __SIG_SUPER,
                        func, __Libc_disp_hw_sr, __Libc_disp_sw);}

  __inline void (*interruptnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_REENABLE | __SIG_NORMAL,
                        func, __Libc_disp_hw_nr_nr, __Libc_disp_sw);}
  __inline void (*interruptfnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_REENABLE | __SIG_FAST,
                        func, __Libc_disp_hw_fr_nr, __Libc_disp_sw);}
  __inline void (*interruptsnr (int _sig, void (*func)(int))) (int)
      { return _Signal (_sig, __SIG_NONREENT | __SIG_REENABLE | __SIG_SUPER,
                        func, __Libc_disp_hw_sr_nr, __Libc_disp_sw);}

  __inline void normal_mode (int _mode)
      { _Libc_super(_Libc_normal_mode, _mode); }

  /* masking macros for some library functions */

  #define signal(sig, func) _Signal((sig), __SIG_NORMAL, (func), \
      __Libc_disp_hw_nd, __Libc_disp_sw)
  #define _Signalf(sig, func) _Signal((sig), __SIG_FAST, (func), \
      __Libc_disp_hw_fd, __Libc_disp_sw)
  #define _Signals(sig, func) _Signal((sig), __SIG_SUPER, (func), \
      __Libc_disp_hw_sd, __Libc_disp_sw)

  #define _Signalnr(sig, func) _Signal((sig), __SIG_NORMAL, (func), \
      __Libc_disp_hw_nd_nr, __Libc_disp_sw)
  #define _Signalfnr(sig, func) _Signal((sig), __SIG_FAST, (func), \
      __Libc_disp_hw_fd_nr, __Libc_disp_sw)
  #define _Signalsnr(sig, func) _Signal((sig), __SIG_SUPER, (func), \
      __Libc_disp_hw_sd_nr, __Libc_disp_sw)

  #define _Interrupt(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_NORMAL, (func), \
      __Libc_disp_hw_nr, __Libc_disp_sw)
  #define _Interruptf(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_FAST, (func), \
      __Libc_disp_hw_fr, __Libc_disp_sw)
  #define _Interrupts(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_SUPER, (func), \
      __Libc_disp_hw_sr, __Libc_disp_sw)

  #define _Interruptnr(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_NORMAL, (func), \
      __Libc_disp_hw_nr_nr, __Libc_disp_sw)
  #define _Interruptfnr(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_FAST, (func), \
      __Libc_disp_hw_fr_nr, __Libc_disp_sw)
  #define _Interruptsnr(sig, func) _Signal((sig), \
      __SIG_REENABLE | __SIG_SUPER, (func), \
      __Libc_disp_hw_sr_nr, __Libc_disp_sw)

  #define _Normal_mode(mode) \
      _Libc_super(_Libc_normal_mode, (mode))

  /* macros that make extensions available without leading underscores */

  #define signalf      _Signalf
  #define signals      _Signals
  #define interrupt    _Interrupt
  #define interruptf   _Interruptf
  #define interrupts   _Interrupts
  #define signalnr     _Signalfnr
  #define signalfnr    _Signalfnr
  #define signalsnr    _Signalsnr
  #define interruptnr  _Interruptnr
  #define interruptfnr _Interruptfnr
  #define interruptsnr _Interruptsnr
  #define normal_mode  _Normal_mode

  #ifdef __cplusplus
    }
  #endif
#endif /* __CMCPPTSH__ */

#endif /* __SIGNAL_H */

