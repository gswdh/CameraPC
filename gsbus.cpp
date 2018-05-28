/*
 * gsbus.cpp
 *
 *  Created on: 13 May 2018
 *      Author: George
 */

#include "gsbus.h"

uint8_t GSBusMakePacket(uint32_t addr, uint32_t data, uint16_t gprg, uint8_t* pPacket)
{
	// Keep track of how many bytes we make 
	uint8_t data_counter = 0;

	// First, send a clear bit
	pPacket[data_counter++] = getByte(CLR_BIT);

	// Now go through the data,
	for(uint8_t i = 0; i < 32; i++)
	{
		if (data & (1 << i))
			pPacket[data_counter++] = getByte(i + 1);
	}

	// address,
	for(uint8_t i = 0; i < 32; i++)
	{
		if (addr & (1 << i))
			pPacket[data_counter++] = getByte(i + 33);
	}
	// and general purpose register.
	for(uint8_t i = 0; i < 16; i++)
	{
		if (gprg & (1 << i))
			pPacket[data_counter++] = getByte(i + 97);
	}

	// Finally set the update bit to latch in the data
	pPacket[data_counter++] = getByte(UPD_BIT);

	return data_counter;
}


uint8_t getByte(uint8_t bit_addr)
{
	return (bit_addr << 1) + 1;
}
