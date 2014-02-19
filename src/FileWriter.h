#pragma once

#include "List.h"

#include <fstream>
#include <string>

class FileWriter
{
public:
	FileWriter() = default;
	FileWriter( const std::string& );
	
	void open( const std::string& );
	void close();
	
	void write( const std::string& );
	void writelines( const List< std::string >& );

private:
	std::string _filename;
	std::ofstream outFile;
};
