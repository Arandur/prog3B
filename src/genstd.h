#pragma once

#include "Generator.h"

#include <cstdint>
#include <list>
#include <vector>

class Range :
	public Generator< intmax_t >
{
public:
	using Generator< intmax_t >::_done;
	
	constexpr Range( intmax_t endVal ) :
		Generator< intmax_t >(),
		_endVal( endVal ),
		_step( 1 - 2 * ( endVal < 0 ) )
		{};
	
	constexpr Range( intmax_t startVal, intmax_t endVal ) :
		Generator< intmax_t >(),
		_startVal( startVal ),
		_endVal( endVal ),
		_step( 1 - 2 * ( endVal < startVal ) ),
		_currVal( startVal )
		{};
	
	constexpr Range( intmax_t startVal, intmax_t endVal, intmax_t step ) :
		Generator< intmax_t >(),
		_startVal( ( ( startVal < endVal ) == ( 0 < step ) )
			? startVal : endVal + step * ( 0 > step ) ),
		_endVal( ( ( startVal < endVal ) == ( 0 < step ) )
			? endVal : startVal + step * ( 0 > step ) ),
		_step( step ),
		_currVal( ( ( startVal < endVal ) == ( 0 < step ) )
			? startVal : endVal + step * ( 0 > step ) )
		{};
	
	intmax_t currVal() const
	{
		return _currVal;
	}
	
	void next()
	{
		_currVal += _step;
		
		if( 0 < _step )
			_done = ( _currVal >= _endVal );
		else
			_done = ( _currVal <= _endVal );
	}
	
	void reset()
	{
		_currVal = _startVal;
	}
	
private:
	const intmax_t _startVal = 0, _endVal, _step = 1;
	intmax_t _currVal = 0;
};

class Primes
	: public Generator< uintmax_t >
{
public:
	Primes() :
		Generator< uintmax_t >()
		{};
	
	uintmax_t currVal() const
	{
		return *_a;
	}
	
	void next()
	{
		if( *_a < 5 )
		{
			*_a += *_a - 1;
			return;
		}
	
		do
		{
			*_a += 2 + 2 * oneModSix;
			oneModSix = !oneModSix;
		} while( !isPrime( *_a ) );
	
		_primes.push_back( *_a );
	}
	
	void reset()
	{
		*_a = 2;
	}
	
	constexpr static uintmax_t intsqrt( uintmax_t n, uintmax_t i = 1 )
	{
		return ( i*i > n ) ? i - 1 : intsqrt( n, i + 1 );
	}

private:
	std::list< uintmax_t > _primes = { 2, 3, 5 };
	uintmax_t* _a = new uintmax_t( 2 );
	bool oneModSix = false;
	
	bool isPrime( uintmax_t n )
	{
		uintmax_t max = intsqrt( n );
	
		for( uintmax_t i : _primes )
		{
			if( i <= max )
			{
				if( !( n % i ) )
					return false;
			}
			else
				break;
		}
		
		return true;
	}
};

class Fibs
	: public Generator< uintmax_t >
{
public:
	constexpr Fibs() :
		Generator< uintmax_t >()
		{};
	
	uintmax_t currVal() const
	{
		return _a;
	}
	
	void next()
	{
		_b += _a;
		_a = _b - _a;
	}
	
	void reset()
	{
		_a = 1, _b = 1;
		_done = false;
	}

private:
	uintmax_t _a = 1, _b = 1;
};
