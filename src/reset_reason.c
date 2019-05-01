#include "reset_reason.h"
#include "hal_1967VN034R1.h"

static RstRsn_t reset_rsn = NORMAL_RESET;

// -----------------------------------------------------------------------------
void RstRsnDetect(void) {
	if ((!LX_CMU->SYS_STS.b.POR) && (LX_CMU->SYS_STS.b.RST)) {
		reset_rsn = WD_TIMER;
	} else {
		reset_rsn = NORMAL_RESET;
	}
	LX_CMU->SYS_STS.word =0;
}

// -----------------------------------------------------------------------------
RstRsn_t RstRsnGetState(void) {
	return reset_rsn;
}
