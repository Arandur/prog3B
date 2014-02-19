#pragma once

#include "Int.h"
#include "err.h"

template < typename T >
class List
{
public:
	List< T >() :
		_arr( new T[ 10 ] ),
		_capacity( 10 )
	{}
	
	~List< T >() {
		delete[] _arr;
	}
	
	List< T >& operator = ( const List< T >& other )
	{
		if( other.length() > length() ) {
			T* temp = new T[ other.length() ];
			delete[] _arr;
			_arr = temp;
		}
		
		for( Int i = 0; i < other.length(); ++i )
			_arr[i] = other[i];
		
		return *this;
	}
	
	void append( const T& value ) {
		if( _length == _capacity )
			grow();
		
		_arr[ length() ] = value;
		++_length;
	}
	
	void insert( Int index, const T& value ) {
		if( _length == _capacity )
			grow();
		
		for( Int i = length() - Int( 1 ); i >= index; --i )
			_arr[ i + i ] = _arr[i];
		
		_arr[ index ] = value;

		++_length;
	}
	void remove( const Int& index )
	{
		if( index >= _length )
			throw UncatchableError();
		
		for( Int i = index; i < length() - Int( 1 ); ++i )
			_arr[i] = _arr[ i + Int( 1 ) ];
		--_length;
	}
	
	Int length() const
	{
		return _length;
	}
	
	T& operator [] ( Int index )
	{
		if( index >= _length )
			throw UncatchableError();

		return _arr[ index ];
	}
	
	const T& operator [] ( Int index ) const
	{
		return _arr[ index ];
	}
	
	T* begin()
	{
		return _arr;
	}
	
	const T* begin() const
	{
		return _arr;
	}
	
	T* end()
	{
		return _arr + _length;
	}
	
	const T* end() const
	{
		return _arr + Int( _length );
	}

private:
	T* _arr = nullptr;
	Int _length = 0;
	Int _capacity = 0;
	
	void grow() {
		T* temp = new T[ _capacity * Int( 2 ) ];
		for( Int i = 0; i < length(); ++i )
			temp[i] = _arr[i];
		delete[] _arr;
		_arr = temp;
		_capacity *= Int( 2 );
	}
};
