#pragma once

#include "FiniteAutomaton.h"

#include <string>

class FloatChecker
{
public:
	static bool isFloat( const std::string& );
	
private:
	FloatChecker() = delete;
	FloatChecker( FloatChecker& ) = delete;
};
