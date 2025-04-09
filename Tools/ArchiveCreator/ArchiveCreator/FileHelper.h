#ifndef FILE_HELPER
#define FILE_HELPER

#include "Defines.h"

#include <fstream>
#include <stdarg.h>

namespace utils
{
	class FileStream
	{
	protected:
		int m_fileSize;

	public:
		FileStream() : m_fileSize(0) {}
		virtual ~FileStream() {}

		virtual bool OpenFile(const char* fileName, ABYSS_FILE_TYPE fileType) = 0;
		virtual void CloseFile() = 0;

		virtual void SeekStreamToStart() = 0;
		virtual void SeekStreamToEnd() = 0;
		virtual void SeekPast(int offset) = 0;
		virtual int GetSeekPosition() = 0;

		virtual bool Read(char* buffer, int bytesToRead) = 0;
		virtual bool Write(char* buffer, int bytesToWrite) = 0;

		int GetFileSize() { return m_fileSize; }
		virtual bool IsOpen() = 0;
	};

	class FileInputStream : public FileStream
	{
		std::ifstream m_fileStream;

	public:
		FileInputStream() {}

		FileInputStream(const char* fileName, ABYSS_FILE_TYPE fileType)
		{
			OpenFile(fileName, fileType);
		}

		~FileInputStream()
		{
			CloseFile();
		}

		bool OpenFile(const char* fileName, ABYSS_FILE_TYPE fileType);
		void CloseFile();

		void SeekStreamToStart();
		void SeekStreamToEnd();
		void SeekPast(int offset);
		int GetSeekPosition();

		bool Read(char* buffer, int bytesToRead);
		bool Write(char* buffer, int bytesToWrite);

		bool IsOpen();
	};

	class FileOutputStream : public FileStream
	{
		std::ofstream m_fileStream;

	public:
		FileOutputStream() {}

		FileOutputStream(const char* fileName, ABYSS_FILE_TYPE fileType)
		{
			OpenFile(fileName, fileType);
		}

		~FileOutputStream()
		{
			CloseFile();
		}

		bool OpenFile(const char* fileName, ABYSS_FILE_TYPE fileType);
		void CloseFile();

		void SeekStreamToStart();
		void SeekStreamToEnd();
		void SeekPast(int offset);
		int GetSeekPosition();

		bool Read(char* buffer, int bytesToRead);
		bool Write(char* buffer, int bytesToWrite);

		bool IsOpen();
	};
}

#endif