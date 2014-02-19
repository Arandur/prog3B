#pragma once

#include "Generator.h"
#include "genstd.h"

#include <cstdint>
#include <vector>

std::vector< uintmax_t > factors( uintmax_t num )
{
	std::vector< uintmax_t > factVec, remaining_factors;
	uintmax_t sqrt = Primes::intsqrt( num );
	
	for( auto p : Primes() )
	{
		if( num % p == 0 )
		{
			factVec.push_back( p );
			remaining_factors = factors( num / p );
			factVec.insert( factVec.end(), remaining_factors.begin(), remaining_factors.end() );
			return factVec;
		}
		if( p > sqrt )
			break;
	}
	
	remaining_factors.push_back( num );
	
	return remaining_factors;
}
