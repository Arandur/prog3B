#include "FiniteAutomaton.h"

void FiniteAutomaton::addState( const state_type& q )
{
	Q.insert( q );
}

void FiniteAutomaton::delState( const state_type& q )
{
	if( ! isState( q ) )
		throw StateNotInQ( q );
		
	Q.erase( q );
	
	for( Delta_type::value_type transition : Delta )
		if( transition.first == q )
			Delta.erase( q );
		else for( Delta_type::mapped_type::value_type adj : transition.second )
			if( adj.second == q )
				transition.second.erase( adj.first );
}

bool FiniteAutomaton::isState( const state_type& q ) const
{
	return ( Q.find( q ) != Q.end() );
}

void FiniteAutomaton::addSymbol( const symbol_type& a )
{
	Sigma.insert( a );
}

void FiniteAutomaton::delSymbol( const symbol_type& a )
{
	if( ! isSymbol( a ) )
		throw SymbolNotInSigma( a );	
	
	Sigma.erase( a );
	
	for( Delta_type::value_type transition : Delta )
		for( Delta_type::mapped_type::value_type adj : transition.second )
			if( adj.first == a )
				transition.second.erase( adj.first );
}

bool FiniteAutomaton::isSymbol( const symbol_type& a ) const
{
	return ( Sigma.find( a ) != Sigma.end() ); 
}

void FiniteAutomaton::addTransition( const state_type& q, const symbol_type& a, const state_type& r )
{
	if( ! isState( q ) or ! isState( r ) )
		return;
	if( ! isSymbol( a ) )
		return;
	
	Delta.insert( { q, { { a, r } } } );
}

void FiniteAutomaton::delTransition( const state_type& q, const symbol_type& a, const state_type& r )
{
	typename Delta_type::iterator elem = Delta.find( q );
	if( elem == Delta.end() )
		return;
	
	typename Delta_type::mapped_type::iterator elem2 = elem->second.find( a );
	if( elem2 == elem->second.end() )
		return;
	if( elem2->second != r )
		return;
	
	elem->second.erase( elem2 );
}

void FiniteAutomaton::makeFinal( const state_type& q )
{
	if( ! isState( q ) )
		return;
	
	F.insert( q );
}

void FiniteAutomaton::makeNotFinal( const state_type& q )
{
	if( ! isState( q ) )
		return;
	
	if( isFinal( q ) )
		F.erase( q );
}

bool FiniteAutomaton::isFinal( const state_type& q ) const
{
	return ( F.find( q ) != F.end() );
}

void FiniteAutomaton::makeInitial( const state_type& q )
{
	if( ! isState( q ) )
		return;
		
	q_0 = q;
}

bool FiniteAutomaton::accepts( const std::string& str ) const
{
	return ( isFinal( delta( q_0, str ) ) );
}

FiniteAutomaton::state_type FiniteAutomaton::delta( const state_type& q_, const symbol_type& a ) const
{
	state_type q = q_;
	
	try
	{
		q = Delta.at( q ).at( a );
	}
	catch( std::out_of_range& e )
	{
		return "";
	}
	
	return q;
}

FiniteAutomaton::state_type FiniteAutomaton::delta( const state_type& q_, const std::string& str ) const
{
	state_type q = q_;
	
	for( symbol_type a : str )
	{
		try
		{
			q = Delta.at( q ).at( a );
		}
		catch( std::out_of_range& e )
		{
			return "";
		}
	}
	
	return q;
}
