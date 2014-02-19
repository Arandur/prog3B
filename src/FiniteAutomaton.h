#pragma once

#include <set>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <iostream>
using std::cout;
using std::endl;

#include "FAExcept.h"
using namespace FAExcept;

class FiniteAutomaton
{
public:
	typedef std::string state_type;
	typedef char symbol_type;
	typedef std::set< state_type > Q_type;
	typedef std::set< symbol_type > Sigma_type;
	typedef std::map< state_type, std::map< symbol_type, state_type > > Delta_type;
	
	FiniteAutomaton();
	
	FiniteAutomaton( const Q_type& Q_,
					 const Sigma_type& Sigma_,
					 const state_type& q_0_,
					 const Delta_type& Delta_,
					 const Q_type& F_ )
	{
		if( Q_.find( q_0_ ) == Q_.end() )
			throw StateNotInQ( q_0_ );
		
		for( typename Delta_type::value_type p : Delta_ )
			if( Q_.find( p.first ) == Q_.end() )
				throw StateNotInQ( p.first );
			else for( typename Delta_type::mapped_type::value_type pp : p.second )
				if( Q_.find( pp.second ) == Q_.end() )
					throw StateNotInQ( pp.second );
				else if( Sigma_.find( pp.first ) == Sigma_.end() )
					throw SymbolNotInSigma( pp.first );
		
		for( state_type f : F_ )
			if( Q_.find( f ) == Q_.end() )
				throw StateNotInQ( f );
		
		Q = Q_;
		Sigma = Sigma_;
		q_0 = q_0_;
		Delta = Delta_;
		F = F_;
	}
	
	Q_type get_Q() const { return Q; }
	Sigma_type get_Sigma() const { return Sigma; }
	state_type get_q_0() const { return q_0; }
	Delta_type get_Delta() const { return Delta; }
	Q_type get_F() const { return F; }
	
	void addState( const state_type& );
	void delState( const state_type& );
	
	bool isState( const state_type& ) const;
	
	void addSymbol( const symbol_type& );
	void delSymbol( const symbol_type& );
	
	bool isSymbol( const symbol_type& ) const;
	
	void addTransition( const state_type&, const symbol_type&, const state_type& );
	void delTransition( const state_type&, const symbol_type&, const state_type& );
	
	void makeFinal( const state_type& );
	void makeNotFinal( const state_type& );
	
	bool isFinal( const state_type& ) const;
	
	void makeInitial( const state_type& );
	
	bool accepts( const std::string& ) const;
	state_type delta( const state_type&, const symbol_type& ) const;
	state_type delta( const state_type&, const std::string& ) const;

private:
	Q_type Q = {};
	Sigma_type Sigma = {};
	state_type q_0 = "";
	Delta_type Delta = {};
	Q_type F = {};
};
