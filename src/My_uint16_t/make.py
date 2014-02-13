#!/usr/bin/python

import os.path

header="""#pragma once

#include "My_uint16_tInterface.h"

class My_uint16_t_{0} :
	public My_uint16_tInterface
{{
public:
	My_uint16_tInterface* next() const;
	void* stuff( God* = 0 );
}};"""

source="""#include "My_uint16_t_{0}.h"
#include "My_uint16_t_{1}.h"

My_uint16_tInterface* My_uint16_t_{0}::next() const
{{
	return new My_uint16_t_{1};
}}

void* My_uint16_t_{0}::stuff( God* )
{{
	return new int({0});
}}"""

interface="""#pragma once

#include "../Object/ObjectInterface.h"

class My_uint16_tInterface :
	public ObjectInterface
{
public:
	~My_uint16_tInterface() = default;
	virtual My_uint16_tInterface* next() const = 0;
	virtual void* stuff( God* = 0 ) = 0;
};"""

PATH = os.path.dirname( os.path.realpath( __file__ ) )

with open( os.path.join( PATH, "My_uint16_tInterface.h" ), "w" ) as f:
	f.write( interface )

for i in range( 65536 ):
	with open( os.path.join( PATH, "My_uint16_t_{}.h".format( i ) ), "w" ) as f:
		f.write( header.format( i ) )
	with open( os.path.join( PATH, "My_uint16_t_{}.cpp".format( i ) ), "w" ) as f:
		f.write( source.format( i, i + 1 if i < 65535 else 0 ) )

