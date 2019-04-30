#pragma once

#include <stddef.h>
#include "errno.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sem_t_ *sem_t;

extern int sem_init(sem_t *sem, int pshared, unsigned int value);
extern int sem_destroy(sem_t *sem);
extern int sem_getvalue(sem_t *sem, int *sval);
extern int sem_post(sem_t *sem);
extern int sem_wait(sem_t *sem);
extern int sem_trywait(sem_t *sem);

#ifdef __cplusplus
}
#endif
