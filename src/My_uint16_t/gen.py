#!/usr/bin/python

header="""#pragma once

#include "My_uint16_tInterface.h"

class My_uint16_t_{0} :
	public My_uint16_tInterface
{{
public:
	My_uint16_tInterface* next() const;
	void* stuff( God* = 0 ) const;
}};"""

source="""#include "My_uint16_t_{0}.h"
#include "My_uint16_t_{1}.h"

My_uint16_tInterface* My_uint16_t_{0}::next() const
{{
	return new My_uint16_t_{1};
}}

void* My_uint16_t_{0}::stuff( God* ) const
{{
	return new int({0});
}}"""

for i in range( 2, 65536 ):
	with open( "My_uint16_t_{}.h".format( i ), "w" ) as f:
		f.write( header.format( i ) )
	with open( "My_uint16_t_{}.cpp".format( i ), "w" ) as f:
		f.write( source.format( i, i + 1 if i < 65535 else 0 ) )

