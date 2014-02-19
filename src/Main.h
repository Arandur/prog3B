#pragma once

#include <string>

class Main
{
public:
	static void run();

private:
	Main() = delete;
	Main( const Main& ) = delete;
	
	static void ( *action )( const std::string& );
	
	static void read( const std::string& );
	static void write( const std::string& );
	static void modify( const std::string& );
};
