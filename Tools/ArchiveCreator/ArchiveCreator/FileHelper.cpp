#include "FileHelper.h"

namespace utils
{
	bool FileInputStream::OpenFile(const char* fileName, ABYSS_FILE_TYPE fileType)
	{
		if (IsOpen())
		{
			CloseFile();
		}

		if (fileType == ABYSS_FILE_TYPE::ABYSS_TEXT_FILE)
		{
			m_fileStream.open(fileName, std::ifstream::in);
		}
		else
		{
			m_fileStream.open(fileName, std::ifstream::in | std::ifstream::binary);
		}

		m_fileStream.seekg(0, std::ios::end);
		m_fileSize = m_fileStream.tellg();
		m_fileStream.seekg(0, std::ios::beg);
		m_fileSize++;

		return IsOpen();
	}

	void FileInputStream::CloseFile()
	{
		m_fileStream.close();
	}

	void FileInputStream::SeekStreamToStart()
	{
		m_fileStream.seekg(0, std::ios::beg);
	}

	void FileInputStream::SeekStreamToEnd()
	{
		m_fileStream.seekg(0, std::ios::end);
	}

	void FileInputStream::SeekPast(int offset)
	{
		m_fileStream.seekg(offset, std::ios::cur);
	}

	int FileInputStream::GetSeekPosition()
	{
		return m_fileStream.tellg();
	}

	bool FileInputStream::Read(char* buffer, int bytesToRead)
	{
		if (!IsOpen() || buffer == nullptr || bytesToRead <= 0)
		{
			return false;
		}

		m_fileStream.read(buffer, bytesToRead);

		return true;
	}

	bool FileInputStream::Write(char* buffer, int bytesToWrite)
	{
		return false;
	}

	bool FileInputStream::IsOpen()
	{
		if (!m_fileStream.is_open())
		{
			return false;
		}

		return true;
	}

	// OUTPUT FILE

	bool FileOutputStream::OpenFile(const char* fileName, ABYSS_FILE_TYPE fileType)
	{
		if (IsOpen())
		{
			CloseFile();
		}

		if (fileType == ABYSS_FILE_TYPE::ABYSS_TEXT_FILE)
		{
			m_fileStream.open(fileName, std::ofstream::in | std::ofstream::trunc);
		}
		else
		{
			m_fileStream.open(fileName, std::ofstream::in | std::ofstream::trunc | std::ofstream::binary);
		}

		return IsOpen();
	}

	void FileOutputStream::CloseFile()
	{
		m_fileStream.close();
	}

	void FileOutputStream::SeekStreamToStart()
	{
		m_fileStream.seekp(0, std::ios::beg);
	}

	void FileOutputStream::SeekStreamToEnd()
	{
		m_fileStream.seekp(0, std::ios::end);
	}

	void FileOutputStream::SeekPast(int offset)
	{
		m_fileStream.seekp(offset, std::ios::cur);
	}

	int FileOutputStream::GetSeekPosition()
	{
		return m_fileStream.tellp();
	}

	bool FileOutputStream::Read(char* buffer, int bytesToRead)
	{
		return false;
	}

	bool FileOutputStream::Write(char* buffer, int bytesToWrite)
	{
		if (!IsOpen() || buffer == nullptr || bytesToWrite <= 0)
		{
			return false;
		}

		m_fileStream.write(buffer, bytesToWrite);
		m_fileSize += bytesToWrite;

		return true;
	}

	bool FileOutputStream::IsOpen()
	{
		if (!m_fileStream.is_open())
		{
			return false;
		}

		return true;
	}
}