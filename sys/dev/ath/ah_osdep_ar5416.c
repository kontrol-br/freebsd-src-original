/*-
 * Copyright 2017 Adrian Chadd <adrian@FreeBSD.org>.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 *
 */

#include "opt_ah.h"
#include "opt_wlan.h"

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>

#include <dev/ath/ath_hal/ah.h>
#include <dev/ath/ath_hal/ah_internal.h>

extern struct ath_hal_chip AR5416_chip;
extern struct ath_hal_chip AR9160_chip;
extern struct ath_hal_chip AR9280_chip;
extern struct ath_hal_chip AR9285_chip;
extern struct ath_hal_chip AR9287_chip;

extern struct ath_hal_rf RF2133_rf;
extern struct ath_hal_rf RF9280_rf;
extern struct ath_hal_rf RF9285_rf;
extern struct ath_hal_rf RF9287_rf;

static int
ath_hal_ar5416_modevent(module_t mod __unused, int type, void *data __unused)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		ath_hal_add_chip(&AR5416_chip);
		ath_hal_add_chip(&AR9160_chip);
		ath_hal_add_chip(&AR9280_chip);
		ath_hal_add_chip(&AR9285_chip);
		ath_hal_add_chip(&AR9287_chip);
		ath_hal_add_rf(&RF2133_rf);
		ath_hal_add_rf(&RF9280_rf);
		ath_hal_add_rf(&RF9285_rf);
		ath_hal_add_rf(&RF9287_rf);
		printf("[ar5416] loaded\n");
		break;

	case MOD_UNLOAD:
		ath_hal_remove_chip(&AR5416_chip);
		ath_hal_remove_chip(&AR9160_chip);
		ath_hal_remove_chip(&AR9280_chip);
		ath_hal_remove_chip(&AR9285_chip);
		ath_hal_remove_chip(&AR9287_chip);
		ath_hal_remove_rf(&RF2133_rf);
		ath_hal_remove_rf(&RF9280_rf);
		ath_hal_remove_rf(&RF9285_rf);
		ath_hal_remove_rf(&RF9287_rf);
		printf("[ar5416] unloaded\n");
		break;

	case MOD_SHUTDOWN:
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}

DEV_MODULE(ath_hal_ar5416, ath_hal_ar5416_modevent, NULL);
MODULE_VERSION(ath_hal_ar5416, 1);
MODULE_DEPEND(ath_hal_ar5416, ath_hal, 1, 1, 1);
MODULE_DEPEND(ath_hal_ar5416, ath_hal_ar5212, 1, 1, 1);
