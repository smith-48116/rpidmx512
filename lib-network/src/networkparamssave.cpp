/**
 * @file networkparams.cpp
 *
 */
/* Copyright (C) 2019-2020 by Arjan van Vught mailto:info@orangepi-dmx.nl
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

#if !defined(__clang__)	// Needed for compiling on MacOS
 #pragma GCC push_options
 #pragma GCC optimize ("Os")
#endif

#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "network.h"
#include "networkparams.h"
#include "networkconst.h"

#include "propertiesbuilder.h"

#include "debug.h"

void NetworkParams::Builder(const struct TNetworkParams *ptNetworkParams, uint8_t *pBuffer, uint32_t nLength, uint32_t &nSize) {
	DEBUG_ENTRY

	assert(pBuffer != 0);

	if (ptNetworkParams != 0) {
		memcpy(&m_tNetworkParams, ptNetworkParams, sizeof(struct TNetworkParams));
	} else {
		m_pNetworkParamsStore->Copy(&m_tNetworkParams);
	}

	PropertiesBuilder builder(NetworkConst::PARAMS_FILE_NAME, pBuffer, nLength);

	builder.Add(NetworkConst::PARAMS_USE_DHCP, m_tNetworkParams.bIsDhcpUsed, isMaskSet(NETWORK_PARAMS_MASK_DHCP));
	builder.AddIpAddress(NetworkConst::PARAMS_IP_ADDRESS, m_tNetworkParams.nLocalIp, isMaskSet(NETWORK_PARAMS_MASK_IP_ADDRESS));
	builder.AddIpAddress(NetworkConst::PARAMS_NET_MASK, m_tNetworkParams.nNetmask, isMaskSet(NETWORK_PARAMS_MASK_NET_MASK));
	builder.AddIpAddress(NetworkConst::PARAMS_DEFAULT_GATEWAY, m_tNetworkParams.nGatewayIp, isMaskSet(NETWORK_PARAMS_MASK_DEFAULT_GATEWAY));

	if (!isMaskSet(NETWORK_PARAMS_MASK_HOSTNAME)) {
		strncpy((char *)m_tNetworkParams.aHostName, Network::Get()->GetHostName(), NETWORK_HOSTNAME_SIZE);
		m_tNetworkParams.aHostName[NETWORK_HOSTNAME_SIZE - 1] = '\0';
	}
	builder.Add(NetworkConst::PARAMS_HOSTNAME, (const char *)m_tNetworkParams.aHostName, isMaskSet(NETWORK_PARAMS_MASK_HOSTNAME));

	builder.AddIpAddress(NetworkConst::PARAMS_NTP_SERVER, m_tNetworkParams.nNtpServerIp, isMaskSet(NETWORK_PARAMS_MASK_NTP_SERVER));
	builder.Add(NetworkConst::PARAMS_NTP_UTC_OFFSET, m_tNetworkParams.fNtpUtcOffset, isMaskSet(NETWORK_PARAMS_MASK_NTP_UTC_OFFSET));

	nSize = builder.GetSize();

	DEBUG_PRINTF("nSize=%d", nSize);

	DEBUG_EXIT
	return;
}

void NetworkParams::Save(uint8_t *pBuffer, uint32_t nLength, uint32_t &nSize) {
	DEBUG_ENTRY

	if (m_pNetworkParamsStore == 0) {
		nSize = 0;
		DEBUG_EXIT
		return;
	}

	Builder(0, pBuffer, nLength, nSize);

	return;
}
