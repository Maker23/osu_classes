#ifndef FILE_H
#define FILE_H

#define DEBUG false
#define SEARCH_TARGET 0

#define DATA_DIRECORY "DataFiles/"  // End with a slash please

#include <string>
#include <vector>

class DataFile {
private:
	std::string FilenameExtension;
	std::string PromptString;
	int TargetPositionInFile;
public:
	DataFile() {};
	DataFile(std::string FilNam, std::string ProStr, int TarPos);
	bool Sorted;
	std::string Name();
	std::string Prompt();
	int TargetPosition();
};

class FileList {
public:
	std::string Directory;
	std::string FilenameHeader;
	std::vector <DataFile> List;
};

#endif // FILE_H
