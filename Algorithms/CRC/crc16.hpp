#ifndef _CRC16_HPP_
#define _CRC16_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define min(a,b) ((a<=b)?a:b)
#define max(a,b) ((a>=b)?a:b)

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

enum CRC16_TYPE { CRC16_CCITT = 0, CRC16_CCITT_FALSE = 1, CRC16_XMODEM = 2, CRC16_X25 = 3, CRC16_MODBUS = 4, CRC16_IBM = 5, CRC16_MAXIM = 6, CRC16_USB = 7 };
int CalcCRC16(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);

int CRC16Calc(FILE* fr, CRC16_TYPE crc16_type, uint16_t& crc16value)
{
	int value = 0;
	switch (crc16_type)
	{
	case CRC16_CCITT:
		value = CalcCRC16(fr, crc16value, 0x0000, 0x1021);
		break;
	case CRC16_CCITT_FALSE:
		value = CalcCRC16(fr, crc16value, 0xFFFF, 0x1021);
		break;
	case CRC16_XMODEM:
		value = CalcCRC16(fr, crc16value, 0x0000, 0x1021);
		break;
	case CRC16_X25:
		value = CalcCRC16(fr, crc16value, 0x0000, 0x1021);
		break;
	case CRC16_MODBUS:
		value = CalcCRC16(fr, crc16value, 0xFFFF, 0x8005);
		break;
	case CRC16_IBM:
		value = CalcCRC16(fr, crc16value, 0x0000, 0x8005);
		break;
	case CRC16_MAXIM:
		value = CalcCRC16(fr, crc16value, 0x0000, 0x8005);
		break;
	case CRC16_USB:
		value = CalcCRC16(fr, crc16value, 0xFFFF, 0x8005);
		break;
	default:
		value = -1;
		break;
	}
	return value;
}

int CalcCRC16(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres)
{
	if ((fr == nullptr) || ((crc_startvalue != 0x0000) && (crc_startvalue != 0xFFFF)))
	{
		printf("CRC16:Invalid parameter!\n");
		return -1;
	}
	uint16_t crc16reg = crc_startvalue;
	uint16_t r_polyrepres = 0x00;
	uint32_t filesize = 0;
	uint8_t* prdatabuffer = nullptr;
	for (uint8_t a = 0; a < 16; a++)
	{
		r_polyrepres <<= 1;
		r_polyrepres |= (polyrepres & 0x01);
		polyrepres >>= 1;
	}
	fseek(fr, 0, SEEK_SET);
	fseek(fr, 0, SEEK_END);
	filesize = ftell(fr);
	prdatabuffer = new uint8_t[0x400000];
	fseek(fr, 0, SEEK_SET);
	while (filesize>0)
	{
		uint32_t readsize = min(filesize, 0x400000);
		fread(prdatabuffer, 1, readsize, fr);
		filesize = filesize - readsize;
		for (uint32_t i = 0; i<readsize; i++)
		{
			crc16reg = prdatabuffer[i] ^ crc16reg;
			for (uint8_t shift_t = 0; shift_t<8; shift_t++)
			{
				if ((crc16reg & 0x01) == 0x01)
				{
					crc16reg = crc16reg >> 1;
					crc16reg ^= r_polyrepres;
				}
				else
				{
					crc16reg = crc16reg >> 1;
				}
			}
		}
	}
	//crc16value = (crc16reg >> 8) | (crc16reg << 8);
	crc16value = crc16reg;
	delete[] prdatabuffer;
	prdatabuffer = nullptr;
	return 0;
}

#endif

