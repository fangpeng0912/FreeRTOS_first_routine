#ifndef _BIT_BAND_H_
#define _BIT_BAND_H_

#include "stdint.h"

#define BitBandAliasAddr(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 \
                                      + ((addr & 0x000FFFFF) << 5) \
														         	+ (bitnum << 2))
															
#define BitBandAlias(addr, bitnum) *((volatile uint32_t*)(BitBandAliasAddr(addr, bitnum)))

#endif
