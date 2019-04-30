#pragma once

#include <stddef.h>
#include "errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ************************    Threads    ************************
 */

typedef void *pthread_t;

typedef struct sched_param
{
	int sched_priority;
} sched_param_t;

typedef struct pthread_attr_t_ *pthread_attr_t;

extern int pthread_create(pthread_t *th, const pthread_attr_t *attr, void*(*th_func)(void *), void *arg);
extern int pthread_cancel(pthread_t th);
extern void pthread_exit(void *val);
extern pthread_t pthread_self(void);

extern int pthread_attr_init(pthread_attr_t *attr);
extern int pthread_attr_destroy(pthread_attr_t *attr);
extern int pthread_getattr_np(pthread_t th, pthread_attr_t *attr);
extern int pthread_attr_setschedparam(pthread_attr_t *attr, const sched_param_t *param);
extern int pthread_attr_getschedparam(const pthread_attr_t *attr, sched_param_t *param);

extern int pthread_setschedprio(pthread_t th, int prio);

/*
 ************************    Mutex    ************************
 */

typedef struct pthread_mutex_t_ *pthread_mutex_t;
typedef struct pthread_mutexattr_t_ *pthread_mutexattr_t;

extern int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
extern int pthread_mutex_destroy(pthread_mutex_t *mutex);

extern int pthread_mutex_lock (pthread_mutex_t *mutex);
extern int pthread_mutex_trylock(pthread_mutex_t *mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *mutex);

#ifdef __cplusplus
}
#endif
