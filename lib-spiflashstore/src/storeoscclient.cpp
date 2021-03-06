/**
 * @file storeoscclient.cpp
 *
 */
/* Copyright (C) 2019 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <assert.h>

#include "storeoscclient.h"

#include "oscclientparams.h"

#include "spiflashstore.h"

#include "debug.h"

StoreOscClient *StoreOscClient::s_pThis = 0;

StoreOscClient::StoreOscClient(void) {
	DEBUG_ENTRY

	s_pThis = this;

	DEBUG_PRINTF("%p", s_pThis);

	DEBUG_EXIT
}

StoreOscClient::~StoreOscClient(void) {
	DEBUG_ENTRY

	DEBUG_EXIT
}

void StoreOscClient::Update(const struct TOscClientParams* pOscClientParams) {
	DEBUG_ENTRY

	SpiFlashStore::Get()->Update(STORE_OSC_CLIENT, (void *)pOscClientParams, sizeof(struct TOscClientParams));

	DEBUG_EXIT
}

void StoreOscClient::Copy(struct TOscClientParams* pOscClientParams) {
	DEBUG_ENTRY

	SpiFlashStore::Get()->Copy(STORE_OSC_CLIENT, (void *)pOscClientParams, sizeof(struct TOscClientParams));

	DEBUG_EXIT
}
