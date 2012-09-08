/*
**	MEYER Thibault		(meyer_t@0xbaadf00d.com)
**
**	Filename: ProcessMemory.h
**	Comment : This is a simple class to help developer
**			  to read and write data on a running 
**			  application memory area.
*/
#ifndef H_PROCESS_MEMORY_H_
# define H_PROCESS_MEMORY_H_
# include <stdint.h>
# include <Windows.h>

class				ProcessMemory
{
private:
	HWND			m_hWindow;
	HANDLE			m_hProc;
	DWORD			m_PID;

public:
	ProcessMemory(void);
	~ProcessMemory(void);

	/* LOAD / CLOSE*/
	bool			loadProcessByWindowName(const char* name);
	bool			loadProcessByPID(DWORD pid);
	bool			closeHandle(void);

	/* READ OPERATIONS */
	unsigned char	read1(uint32_t address);
	uint16_t		read2(uint32_t address);
	ULONG32			read4(uint32_t address);
	ULONG64			read8(uint32_t address);
	unsigned int	readData(char* out, uint32_t address, uint32_t len);

	/* WRITE OPERATION */
	bool			write1(uint32_t address, unsigned char value);
	bool			write2(uint32_t address, uint16_t value);
	bool			write4(uint32_t address, ULONG32 value);
	bool			write8(uint32_t address, ULONG64 value);
	bool			writeData(uint32_t address, const char* in, uint32_t len);
};

#endif
