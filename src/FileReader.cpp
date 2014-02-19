#include "FileReader.h"
#include "err.h"

FileReader::FileReader( const std::string& filename ) :
	_filename( filename )
{
	open( filename );
}

void FileReader::open( const std::string& filename )
{
	inFile.open( filename.c_str() );
	
	if( inFile.fail() )
		throw UncatchableError();
}

void FileReader::close()
{
	inFile.close();
}

std::string FileReader::read()
{
	std::string contents;
	
	while( ! inFile.eof() )
		contents.push_back( inFile.get() );
	
	return contents;
}

List< std::string > FileReader::readlines()
{
	List< std::string > lines;
	std::string line;
	char c;
	
	while( ! inFile.eof() )
		if( ( c = inFile.get() ) != '\n' )
			line.push_back( c );
		else {
			lines.append( line );
			line.erase();
		}
	
	return lines;
}
