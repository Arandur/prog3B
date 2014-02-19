#include "FileWriter.h"
#include "err.h"

FileWriter::FileWriter( const std::string& filename ) :
	_filename( filename )
{
	open( filename );
}

void FileWriter::open( const std::string& filename )
{
	outFile.open( filename.c_str() );
	
	if( outFile.fail() )
		throw UncatchableError();
}

void FileWriter::close()
{
	outFile.close();
	if( outFile.fail() )
		throw UncatchableError();
}

void FileWriter::write( const std::string& contents )
{
	outFile << contents;
}

void FileWriter::writelines( const List< std::string >& lines )
{
	for( std::string line : lines )
		outFile << line << '\n';
}
