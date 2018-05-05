#include "crc16.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
Name				Polynomial	Starting value	Big-Edian/Little-endian	Result processing
CRC16_CCITT			0x1021		0x0000			Little-endian			XOR with 0x0000
CRC16_CCITT_FALSE	0x1021		0xFFFF			Little-endian			XOR with 0x0000
CRC16_XMODEM		0x1021		0x0000			Little-endian			XOR with 0x0000
CRC16_X25			0x1021		0x0000			Little-endian			XOR with 0xFFFF
CRC16_MODBUS		0x8005		0xFFFF			Little-endian			XOR with 0x0000
CRC16_IBM			0x8005		0x0000			Little-endian			XOR with 0x0000
CRC16_MAXIM			0x8005		0x0000			Little-endian			XOR with 0xFFFF
CRC16_USB			0x8005		0xFFFF			Little-endian			XOR with 0xFFFF

*/

int main() 
{
	FILE* fr = nullptr;
	fr = fopen("./ThunderSpeed.exe", "rb+");
	uint16_t crc16le = 0x00;
	uint16_t crc16be = 0x00;
	if (fr != nullptr)
	{
		if (CRC16Calc(fr, CRC16_IBM, crc16le) != -1)
		{
			printf("CRC16 Little-endian:0x%04X\n", crc16le);
			crc16be = (crc16le >> 8) | (crc16le << 8);
			printf("CRC16 Big-edian:0x%04X\n", crc16be);
		}
		fclose(fr);
	}
	else
	{
		printf("Can't open file!\n");
	}
    return 0;
}

