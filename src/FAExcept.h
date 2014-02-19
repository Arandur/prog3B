#pragma once

#include <exception>
#include <sstream>
#include <string>

namespace FAExcept
{

struct FAException {};

class StateNotInQ :
	public std::exception, public FAException
{
public:
	StateNotInQ( std::string state ) :
		state( state )
	{}
	virtual const char* what() const noexcept( true )
	{
		std::stringstream ss;
		ss << "State " << state << " is not in Q." << std::endl;
		return ss.str().c_str();
	}

private:
	std::string state = "";
};

class SymbolNotInSigma :
	public std::exception, public FAException
{
public:
	SymbolNotInSigma( char symbol ) :
		symbol( symbol )
	{}
	virtual const char* what() const noexcept( true )
	{
		std::stringstream ss;
		ss << "Symbol " << symbol << " is not in Q." << std::endl;
		return ss.str().c_str();
	}
	
private:
	char symbol = 0;
};

}
