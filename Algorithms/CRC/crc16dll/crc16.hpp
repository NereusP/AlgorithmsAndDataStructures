#ifndef _CRC16_HPP_
#define _CRC16_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN(a,b) (((a)<=(b))?(a):(b))
#define MAX(a,b) (((a)>=(b))?(a):(b))

/*
Name				Polynomial	Starting value	Big-Edian/Little-endian	Result processing
CRC16_CCITT			0x1021		0x0000			Little-endian			XOR with 0x0000
CRC16_CCITT_FALSE	0x1021		0xFFFF			Little-endian			XOR with 0x0000
CRC16_XMODEM		0x1021		0x0000			Little-endian			XOR with 0x0000
CRC16_X25			0x1021		0xFFFF			Little-endian			XOR with 0xFFFF
CRC16_MODBUS		0x8005		0xFFFF			Little-endian			XOR with 0x0000
CRC16_IBM			0x8005		0x0000			Little-endian			XOR with 0x0000
CRC16_MAXIM			0x8005		0x0000			Little-endian			XOR with 0xFFFF
CRC16_USB			0x8005		0xFFFF			Little-endian			XOR with 0xFFFF
*/

enum CRC16_TYPE { CRC16_CCITT = 0, CRC16_CCITT_FALSE = 1, CRC16_XMODEM = 2, CRC16_X25 = 3, CRC16_MODBUS = 4, CRC16_IBM = 5, CRC16_MAXIM = 6, CRC16_USB = 7 };

#ifdef CRC16_EXPORTS
extern "C" _declspec(dllexport) int CalcCRC16(void* buf, uint32_t len, CRC16_TYPE crc16_type, uint16_t& crc16value);
extern "C" _declspec(dllexport) int CalcCRC16Ex(void* buf, uint32_t len, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);
extern "C" _declspec(dllexport) int CalcCRC16_file(FILE* fr, CRC16_TYPE crc16_type, uint16_t& crc16value);
extern "C" _declspec(dllexport) int CalcCRC16Ex_file(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);
#else
extern "C" _declspec(dllimport) int CalcCRC16(void* buf, uint32_t len, CRC16_TYPE crc16_type, uint16_t& crc16value);
extern "C" _declspec(dllimport) int CalcCRC16Ex(void* buf, uint32_t len, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);
extern "C" _declspec(dllimport) int CalcCRC16_file(FILE* fr, CRC16_TYPE crc16_type, uint16_t& crc16value);
extern "C" _declspec(dllimport) int CalcCRC16Ex_file(FILE* fr, uint16_t& crc16value, uint16_t crc_startvalue, uint16_t polyrepres);
#endif

#endif
