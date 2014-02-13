#pragma once

#include "GodGetter_charInterface.h"

class GodGetter_char_0 :
	public GodGetter_charInterface
{
public:
	GodGetter_charInterface* next() const;
	void* stuff( God* = 0 );
};
