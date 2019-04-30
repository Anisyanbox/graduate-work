#ifndef TIME_H
#define TIME_H

#include <stdlib.h>
#include <sysreg.h>

typedef long long clock_t;
static __inline clock_t clock(void)
{
    return __read_ccnt();
}

typedef clock_t CORE_TICKS;
typedef double  secs_ret;

void start_time(void);
void stop_time(void);
CORE_TICKS get_time(void);
secs_ret time_in_secs(CORE_TICKS ticks);

#endif /* TIME_H */
