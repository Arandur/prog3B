#pragma once

#include "List.h"

#include <fstream>
#include <string>

class FileReader
{
public:
	FileReader() = default;
	FileReader( const std::string& );
	
	void open( const std::string& );
	void close();
	
	std::string read();
	List< std::string > readlines();

private:
	const std::string& _filename;
	std::ifstream inFile;
};
