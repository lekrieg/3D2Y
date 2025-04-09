#ifndef FILE_ARCHIVER_HELPER_H
#define FILE_ARCHIVER_HELPER_H

#include "FileHelper.h"

#include <stdio.h>
#include <string.h>

namespace utils
{
#define ARCHIVE_ID "AE1"
#define ARCHIVE_MAJOR 1
#define ARCHIVE_MINOR 0

	class ArchiveHeader
	{
		char m_id[5] = { '\0' };
		int m_majorVersion;
		int m_minorVersion;
		int m_totalFiles;

	public:
		ArchiveHeader() : m_majorVersion(0), m_minorVersion(0), m_totalFiles(0) {}

		char* GetId() { return m_id; }
		int GetMajorVersion() const { return m_majorVersion; }
		int GetMinorVersion() const { return m_minorVersion; }
		int GetTotalFiles() const { return m_totalFiles; }

		void SetMajorVersion(int major) { m_majorVersion = major; }
		void SetMinorVersion(int minor) { m_minorVersion = minor; }
		void SetTotalFiles(int total) { m_totalFiles = total; }

		void SetId(const char* id)
		{
			if (id == nullptr)
			{
				return;
			}

			memcpy(m_id, id, 4);
			m_id[4] = '\0';
		}
	};

	class ArchiveFileHeader
	{
		char m_fileName[256] = { '\0' };
		int m_size;
		int m_offset;

	public:
		ArchiveFileHeader() : m_size(0), m_offset(0) {}

		char* GetFileName() { return m_fileName; }
		int GetSize() const { return m_size; }
		int GetOffset() const { return m_offset; }

		void SetSize(int size) { m_size = size; }
		void SetOffset(int offset) { m_offset = offset; }

		void SetFileName(char* fileName)
		{
			int len;
			m_fileName[0] = '\0';

			if (fileName == nullptr)
			{
				return;
			}

			len = strlen(fileName);

			if (len > 255)
			{
				return;
			}

			memcpy(m_fileName, fileName, len);
			m_fileName[len] = '\0';
		}

		void operator=(ArchiveFileHeader& header)
		{
			m_size = header.GetSize();
			SetFileName(header.GetFileName());
			m_offset = header.GetOffset();
		}
	};

	class Archive
	{
		ArchiveFileHeader* m_headers;
		FileInputStream m_fileStream;
		int m_totalHeaders;

	public:
		Archive();
		~Archive();

		bool ReadArchiveFile(char* fileName);
		bool WriteArchiveFile(char* fileName, ArchiveFileHeader* headers, int totalHeaders);
		void CloseArchive();

		bool Extract(int index, char* location);
		bool Extract(char* fileName, char* location);

		int GetFileIndex(char* fileName);
		bool GetFileData(int index, char* buffer, int bytesToRead);
		bool GetFileData(char* fileName, char* buffer, int bytesToRead);
		bool GetFileHeaderInfoByIndex(int index, ArchiveFileHeader* fh);

		int GetTotalHeaders() const { return m_totalHeaders; }

		bool IsArchiveOpen()
		{
			return m_fileStream.IsOpen();
		}
	};
}

#endif