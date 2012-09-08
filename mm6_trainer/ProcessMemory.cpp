/*
**	MEYER Thibault		(meyer_t@0xbaadf00d.com)
**
**	Filename: ProcessMemory.cpp
**	Comment : This is a simple class to help developer
**			  to read and write data on a running 
**			  application memory area.
*/
#include "ProcessMemory.h"
#include <iostream>

ProcessMemory::ProcessMemory(void)
{
	m_hWindow = NULL;
	m_hProc = NULL;
	m_PID = 0;
}

ProcessMemory::~ProcessMemory(void)
{
	if (m_hProc)
		CloseHandle(m_hProc);
}

bool			ProcessMemory::loadProcessByWindowName(const char* winName)
{
	DWORD		retVal = 0;

	m_hWindow = FindWindowA(NULL, winName);
	if (m_hWindow) {
		retVal = GetWindowThreadProcessId(m_hWindow, (LPDWORD)&m_PID);
		if (retVal) {
			m_hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, m_PID);
			if (m_hProc)
				return (true);
		}
	}
	return (false);
}

bool			ProcessMemory::loadProcessByPID(DWORD pid)
{
	DWORD		retVal = 0;

	retVal = GetWindowThreadProcessId(m_hWindow, (LPDWORD)&pid);
	if (retVal) {
		m_PID = pid;
		m_hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, m_PID);
		if (m_hProc)
			return (true);
	}
	return (false);
}

bool			ProcessMemory::closeHandle(void)
{
	if (m_hProc) {
		CloseHandle(m_hProc);
		m_hProc = NULL;
		return (true);
	}
	return (false);
}

unsigned char		ProcessMemory::read1(uint32_t address)
{
	unsigned char	val = 0;
	SIZE_T			nbReaded = 0;

	ReadProcessMemory(m_hProc, (LPCVOID)address, (LPVOID)&val, 1, &nbReaded);
	return (val);
}

uint16_t			ProcessMemory::read2(uint32_t address)
{
	uint16_t		val = 0;
	SIZE_T			nbReaded = 0;

	ReadProcessMemory(m_hProc, (LPCVOID)address, (LPVOID)&val, 2, &nbReaded);
	return (val);
}

ULONG32				ProcessMemory::read4(uint32_t address)
{
	ULONG32		val = 0;
	SIZE_T		nbReaded = 0;

	ReadProcessMemory(m_hProc, (LPCVOID)address, (LPVOID)&val, 4, &nbReaded);
	return (val);
}

ULONG64					ProcessMemory::read8(uint32_t address)
{
	ULONG64				val = 0;
	SIZE_T				nbReaded = 0;

	ReadProcessMemory(m_hProc, (LPCVOID)address, (LPVOID)&val, 8, &nbReaded);
	return (val);
}

unsigned int	ProcessMemory::readData(char* out, uint32_t address, uint32_t len)
{
	SIZE_T		nbReaded = 0;

	ReadProcessMemory(m_hProc, (LPCVOID)address, (LPVOID)out, len, &nbReaded);
	return (nbReaded);
}

bool			ProcessMemory::write1(uint32_t address, unsigned char value)
{
	SIZE_T		nbWritten = 0;

	return (WriteProcessMemory(m_hProc, (LPVOID)address, (LPCVOID)&value, 1, &nbWritten));
}

bool			ProcessMemory::write2(uint32_t address, uint16_t value)
{
	SIZE_T		nbWritten = 0;

	return (WriteProcessMemory(m_hProc, (LPVOID)address, (LPCVOID)&value, sizeof(uint16_t), &nbWritten));
}

bool			ProcessMemory::write4(uint32_t address, ULONG32 value)
{
	SIZE_T		nbWritten = 0;

	return (WriteProcessMemory(m_hProc, (LPVOID)address, (LPCVOID)&value, sizeof(ULONG32), &nbWritten));
}

bool			ProcessMemory::write8(uint32_t address, ULONG64 value)
{
	SIZE_T		nbWritten = 0;

	return (WriteProcessMemory(m_hProc, (LPVOID)address, (LPCVOID)&value, sizeof(ULONG64), &nbWritten));
}

bool			ProcessMemory::writeData(uint32_t address, const char* in, uint32_t len)
{
	SIZE_T		nbWritten = 0;

	return (WriteProcessMemory(m_hProc, (LPVOID)address, (LPCVOID)in, len, &nbWritten));
}
