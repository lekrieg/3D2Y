# Archive

The Archive is used to save the assets inside a compacted file to be used on the projects.

It uses headers container the file infos to lacate the date when needed and save the files.

You can:

<details>
<summary>Disponible methods</summary>
```C++
- bool ReadArchiveFile(char* fileName);
- bool WriteArchiveFile(char* fileName, ArchiveFileHeader* headers, std::vector<std::string>& paths, int totalHeaders);
- void CloseArchive();bool Extract(int index, char* location);
- bool Extract(char* fileName, char* location);
- int GetFileIndex(char* fileName);
- bool GetFileData(int index, char* buffer, int bytesToRead);
- bool GetFileData(char* fileName, char* buffer, int bytesToRead);
- bool GetFileHeaderInfoByIndex(int index, ArchiveFileHeader* fh);
- int GetTotalHeaders();
- bool IsArchiveOpen();
```
</details>

## Examples

<details>
<summary>Reading the data</summary>

```C++
char dataFileName[] = "data.abyss";
m_archiver.ReadArchiveFile(dataFileName);

char fileName[] = "";
int fileIndex = m_archiver.GetFileIndex(strcpy(fileName, path.c_str()));

archiver::ArchiveFileHeader* header = new archiver::ArchiveFileHeader;
m_archiver.GetFileHeaderInfoByIndex(fileIndex, header);
char* buffer = new char[header->GetSize()];
m_archiver.GetFileData(fileIndex, buffer, header->GetSize());
if (!m_texture.loadFromMemory(buffer, header->GetSize()))
{
     ABYSS_ERROR("Failed to load texture!")
}
m_archiver.CloseArchive();
```

</details>

<details>
<summary>Saving data</summary>

```C++
const auto& headers = new archiver::ArchiveFileHeader[totalFiles];
for (int i = 0; i < totalFiles; i++)
{
    char n[fileNames[i].size() + 1];
    strcpy(n, fileNames[i].c_str());
    headers[i].SetFileName(n);
 }

char dataFileName[] = "data.abyss";
if (m_app->GetArchiver().WriteArchiveFile(dataFileName, headers, filePaths, totalFiles))
{
    ABYSS_INFO("Archive %s created!", dataFileName)
}
else
{
    ABYSS_ERROR("Error creating archive %s!", dataFileName)
    return false;
 }

m_app->GetArchiver().CloseArchive();

delete[] headers;
```

</details>


### Reference for implementation

- Ultimate 3D Game Engine - Design and architecture ~ Allen Sherrod
