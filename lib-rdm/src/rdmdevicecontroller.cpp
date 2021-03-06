/**
 * @file rdmdevicecontroller.cpp
 *
 */
/* Copyright (C) 2017-2019 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
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
#include <string.h>

#include "rdmdevicecontroller.h"
#include "rdmdevice.h"

#include "debug.h"

#ifndef ALIGNED
 #define ALIGNED __attribute__ ((aligned (4)))
#endif

#if defined (H3)
 static const char DEVICE_LABEL[] ALIGNED = "Orange Pi RDM Controller";
#else
 static const char DEVICE_LABEL[] ALIGNED = "Raspberry Pi RDM Controller";
#endif

RDMDeviceController::RDMDeviceController(void) {
	DEBUG_ENTRY

	struct TRDMDeviceInfoData info;

	info.data = (uint8_t *) DEVICE_LABEL;
	info.length = sizeof(DEVICE_LABEL) - 1;

	SetLabel(&info);

	DEBUG_EXIT
}

RDMDeviceController::~RDMDeviceController(void) {
}

void RDMDeviceController::Init(void) {
	DEBUG_ENTRY

	RDMDevice::Init();

	DEBUG_EXIT
}

void RDMDeviceController::Print(void) {
	RDMDevice::Print();
}
