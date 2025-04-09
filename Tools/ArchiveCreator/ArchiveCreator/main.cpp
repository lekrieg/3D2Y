#include <iostream>
#include <vector>

#include "FileArchiverHelper.h"

int main(int args, char** arg)
{
	if (args < 3)
	{
		std::cout << "Not enough arguments defined." << std::endl;
		return 0;
	}
	
	// Arg 1 is total files, 2 is archive file,
	// 3+ are all file names to go into archive.
	if (arg[1] == nullptr)
	{
		std::cout << "No total files defined." << std::endl;
		return 0;
	}

	int totalFiles = atoi(arg[1]);

	for (int i = 2; i < totalFiles; i++)
	{
		if (arg[i] == nullptr)
		{
			std::cout << "Argument " << i << " is NULL!" << std::endl;
			return 0;
		}
	}

	utils::ArchiveFileHeader* headers = new utils::ArchiveFileHeader[totalFiles];
	utils::Archive archiveFile;

	for (int i = 0; i < totalFiles; i++)
	{
		headers[i].SetFileName(arg[i + 3]);
	}


	if (archiveFile.WriteArchiveFile(arg[2], headers, totalFiles))
	{
		std::cout << "Archive " << "NAME" << " created!\n";
	}
	else
	{
		std::cout << "Archive " << "NAME" << " NOT created!\n";
	}

	archiveFile.CloseArchive();

	delete[] headers;

	return 1;
}