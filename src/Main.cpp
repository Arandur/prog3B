#include "Main.h"
#include "Int.h"
#include "List.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "FloatChecker.h"
#include "genutil.h"
#include "err.h"

#include <iostream>
using namespace std;

#include <string>

void ( *Main::action )( const std::string& ) = nullptr;

void Main::run()
{
	std::string filename, str;
	
	while( action == nullptr ) {
		cout << "Please enter filename.\n>> ";
		cin >> filename;
	
		cout << "[R]ead, [W]rite, or [M]odify?\n>> ";
		cin >> str;
	
		if( str[0] == 'r' or str[0] == 'R' )
			action = read;
		else if( str[0] == 'w' or str[0] == 'W' )
			action = write;
		else if( str[0] == 'm' or str[0] == 'M' )
			action = modify;
		else {
			cout << "Invalid entry.\n";
		}
	}
	
	action( filename );
}

void Main::read( const std::string& filename )
{
	FileReader reader( filename );
	
	for( std::string line : reader.readlines() )
		cout << line << endl;
}

void Main::write( const std::string& filename )
{
	FileWriter writer( filename );
	Int filesize;
	std::string number;
	List< std::string > numbers;
	
	cout << "How many entries?\n>> ";
	cin >> filesize;
	
	for( Int i : Range( filesize ) )
		while( true ) {
			cout << "Enter number\n>> ";
			cin >> number;
			i = i;
		
			if( FloatChecker::isFloat( number ) ) {
				numbers.append( number );
				break;
			}
			else
				cout << "Invalid entry.\n";
		}
	
	writer.writelines( numbers );
}

void Main::modify( const std::string& filename )
{
	FileReader reader( filename );
	FileWriter writer;
	List< std::string > numbers = reader.readlines();
	reader.close();
	Int pos = 0;
	std::string input, number, other_filename;
	other_filename = filename;
	
	while( true ) {
		if( pos == Int( -1 ) )
			cout << "\nBEGINNING OF LIST\n\n";
		else
			cout << endl << numbers[ pos ] << endl << endl;
		
		cout << "[P]revious  [N]ext   [I]nsert   [R]eplace\n"
				"[D]elete    [S]ave   Save [A]s  [C]ancel\n>> ";
		
		cin >> input;
		
		switch( input[0] ) {
		case 'P' :
		case 'p' :
			if( pos > Int( -1 ) )
				--pos;
			break;
			
		case 'N' :
		case 'n' :
			if( pos < numbers.length() - Int( 1 ) )
				++pos;
			break;
			
		case 'I' :
		case 'i' :
			cout << "Enter new number\n>> ";
			cin >> number;
		
			if( FloatChecker::isFloat( number ) )
				numbers.insert( pos + Int( 1 ), number );
			else
				cout << "Invalid entry.";
			break;
		
		case 'R' :
		case 'r' :
			if( pos == Int( -1 ) )
				throw UncatchableError();
			else {
				cout << "Enter new number\n>> ";
				cin >> number;
			
				if( FloatChecker::isFloat( number ) )
					numbers[ pos ] = number;
			}
			break;
			
		case 'D' :
		case 'd' :
			if( pos == Int( -1 ) )
				throw UncatchableError();
			else {
				numbers.remove( pos );
				--pos;
			}
			
			break;
		
		case 'A' :
		case 'a' :
			cout << "Enter filename\n>> ";
			cin >> other_filename;
			// Fallthrough!
			
		case 'S' :
		case 's' :
			writer.open( other_filename );
			writer.writelines( numbers );
			writer.close();
			return;
			break;
			
		case 'C' :
		case 'c' :
			return;
			break;
		}
	}
}
