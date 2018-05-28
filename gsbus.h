/*
 * gsbus.h
 *
 *  Created on: 13 May 2018
 *      Author: George
 */
#include <stdint.h>

#define CLR_BIT 0
#define UPD_BIT 127

uint8_t GSBusMakePacket(uint32_t addr, uint32_t data, uint16_t gprg, uint8_t* pPacket);
uint8_t getByte(uint8_t bit_addr);


