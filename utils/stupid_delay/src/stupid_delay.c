#include "stupid_delay.h"

void StupidDelay(int waitTicks) {
	int i;
	for (i = 0; i < waitTicks; i++);
}
