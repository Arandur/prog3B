#pragma once

#include "My_uint16_tInterface.h"

class My_uint16_t_0 :
	public My_uint16_tInterface
{
public:
	virtual My_uint16_tInterface* next() const;
	virtual void* stuff( God* = 0 ) const;
};