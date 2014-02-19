#ifndef __INCL_GENERATOR_H__
#define __INCL_GENERATOR_H__

#include <utility>

template < class T >
class Generator;

template < class T >
class GenIter
{
public:
	constexpr GenIter( Generator< T >* const owner ) :
		_owner( owner )
		{};
	
	constexpr bool operator != ( const GenIter& ) const;
	
	T operator* () const;
	
	const GenIter& operator++ () const;

private:
	Generator< T >* const _owner;
};

template < class T >
class Generator
{
public:
	constexpr Generator() :
		_done( false )
		{};
	
	Generator( const Generator< T >& cGenerator ) :
		_done( cGenerator._done )
		{};
	
	virtual ~Generator() {};
	
	GenIter< T > begin();
	GenIter< T > end();
	virtual T currVal() const;
	bool isDone() const;
	virtual void next();
	
	virtual void reset();
	
	typedef T type;

protected:
	bool _done;
};

template < class T >
constexpr bool GenIter< T >::operator != ( const GenIter< T >& ) const
{
	return !_owner->isDone();
}

template < class T >
T GenIter< T >::operator* () const
{
	return _owner->currVal();
}

template < class T >
const GenIter< T >& GenIter< T >::operator++ () const
{
	_owner->next();
	
	return *this;
}

template < class T >
GenIter< T > Generator< T >::begin()
{
	return GenIter< T >( this );
}

template < class T >
GenIter< T > Generator< T >::end()
{
	return GenIter< T >( this );
}

template < class T >
T Generator< T >::currVal() const
{
	return T( 0 );
}

template < class T >
bool Generator< T >::isDone() const
{
	return _done;
}

template < class T >
void Generator< T >::next()
{
}

template < class T >
void Generator< T >::reset()
{
}

#endif
