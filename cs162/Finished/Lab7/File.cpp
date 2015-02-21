#include <string>
#include "File.h"

DataFile::DataFile(std::string FilNam, std::string ProStr, int TarPos)
{
	FilenameExtension = FilNam;
	PromptString = ProStr;
	TargetPositionInFile = TarPos;
	Sorted = false;
}

std::string DataFile::Prompt()
{
	return(PromptString);
}
std::string DataFile::Name()
{
	return(FilenameExtension);
}
int DataFile::TargetPosition()
{
	return(TargetPositionInFile);
}

