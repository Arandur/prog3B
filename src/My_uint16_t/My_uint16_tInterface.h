#pragma once

#include "../Object/ObjectInterface.h"

class My_uint16_tInterface :
	public ObjectInterface
{
public:
	~My_uint16_tInterface() = default;
	virtual My_uint16_tInterface* next() const = 0;
	virtual void* stuff( God* = 0 ) = 0;
};