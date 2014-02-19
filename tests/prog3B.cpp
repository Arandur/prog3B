#include <Main.h>
#include <err.h>

#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main()
{
	std::string s;
	try {
		Main::run();
	} catch( UncatchableError& e ) {
		std::cout << 
			"According to Dr. C, the only errors we may check for are "
			"those which he specifically noted. Therefore, I have not "
			"implemented error checking for this specific scenario. "
			"Anything could happen. I wonder what will?"
			"\nPress ENTER to continue.\n";
		cin.ignore( std::numeric_limits< streamsize >::max(), '\n' );
		getline( cin, s );
	}
	
	return 0;
}
